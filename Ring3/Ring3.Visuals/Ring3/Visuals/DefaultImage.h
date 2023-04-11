/// @file Ring3/Visuals/DefaultImage.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_DEFAULTIMAGE_H_INCLUDED)
#define RING3_DEFAULTIMAGE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/DefaultImage.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Visuals/Image.h"


MACHINE_DECLARE_CLASSTYPE(Ring3_DefaultImage)

void
Ring3_DefaultImage_construct
  (
    Ring3_DefaultImage* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an image from pixel data.
/// @param pixelFormat The pixel format of a pixel.
/// @param width The number of pixels along the horizontal axis.
/// @param height The number of pixels along the vertical axis.
/// @param pixels A pointer to a Byte buffer containing the pixels.
/// @return A pointer to the image.
Ring1_NoDiscardReturn() Ring3_DefaultImage*
Ring3_DefaultImage_create
  (
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  );


#endif // RING3_DEFAULTIMAGE_H_INCLUDED
