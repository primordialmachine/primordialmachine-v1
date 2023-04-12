/// @file Ring3/PixelFormat.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#if !defined(RING3_PIXELFORMAT_H_INCLUDED)
#define RING3_PIXELFORMAT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "Ring2/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_PixelFormat)

enum Ring3_PixelFormat
{
  Ring3_PixelFormat_Rgb,
  Ring3_PixelFormat_Rgba,
  Ring3_PixelFormat_Bgr,
  Ring3_PixelFormat_Bgra,
  Ring3_PixelFormat_Grayscale,
};

#ifdef __cplusplus
}
#endif

#endif // RING3_PIXELFORMAT_H_INCLUDED
