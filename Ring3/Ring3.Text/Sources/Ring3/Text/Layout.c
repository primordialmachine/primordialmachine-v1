#define RING3_TEXT_PRIVATE (1)
#include "Ring3/Text/Layout.h"

#include "Ring3/Text/LayoutLine.h"
#undef RING3_TEXT_PRIVATE

#include "Ring1/All/_Include.h"
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

static void parse(Ring2_String* text, Ring2_Collections_List* lines) {
  const char* start = Ring2_String_getBytes(text),
            * end = Ring2_String_getBytes(text) + Ring2_String_getNumberOfBytes(text);

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
      Ring2_Value t;
      Ring2_Value_setObject(&t, (Machine_Object *)line);
      Ring2_Collections_List_append(lines, t);
      lineStart = lineEnd;
    }
    lineEnd++;
  }
  if (lineEnd != lineStart) {
    Machine_Text_LayoutLine* line = Machine_Text_LayoutLine_create(lineStart - start, lineEnd - lineStart);
    Ring2_Value t;
    Ring2_Value_setObject(&t, (Machine_Object *)line);
    Ring2_Collections_List_append(lines, t);
  }
}

static void updateLinesBounds(Ring3_Math_Vector2f32* position, Ring3_Font* font, Ring2_String* text, Ring2_Collections_List* lines, bool yup) {
  Ring3_Math_Vector2f32* position0 = Ring3_Math_Vector2f32_create();
#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  Ring3_Math_Vector2f32_set(position0, floorf(Ring3_Math_Vector2f32_getX(position)),
                                       floorf(Ring3_Math_Vector2f32_getY(position)));
#else
  Ring3_Math_Vector2f32_set(position0, Ring3_Math_Vector2f32_getX(position),
                                       Ring3_Math_Vector2f32_getY(position));
#endif

  Ring3_Math_Vector2f32* cursorPosition = Ring3_Math_Vector2f32_create();
  Ring3_Math_Rectangle2* lineBounds = Ring3_Math_Rectangle2_create();

  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, lines)); i < n; ++i) {
    Ring2_Value t = Ring2_Collections_List_getAt(lines, i);
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Ring2_Value_getObject(&t);
    const char* bytes = Ring2_String_getBytes(text);

    Ring3_Math_Vector2f32* position = Ring3_Math_Vector2f32_create();
    Ring3_Math_Vector2f32_copy(position, cursorPosition);
    Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
    Ring3_Math_Vector2f32_set(size, 0.f, 0.f);

    Ring3_Math_Rectangle2_setPosition(lineBounds, position);
    Ring3_Math_Rectangle2_setSize(lineBounds, size);

    Ring3_Math_Vector2f32* symbolAdvance = Ring3_Math_Vector2f32_create();
    Ring3_Math_Rectangle2* symbolBounds = Ring3_Math_Rectangle2_create();
    for (size_t j = layoutLine->start, m = layoutLine->start + layoutLine->length; j < m; ++j) {
      uint32_t codepoint = bytes[j];
      Ring3_Texture* symbolTexture;
      bool skip = !Ring3_Font_getCodePointInfo(font, codepoint, symbolBounds, symbolAdvance, &symbolTexture);
      if (skip) {
        continue;
      }

      float l = Ring3_Math_Vector2f32_getX(cursorPosition) + Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getPosition(symbolBounds));
      float r = l + Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getSize(symbolBounds));
      float t, b;
      if (yup) {
        t = Ring3_Math_Vector2f32_getY(cursorPosition) + (Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds)) - Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getPosition(symbolBounds)));
        b = t - Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds));
      } else {
        t = Ring3_Math_Vector2f32_getY(cursorPosition) - (Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds)) - Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getPosition(symbolBounds)));
        b = t + Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds));
      }

      Ring3_Math_Vector2f32* min = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(min, l, t);
      Ring3_Math_Vector2f32* max = Ring3_Math_Vector2f32_create();
      Ring3_Math_Vector2f32_set(max, r, b);
      Ring3_Math_Rectangle2_addPoint(lineBounds, min);
      Ring3_Math_Rectangle2_addPoint(lineBounds, max);

      Ring3_Math_Vector2f32_add(cursorPosition, symbolAdvance, cursorPosition);
    }
    layoutLine->left = Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getPosition(lineBounds));
    layoutLine->width = Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getSize(lineBounds));
    layoutLine->top = Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getPosition(lineBounds));
    layoutLine->height = Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(lineBounds));

    Ring3_Math_Vector2f32_set(cursorPosition, 0.f,  Ring3_Math_Vector2f32_getY(cursorPosition) + Ring3_Font_getBaselineDistance(font));
  }

  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, lines)); i < n; ++i) {
    Ring2_Value t = Ring2_Collections_List_getAt(lines, i);
    Machine_Text_LayoutLine* layoutLine = Ring1_cast(Machine_Text_LayoutLine *, Ring2_Value_getObject(&t));
    layoutLine->top += Ring3_Math_Vector2f32_getY(position0);
    layoutLine->left += Ring3_Math_Vector2f32_getX(position0);
  }
}

