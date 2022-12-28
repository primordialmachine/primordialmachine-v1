// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbU8Extensions.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_COLORRGBU8EXTENSIONS_H_INCLUDED)
#define RING3_MATH_COLORRGBU8EXTENSIONS_H_INCLUDED

#include "Ring3/Math/ColorRgbU8.h"

/// @brief Pack this color into an array of 3 Bytes.
/// @param self A pointer to this Ring3_Math_ColorRgbU8 object.
/// @param target A pointer to an array of 3 Bytes.
/// @return #Ring1_Result_Succcess on success. #Ring1_Result_Failure on failure.
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
Ring3_Math_ColorRgbU8_packRgb
  (
    Ring3_Math_ColorRgbU8* self,
    char* target
  );

/// @brief Pack this color into an array of 3 Bytes.
/// @param self A pointer to this Ring3_Math_ColorRgbU8 object.
/// @param target A pointer to an array of 3 Bytes.
/// @return #Ring1_Result_Succcess on success. #Ring1_Result_Failure on failure.
/// @remark
/// If the environment Byte order is big endian:
/// - The red component value is written to the Byte at index 2,
/// - the green component value is written to the Byte at index 1, and
/// - the blue compnent value is written to the Byte at index 0.
/// If the environment Byte order is little endian (e.g. Windows):
/// - The red component value is written to the Byte at index 0,
/// - the green component value is written to the Byte at index 1, and
/// - the blue compnent value is written to the Byte at index 2.
void
Ring3_Math_ColorRgbU8_packBgr
  (
    Ring3_Math_ColorRgbU8* self,
    char* target
  );

#endif // RING3_MATH_COLORRGBU8EXTENSIONS_H_INCLUDED
