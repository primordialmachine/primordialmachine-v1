/// @file Ring3/Visuals/MaterialBuilder.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/MaterialBuilder.h"
#undef RING3_VISUALS_PRIVATEwwwww

MACHINE_DEFINE_INTERFACETYPE(Ring3_MaterialBuilder, NULL)

void
Ring3_MaterialBuilder_setExistingBlendFunction
  (
    Ring3_MaterialBuilder* self,
    Ring3_BlendFunction existingBlendFunction
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, setExistingBlendFunction, , self, existingBlendFunction); }

Ring1_CheckReturn() Ring3_BlendFunction
Ring3_MaterialBuilder_getExistingBlendFunction
  (
    Ring3_MaterialBuilder const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, getExistingBlendFunction, return, self); }

void
Ring3_MaterialBuilder_setIncomingBlendFunction
  (
    Ring3_MaterialBuilder* self,
    Ring3_BlendFunction incomingBlendFunction
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, setIncomingBlendFunction, , self, incomingBlendFunction); }

Ring1_CheckReturn() Ring3_BlendFunction
Ring3_MaterialBuilder_getIncomingBlendFunction
  (
    Ring3_MaterialBuilder const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, getIncomingBlendFunction, return, self); }

void
Ring3_MaterialBuilder_setDepthTestFunction
  (
    Ring3_MaterialBuilder* self,
    Ring3_DepthTestFunction depthTestFunction
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, setDepthTestFunction, , self, depthTestFunction); }

Ring1_CheckReturn() Ring3_DepthTestFunction
Ring3_MaterialBuilder_getDepthTestFunction
  (
    Ring3_MaterialBuilder const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, getDepthTestFunction, return, self); }

void
Ring3_MaterialBuilder_setDepthWriteEnabled
  (
    Ring3_MaterialBuilder* self,
    Ring2_Boolean depthWriteEnabled
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, setDepthWriteEnabled, , self, depthWriteEnabled); }

Ring1_CheckReturn() Ring2_Boolean
Ring3_MaterialBuilder_getDepthWriteEnabled
  (
    Ring3_MaterialBuilder const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, getDepthWriteEnabled, return, self); }

Ring1_CheckReturn() Ring3_Material*
Ring3_MaterialBuilder_build
  (
    Ring3_MaterialBuilder const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_MaterialBuilder, build, return, self); }
