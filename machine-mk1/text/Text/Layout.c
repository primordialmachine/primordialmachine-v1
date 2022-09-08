#define MACHINE_TEXT_PRIVATE (1)
#include "Text/Layout.h"



#include "_Graphics2.h"
#include "_Fonts.h"
#include "Text/LayoutLine.h"
#include <string.h>
#include <math.h>



static const float OFFSET_X = 0.f;

static const float OFFSET_Y = 0.f;

#define WITH_SNAPTOGRID (1)

#define Y_UP (1)

static void Machine_Text_Layout_visit(Machine_Text_Layout* self) {
  if (self->color) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->color);
  }
  if (self->position) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->position);
  }
  if (self->font) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->font);
  }
  if (self->text) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->text);
  }
  if (self->lines) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->lines);
  }
  if (self->visualBounds) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->visualBounds);
  }
  if (self->clipRectangle) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->clipRectangle);
  }
}

static void parse(Ring2_String* text, Machine_PointerArray* lines) {
  const char* start = Ring2_String_getBytes(Ring2_Context_get(), text),
            * end = Ring2_String_getBytes(Ring2_Context_get(), text) + Ring2_String_getNumberOfBytes(Ring2_Context_get(), text);

  const char* lineStart = start,
    * lineEnd = start;

  while (lineEnd != end) {
    // terminates a line
    if (*lineEnd == '\n' || *lineEnd == '\r') {
      int old = *lineEnd;
      lineEnd++;
      if (old != *lineEnd && (*lineEnd == '\n' || *lineEnd == '\r')) {
        lineEnd++;
      }
      Machine_Text_LayoutLine* line = Machine_Text_LayoutLine_create(lineStart - start, lineEnd - lineStart);
      Machine_PointerArray_append(lines, line);
      lineStart = lineEnd;
    }
    lineEnd++;
  }
  if (lineEnd != lineStart) {
    Machine_Text_LayoutLine* line = Machine_Text_LayoutLine_create(lineStart - start, lineEnd - lineStart);
    Machine_PointerArray_append(lines, line);
  }
}

static void updateLinesBounds(Machine_Math_Vector2* position, Machine_Font* font, Ring2_String* text, Machine_PointerArray* lines, bool yup) {
  Machine_Math_Vector2* position0 = Machine_Math_Vector2_create();
#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  Machine_Math_Vector2_set(position0, floorf(Machine_Math_Vector2_getX(position)),
                                      floorf(Machine_Math_Vector2_getY(position)));
#else
  Machine_Math_Vector2_set(position0, (Machine_Math_Vector2_getX(position)),
                                      (Machine_Math_Vector2_getY(position)));
#endif

  Machine_Math_Vector2* cursorPosition = Machine_Math_Vector2_create();
  Machine_Math_Rectangle2* lineBounds = Machine_Math_Rectangle2_create();

  for (size_t i = 0, n = Machine_PointerArray_getSize(lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(lines, i);
    const char* bytes = Ring2_String_getBytes(Ring2_Context_get(), text);

    Machine_Math_Vector2* position = Machine_Math_Vector2_create();
    Machine_Math_Vector2_copy(position, cursorPosition);
    Machine_Math_Vector2* size = Machine_Math_Vector2_create();
    Machine_Math_Vector2_set(size, 0.f, 0.f);

    Machine_Math_Rectangle2_setPosition(lineBounds, position);
    Machine_Math_Rectangle2_setSize(lineBounds, size);

    Machine_Math_Vector2* symbolAdvance = Machine_Math_Vector2_create();
    Machine_Math_Rectangle2* symbolBounds = Machine_Math_Rectangle2_create();
    for (size_t j = layoutLine->start, m = layoutLine->start + layoutLine->length; j < m; ++j) {
      uint32_t codepoint = bytes[j];
      Machine_Texture* symbolTexture;
      bool skip = !Machine_Font_getCodePointInfo(font, codepoint, symbolBounds, symbolAdvance, &symbolTexture);
      if (skip) {
        continue;
      }

      float l = Machine_Math_Vector2_getX(cursorPosition) + Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getPosition(symbolBounds));
      float r = l + Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(symbolBounds));
      float t, b;
      if (yup) {
        t = Machine_Math_Vector2_getY(cursorPosition) + (Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds)) - Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getPosition(symbolBounds)));
        b = t - Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds));
      } else {
        t = Machine_Math_Vector2_getY(cursorPosition) - (Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds)) - Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getPosition(symbolBounds)));
        b = t + Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds));
      }

      Machine_Math_Vector2* min = Machine_Math_Vector2_create();
      Machine_Math_Vector2_set(min, l, t);
      Machine_Math_Vector2* max = Machine_Math_Vector2_create();
      Machine_Math_Vector2_set(max, r, b);
      Machine_Math_Rectangle2_addPoint(lineBounds, min);
      Machine_Math_Rectangle2_addPoint(lineBounds, max);

      Machine_Math_Vector2_add(cursorPosition, cursorPosition, symbolAdvance);
    }
    layoutLine->left = Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getPosition(lineBounds));
    layoutLine->width = Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(lineBounds));
    layoutLine->top = Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getPosition(lineBounds));
    layoutLine->height = Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(lineBounds));

    Machine_Math_Vector2_set(cursorPosition, 0.f,  Machine_Math_Vector2_getY(cursorPosition) + Machine_Font_getBaselineDistance(font));
  }

  for (size_t i = 0, n = Machine_PointerArray_getSize(lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(lines, i);
    layoutLine->top += Machine_Math_Vector2_getY(position0);
    layoutLine->left += Machine_Math_Vector2_getX(position0);
  }
}

