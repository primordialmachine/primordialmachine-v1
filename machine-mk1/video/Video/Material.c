/// @file Video/Material.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "./../Video/Material.h"

static void Machine_Material_visit(Machine_Material* self);

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Material, Machine_Object, &Machine_Material_visit, &Machine_Material_construct, NULL)

static void Machine_Material_visit(Machine_Material* self)
{/*Intentionally empty.*/}

void Machine_Material_construct(Machine_Material* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->existingBlendFunction = Machine_BlendFunction_OneMinusIncomingAlpha;
  self->incomingBlendFunction = Machine_BlendFunction_IncomingAlpha;
  self->depthTestFunction = Machine_DepthTestFunction_Always;
  self->depthWriteEnabled = false;
  Machine_setClassType((Machine_Object*)self, Machine_Material_getClassType());
}

Machine_Material* Machine_Material_create() {
  Machine_ClassType* ty = Machine_Material_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Material* self = (Machine_Material*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Material_assign(Machine_Material* self, const Machine_Material* other) {
  if (self != other) {
    self->depthTestFunction = other->depthTestFunction;
    self->depthWriteEnabled = other->depthWriteEnabled;
    self->existingBlendFunction = other->existingBlendFunction;
    self->incomingBlendFunction = other->incomingBlendFunction;
  }
}


void Machine_Material_setExistingBlendFunction(Machine_Material* self, Machine_BlendFunction existingBlendFunction) {
  self->existingBlendFunction = existingBlendFunction;
}

Machine_BlendFunction Machine_Material_getExistingBlendFunction(const Machine_Material* self) {
  return self->existingBlendFunction;
}


void Machine_Material_setIncomingBlendFunction(Machine_Material* self, Machine_BlendFunction incomingBlendFunction) {
  self->incomingBlendFunction = incomingBlendFunction;
}

Machine_BlendFunction Machine_Material_getIncomingBlendFunction(const Machine_Material* self) {
  return self->incomingBlendFunction;
}


void Machine_Material_setDepthTestFunction(Machine_Material* self, Machine_DepthTestFunction depthTestFunction) {
  self->depthTestFunction = depthTestFunction;
}

Machine_DepthTestFunction Machine_Material_getDepthTestFunction(const Machine_Material* self) {
  return self->depthTestFunction;
}


void Machine_Material_setDepthWriteEnabled(Machine_Material* self, bool depthWriteEnabled) {
  self->depthWriteEnabled = depthWriteEnabled;
}

bool Machine_Material_getDepthWriteEnabled(const Machine_Material* self) {
  return self->depthWriteEnabled;
}
