/// @file Video/ImagesContext.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_IMAGESCONTEXT_H_INCLUDED)
#define MACHINE_VIDEO_IMAGESCONTEXT_H_INCLUDED

#include "Video/_header.i"
#include "Video/PixelFormat.h"

MACHINE_DECLARE_CLASSTYPE(Machine_ImagesContext);

struct Machine_ImagesContext_Class {
  Machine_Object_Class parent;
  Machine_Image* (*createFromPath)(Machine_ImagesContext* self, Ring2_String* path);
  Machine_Image* (*createDirect)(Machine_ImagesContext* self, Machine_PixelFormat pixelFormat,
                                 Ring2_Integer width, Ring2_Integer height,
                                 Machine_ByteBuffer* pixels);
};

struct Machine_ImagesContext {
  Machine_Object parent;
};

/// @brief Construct this images context.
/// @param self This images context.
/// @param numberOfArguments, arguments The arguments.
void Machine_ImagesContext_construct(Machine_ImagesContext* self, size_t numberOfArguments,
                                     Machine_Value const* arguments);

/// @brief Create an image from a file given the pathname of the file.
/// @param self This images context.
/// @param path The pathname of the file.
/// @return The image.
Machine_Image* Machine_ImagesContext_createFromPath(Machine_ImagesContext* self,
                                                    Ring2_String* path);

/// @brief Create an image given its data.
/// @param self This images context.
/// @param pixelFormat The pixel format.
/// @param width, height The width and the height, both in pixels, of the image.
/// @param pixels A pointer to an Byte buffer containing the Bytes of the pixels of the image.
Machine_Image* Machine_ImagesContext_createDirect(Machine_ImagesContext* self,
                                                  Machine_PixelFormat pixelFormat,
                                                  Ring2_Integer width, Ring2_Integer height,
                                                  Machine_ByteBuffer* pixels);

#endif // MACHINE_VIDEO_IMAGESCONTEXT_H_INCLUDED
