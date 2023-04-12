/// @file Ring3/Visuals/ImagesContext.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/ImagesContext.h"
#undef RING3_VISUALS_PRIVATE

#include "Ring1/All/_Include.h"


static void
addDecoderImpl
  (
    Ring3_ImagesContext* self,
    Ring3_ImagesDecoder* decoder
  );

static void
constructClass
  (
    Ring3_ImagesContext_Class* self
  );

static Ring3_Image*
createImageFromByteBufferImpl
  (
    Ring3_ImagesContext* self,
    Ring2_ByteBuffer* byteBuffer
  );

static Ring3_Image*
createImageFromPathImpl
  (
    Ring3_ImagesContext* self,
    Ring2_String* path
  );

static Ring3_Image*
createImageImpl
  (
    Ring3_ImagesContext* self,
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  );

static Ring2_Integer64
getNumberOfDecoders
  (
    Ring3_ImagesContext* self
  );

static Ring3_ImagesDecoder*
getDecoderAt
  (
    Ring3_ImagesContext* self,
    Ring2_Integer64 index
  );

static Ring3_Image*
tryDecoder
  (
    Ring3_ImagesContext* self,
    Ring3_ImagesDecoder* decoder,
    Ring2_ByteBuffer* byteBuffer
  );

static Ring3_Image*
tryDecoders
  (
    Ring3_ImagesContext* self,
    Ring2_ByteBuffer* byteBuffer
  );

static void
visit
  (
    Ring3_ImagesContext* self
  );

static void
addDecoderImpl
  (
    Ring3_ImagesContext* self,
    Ring3_ImagesDecoder* decoder
  )
{
  Ring2_Value temporary = Ring2_Value_StaticInitializerVoid();
  Ring2_Value_setObject(&temporary, Ring1_cast(Machine_Object*, decoder));
  Ring2_Collections_List_append(self->decoders, temporary);
}

static void
constructClass
  (
    Ring3_ImagesContext_Class* self 
  )
{
  self->addDecoder = &addDecoderImpl;
  self->createImage = (Ring3_Image * (*)(Ring3_ImagesContext*, Ring3_PixelFormat, Ring2_Integer, Ring2_Integer, Ring2_ByteBuffer*)) & createImageImpl;
  self->createImageFromByteBuffer = &createImageFromByteBufferImpl;
  self->createImageFromPath = &createImageFromPathImpl;
}

static Ring3_Image*
createImageFromByteBufferImpl
  (
    Ring3_ImagesContext* self,
    Ring2_ByteBuffer* byteBuffer
  )
{
  return tryDecoders(self, byteBuffer);
}

static Ring3_Image*
createImageFromPathImpl
  (
    Ring3_ImagesContext* self,
    Ring2_String* path
  )
{
  Ring2_ByteBuffer* byteBuffer = Machine_getFileContentsAsByteBuffer(path);
  return
      Ring3_ImagesContext_createImageFromByteBuffer
        (
          Ring1_cast(Ring3_ImagesContext*, self),
          byteBuffer
        );
}

static Ring3_Image*
createImageImpl
  (
    Ring3_ImagesContext* self,
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  )
{ return Ring1_cast(Ring3_Image*, Ring3_DefaultImage_create(pixelFormat, width, height, pixels)); }

static Ring2_Integer64
getNumberOfDecoders
  (
    Ring3_ImagesContext* self
  )
{
  Ring2_Collections_List* l = Ring1_cast(Ring3_ImagesContext*, self)->decoders;
  return Ring2_Collections_Collection_getSize(Ring1_cast(Ring2_Collections_Collection*, l));
}

static Ring3_ImagesDecoder*
getDecoderAt
  (
    Ring3_ImagesContext* self,
    Ring2_Integer64 index
  )
{
  Ring2_Collections_List* l = Ring1_cast(Ring3_ImagesContext*, self)->decoders;
  Ring2_Value temporary = Ring2_Collections_List_getAt(l, index);
  Ring3_ImagesDecoder* decoder = Ring1_cast(Ring3_ImagesDecoder*, Ring2_Value_getObject(&temporary));
  return decoder;
}

static Ring3_Image*
tryDecoder
  (
    Ring3_ImagesContext* self,
    Ring3_ImagesDecoder* decoder,
    Ring2_ByteBuffer* byteBuffer
  )
{
  void* bytes;
  Ring2_Integer64 numberOfBytes;
  Ring3_PixelFormat pixelFormat;
  int width, height;
  Ring3_ImagesDecoder_decode
  (
    decoder,
    Ring2_ByteBuffer_getBytes(byteBuffer),
    Ring2_ByteBuffer_getNumberOfBytes(byteBuffer),
    &bytes,
    &numberOfBytes,
    &pixelFormat,
    &width,
    &height
  );
  Ring2_ByteBuffer* pixels = NULL;
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    pixels = Ring2_ByteBuffer_create();
    Ring2_ByteBuffer_appendBytes(pixels, bytes, numberOfBytes);
    Ring1_Memory_deallocate(bytes);
    bytes = NULL;
    Ring2_popJumpTarget();
  }
  else {
    Ring2_popJumpTarget();
    Ring2_jump();
  }
  Ring3_Image* image =
    Ring3_ImagesContext_createImage
      (
        Ring1_cast(Ring3_ImagesContext*, self),
        pixelFormat,
        width,
        height,
        pixels
      );
  return image;
}

static Ring3_Image*
tryDecoders
  (
    Ring3_ImagesContext* self,
    Ring2_ByteBuffer* byteBuffer
  )
{
  for (Ring2_Integer i = 0, n = getNumberOfDecoders(self); i < n; ++i) {
    Ring3_ImagesDecoder* decoder = getDecoderAt(self, i);
    Ring2_JumpTarget jumpTarget;
    Ring2_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      Ring3_Image* image = tryDecoder(self, decoder, byteBuffer);
      Ring2_popJumpTarget();
      return image;
    }
    else {
      Ring2_popJumpTarget();
    }
  }
  Ring1_Status_set(Ring1_Status_DecodingError);
  Ring2_jump();
}

static void
visit
  (
    Ring3_ImagesContext* self
  )
{
  if (self->decoders) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->decoders);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_ImagesContext,
                         Machine_Object,
                         &visit,
                         &Ring3_ImagesContext_construct,
                         NULL,
                         &constructClass,
                         NULL)

void
Ring3_ImagesContext_construct
  (
    Ring3_ImagesContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->decoders = Ring1_cast(Ring2_Collections_List*, Ring2_Collections_ArrayList_create());
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_ImagesContext_getType());
}

Ring1_NoDiscardReturn() Ring3_ImagesContext*
Ring3_ImagesContext_create
  (
  )
{
  Machine_Type* ty = Ring3_ImagesContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_ImagesContext* self = Ring1_cast(Ring3_ImagesContext*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createImageFromPath
  (
    Ring3_ImagesContext* self,
    Ring2_String* path
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_ImagesContext, createImageFromPath, path); }

Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createImageFromByteBuffer
  (
    Ring3_ImagesContext* self,
    Ring2_ByteBuffer* byteBuffer
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_ImagesContext, createImageFromByteBuffer, byteBuffer); }

Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createImage
  (
    Ring3_ImagesContext* self,
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_ImagesContext, createImage, pixelFormat, width, height, pixels); }

void
Ring3_ImagesContext_addDecoder
  (
    Ring3_ImagesContext* self,
    Ring3_ImagesDecoder* decoder
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_ImagesContext, addDecoder, decoder); }
