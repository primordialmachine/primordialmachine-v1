/// @file Ring3/Visuals/PixelFormat.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_PIXELFORMAT_H_INCLUDED)
#define RING3_VISUALS_PIXELFORMAT_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/PixelFormat.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// @brief
/// An enumeration of pixel formats.
MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_PixelFormat)

enum Ring3_PixelFormat {

  /// @brief A pixel is three consecutive Bytes: 1st Byte is "red", 2dn Byte is "green", and 3rd
  /// Byte is "blue".
  Ring3_PixelFormat_RGB,
  /// @brief A pixel is four consecutive Bytes: 1st Byte is "red", 2dn Byte is "green", 3rd Byte is
  /// "blue", and 4th Byte is "alpha".
  Ring3_PixelFormat_RGBA,

  /// @brief A pixel is three consecutive Bytes: 1st Byte is "blue", 2dn Byte is "green", and 3rd
  /// Byte is "red".
  Ring3_PixelFormat_BGR,
  /// @brief A pixel is four consecutive Bytes: 1st Byte is "blue", 2dn Byte is "green", 3rd Byte is
  /// "red", and 4th Byte is "alpha".
  Ring3_PixelFormat_BGRA,

  /// @brief A pixel is one Byte: That Byte is "gray".
  Ring3_PixelFormat_GRAYSCALE,

};

Ring1_CheckReturn() Ring1_Inline() uint8_t
Ring3_PixelFormat_getBytesPerPixel
  (
    Ring3_PixelFormat self
  )
{
  switch (self) {
    case Ring3_PixelFormat_RGB:
      return 3;
    case Ring3_PixelFormat_RGBA:
      return 4;
    case Ring3_PixelFormat_BGR:
      return 3;
    case Ring3_PixelFormat_BGRA:
      return 4;
    case Ring3_PixelFormat_GRAYSCALE:
      return 1;
    default:
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
  };
}

#endif // RING3_VISUALS_PIXELFORMAT_H_INCLUDED
