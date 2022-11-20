/// @file Video/Font.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_FONT_H_INCLUDED)
#define MACHINE_VIDEO_FONT_H_INCLUDED

#include "Video/_header.i"
#include "Video/Binding.h"
#include "Video/Texture.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Font)

struct Machine_Font_Class {
  Machine_Object_Class __parent;
  Ring2_Real32 (*getBaselineDistance)(Machine_Font* self);
  Ring2_Boolean (*getCodePointInfo)(Machine_Font* self, uint32_t codepoint,
                                    Ring3_Math_Rectangle2* bounds,
                                    Ring3_Math_Vector2* advance, Machine_Texture** texture);
  Machine_Binding* (*getVideoBinding)(Machine_Font* self);
  Machine_ShaderProgram* (*getVideoShaderProgram)(Machine_Font* self);
  Machine_VideoBuffer* (*getVideoBuffer)(Machine_Font* self);
};

struct Machine_Font {
  Machine_Object __parent;
};

/// @brief Construct this font.
/// @param self This font.
/// @param numberOfArguments, arguments The arguments.
/// The following signatures are supported:
/// <code>()</code>.
void
Machine_Font_construct
  (
    Machine_Font* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Get the baseline distance.
/// @param self This font.
/// @return The baseline distance.
Ring2_Real32
Machine_Font_getBaselineDistance
  (
    Machine_Font* self
  );

/// @brief Get the information of an unicode codepoint.
/// @param self This font.
/// @param codepoint The unicode codepoint.
/// @param bounds A pointer to a <code>rect2</code> variable.
/// @param advance A pointer to a <code>Machine_Math_Vector2</code> object.
/// The object is assigned the advance.
/// @param texture The texture.
Ring2_Boolean
Machine_Font_getCodePointInfo
  (
    Machine_Font* self,
    uint32_t codepoint,
    Ring3_Math_Rectangle2* bounds,
    Ring3_Math_Vector2* advance,
    Machine_Texture** texture
  );

/// @brief Get the binding to be used when rendering the font.
/// @param self This font.
/// @return The binding.
Machine_Binding*
Machine_Font_getVideoBinding
  (
    Machine_Font* self
  );

/// @brief Get the video shader program.
/// @param self This font.
/// @return The video shader program.
Machine_ShaderProgram*
Machine_Font_getVideoShaderProgram
  (
    Machine_Font* self
  );

/// @brief Get the video buffer.
/// @param self This font.
/// @return The video buffer.
Machine_VideoBuffer*
Machine_Font_getVideoBuffer
  (
    Machine_Font* self
  );

#endif // MACHINE_VIDEO_FONT_H_INCLUDED