static void updateBounds(Machine_Text_Layout* self) {
  Machine_Math_Vector2* position0 = Machine_Math_Vector2_create();
#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  Machine_Math_Vector2_set(position0, floorf(Machine_Math_Vector2_getX(self->position)),
                                      floorf(Machine_Math_Vector2_getY(self->position)));
#else
  Machine_Math_Vector2_set(position0, (Machine_Math_Vector2_getX(self->position)),
                                      (Machine_Math_Vector2_getY(self->position)));
#endif

  Machine_Math_Vector2* cursorPosition = Machine_Math_Vector2_create();
  Machine_Math_Vector2_copy(cursorPosition, position0);

  Machine_Math_Rectangle2* bounds = Machine_Math_Rectangle2_create();
  Machine_Math_Vector2* p = Machine_Math_Vector2_create();
  Machine_Math_Vector2_copy(p, cursorPosition);
  Machine_Math_Rectangle2_setPosition(bounds, p);

  const char* bytes = Ring2_String_getBytes(Ring2_Context_get(), self->text);

  for (size_t i = 0, n = Machine_PointerArray_getSize(self->lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(self->lines, i);
    Machine_Math_Vector2_set(p, layoutLine->left, layoutLine->top);
    Machine_Math_Rectangle2_addPoint(bounds, p);
    Machine_Math_Vector2_set(p, layoutLine->left + layoutLine->width, layoutLine->top + layoutLine->height);
    Machine_Math_Rectangle2_addPoint(bounds, p);

    Machine_Math_Vector2_set(cursorPosition, Machine_Math_Vector2_getX(self->position),
                                             Machine_Math_Vector2_getY(cursorPosition) + Machine_Font_getBaselineDistance(self->font));
  }

  if (!self->visualBounds) {
    self->visualBounds = Machine_Rectangle2_create();
  }
  Machine_Rectangle2_setRectangle(self->visualBounds, bounds);
}

MACHINE_DEFINE_CLASSTYPE(Machine_Text_Layout, Machine_Object, &Machine_Text_Layout_visit,
                         &Machine_Text_Layout_construct, NULL, NULL, NULL)

void Machine_Text_Layout_construct(Machine_Text_Layout* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->color = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(self->color, 0.f, 0.f, 0.f);
  self->position = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(self->position, 0.f, 0.f);
  self->text = Ring2_Value_getString(arguments + 0);
  self->font = (Machine_Font *)Ring2_Value_getObject(arguments + 1);
  self->lines = Machine_PointerArray_create();
  self->yup = true;
  self->flags |= LINES_DIRTY;
  Machine_setClassType((Machine_Object*)self, Machine_Text_Layout_getType());
}