static void updateBounds(Machine_Text_Layout* self) {
  Ring3_Math_Vector2f32* position0 = Ring3_Math_Vector2f32_create();
#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  Ring3_Math_Vector2f32_set(position0, floorf(Ring3_Math_Vector2f32_getX(self->position)),
                                       floorf(Ring3_Math_Vector2f32_getY(self->position)));
#else
  Ring3_Math_Vector2f32_set(position0, Ring3_Math_Vector2f32_getX(self->position),
                                       Ring3_Math_Vector2f32_getY(self->position));
#endif

  Ring3_Math_Vector2f32* cursorPosition = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_copy(cursorPosition, position0);

  Ring3_Math_Rectangle2* bounds = Ring3_Math_Rectangle2_create();
  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_copy(p, cursorPosition);
  Ring3_Math_Rectangle2_setPosition(bounds, p);

  const char* bytes = Ring2_String_getBytes(self->text);

  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, self->lines)); i < n; ++i) {
    Ring2_Value e = Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List *, self->lines), i);
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Ring2_Value_getObject(&e);
    Ring3_Math_Vector2f32_set(p, layoutLine->left, layoutLine->top);
    Ring3_Math_Rectangle2_addPoint(bounds, p);
    Ring3_Math_Vector2f32_set(p, layoutLine->left + layoutLine->width, layoutLine->top + layoutLine->height);
    Ring3_Math_Rectangle2_addPoint(bounds, p);

    Ring3_Math_Vector2f32_set(cursorPosition, Ring3_Math_Vector2f32_getX(self->position),
                                              Ring3_Math_Vector2f32_getY(cursorPosition) + Ring3_Font_getBaselineDistance(self->font));
  }

  if (!self->visualBounds) {
    self->visualBounds = Ring3_Graphics2_Rectangle_create();
  }
  Ring3_Graphics2_Rectangle_setRectangle(self->visualBounds, bounds);
}

MACHINE_DEFINE_CLASSTYPE(Machine_Text_Layout,
                         Machine_Object,
                         &Machine_Text_Layout_visit,
                         &Machine_Text_Layout_construct,
                         NULL,
                         NULL,
                         NULL)

void Machine_Text_Layout_construct(Machine_Text_Layout* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->color = Ring3_Math_Vector3f32_create();
  Ring3_Math_Vector3f32_set(self->color, 0.f, 0.f, 0.f);
  self->position = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(self->position, 0.f, 0.f);
  self->text = Ring2_Value_getString(arguments + 0);
  self->font = (Ring3_Font *)Ring2_Value_getObject(arguments + 1);
  self->lines = Ring2_Collections_ArrayList_create();
  self->yup = true;
  self->flags |= LINES_DIRTY;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Text_Layout_getType());
}

