// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaF64.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_COLORRGBAF64_H_INCLUDED)
#define RING3_MATH_COLORRGBAF64_H_INCLUDED

#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Math_ColorRgbaF64)

/// @brief Create a new Ring3_Math_ColorRgbaF64 object.
/// @param red, green, blue, alpha The red, green, blue, and alpha component values.
/// @return A pointer to a new Ring3_Math_ColorRgbaF64 object with the specified component values.
/// @warning
/// The specified component values should be within the bounds of 0 (incl.) and 1 (incl.).
/// However, if a component value is clamped to these bounds if it is not within these bounds.
Ring1_CheckReturn() Ring3_Math_ColorRgbaF64 *
Ring3_Math_ColorRgbaF64_create
  (
    double red,
    double green,
    double blue,
    double alpha
  );

/// @brief Clone this Ring3_Math_ColorRgbF64 object.
/// @param self A pointer to this Ring3_Math_ColorRgbaF64 object.
/// @return A pointer to a new clone of this object.
Ring1_CheckReturn() Ring3_Math_ColorRgbaF64 *
Ring3_Math_ColorRgbaF64_clone
  (
    Ring3_Math_ColorRgbaF64 *self
  );

/// @brief Get the red component value of this Ring3_Math_RgbaF64 object.
/// @param self A pointer to this Ring3_Math_RgbaF64 object.
/// @return The red component value of this color object.
Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getRed
  (
    Ring3_Math_ColorRgbaF64* self
  );

/// @brief Get the green component value of this Ring3_Math_RgbaF64 object.
/// @param self A pointer to this Ring3_Math_RgbaF64 object.
/// @return The green component value of this color object.
Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getGreen
  (
    Ring3_Math_ColorRgbaF64* self
  );

/// @brief Get the blue component value of this Ring3_Math_RgbaF64 object.
/// @param self A pointer to this Ring3_Math_RgbaF64 object.
/// @return The blue component value of this color object.
Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getBlue
  (
    Ring3_Math_ColorRgbaF64* self
  );

/// @brief Get the alpha component value of this Ring3_Math_RgbaF64 object.
/// @param self A pointer to this Ring3_Math_RgbaF64 object.
/// @return The alpha component value of this color object.
Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getAlpha
  (
    Ring3_Math_ColorRgbaF64* self
  );

#endif // RING3_MATH_COLORRGBAF64_H_INCLUDED