Machine_Text_Layout* Machine_Text_Layout_create(Ring2_String* text, Machine_Font* font) {
  Ring2_assertNotNull(text);
  Ring2_assertNotNull(font);

  Machine_ClassType* ty = Machine_Text_Layout_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2] = { Ring2_Value_StaticInitializerVoid(), Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&arguments[0], text);
  Ring2_Value_setObject(&arguments[1], (Machine_Object *)font);
  Machine_Text_Layout* self = (Machine_Text_Layout*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

const Machine_Math_Rectangle2* Machine_Text_Layout_getBounds(Machine_Text_Layout* self) {
  if ((self->flags & LINES_DIRTY) == LINES_DIRTY) {
    Machine_PointerArray_clear(self->lines);
    parse(self->text, self->lines);
    self->flags |= LINE_BOUNDS_DIRTY;
    self->flags &= ~LINES_DIRTY;
  }
  if ((self->flags & LINE_BOUNDS_DIRTY) == LINE_BOUNDS_DIRTY) {
    updateLinesBounds(self->position, self->font, self->text, self->lines, self->yup);
    self->flags |= BOUNDS_DIRTY;
    self->flags &= ~LINE_BOUNDS_DIRTY;
  }
  if ((self->flags & BOUNDS_DIRTY) == BOUNDS_DIRTY) {
    updateBounds(self);
    self->flags &= ~BOUNDS_DIRTY;
  }
  return Machine_Rectangle2_getRectangle(self->visualBounds);
}

void Machine_Text_Layout_render(Machine_Text_Layout* self, Machine_Context2* context2) {
  if ((self->flags & LINES_DIRTY) == LINES_DIRTY) {
    Machine_PointerArray_clear(self->lines);
    parse(self->text, self->lines);
    self->flags |= LINE_BOUNDS_DIRTY;
    self->flags &= ~LINES_DIRTY;
  }
  if ((self->flags & LINE_BOUNDS_DIRTY) == LINE_BOUNDS_DIRTY) {
    updateLinesBounds(self->position, self->font, self->text, self->lines, self->yup);
    self->flags |= BOUNDS_DIRTY;
    self->flags &= ~LINE_BOUNDS_DIRTY;
  }
  if ((self->flags & BOUNDS_DIRTY) == BOUNDS_DIRTY) {
    updateBounds(self);
    self->flags &= ~BOUNDS_DIRTY;
  }

  if (self->clipRectangle) {
    Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 0, true);
    Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 1, true);
    Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 2, true);
    Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 3, true);
  }
  if (self->renderVisualBounds) {
    if (!self->visualBounds) {
      updateBounds(self);
    }
    Machine_Math_Vector4* color = Machine_Math_Vector4_create();
    Machine_Math_Vector4_set(color, .3f, .6f, .3f, 1.f);
    Machine_Rectangle2_setColor(self->visualBounds, color);
    Machine_Context2* context = Machine_Context2_create(context2->videoContext);
    Machine_Context2_setTargetSize(context, Machine_Context2_getTargetWidth(context2), Machine_Context2_getTargetHeight(context2));
    Machine_Shape2_render((Machine_Shape2*)self->visualBounds, context);
  }

#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  float position0[] = { floorf(Machine_Math_Vector2_getX(self->position)),
                        floorf(Machine_Math_Vector2_getY(self->position)) };
#else
  float position0[] = { Machine_Math_Vector2_getX(self->position),
                        Machine_Math_Vector2_getY(self->position) };
