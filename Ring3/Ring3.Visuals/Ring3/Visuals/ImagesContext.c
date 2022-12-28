/// @file Ring3/Visuals/ImagesContext.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/ImagesContext.h"
#undef RING3_VISUALS_PRIVATE

#include "Ring1/All/_Include.h"

MACHINE_DEFINE_CLASSTYPE(Ring3_ImagesContext,
                         Machine_Object,
                         NULL,
                         &Ring3_ImagesContext_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_ImagesContext_construct
  (
    Ring3_ImagesContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_ImagesContext_getType());
}

Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createFromPath
  (
    Ring3_ImagesContext* self,
    Ring2_String* path
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_ImagesContext, createFromPath, path); }

Ring1_NoDiscardReturn() Ring3_Image*
Ring3_ImagesContext_createDirect
  (
    Ring3_ImagesContext* self,
    Ring3_PixelFormat pixelFormat,
    Ring2_Integer width,
    Ring2_Integer height,
    Ring2_ByteBuffer* pixels
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_ImagesContext, createDirect, pixelFormat, width, height, pixels); }