Ring1_NoDiscardReturn() Machine_Text_Layout*
Machine_Text_Layout_create
  (
    Ring2_String* text,
    Ring3_Font* font
  )
{
  Ring2_assertNotNull(text);
  Ring2_assertNotNull(font);

  Machine_Type* ty = Machine_Text_Layout_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setString(&arguments[0], text);
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,font));
  Machine_Text_Layout* self = Ring1_cast(Machine_Text_Layout*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Machine_Text_Layout_getBounds
  (
    Machine_Text_Layout* self
  )
{
  if ((self->flags & LINES_DIRTY) == LINES_DIRTY) {
    Ring2_Collections_Collection_clear(Ring1_cast(Ring2_Collections_Collection *, self->lines));
    parse(self->text, Ring1_cast(Ring2_Collections_List *, self->lines));
    self->flags |= LINE_BOUNDS_DIRTY;
    self->flags &= ~LINES_DIRTY;
  }
  if ((self->flags & LINE_BOUNDS_DIRTY) == LINE_BOUNDS_DIRTY) {
    updateLinesBounds(self->position, self->font, self->text, Ring1_cast(Ring2_Collections_List *, self->lines), self->yup);
    self->flags |= BOUNDS_DIRTY;
    self->flags &= ~LINE_BOUNDS_DIRTY;
  }
  if ((self->flags & BOUNDS_DIRTY) == BOUNDS_DIRTY) {
    updateBounds(self);
    self->flags &= ~BOUNDS_DIRTY;
  }
  return Ring3_Graphics2_Rectangle_getRectangle(self->visualBounds);
}

void
Machine_Text_Layout_render
  (
    Machine_Text_Layout* self,
    Ring3_Graphics2_Context* context2
  )
{
  if ((self->flags & LINES_DIRTY) == LINES_DIRTY) {
    Ring2_Collections_Collection_clear(Ring1_cast(Ring2_Collections_Collection *, self->lines));
    parse(self->text, Ring1_cast(Ring2_Collections_List *, self->lines));
    self->flags |= LINE_BOUNDS_DIRTY;
    self->flags &= ~LINES_DIRTY;
  }
  if ((self->flags & LINE_BOUNDS_DIRTY) == LINE_BOUNDS_DIRTY) {
    updateLinesBounds(self->position, self->font, self->text, Ring1_cast(Ring2_Collections_List *, self->lines), self->yup);
    self->flags |= BOUNDS_DIRTY;
    self->flags &= ~LINE_BOUNDS_DIRTY;
  }
  if ((self->flags & BOUNDS_DIRTY) == BOUNDS_DIRTY) {
    updateBounds(self);
    self->flags &= ~BOUNDS_DIRTY;
  }

  if (self->clipRectangle) {
    Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 0, true);
    Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 1, true);
    Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 2, true);
    Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 3, true);
  }
  if (self->renderVisualBounds) {
    if (!self->visualBounds) {
      updateBounds(self);
    }
    Ring3_Math_Vector4f32* color = Ring3_Math_Vector4f32_create();
    Ring3_Math_Vector4f32_set(color, .3f, .6f, .3f, 1.f);
    Ring3_Graphics2_Rectangle_setColor(self->visualBounds, color);
    Ring3_Graphics2_Context* context = Ring3_Graphics2_Context_create(context2->visualsContext,
                                                                      context2->imagesContext,
                                                                      context2->fontsContext);
    Ring3_Graphics2_Context_setTargetSize(context, Ring3_Graphics2_Context_getTargetWidth(context2),
                                                   Ring3_Graphics2_Context_getTargetHeight(context2));
    Ring3_Graphics2_Shape_render((Ring3_Graphics2_Shape*)self->visualBounds, context);
  }

#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  float position0[] = { floorf(Ring3_Math_Vector2f32_getX(self->position)),
                        floorf(Ring3_Math_Vector2f32_getY(self->position)) };
#else
  float position0[] = { Ring3_Math_Vector2f32_getX(self->position),
                        Ring3_Math_Vector2f32_getY(self->position) };
