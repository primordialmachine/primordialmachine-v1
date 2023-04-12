// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaU8.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_COLORRGBAU8_H_INCLUDED)
#define RING3_MATH_COLORRGBAU8_H_INCLUDED

#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Math_ColorRgbaU8)

/// @brief Create a new Ring3_Math_ColorRgbaU8 object.
/// @param red, green, blue, alpha The red, green, blue, and alpha component values.
/// @return A pointer to a new Ring3_Math_ColorRgbaU8 object with the specified component values.
Ring1_CheckReturn() Ring3_Math_ColorRgbaU8 *
Ring3_Math_ColorRgbaU8_create
  (
    uint8_t red,
    uint8_t green,
    uint8_t blue,
    uint8_t alpha
  );

/// @brief Clone this Ring3_Math_ColorRgbaU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @return A pointer to a new clone of this object.
Ring1_CheckReturn() Ring3_Math_ColorRgbaU8 *
Ring3_Math_ColorRgbaU8_clone
  (
    Ring3_Math_ColorRgbaU8 *self
  );

/// @brief Get the red component value of this Ring3_Math_ColorRgbaU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @return The red component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getRed
  (
    Ring3_Math_ColorRgbaU8* self
  );

/// @brief Get the green component value of this Ring3_Math_ColorRgbaU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @return The green component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getGreen
  (
    Ring3_Math_ColorRgbaU8* self
  );

/// @brief Get the blue component value of this Ring3_Math_ColorRgbaU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @return The blue component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getBlue
  (
    Ring3_Math_ColorRgbaU8* self
  );

/// @brief Get the alpha component value of this Ring3_Math_ColorRgbaU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @return The alpha component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getAlpha
  (
    Ring3_Math_ColorRgbaU8* self
  );

#endif // RING3_MATH_COLORRGBAU8_H_INCLUDED