#endif

  // Set the world matrix, view matrix, and projection matrix.
  Machine_Context2_setOriginBottomLeft(context2, Y_UP);
  Machine_Math_Matrix4 const* modelSpaceToProjectiveSpace = Machine_Context2_getModelSpaceToProjectiveSpaceMatrix(context2);
  Machine_Math_Matrix4 const* modelSpaceToWorldSpace = Machine_Context2_getModelSpaceToWorldSpaceMatrix(context2);

  Machine_ShaderProgram* shaderProgram = Machine_Font_getVideoShaderProgram(self->font);
  Machine_Binding* binding = Machine_Font_getVideoBinding(self->font);

  Machine_Binding_activate(binding);
  if (self->clipRectangle) {
    Machine_Math_Vector2* position = Machine_Math_Rectangle2_getPosition(self->clipRectangle);
    const Machine_Math_Vector2* size = Machine_Math_Rectangle2_getSize(self->clipRectangle);
    // left
    {
      float N[]= { 1.f, 0.f, 0.f };
      Machine_Math_Vector3* n2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(n2, N[0], N[1], N[2]);
      Machine_Math_Vector3* p2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(p2, Machine_Math_Vector2_getX(position), 0.0f, 0.0f);
      float d = -Machine_Math_Vector3_dot(n2, p2);
      Machine_Math_Vector4* x = Machine_Math_Vector4_create();
      Machine_Math_Vector4_set(x, N[0], N[1], N[2], d);
      Machine_Binding_bindVector4(binding, Ring2_String_create(Ring2_Context_get(), "clipPlane0", strlen("clipPlane0") + 1), x);
    }
    // right
    {
      float N[] = { -1.f, 0.f, 0.f };
      Machine_Math_Vector3* n2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(n2, N[0], N[1], N[2]);
      Machine_Math_Vector3* p2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(p2, Machine_Math_Vector2_getX(position) + Machine_Math_Vector2_getX(size), 0.0f, 0.0f);
      Ring2_assert(Machine_Math_Vector2_getX(size) >= 0.f, Ring1_Status_InvalidArgument);
      float d = -Machine_Math_Vector3_dot(n2, p2);
      Machine_Math_Vector4* x = Machine_Math_Vector4_create();
      Machine_Math_Vector4_set(x, N[0], N[1], N[2], d);
      Machine_Binding_bindVector4(binding, Ring2_String_create(Ring2_Context_get(), "clipPlane1", strlen("clipPlane1") + 1), x);
    }
    // bottom
    {
      float N[] = { 0.f, +1.f, 0.f };
      Machine_Math_Vector3* n2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(n2, N[0], N[1], N[2]);
      Machine_Math_Vector3* p2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(p2, 0.f, Machine_Math_Vector2_getY(position), 0.0f);
      float d = -Machine_Math_Vector3_dot(n2, p2);
      Machine_Math_Vector4* x = Machine_Math_Vector4_create();
      Machine_Math_Vector4_set(x, N[0], N[1], N[2], d);
      Machine_Binding_bindVector4(binding, Ring2_String_create(Ring2_Context_get(), "clipPlane2", strlen("clipPlane2") + 1), x);
    }
    // top
    {
      float N[] = { 0.f, -1.f, 0.f };
      Machine_Math_Vector3* n2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(n2, N[0], N[1], N[2]);
      Machine_Math_Vector3* p2 = Machine_Math_Vector3_create(); Machine_Math_Vector3_set(p2, 0.f, Machine_Math_Vector2_getY(position) + Machine_Math_Vector2_getY(size), 0.0f);
      Ring2_assert(Machine_Math_Vector2_getY(size) >= 0.f, Ring1_Status_InvalidArgument);
      float d = -Machine_Math_Vector3_dot(n2, p2);
      Machine_Math_Vector4* x = Machine_Math_Vector4_create();
      Machine_Math_Vector4_set(x, N[0], N[1], N[2], d);
      Machine_Binding_bindVector4(binding, Ring2_String_create(Ring2_Context_get(), "clipPlane3", strlen("clipPlane3") + 1), x);
    }
  }
  Machine_Binding_bindVector3(binding, Ring2_String_create(Ring2_Context_get(), "mesh_color", strlen("mesh_color") + 1), self->color);
  Machine_Binding_bindMatrix4(binding, Ring2_String_create(Ring2_Context_get(), "modelToWorldMatrix", strlen("modelToWorldMatrix") + 1), modelSpaceToWorldSpace);
  Machine_Binding_bindMatrix4(binding, Ring2_String_create(Ring2_Context_get(), "modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), modelSpaceToProjectiveSpace);

  Machine_VideoContext_setDepthTestFunction(context2->videoContext, Machine_DepthTestFunction_Always);
  Machine_VideoContext_setDepthWriteEnabled(context2->videoContext, false);
  Machine_VideoContext_setIncomingBlendFunction(context2->videoContext, Machine_BlendFunction_IncomingAlpha);
  Machine_VideoContext_setExistingBlendFunction(context2->videoContext, Machine_BlendFunction_OneMinusIncomingAlpha);

  float cursorPosition[] = { position0[0], position0[1] };

  const char* bytes = Ring2_String_getBytes(Ring2_Context_get(), self->text);

  Machine_Math_Vector2* symbolAdvance = Machine_Math_Vector2_create();
  Machine_Math_Rectangle2* symbolBounds = Machine_Math_Rectangle2_create();
  for (size_t i = 0, n = Machine_PointerArray_getSize(self->lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(self->lines, i);
    for (size_t j = layoutLine->start, m = layoutLine->start + layoutLine->length; j < m; ++j) {
      uint32_t codepoint = bytes[j];
      Machine_Texture* symbolTexture;
      bool skip = !Machine_Font_getCodePointInfo(self->font, codepoint, symbolBounds, symbolAdvance, &symbolTexture);
      if (skip) continue;

      float l = OFFSET_X + cursorPosition[0] + Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getPosition(symbolBounds));
      float r = l + Machine_Math_Vector2_getX(Machine_Math_Rectangle2_getSize(symbolBounds));
      float t, b;
    #if defined(Y_UP)
      t = OFFSET_Y + cursorPosition[1] + (Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds)) - Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getPosition(symbolBounds)));
      b = t - Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds));
    #else
      t = OFFSET_Y + cursorPosition[1] - (Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds)) - symbolBounds.b);
      b = t + Machine_Math_Vector2_getY(Machine_Math_Rectangle2_getSize(symbolBounds));
    #endif

      const struct {
        float x, y;
        float u, v;
      } vertices[] = {
        { l,  t,  0.f, 1.f }, // left/bottom
        { r,  t,  1.f, 1.f }, // right/bottom
        { l,  b,  0.f, 0.f }, // left/top
        { r,  b,  1.f, 0.f }, // right/top
      };

      Machine_VideoBuffer_setData(Machine_Font_getVideoBuffer(self->font), sizeof(vertices), (void const *)vertices);

      static const uint8_t indices[] = {
        0, 1, 2,
        2, 1, 3,
      };
      static const size_t UNIT = 0;
      Machine_VideoContext_bindTexture(context2->videoContext, 0, symbolTexture);
      Machine_Binding_bindSampler(binding, Ring2_String_create(Ring2_Context_get(), "texture_1", strlen("texture_1")), UNIT);
      Machine_VideoContext_drawIndirect(context2->videoContext, 0, 6, indices);

      cursorPosition[0] += Machine_Math_Vector2_getX(symbolAdvance);
      cursorPosition[1] += Machine_Math_Vector2_getY(symbolAdvance);
    }
    cursorPosition[0] = position0[0];
    cursorPosition[1] += Machine_Font_getBaselineDistance(self->font);
  }
  Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 3, false);
  Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 2, false);
  Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 1, false);
  Machine_VideoContext_setClipDistanceEnabled(context2->videoContext, 0, false);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setText(Machine_Text_Layout* self, Ring2_String* text) {
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(text);

  if (!Ring2_String_isEqualTo(Ring2_Context_get(), self->text, text)) {
    self->text = text;
    self->flags |= LINES_DIRTY | LINE_BOUNDS_DIRTY | BOUNDS_DIRTY;
  }
}

