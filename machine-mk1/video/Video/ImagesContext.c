/// @file Video/ImagesContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "./../Video/ImagesContext.h"



MACHINE_DEFINE_CLASSTYPE_EX(Machine_ImagesContext, Machine_Object, NULL, &Machine_ImagesContext_construct, NULL)

void Machine_ImagesContext_construct(Machine_ImagesContext* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_Object_getClassType((Machine_Object*)self, Machine_ImagesContext_getClassType());
}

Machine_Image* Machine_ImagesContext_createFromPath(Machine_ImagesContext* self, Machine_String* path) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_ImagesContext, createFromPath, path);
}

Machine_Image* Machine_ImagesContext_createDirect(Machine_ImagesContext* self, Machine_PixelFormat pixelFormat, Machine_Integer width, Machine_Integer height, Machine_ByteBuffer* pixels) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_ImagesContext, createDirect, pixelFormat, width, height, pixels);
}
