/// @file Video/PixelFormat.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_PIXELFORMAT_H_INCLUDED)
#define MACHINE_VIDEO_PIXELFORMAT_H_INCLUDED

#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif

#include "_Runtime.h"

typedef enum Machine_PixelFormat Machine_PixelFormat;

enum Machine_PixelFormat {

  /// @brief A pixel is three consecutive Bytes: 1st Byte is "red", 2dn Byte is "green", and 3rd Byte is "blue".
  Machine_PixelFormat_RGB,
  /// @brief A pixel is four consecutive Bytes: 1st Byte is "red", 2dn Byte is "green", 3rd Byte is "blue", and 4th Byte is "alpha".
  Machine_PixelFormat_RGBA,

  /// @brief A pixel is three consecutive Bytes: 1st Byte is "blue", 2dn Byte is "green", and 3rd Byte is "red".
  Machine_PixelFormat_BGR,
  /// @brief A pixel is four consecutive Bytes: 1st Byte is "blue", 2dn Byte is "green", 3rd Byte is "red", and 4th Byte is "alpha".
  Machine_PixelFormat_BGRA,

  /// @brief A pixel is one Byte: That Byte is "gray".
  Machine_PixelFormat_GRAYSCALE,

};

static inline uint8_t Machine_PixelFormat_getBytesPerPixel(Machine_PixelFormat self) {
  switch (self) {
  case Machine_PixelFormat_RGB:
    return 3;
  case Machine_PixelFormat_RGBA:
    return 4;
  case Machine_PixelFormat_BGR:
    return 3;
  case Machine_PixelFormat_BGRA:
    return 4;
  case Machine_PixelFormat_GRAYSCALE:
    return 1;
  default:
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  };
}

#endif // MACHINE_VIDEO_PIXELFORMAT_H_INCLUDED
