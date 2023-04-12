/// @file Ring3/Visuals/DefaultImage.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/DefaultImage.h"
#undef RING3_VISUALS_PRIVATE


struct Ring3_DefaultImage_Class {
  Ring3_Image_Class __parent;
};

struct Ring3_DefaultImage {
  Ring3_Image __parent;

  int width;
  int height;
  Ring3_PixelFormat pixelFormat;
  void* pixels;
};

static void
getSize
  (
    Ring3_DefaultImage const* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  )
{
  *width = self->width;
  *height = self->height;
}

static Ring3_PixelFormat
getPixelFormat
  (
    Ring3_DefaultImage const* self
  )
{ return self->pixelFormat; }

static void const*
getPixels
  (
    Ring3_DefaultImage const* self
  )
{ return self->pixels; }

static void
Ring3_DefaultImage_destruct
  (
    Ring3_DefaultImage* self
  )
{
  if (self->pixels) {
    Ring1_Memory_deallocate(self->pixels);
    self->pixels = NULL;
  }
}

static void
constructClass
  (
    Ring3_DefaultImage_Class* self
  )
{
  ((Ring3_Image_Class*)self)->getPixelFormat = (Ring3_PixelFormat(*)(Ring3_Image const*)) & getPixelFormat;
  ((Ring3_Image_Class*)self)->getPixels = (void const* (*)(Ring3_Image const*)) & getPixels;
  ((Ring3_Image_Class*)self)->getSize = (void (*)(Ring3_Image const*, Ring2_Integer*, Ring2_Integer*)) & getSize;
}

MACHINE_DEFINE_CLASSTYPE(Ring3_DefaultImage,
                         Ring3_Image,
                         NULL,
                         &Ring3_DefaultImage_construct,
                         &Ring3_DefaultImage_destruct,
                         &constructClass,
                         NULL);

void
Ring3_DefaultImage_construct
  (
    Ring3_DefaultImage* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  // (1) Supertype constructor.
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Image_construct(Ring1_cast(Ring3_Image*,self), NUMBER_OF_ARGUMENTS, ARGUMENTS);

  Ring2_Integer pixelFormat = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 0);
  Ring2_Integer width = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 1);
  Ring2_Integer height = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 2);
  Ring2_ByteBuffer* pixels = (Ring2_ByteBuffer*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                      arguments,
                                                                                      3,
                                                                                      Ring2_ByteBuffer_getType());

  // (3) Store.
  self->width = width;
  self->height = height;
  self->pixelFormat = pixelFormat;
  self->pixels = NULL;
  if (Ring1_Memory_allocateArray(&self->pixels, width * height,
                                 Ring3_PixelFormat_getBytesPerPixel(pixelFormat))) {
    Ring2_jump();
  }
  Ring1_Memory_copyFast(self->pixels, Ring2_ByteBuffer_getBytes(pixels),
                        width * height * Ring3_PixelFormat_getBytesPerPixel(pixelFormat));

  // (4) Set class type.
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_DefaultImage_getType());
}

Ring1_NoDiscardReturn() Ring3_DefaultImage*
Ring3_DefaultImage_create
  (
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  )
{
  Machine_Type* ty = Ring3_DefaultImage_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value arguments[4];
  Ring2_Value_setInteger(&arguments[0], pixelFormat);
  Ring2_Value_setInteger(&arguments[1], width);
  Ring2_Value_setInteger(&arguments[2], height);
  Ring2_Value_setObject(&arguments[3], Ring1_cast(Machine_Object*, pixels));
  Ring3_DefaultImage* self = Ring1_cast(Ring3_DefaultImage*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
