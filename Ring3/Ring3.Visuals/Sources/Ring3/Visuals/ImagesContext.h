/// @file Ring3/Visuals/ImagesContext.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_IMAGESCONTEXT_H_INCLUDED)
#define RING3_VISUALS_IMAGESCONTEXT_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/ImagesContext.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"
typedef struct Ring3_Image Ring3_Image;
typedef struct Ring3_ImagesDecoder Ring3_ImagesDecoder;

MACHINE_DECLARE_CLASSTYPE(Ring3_ImagesContext);

struct Ring3_ImagesContext_Class {
  Machine_Object_Class parent;

  Ring3_Image*
  (*createImageFromPath)
    (
      Ring3_ImagesContext*,
      Ring2_String*
    );
  
  Ring3_Image*
  (*createImageFromByteBuffer)
    (
      Ring3_ImagesContext*,
      Ring2_ByteBuffer*
    );

  Ring3_Image*
  (*createImage)
    (
      Ring3_ImagesContext*,
      Ring3_PixelFormat,
      Ring2_Integer,
      Ring2_Integer,
      Ring2_ByteBuffer*
    );

  void
  (*addDecoder)
    (
      Ring3_ImagesContext*,
      Ring3_ImagesDecoder*
    );

};

struct Ring3_ImagesContext {
  Machine_Object parent;
  /// @brief List of decoders.
  Ring2_Collections_List* decoders;
};

/// @brief Construct this images context.
/// @param self This images context.
/// @param numberOfArguments, arguments The arguments.
void
Ring3_ImagesContext_construct
  (
    Ring3_ImagesContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_ImagesContext*
Ring3_ImagesContext_create
  (
  );

/// @brief Create an image from a file given the path of the file.
/// @param self This images context.
/// @param path The pathname of the file.
/// @return The image.
Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createImageFromPath
  (
    Ring3_ImagesContext* self,
    Ring2_String* path
  );

/// @brief Create an image from the Bytes in a Byte buffer.
/// @param self This images context.
/// @param byteBuffer The Byte buffer.
/// @return The image.
Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createImageFromByteBuffer
  (
    Ring3_ImagesContext* self,
    Ring2_ByteBuffer* byteBuffer
  );

/// @brief Create an image given its data.
/// @param self This images context.
/// @param pixelFormat The pixel format.
/// @param width, height The width and the height, both in pixels, of the image.
/// @param pixels A pointer to an Byte buffer containing the Bytes of the pixels of the image.
Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createImage
  (
    Ring3_ImagesContext* self,
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  );

/// @brief Add an images decoder to this images context.
/// @param self This images context.
/// @param decoder The decoder.
void
Ring3_ImagesContext_addDecoder
  (
    Ring3_ImagesContext* self,
    Ring3_ImagesDecoder* decoder
  );


#endif // RING3_VISUALS_IMAGESCONTEXT_H_INCLUDED
