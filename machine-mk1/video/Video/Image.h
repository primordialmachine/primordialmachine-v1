/// @file Video/Image.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_IMAGE_H_INCLUDED)
#define MACHINE_VIDEO_IMAGE_H_INCLUDED

#include "Video/_header.i"
#include "Video/External.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Image);

struct Machine_Image_Class {
  Machine_Object_Class parent;

  void const* (*getPixels)(Machine_Image const* self);
  void (*getSize)(Machine_Image const* self, Ring2_Integer* width, Ring2_Integer* height);
  Ring3_PixelFormat (*getPixelFormat)(Machine_Image const* self);
};

struct Machine_Image {
  Machine_Object parent;
};

/// @brief Construct this image.
/// @param self This image.
/// @param numberOfArguments, arguments The arguments.
void
Machine_Image_construct
  (
    Machine_Image* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Get the pixels of an image.
/// @param self This image.
/// @return The pixels.
void const*
Machine_Image_getPixels
  (
    Machine_Image const* self
  );

/// @brief Get the size, in pixels, of this image.
/// @param self This image.
/// @param [out] width A pointer to an @a int variable receiving the width on success.
/// Not dereferenced on error.
/// @param {out] height A pointer to an @a int variable receiving the height on success.
/// Not dereferenced on error.
void
Machine_Image_getSize
  (
    Machine_Image const* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  );

/// @brief Get the pixel format of this image.
/// @param self This image.
/// @return The pixel format.
Ring3_PixelFormat
Machine_Image_getPixelFormat
  (
    Machine_Image const* self
  );

#endif // MACHINE_VIDEO_IMAGE_H_INCLUDED
