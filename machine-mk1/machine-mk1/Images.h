/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#if !defined(MACHINE_IMAGES_H_INCLUDED)
#define MACHINE_IMAGES_H_INCLUDED

#include "_Runtime.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Images_Image)

typedef enum Machine_Images_PixelFormat {
  
  Machine_Images_PixelFormat_RGB,
  Machine_Images_PixelFormat_RGBA,
  
  Machine_Images_PixelFormat_BGR,
  Machine_Images_PixelFormat_BGRA,

  Machine_Images_PixelFormat_GRAYSCALE,

} Machine_Images_PixelFormat;

/**
 * @brief Get the size, in pixels, of this image.
 * @param self This image.
 * @param [out] width A pointer to an @a int variable receiving the width on success.
 * Not dereferenced on failure.
 * @param {out] height A pointer to an @a int variable receiving the height on success.
 * Not dereferenced on failure.
 */
int Machine_Images_Image_getSize(Machine_Images_Image* self, int* width, int* height);

/**
 * @brief Get the pixel format of this image.
 * @param self This image.
 * @param [out] pixelFormat A pointer to a @a Machine_Images_PixelFormat variable receiving the pixel format on success.
 * Not dereferenced on failure.
 * @return @a 0 on success, a non-zero value on failure.
 */
Machine_Images_PixelFormat Machine_Images_Image_getPixelFormat(Machine_Images_Image* self);

/**
 * @brief Get the pixel format of the image.
 * @param self This image.
 * @param [out] pixelFormat A pointer to a @a Machine_Images_PixelFormat variable receiving the pixel format on success.
 * Not dereferenced on failure.
 * @return @a 0 on success, a non-zero value on failure.
 */
void *Machine_Images_Image_getPixels(Machine_Images_Image* self);

/**
 * Increment the image module by @a 1.
 * FAILS if the reference count is INT_MAX.
 * @return @a 0 on success, a non-zero value on failure.
 */
int Machine_Images_startup();

/**
 * Decrement the images module by @a 1.
 * UNDEFINED if the reference count is @a 0.
 */
void Machine_Images_shutdown();

/**
 * @brief Load an image.
 * @param path The path.
 * @return A pointer to the image on success, null on failure.
 */
int Machine_Images_createImage(const char* path, Machine_Images_Image** image);

int Machine_Images_createImageDirect(Machine_Images_PixelFormat pixelFormat, int width, int height, void *pixels, Machine_Images_Image** image);

#endif // MACHINE_IMAGES_H_INCLUDED