#endif

  // Set the world matrix, view matrix, and projection matrix.
  Ring3_Graphics2_Context_setOriginBottomLeft(context2, Y_UP);
  Ring3_Math_Matrix4x4f32 const* modelSpaceToProjectiveSpace = Ring3_Graphics2_Context_getModelSpaceToProjectiveSpaceMatrix(context2);
  Ring3_Math_Matrix4x4f32 const* modelSpaceToWorldSpace = Ring3_Graphics2_Context_getModelSpaceToWorldSpaceMatrix(context2);

  Ring3_GpuProgram* shaderProgram = Ring3_Font_getVideoShaderProgram(self->font);
  Ring3_Binding* binding = Ring3_Font_getVideoBinding(self->font);

  if (self->clipRectangle) {
    Ring3_Math_Vector2f32* position = Ring3_Math_Rectangle2_getPosition(self->clipRectangle);
    const Ring3_Math_Vector2f32* size = Ring3_Math_Rectangle2_getSize(self->clipRectangle);
    // left
    {
      float N[]= { 1.f, 0.f, 0.f };
      Ring3_Math_Vector3f32* n2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(n2, N[0], N[1], N[2]);
      Ring3_Math_Vector3f32* p2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(p2, Ring3_Math_Vector2f32_getX(position), 0.0f, 0.0f);
      float d = -Ring3_Math_Vector3f32_dot(n2, p2);
      Ring3_Math_Vector4f32* x = Ring3_Math_Vector4f32_create();
      Ring3_Math_Vector4f32_set(x, N[0], N[1], N[2], d);
      Ring3_Binding_bindVector4(binding, Ring2_String_create("clipPlane0", crt_strlen("clipPlane0") + 1), x);
    }
    // right
    {
      float N[] = { -1.f, 0.f, 0.f };
      Ring3_Math_Vector3f32* n2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(n2, N[0], N[1], N[2]);
      Ring3_Math_Vector3f32* p2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(p2, Ring3_Math_Vector2f32_getX(position) + Ring3_Math_Vector2f32_getX(size), 0.0f, 0.0f);
      Ring2_assert(Ring3_Math_Vector2f32_getX(size) >= 0.f, Ring1_Status_InvalidArgument);
      float d = -Ring3_Math_Vector3f32_dot(n2, p2);
      Ring3_Math_Vector4f32* x = Ring3_Math_Vector4f32_create();
      Ring3_Math_Vector4f32_set(x, N[0], N[1], N[2], d);
      Ring3_Binding_bindVector4(binding, Ring2_String_create("clipPlane1", crt_strlen("clipPlane1") + 1), x);
    }
    // bottom
    {
      float N[] = { 0.f, +1.f, 0.f };
      Ring3_Math_Vector3f32* n2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(n2, N[0], N[1], N[2]);
      Ring3_Math_Vector3f32* p2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(p2, 0.f, Ring3_Math_Vector2f32_getY(position), 0.0f);
      float d = -Ring3_Math_Vector3f32_dot(n2, p2);
      Ring3_Math_Vector4f32* x = Ring3_Math_Vector4f32_create();
      Ring3_Math_Vector4f32_set(x, N[0], N[1], N[2], d);
      Ring3_Binding_bindVector4(binding, Ring2_String_create("clipPlane2", crt_strlen("clipPlane2") + 1), x);
    }
    // top
    {
      float N[] = { 0.f, -1.f, 0.f };
      Ring3_Math_Vector3f32* n2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(n2, N[0], N[1], N[2]);
      Ring3_Math_Vector3f32* p2 = Ring3_Math_Vector3f32_create(); Ring3_Math_Vector3f32_set(p2, 0.f, Ring3_Math_Vector2f32_getY(position) + Ring3_Math_Vector2f32_getY(size), 0.0f);
      Ring2_assert(Ring3_Math_Vector2f32_getY(size) >= 0.f, Ring1_Status_InvalidArgument);
      float d = -Ring3_Math_Vector3f32_dot(n2, p2);
      Ring3_Math_Vector4f32* x = Ring3_Math_Vector4f32_create();
      Ring3_Math_Vector4f32_set(x, N[0], N[1], N[2], d);
      Ring3_Binding_bindVector4(binding, Ring2_String_create("clipPlane3", crt_strlen("clipPlane3") + 1), x);
    }
  }
  Ring3_Binding_bindVector3(binding, Ring2_String_create("mesh_color", crt_strlen("mesh_color") + 1), self->color);
  Ring3_Binding_bindMatrix4(binding, Ring2_String_create("modelToWorldMatrix", crt_strlen("modelToWorldMatrix") + 1), modelSpaceToWorldSpace);
  Ring3_Binding_bindMatrix4(binding, Ring2_String_create("modelToProjectionMatrix", crt_strlen("modelToProjectionMatrix") + 1), modelSpaceToProjectiveSpace);

  Ring3_VisualsContext_setDepthTestFunction(context2->visualsContext, Ring3_DepthTestFunction_Always);
  Ring3_VisualsContext_setDepthWriteEnabled(context2->visualsContext, false);
  Ring3_VisualsContext_setIncomingBlendFunction(context2->visualsContext, Ring3_BlendFunction_IncomingAlpha);
  Ring3_VisualsContext_setExistingBlendFunction(context2->visualsContext, Ring3_BlendFunction_OneMinusIncomingAlpha);

  float cursorPosition[] = { position0[0], position0[1] };

  const char* bytes = Ring2_String_getBytes(self->text);

  Ring3_Math_Vector2f32* symbolAdvance = Ring3_Math_Vector2f32_create();
  Ring3_Math_Rectangle2* symbolBounds = Ring3_Math_Rectangle2_create();
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection *, self->lines)); i < n; ++i) {
    Ring2_Value t = Ring2_Collections_List_getAt(Ring1_cast(Ring2_Collections_List *, self->lines), i);
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Ring2_Value_getObject(&t);
    for (size_t j = layoutLine->start, m = layoutLine->start + layoutLine->length; j < m; ++j) {
      uint32_t codepoint = bytes[j];
      Ring3_Texture* symbolTexture;
      bool skip = !Ring3_Font_getCodePointInfo(self->font, codepoint, symbolBounds, symbolAdvance, &symbolTexture);
      if (skip) continue;

      float l = OFFSET_X + cursorPosition[0] + Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getPosition(symbolBounds));
      float r = l + Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getSize(symbolBounds));
      float t, b;
    #if defined(Y_UP)
      t = OFFSET_Y + cursorPosition[1] + (Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds)) - Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getPosition(symbolBounds)));
      b = t - Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds));
    #else
      t = OFFSET_Y + cursorPosition[1] - (Ring3_Math_Vector2_getY(Ring3_Math_Rectangle2_getSize(symbolBounds)) - symbolBounds.b);
      b = t + Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getSize(symbolBounds));
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

      Ring3_GpuBuffer_setData(Ring3_Font_getVideoBuffer(self->font), sizeof(vertices), (void const *)vertices);

      static uint8_t const indices[] = {
        0, 1, 2,
        2, 1, 3,
      };
      static size_t const UNIT = 0;
      Ring3_VisualsContext_bindTexture(context2->visualsContext, 0, symbolTexture);
      Ring3_Binding_bindSampler(binding, Ring2_String_create("texture_1", crt_strlen("texture_1") + 1), UNIT);
      Ring3_Binding_activate(binding);
      Ring3_VisualsContext_drawIndirect(context2->visualsContext, 0, 6, indices);

      cursorPosition[0] += Ring3_Math_Vector2f32_getX(symbolAdvance);
      cursorPosition[1] += Ring3_Math_Vector2f32_getY(symbolAdvance);
    }
    cursorPosition[0] = position0[0];
    cursorPosition[1] += Ring3_Font_getBaselineDistance(self->font);
  }
  Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 3, false);
  Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 2, false);
  Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 1, false);
  Ring3_VisualsContext_setClipDistanceEnabled(context2->visualsContext, 0, false);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Text_Layout_setText
  (
    Machine_Text_Layout* self,
    Ring2_String* text
  )
{
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(text);

  if (!Ring2_String_isEqualTo(Ring2_Context_get(), self->text, text)) {
    self->text = text;
    self->flags |= LINES_DIRTY | LINE_BOUNDS_DIRTY | BOUNDS_DIRTY;
  }
}

