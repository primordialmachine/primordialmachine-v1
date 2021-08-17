#if !defined(MACHINE_IMAGES_IMAGE_H_INCLUDED)
#define MACHINE_IMAGES_IMAGE_H_INCLUDED



#if !defined(MACHINE_IMAGES_PRIVATE)
#error("Do not include this file directly, include `_Images.h` instead.")
#endif
#include "_Video.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Images_Image)

void Machine_Images_Image_constructFromPath(Machine_Images_Image* self, Machine_String* path);

void Machine_Images_Image_constructDirect(Machine_Images_Image* self, Machine_PixelFormat pixelFormat, Machine_Integer width, Machine_Integer height, Machine_ByteBuffer* pixels);

/// @brief Create an image from a file.
/// @param path A pointer to the string denoting the path of the file.
/// @return A pointer to the image.
Machine_Images_Image* Machine_Images_Image_createImageFromPath(Machine_String* path);

/// @brief Create an image from pixel data.
/// @param pixelFormat The pixel format of a pixel.
/// @param width The number of pixels along the horizontal axis.
/// @param height The number of pixels along the vertical axis.
/// @param pixels A pointer to a Byte buffer containing the pixels.
/// @return A pointer to the image.
Machine_Images_Image* Machine_Images_Image_createImageDirect(Machine_PixelFormat pixelFormat, Machine_Integer width, Machine_Integer height, Machine_ByteBuffer* pixels);



#endif // MACHINES_IMAGES_IMAGE_H_INCLUDED
