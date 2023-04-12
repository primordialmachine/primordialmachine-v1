/// @file Ring3/Visuals/Font.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_FONT_H_INCLUDED)
#define RING3_VISUALS_FONT_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/Font.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Math/_Include.h"
typedef struct Ring3_Texture Ring3_Texture;
typedef struct Ring3_Binding Ring3_Binding;
typedef struct Ring3_GpuBuffer Ring3_GpuBuffer;
typedef struct Ring3_GpuProgram Ring3_GpuProgram;

MACHINE_DECLARE_CLASSTYPE(Ring3_Font)

struct Ring3_Font_Class {
  Machine_Object_Class __parent;
  
  Ring2_Real32
  (*getBaselineDistance)
    (
      Ring3_Font* self
    );
  
  Ring2_Boolean
  (*getCodePointInfo)
    (
      Ring3_Font* self,
      uint32_t codepoint,
      Ring3_Math_Rectangle2* bounds,
      Ring3_Math_Vector2f32* advance,
      Ring3_Texture** texture
    );

  Ring3_Binding*
  (*getVideoBinding)
    (
      Ring3_Font* self
    );
  
  Ring3_GpuProgram*
  (*getVideoShaderProgram)
    (
      Ring3_Font* self
    );
  
  Ring3_GpuBuffer*
  (*getVideoBuffer)
    (
      Ring3_Font* self
    );
};

struct Ring3_Font {
  Machine_Object __parent;
};

/// @brief Construct this font.
/// @param self This font.
/// @param numberOfArguments, arguments The arguments.
/// The following signatures are supported:
/// <code>()</code>.
void
Ring3_Font_construct
  (
    Ring3_Font* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Get the baseline distance.
/// @param self This font.
/// @return The baseline distance.
Ring2_Real32
Ring3_Font_getBaselineDistance
  (
    Ring3_Font* self
  );

/// @brief Get the information of an unicode codepoint.
/// @param self This font.
/// @param codepoint The unicode codepoint.
/// @param bounds A pointer to a <code>rect2</code> variable.
/// @param advance A pointer to a <code>Machine_Math_Vector2</code> object.
/// The object is assigned the advance.
/// @param texture The texture.
Ring2_Boolean
Ring3_Font_getCodePointInfo
  (
    Ring3_Font* self,
    uint32_t codepoint,
    Ring3_Math_Rectangle2* bounds,
    Ring3_Math_Vector2f32* advance,
    Ring3_Texture** texture
  );

/// @brief Get the binding to be used when rendering the font.
/// @param self This font.
/// @return The binding.
Ring3_Binding*
Ring3_Font_getVideoBinding
  (
    Ring3_Font* self
  );

/// @brief Get the video shader program.
/// @param self This font.
/// @return The video shader program.
Ring3_GpuProgram*
Ring3_Font_getVideoShaderProgram
  (
    Ring3_Font* self
  );

/// @brief Get the video buffer.
/// @param self This font.
/// @return The video buffer.
Ring3_GpuBuffer*
Ring3_Font_getVideoBuffer
  (
    Ring3_Font* self
  );

#endif // RING3_VISUALS_FONT_H_INCLUDED
