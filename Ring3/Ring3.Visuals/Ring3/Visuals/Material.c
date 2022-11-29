/// @file Ring3/Visuals/Material.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Material.h"
#undef RING3_VISUALS_PRIVATE

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Material.protected.h"
#undef RING3_VISUALS_PRIVATE

#include "Ring1/Intrinsic.h"

MACHINE_DEFINE_CLASSTYPE(Ring3_Material/*type*/,
                         Machine_Object/*parentType*/,
                         NULL/*visit*/,
                         &Ring3_Material_construct/*construct*/,
                         NULL/*destruct*/,
                         NULL/*classConstruct*/,
                         NULL/*implementInterfaces*/)

Ring1_CheckReturn() Ring3_BlendFunction
Ring3_Material_getExistingBlendFunction
  (
    Ring3_Material const* self
  )
{ return self->existingBlendFunction; }

Ring1_CheckReturn() Ring3_BlendFunction
Ring3_Material_getIncomingBlendFunction
  (
    Ring3_Material const* self
  ) 
{ return self->incomingBlendFunction; }

Ring1_CheckReturn() Ring3_DepthTestFunction
Ring3_Material_getDepthTestFunction
  (
    Ring3_Material const* self
  )
{ return self->depthTestFunction; }

Ring1_CheckReturn() Ring2_Boolean
Ring3_Material_getDepthWriteEnabled
  (
    Ring3_Material const* self
  )
{ return self->depthWriteEnabled; }
