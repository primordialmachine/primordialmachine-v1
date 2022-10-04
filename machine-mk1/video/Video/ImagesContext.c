/// @file Video/ImagesContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/ImagesContext.h"


#include "Ring1/Intrinsic.h"


MACHINE_DEFINE_CLASSTYPE(Machine_ImagesContext, Machine_Object, NULL,
                         &Machine_ImagesContext_construct, NULL, NULL, NULL)

void Machine_ImagesContext_construct(Machine_ImagesContext* self, size_t numberOfArguments,
                                     Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_ImagesContext_getType());
}

Machine_Image* Machine_ImagesContext_createFromPath(Machine_ImagesContext* self,
                                                    Ring2_String* path) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_ImagesContext, createFromPath, path);
}

Machine_Image* Machine_ImagesContext_createDirect(Machine_ImagesContext* self,
                                                  Machine_PixelFormat pixelFormat,
                                                  Ring2_Integer width, Ring2_Integer height,
                                                  Machine_ByteBuffer* pixels) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_ImagesContext, createDirect, pixelFormat, width, height,
                                  pixels);
}
