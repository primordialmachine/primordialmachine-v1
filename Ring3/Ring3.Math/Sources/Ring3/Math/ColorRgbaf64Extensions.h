// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaF64Extensions.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_COLORRGBAF64EXTENSIONS_H_INCLUDED)
#define RING3_MATH_COLORRGBAF64EXTENSIONS_H_INCLUDED

#include "Ring3/Math/ColorRgbaF64.h"

/// @brief Pack this color into an array of 4 Bytes.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @param target A pointer to an array of 4 Bytes.
/// @return #Ring1_Result_Succcess on success. #Ring1_Result_Failure on failure.
/// @remark
/// The component values are multiplied by 255 and clamped to the range [0,255].
/// If the environment Byte order is big endian:
/// - The red component value is written to the Byte at index 0,
/// - the green component value is written to the Byte at index 1, and
/// - the blue component value is written to the Byte at index 2.
/// If the environment Byte order is little endian (e.g. Windows):
/// - The red component value is written to the Byte at index 2,
/// - the green component value is written to the Byte at index 1, and
/// - the blue component value is written to the Byte at index 0.
void
Ring3_Math_ColorRgbaF64_packRgb
  (
    Ring3_Math_ColorRgbaF64* self,
    char* target
  );

/// @brief Pack this color into an array of 4 Bytes.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @param target A pointer to an array of 4 Bytes.
/// @return #Ring1_Result_Succcess on success. #Ring1_Result_Failure on failure.
/// @remark
/// The component values are clamped to the range [0,1] and multiplied by 255.
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
Ring3_Math_ColorRgbaF64_packRgba
  (
    Ring3_Math_ColorRgbaF64* self,
    char* target
  );

/// @brief Pack this color into an array of 4 Bytes.
/// @param self A pointer to this Ring3_Math_ColorRgbaU8 object.
/// @param target A pointer to an array of 4 Bytes.
/// @return #Ring1_Result_Succcess on success. #Ring1_Result_Failure on failure.
/// @remark
/// The component values are clamped to the range [0,1] and multiplied by 255.
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
Ring3_Math_ColorRgbaF64_packArgb
  (
    Ring3_Math_ColorRgbaF64* self,
    char* target
  );

#endif // RING3_MATH_COLORRGBAF64EXTENSIONS_H_INCLUDED