Ring2_String* Machine_Text_Layout_getText(Machine_Text_Layout* self) {
  return self->text;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setPosition(Machine_Text_Layout* self, Machine_Math_Vector2* position) {
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(position);

  Machine_Math_Vector2_copy(self->position, position);
  self->flags |= LINE_BOUNDS_DIRTY | BOUNDS_DIRTY;
}

const Machine_Math_Vector2* Machine_Text_Layout_getPosition(Machine_Text_Layout* self) {
  return self->position;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setColor(Machine_Text_Layout* self, const Machine_Math_Vector3* color) {
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(color);
  Machine_Math_Vector3_copy(self->color, color);
}

const Machine_Math_Vector3* Machine_Text_Layout_getColor(Machine_Text_Layout* self) {
  return self->color;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setRenderVisualBoundsEnabled(Machine_Text_Layout* self, bool renderVisualBounds) {
  self->renderVisualBounds = renderVisualBounds;
}

bool Machine_Text_Layout_getRenderVisualBoundsEnabled(Machine_Text_Layout* self) {
  return self->renderVisualBounds;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setClipRectangle(Machine_Text_Layout* self, Machine_Math_Rectangle2* clipRectangle) {
  if (clipRectangle) {
    Ring2_assert(clipRectangle->w >= 0.f, Ring1_Status_InvalidArgument);
    Ring2_assert(clipRectangle->h >= 0.f, Ring1_Status_InvalidArgument);
    if (!self->clipRectangle) {
      Machine_Math_Rectangle2 * temporary = Machine_Math_Rectangle2_create();
      Machine_Math_Rectangle2_copy(temporary, clipRectangle);
      self->clipRectangle = temporary;
    } else {
      Machine_Math_Rectangle2_copy(self->clipRectangle, clipRectangle);
    }
  } else {
    self->clipRectangle = NULL;
  }
}

Machine_Math_Rectangle2* Machine_Text_Layout_getClipRectangle(Machine_Text_Layout* self) {
  return self->clipRectangle;
}
