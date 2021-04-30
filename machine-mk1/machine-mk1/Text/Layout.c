#include "./../Text/Layout.h"

#include "./../Fonts.h"
#include "./../Video.h"
#include "./../Text/LayoutLine.h"

static const float OFFSET_X = 0.f;

static const float OFFSET_Y = 0.f;

#define WITH_SNAPTOGRID (1)

#define Y_UP (1)

static void visit(Machine_Text_Layout* self) {
  if (self->color) {
    Machine_visit(self->color);
  }
  if (self->position) {
    Machine_visit(self->position);
  }
  if (self->font) {
    Machine_visit(self->font);
  }
  if (self->text) {
    Machine_visit(self->text);
  }
  if (self->lines) {
    Machine_visit(self->lines);
  }
}

static void parse(Machine_String* text, Machine_PointerArray* lines) {
  const char* start = Machine_String_getBytes(text),
    * end = Machine_String_getBytes(text) + Machine_String_getNumberOfBytes(text);

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

static void measure(Machine_Math_Vector2 *position, Machine_Fonts_Font* font, Machine_String* text, Machine_PointerArray* lines, bool yup) {
#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  vec2 position0 = { floorf(Machine_Math_Vector2_getX(position)),
                     floorf(Machine_Math_Vector2_getY(position)) };
#else
  vec2 position0 = { (Machine_Math_Vector2_getX(position)),
                     (Machine_Math_Vector2_getY(position)) };
#endif

  vec2 cursorPosition = { position0[0], position0[1] };

  for (size_t i = 0, n = Machine_PointerArray_getSize(lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(lines, i);
    const char* bytes = Machine_String_getBytes(text);

    rect2 lineBounds;
    lineBounds.l = cursorPosition[0];
    lineBounds.w = 0.f;
    lineBounds.b = cursorPosition[1];
    lineBounds.h = 0.f;

    for (size_t j = layoutLine->start, m = layoutLine->start + layoutLine->length; j < m; ++j) {
      uint32_t codepoint = bytes[j];
      rect2 symbolBounds;
      vec2 symbolAdvance;
      Machine_Texture* symbolTexture;
      bool skip = !Machine_Font_getCodePointInfo(font, codepoint, &symbolBounds, symbolAdvance, &symbolTexture);
      if (skip) {
        continue;
      }

      float l = cursorPosition[0] + symbolBounds.l;
      float r = l + symbolBounds.w;
      float t, b;
      if (yup) {
        t = cursorPosition[1] + (symbolBounds.h - symbolBounds.b);
        b = t - symbolBounds.h;
      } else {
        t = cursorPosition[1] - (symbolBounds.h - symbolBounds.b);
        b = t + symbolBounds.h;
      }

      vec2 min = { l, t };
      vec2 max = { r, b };

      rect2_add_point(&lineBounds, min);
      rect2_add_point(&lineBounds, max);

      vec2_add(cursorPosition, cursorPosition, symbolAdvance);
    }
    layoutLine->left = lineBounds.l;
    layoutLine->width = lineBounds.w;
    layoutLine->top = lineBounds.b;
    layoutLine->height = lineBounds.h;

    cursorPosition[0] = 0.f;
    cursorPosition[1] += Machine_Font_getBaselineDistance(font);
  }
}

Machine_Text_Layout* Machine_Text_Layout_create(Machine_String* text, Machine_Fonts_Font* font) {
  if (text == NULL) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Text_Layout* self = Machine_allocate(sizeof(Machine_Text_Layout), (Machine_VisitCallback*)&visit, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->color = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(self->color, 0.f, 0.f, 0.f);
  self->position = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(self->position, 0.f, 0.f);
  self->font = font;
  self->text = text;
  self->lines = Machine_PointerArray_create();
  self->yup = true;
  parse(self->text, self->lines);
  measure(self->position, self->font, self->text, self->lines, self->yup);
  return self;
}

void Machine_Text_Layout_setPosition(Machine_Text_Layout* self, Machine_Math_Vector2* position) {
  if (position == NULL) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  self->position = position;
  measure(self->position, self->font, self->text, self->lines, self->yup);
}

void Machine_Text_Layout_setColor(Machine_Text_Layout* self, Machine_Math_Vector3* color) {
  if (color == NULL) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  self->color = color;
}

Machine_Math_Rectangle2* Machine_Text_Layout_getBounds(Machine_Text_Layout* self) {

#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  vec2 position0 = { floorf(Machine_Math_Vector2_getX(self->position)),
                     floorf(Machine_Math_Vector2_getY(self->position)) };
#else
  vec2 position0 = { (Machine_Math_Vector2_getX(self->position)),
                     (Machine_Math_Vector2_getY(self->position)) };
#endif

  vec2 cursorPosition = { position0[0], position0[1] };

  Machine_Math_Rectangle2* bounds = Machine_Math_Rectangle2_create();
  Machine_Math_Vector2* p = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(p, cursorPosition[0], cursorPosition[1]);
  Machine_Math_Rectangle2_setPosition(bounds, p);

  const char* bytes = Machine_String_getBytes(self->text);

  for (size_t i = 0, n = Machine_PointerArray_getSize(self->lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(self->lines, i);
    Machine_Math_Vector2_set(p, layoutLine->left, layoutLine->top);
    Machine_Math_Rectangle2_addPoint(bounds, p);
    Machine_Math_Vector2_set(p, layoutLine->left + layoutLine->width, layoutLine->top + layoutLine->height);
    Machine_Math_Rectangle2_addPoint(bounds, p);

    cursorPosition[0] = Machine_Math_Vector2_getX(self->position);
    cursorPosition[1] += Machine_Font_getBaselineDistance(self->font);
  }

  return bounds;
}

void Machine_Text_Layout_render(Machine_Text_Layout* self, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_UtilitiesGl_call(glViewport(0, 0, width, height));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));

#if defined(WITH_SNAPTOGRID)
  // Snap to pixel (ensure there are no artifacts).
  vec2 position0 = { floorf(Machine_Math_Vector2_getX(self->position)),
                     floorf(Machine_Math_Vector2_getY(self->position)) };
#else
  vec2 position0 = { (Machine_Math_Vector2_getX(self->position)),
                     (Machine_Math_Vector2_getY(self->position)) };
#endif

  // Set the world matrix, view matrix, and projection matrix.
  mat4x4 world, view, projection, wvp;
  mat4x4_identity(world); // world matrix is identity.
  mat4x4_identity(view); // view matrix is identity.
#if defined(Y_UP)
  mat4x4_ortho(projection, 0.f, width, height, 0.f, 1.f, -1.f); // projection matrix
#else
  mat4x4_ortho(projection, 0.f, width, 0.f, height, 1.f, -1.f); // projection matrix
#endif
  // Compute combined world view projection matrix.
  mat4x4_mul(wvp, projection, view);
  mat4x4_mul(wvp, wvp, world);

  Machine_ShaderProgram* shaderProgram = Machine_Font_getShaderProgram(self->font);
  Machine_Binding* binding = Machine_Font_getBinding(self->font);

  Machine_Binding_activate(binding);
  Machine_Video_bindShaderProgram(shaderProgram);
  {
    vec3 x = { Machine_Math_Vector3_getX(self->color), Machine_Math_Vector3_getY(self->color), Machine_Math_Vector3_getZ(self->color) };
    Machine_Binding_bindVector3(binding, Machine_String_create("mesh_color", strlen("mesh_color") + 1), x);
  }
  Machine_Binding_bindMatrix4x4(binding, Machine_String_create("mvp", strlen("mvp") + 1), wvp);

  glDisable(GL_DEPTH_TEST);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

  vec2 cursorPosition = { position0[0], position0[1] };

  const char* bytes = Machine_String_getBytes(self->text);

  for (size_t i = 0, n = Machine_PointerArray_getSize(self->lines); i < n; ++i) {
    Machine_Text_LayoutLine* layoutLine = (Machine_Text_LayoutLine*)Machine_PointerArray_getAt(self->lines, i);
    for (size_t j = layoutLine->start, m = layoutLine->start + layoutLine->length; j < m; ++j) {
      uint32_t codepoint = bytes[j];
      rect2 symbolBounds;
      vec2 symbolAdvance;
      Machine_Texture* symbolTexture;
      bool skip = !Machine_Font_getCodePointInfo(self->font, codepoint, &symbolBounds, symbolAdvance, &symbolTexture);
      if (skip) continue;

      float l = OFFSET_X + cursorPosition[0] + symbolBounds.l;
      float r = l + symbolBounds.w;
      float t, b;
    #if defined(Y_UP)
      t = OFFSET_Y + cursorPosition[1] + (symbolBounds.h - symbolBounds.b);
      b = t - symbolBounds.h;
    #else
      t = OFFSET_Y + cursorPosition[1] - (symbolBounds.h - symbolBounds.b);
      b = t + symbolBounds.h;
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

      Machine_FloatBuffer_setData(Machine_Font_getFloatBuffer(self->font), sizeof(vertices) / sizeof(float), vertices);

      static const uint8_t indices[] = {
        0, 1, 2,
        2, 1, 3,
      };
      static const size_t UNIT = 0;
      Machine_Video_bindTexture(0, symbolTexture);
      Machine_Binding_bindSampler(binding, Machine_String_create("texture_1", strlen("texture_1")), UNIT);
      Machine_UtilitiesGl_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, &indices));

      vec2_add(cursorPosition, cursorPosition, symbolAdvance);
    }
    cursorPosition[0] = Machine_Math_Vector2_getX(self->position);
    cursorPosition[1] += Machine_Font_getBaselineDistance(self->font);
  }
}

