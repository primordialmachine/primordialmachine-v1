/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#if !defined(MACHINE_FONTS_H_INCLUDED)
#define MACHINE_FONTS_H_INCLUDED

#include "Text/LayoutLine.h"
#include "Text/Layout.h"
#include "Binding.h"
#include "_Video.h"
#include <linmath.h>

MACHINE_DECLARE_CLASSTYPE(Machine_Fonts_Font)

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
bool Machine_Font_getCodePointInfo(Machine_Fonts_Font* self, uint32_t codepoint, Machine_Math_Rectangle2 *bounds, vec2 advance, Machine_Texture** texture);

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

#endif // MACHINE_FONTS_H_INCLUDED