Ring1_NoDiscardReturn() Ring2_String*
Machine_Text_Layout_getText
  (
    Machine_Text_Layout* self
  )
{ return self->text; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Text_Layout_setPosition
  (
    Machine_Text_Layout* self,
    Ring3_Math_Vector2f32 const* position
  )
{
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(position);

  Ring3_Math_Vector2f32_copy(self->position, position);
  self->flags |= LINE_BOUNDS_DIRTY | BOUNDS_DIRTY;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Machine_Text_Layout_getPosition
  (
    Machine_Text_Layout* self
  )
{ return Ring3_Math_Vector2f32_clone(self->position); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Text_Layout_setColor
  (
    Machine_Text_Layout* self,
    Ring3_Math_Vector3f32 const* color
  )
{
  Ring2_assertNotNull(self);
  Ring2_assertNotNull(color);
  Ring3_Math_Vector3f32_copy(self->color, color);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Machine_Text_Layout_getColor
  (
    Machine_Text_Layout const* self
  )
{ return Ring3_Math_Vector3f32_clone(self->color); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Text_Layout_setRenderVisualBoundsEnabled
  (
    Machine_Text_Layout* self,
    bool renderVisualBounds
  )
{ self->renderVisualBounds = renderVisualBounds; }

Ring1_NoDiscardReturn() bool
Machine_Text_Layout_getRenderVisualBoundsEnabled
  (
    Machine_Text_Layout const* self
  )
{ return self->renderVisualBounds; }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Text_Layout_setClipRectangle(Machine_Text_Layout* self, Ring3_Math_Rectangle2* clipRectangle) {
  if (clipRectangle) {
    Ring2_assert(clipRectangle->w >= 0.f, Ring1_Status_InvalidArgument);
    Ring2_assert(clipRectangle->h >= 0.f, Ring1_Status_InvalidArgument);
    if (!self->clipRectangle) {
      Ring3_Math_Rectangle2 * temporary = Ring3_Math_Rectangle2_create();
      Ring3_Math_Rectangle2_copy(temporary, clipRectangle);
      self->clipRectangle = temporary;
    } else {
      Ring3_Math_Rectangle2_copy(self->clipRectangle, clipRectangle);
    }
  } else {
    self->clipRectangle = NULL;
  }
}

Ring3_Math_Rectangle2* Machine_Text_Layout_getClipRectangle(Machine_Text_Layout* self) {
  return self->clipRectangle;
}
