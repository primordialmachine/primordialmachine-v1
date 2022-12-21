// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaU8Extensions.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_COLORRGBAU8EXTENSIONS_H_INCLUDED)
#define RING3_MATH_COLORRGBAU8EXTENSIONS_H_INCLUDED

#include "Ring3/Math/ColorRgbaU8.h"

/// @brief Pack this color into an array of 4 Bytes.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @param target A pointer to an array of 4 Bytes.
/// @remark
/// If the environment Byte order is big endian:
/// - The red component value is written to the Byte at index 0,
/// - the green component value is written to the Byte at index 1, and
/// - the blue component value is written to the Byte at index 2.
/// If the environment Byte order is little endian (e.g. Windows):
/// - The red component value is written to the Byte at index 2,
/// - the green component value is written to the Byte at index 1, and
/// - the blue component value is written to the Byte at index 0.
void
Ring3_Math_ColorRgbaU8_packRgb
  (
    Ring3_Math_ColorRgbaU8* self,
    char* target
  );

/// @brief Pack this color into an array of 4 Bytes.
/// @param source A pointer to an Ring3_Math_ColorRgbaU8 object.
/// @param target A pointer to an array of 4 Bytes.
/// @remark
/// If the environment Byte order is big endian:
/// - The red component value is written to the Byte at index 0,
/// - the green component value is written to the Byte at index 1,
/// - the blue component value is written to the Byte at index 2, and
/// - the alpha component value is written to the Byte at index 3.
/// If the environment Byte order is little endian (e.g. Windows):
/// - The red component value is written to the Byte at index 3,
/// - the green component value is written to the Byte at index 2,
/// - the blue component value is written to the Byte at index 1, and
/// - the alpha component value is written to the Byte at index 0.
void
Ring3_Math_ColorRgbaU8_packRgba
  (
    Ring3_Math_ColorRgbaU8* self,
    char* target
  );

/// @brief Pack this color into an array of 4 Bytes.
/// @param source A pointer to an Ring3_Math_ColorRgbaU8 object.
/// @param target A pointer to an array of 4 Bytes.
/// @remark
/// If the environment Byte order is big endian:
/// - The red component value is written to the Byte at index 1,
/// - the green component value is written to the Byte at index 2,
/// - the blue compnent value is written to the Byte at index 3, and
/// - the alpha component value is written to the Byte at index 0.
/// If the environment Byte order is little endian (e.g. Windows):
/// - The red component value is written to the Byte at index 2,
/// - the green component value is written to the Byte at index 1,
/// - the blue compnent value is written to the Byte at index 0, and
/// - the alpha component value is written to the Byte at index 3.
void
Ring3_Math_ColorRgbaU8_packArgb
  (
    Ring3_Math_ColorRgbaU8* self,
    char* target
  );

#endif // RING3_MATH_COLORRGBAU8EXTENSIONS_H_INCLUDED
