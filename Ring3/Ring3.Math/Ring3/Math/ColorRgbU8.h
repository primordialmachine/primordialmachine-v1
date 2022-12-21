// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbU8.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_COLORRGBU8_H_INCLUDED)
#define RING3_MATH_COLORRGBU8_H_INCLUDED

#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Math_ColorRgbU8)

/// @brief Create a new Ring3_Math_ColorRgbU8 object.
/// @param red, green, blue, alpha The red, green, blue, and alpha component values.
/// @return A pointer to a new Ring3_Math_Color_RgbaU8 object with component with the specified component values.
Ring1_CheckReturn() Ring3_Math_ColorRgbU8 *
Ring3_Math_ColorRgbU8_create
  (
    uint8_t red,
    uint8_t green,
    uint8_t blue
  );

/// @brief Clone this Ring3_Math_ColorRgbU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbU8 object.
/// @return A pointer to a new clone of this object.
Ring1_CheckReturn() Ring3_Math_ColorRgbU8 *
Ring3_Math_ColorRgbU8_clone
  (
    Ring3_Math_ColorRgbU8* self
  );

/// @brief Get the red component value of this Ring3_Math_ColorRgbU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbU8 object.
/// @return The red component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbU8_getRed
  (
    Ring3_Math_ColorRgbU8* self
  );

/// @brief Get the green component value of this Ring3_Math_ColorRgbU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbU8 object.
/// @return The green component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbU8_getGreen
  (
    Ring3_Math_ColorRgbU8* self
  );

/// @brief Get the blue component value of this Ring3_Math_ColorRgbU8 object.
/// @param self A pointer to this Ring3_Math_ColorRgbU8 object.
/// @return The blue component value of this color object.
Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbU8_getBlue
  (
    Ring3_Math_ColorRgbU8* self
  );

#endif // RING3_MATH_COLORRGBU8_H_INCLUDED
