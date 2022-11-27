/// @file Ring3/Visuals/DefaultMaterialBuilder.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/DefaultMaterialBuilder.h"
#undef RING3_VISUALS_PRIVATE

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Material.protected.h"
#include "Ring3/Visuals/MaterialBuilder.h"
#undef RING3_VISUALS_PRIVATE

static Ring1_CheckReturn() Ring3_DepthTestFunction
getDepthTestFunctionImpl
  (
    const Ring3_DefaultMaterialBuilder *self
  )
{ return self->depthTestFunction; }

static void
setDepthTestFunctionImpl
  (
    Ring3_DefaultMaterialBuilder *self,
    Ring3_DepthTestFunction depthTestFunction
  )
{ self->depthTestFunction = depthTestFunction; }

static Ring1_CheckReturn() Ring3_BlendFunction
getExistingBlendFunctionImpl
  (
    const Ring3_DefaultMaterialBuilder* self
  )
{ return self->existingBlendFunction; }

static void
setExistingBlendFunctionImpl
  (
    Ring3_DefaultMaterialBuilder* self,
    Ring3_DepthTestFunction existingBlendFunction
  )
{ self->existingBlendFunction = existingBlendFunction; }

static Ring1_CheckReturn() Ring3_BlendFunction
getIncomingBlendFunctionImpl
  (
    const Ring3_DefaultMaterialBuilder* self
  )
{ return self->incomingBlendFunction; }

static void
setIncomingBlendFunctionImpl
  (
    Ring3_DefaultMaterialBuilder* self,
    Ring3_DepthTestFunction incomingBlendFunction
  )
{ self->incomingBlendFunction = incomingBlendFunction; }

static Ring1_CheckReturn() bool
getDepthWriteEnabledImpl
  (
    const Ring3_DefaultMaterialBuilder* self
  )
{ return self->depthWriteEnabled; }

static void
setDepthWriteEnabledImpl
  (
    Ring3_DefaultMaterialBuilder* self,
    bool depthWriteEnabled
  )
{ self->depthWriteEnabled = depthWriteEnabled; }

static Ring1_CheckReturn() Ring3_Material *
buildImpl
  (
    Ring3_DefaultMaterialBuilder const* self
  )
{
  Ring3_Material* material = Ring3_Material_create(self->existingBlendFunction,
                                                   self->depthTestFunction,
                                                   self->depthWriteEnabled,
                                                   self->incomingBlendFunction);
  return material;
}

static void
Ring3_DefaultMaterialBuilder_implement_Ring3_MaterialBuilder
  (
    Ring3_MaterialBuilder_Dispatch* self
  )
{
  self->getDepthTestFunction = &getDepthTestFunctionImpl;
  self->setDepthTestFunction = &setDepthTestFunctionImpl;
  self->getExistingBlendFunction = &getExistingBlendFunctionImpl;
  self->setExistingBlendFunction = &setExistingBlendFunctionImpl;
  self->getIncomingBlendFunction = &getIncomingBlendFunctionImpl;
  self->setIncomingBlendFunction = &setIncomingBlendFunctionImpl;
  self->getDepthWriteEnabled = &getDepthWriteEnabledImpl;
  self->setDepthWriteEnabled = &setDepthWriteEnabledImpl;
  self->build = &buildImpl;
}

static void
Ring3_DefaultMaterialBuilder_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring3_MaterialBuilder_getType(),
                              (Machine_InterfaceConstructCallback*)&Ring3_DefaultMaterialBuilder_implement_Ring3_MaterialBuilder);
}

MACHINE_DEFINE_CLASSTYPE(Ring3_DefaultMaterialBuilder /*type*/,
                         Machine_Object /*parentType*/,
                         NULL/*visit*/,
                         &Ring3_DefaultMaterialBuilder_construct/*construct*/,
                         NULL/*destructor*/,
                         NULL/*constructClass*/,
                         &Ring3_DefaultMaterialBuilder_implementInterfaces/*implementInterfaces*/)

void
Ring3_DefaultMaterialBuilder_construct
  (
    Ring3_DefaultMaterialBuilder* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->existingBlendFunction = Ring3_BlendFunction_OneMinusIncomingAlpha;
  self->incomingBlendFunction = Ring3_BlendFunction_IncomingAlpha;
  self->depthTestFunction = Ring3_DepthTestFunction_Always;
  self->depthWriteEnabled = false;
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_DefaultMaterialBuilder_getType());
}

Ring1_CheckReturn() Ring3_DefaultMaterialBuilder*
Ring3_DefaultMaterialBuilder_create
  (
  )
{
  Machine_ClassType* ty = Ring3_DefaultMaterialBuilder_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_DefaultMaterialBuilder* self = Ring1_cast(Ring3_DefaultMaterialBuilder *, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
