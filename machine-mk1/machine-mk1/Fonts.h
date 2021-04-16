/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#if !defined(MACHINE_FONTS_H_INCLUDED)
#define MACHINE_FONTS_H_INCLUDED

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
    r->b = p[0];
    r->h += d;
  }

  if (r->b + r->h < p[1]) {
    r->h = p[1] - r->b;
  }
}

void Machine_Font_getBounds(Machine_Fonts_Font* self, vec2 position, rect2* bounds);

/**
 * @brief Render a string.
 * @remark '\t' is replaced ' '. '\n' is replaced by ' '.
 * @param self This font.
 */
void Machine_Font_draw(Machine_Fonts_Font *self, vec2 position, vec3 color, float width, float height);

/**
 * @brief Parse text into lines.
 * @param text The text.
 * @return The list of lines.
 */
Machine_PointerArray* Machine_Text_toLines(const char* text);

#endif // MACHINE_FONTS_H_INCLUDED
