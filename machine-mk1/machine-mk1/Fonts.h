/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#if !defined(MACHINE_FONTS_H_INCLUDED)
#define MACHINE_FONTS_H_INCLUDED

#include "Text/LayoutLine.h"
#include "Text/Layout.h"
#include "Binding.h"
#include "Texture.h"
#include <linmath.h>

typedef struct Machine_Fonts_Font Machine_Fonts_Font;

/**
 * Increment the fonts module by @a 1.
 * FAILS if the reference count is INT_MAX.
 * @return @a 0 on success, a non-zero value on failure.
 */
int Machine_Fonts_startup();

/**
 * Decrement the fonts module by @a 1.
 * UNDEFINED if the reference count is @a 0.
 */
void Machine_Fonts_shutdown();

/**
 * @brief Load a font of the specified size.
 * @param path The path.
 * @param pointSize The point size.
 * @return A pointer to the font on success, null on failure.
 */
Machine_Fonts_Font* Machine_Fonts_createFont(const char* path, int pointSize);

typedef struct rect2 {
  float l, b;
  float w, h;
} rect2;

static inline void rect2_get_center(rect2* r, vec2 c) {
  c[0] = r->l + r->w * 0.5f;
  c[1] = r->b + r->h * 0.5f;
}

static inline void rect2_add_point(rect2* r, vec2 p) {
  if (r->l > p[0]) {
    float d = r->l - p[0];
    r->l = p[0];
    r->w += d;
  }
  
  if (r->l + r->w < p[0]) {
    r->w = p[0] - r->l;
  }

  if (r->b > p[1]) {
    float d = r->b - p[1];
    r->b = p[1];
    r->h += d;
  }

  if (r->b + r->h < p[1]) {
    r->h = p[1] - r->b;
  }
}

/**
 * @brief Get the baseline distance.
 * @param self This font.
 * @return The baseline distance.
 */
float Machine_Font_getBaselineDistance(Machine_Fonts_Font* self);

/// @brief Get the information of an unicode codepoint.
/// @param self This font.
/// @param codepoint The unicode codepoint.
/// @param bounds A pointer to a <code>rect2</code> variable.
/// @param advance A pointer to a <code>vec2</code> variable.
/// @param texture The texture.
bool Machine_Font_getCodePointInfo(Machine_Fonts_Font* self, uint32_t codepoint, rect2* bounds, vec2 advance, Machine_Texture** texture);

/// @brief Get the binding to be used when rendering the font.
/// @param self This font.
/// @return The binding.
Machine_Binding* Machine_Font_getBinding(Machine_Fonts_Font* self);

/// @brief Get the shader program.
/// @param self This font.
/// @return The shader program.
Machine_ShaderProgram* Machine_Font_getShaderProgram(Machine_Fonts_Font *self);

/// @brief Get the buffer.
/// @param self This font.
/// @return The shader program.
Machine_FloatBuffer* Machine_Font_getFloatBuffer(Machine_Fonts_Font* self);

/**
 * @brief Get the bounds of the specified text.
 * @param self This font.
 * @param text The text.
 * @param bounds A pointer to a <code>rect2</code> variable.
 */
void Machine_Font_getBounds(Machine_Fonts_Font* self, const char* text, rect2* bounds);

#endif // MACHINE_FONTS_H_INCLUDED
