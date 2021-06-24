/// @file _Images.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_IMAGES_H_INCLUDED)
#define MACHINE_IMAGES_H_INCLUDED



#include "_Video.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Images_Image)

void Machine_Images_Image_constructFromPath(Machine_Images_Image* self, Machine_String* path);
void Machine_Images_Image_constructDirect(Machine_Images_Image* self, Machine_PixelFormat pixelFormat, Machine_Integer width, Machine_Integer height, Machine_ByteBuffer* pixels);

/// @brief Get the size, in pixels, of this image.
/// @param self This image.
/// @param [out] width A pointer to an @a int variable receiving the width on success.
/// Not dereferenced on error.
/// @param {out] height A pointer to an @a int variable receiving the height on success.
/// Not dereferenced on error.
void Machine_Images_Image_getSize(Machine_Images_Image* self, Machine_Integer* width, Machine_Integer* height);

/// @brief Get the pixel format of this image.
/// @param self This image.
/// @return The pixel format.
Machine_PixelFormat Machine_Images_Image_getPixelFormat(Machine_Images_Image* self);

/// @brief Get the pixels of an image.
/// @param self This image.
/// @return The pixels.
void* Machine_Images_Image_getPixels(Machine_Images_Image* self);

/// @brief Create an image from a file.
/// @param path A pointer to the string denoting the path of the file.
/// @return A pointer to the image.
Machine_Images_Image* Machine_Images_createImageFromPath(Machine_String* path);

/// @brief Create an image from pixel data.
/// @param pixelFormat The pixel format of a pixel.
/// @param width The number of pixels along the horizontal axis.
/// @param height The number of pixels along the vertical axis.
/// @param pixels A pointer to a Byte buffer containing the pixels.
/// @return A pointer to the image.
Machine_Images_Image* Machine_Images_createImageDirect(Machine_PixelFormat pixelFormat, Machine_Integer width, Machine_Integer height, Machine_ByteBuffer* pixels);



#endif // MACHINE_IMAGES_H_INCLUDED
