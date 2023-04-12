/// @file Ring2/Visuals/Image.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_IMAGE_H_INCLUDED)
#define RING3_VISUALS_IMAGE_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/Image.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Visuals/PixelFormat.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Image);

struct Ring3_Image_Class {
  Machine_Object_Class parent;

  void const* (*getPixels)(Ring3_Image const* self);
  void (*getSize)(Ring3_Image const* self, Ring2_Integer* width, Ring2_Integer* height);
  Ring3_PixelFormat (*getPixelFormat)(Ring3_Image const* self);
};

struct Ring3_Image {
  Machine_Object parent;
};

/// @brief Construct this image.
/// @param self This image.
/// @param numberOfArguments, arguments The arguments.
void
Ring3_Image_construct
  (
    Ring3_Image* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Get the pixels of an image.
/// @param self This image.
/// @return The pixels.
void const*
Ring3_Image_getPixels
  (
    Ring3_Image const* self
  );

/// @brief Get the size, in pixels, of this image.
/// @param self This image.
/// @param [out] width A pointer to an @a int variable receiving the width on success.
/// Not dereferenced on error.
/// @param {out] height A pointer to an @a int variable receiving the height on success.
/// Not dereferenced on error.
void
Ring3_Image_getSize
  (
    Ring3_Image const* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  );

/// @brief Get the pixel format of this image.
/// @param self This image.
/// @return The pixel format.
Ring1_NoDiscardReturn() Ring3_PixelFormat
Ring3_Image_getPixelFormat
  (
    Ring3_Image const* self
  );

#endif // RING3_VISUALS_IMAGE_H_INCLUDED
