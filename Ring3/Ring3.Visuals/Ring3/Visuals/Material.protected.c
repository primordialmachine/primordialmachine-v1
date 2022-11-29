/// @file Ring3/Visuals/Material.protected.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Material.protected.h"
#undef RING3_VISUALS_PRIVATE

#include "Ring1/Intrinsic.h"
#include "Ring2/Library/_Include.h"

void
Ring3_Material_construct
  (
    Ring3_Material* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->existingBlendFunction = (Ring3_BlendFunction)
    Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 0);
  self->depthTestFunction = (Ring3_DepthTestFunction)
    Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 1);
  self->depthWriteEnabled = (Ring2_Boolean)
    Machine_Extensions_getBooleanArgument(numberOfArguments, arguments, 2);
  self->incomingBlendFunction = (Ring3_BlendFunction)
    Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, 3);

  self->depthWriteEnabled = false;
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Material_getType());
}

Ring1_CheckReturn() Ring3_Material*
Ring3_Material_create
  (
    Ring3_BlendFunction existingBlendFunction,
    Ring3_DepthTestFunction depthTestFunction,
    Ring2_Boolean depthWriteEnabled,
    Ring3_BlendFunction incomingBlendFunction
  )
{
  Machine_ClassType* ty = Ring3_Material_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value ARGUMENTS[] = { 
    Ring2_Value_StaticInitializerVoid(),
    Ring2_Value_StaticInitializerVoid(),
    Ring2_Value_StaticInitializerVoid(),
    Ring2_Value_StaticInitializerVoid(),
  };
  Ring2_Value_setInteger(&ARGUMENTS[0], existingBlendFunction);
  Ring2_Value_setInteger(&ARGUMENTS[1], depthTestFunction);
  Ring2_Value_setBoolean(&ARGUMENTS[2], depthWriteEnabled);
  Ring2_Value_setInteger(&ARGUMENTS[3], incomingBlendFunction);
  Ring3_Material* self = Ring1_cast(Ring3_Material *, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

void
Ring3_Material_setExistingBlendFunction
  (
    Ring3_Material* self,
    Ring3_BlendFunction existingBlendFunction
  )
{ self->existingBlendFunction = existingBlendFunction; }

void
Ring3_Material_setIncomingBlendFunction
  (
    Ring3_Material* self,
    Ring3_BlendFunction incomingBlendFunction
  )
{ self->incomingBlendFunction = incomingBlendFunction; }

void
Ring3_Material_setDepthTestFunction
  (
    Ring3_Material* self,
    Ring3_DepthTestFunction depthTestFunction
  )
{ self->depthTestFunction = depthTestFunction; }

void
Ring3_Material_setDepthWriteEnabled
  (
    Ring3_Material* self,
    Ring2_Boolean depthWriteEnabled
  )
{ self->depthWriteEnabled = depthWriteEnabled; }
