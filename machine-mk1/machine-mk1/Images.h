/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reservied.
 */
#if !defined(MACHINE_IMAGES_H_INCLUDED)
#define MACHINE_IMAGES_H_INCLUDED

typedef struct Machine_Images_Image Machine_Images_Image;

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
Machine_Images_Image* Machine_Images_createImage(const char* path);

void Machine_Images_Image_destroy(Machine_Images_Image* image);

#endif // MACHINE_IMAGES_H_INCLUDED
