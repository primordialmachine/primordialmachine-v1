/// @file Video/Binding.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "./../Video/Binding.h"



#include "./../Video/Buffer.h"
#include "./../Video/ShaderProgram.h"
#include "./../Video/VertexDescriptor.h"



static void Machine_Binding_Node_visit(Machine_Binding_Node* self);

static void Machine_Binding_Node_construct(Machine_Binding_Node* self, size_t numberOfArguments, const Machine_Value* arguments);

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Binding_Node, Machine_Object, Machine_Binding_Node_visit, Machine_Binding_Node_construct, NULL)

static void Machine_Binding_Node_construct(Machine_Binding_Node* self, size_t numberOfArguments, const Machine_Value* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  self->next = NULL;
  self->name = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 0);
  self->isVariable = Machine_Extensions_getBooleanArgument(numberOfArguments, arguments, 1);
  self->value = arguments[2];
  Machine_setClassType((Machine_Object*)self, Machine_Binding_Node_getClassType());
}

static void Machine_Binding_Node_visit(Machine_Binding_Node* self) {
  if (self->next) {
    Machine_visit(self->next);
  }
  if (self->name) {
    Machine_visit(self->name);
  }
  Machine_Value_visit(&self->value);
}

Machine_Binding_Node* Machine_Binding_Node_create(Machine_String* name, size_t index) {
  size_t numberOfArguments = 3;
  Machine_Value arguments[3];
  Machine_Value_setString(&arguments[0], name);
  Machine_Value_setBoolean(&arguments[1], true);
  Machine_Value_setInteger(&arguments[2], index);
  if (index < 0 || index > Machine_Integer_Greatest) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_ClassType* ty = Machine_Binding_Node_getClassType();
  Machine_Binding_Node* self = (Machine_Binding_Node*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}

Machine_Binding_Node* Machine_Binding_Node_createConstant(Machine_String* name, Machine_Value const* value) {
  size_t numberOfArguments = 3;
  Machine_Value arguments[3];
  Machine_Value_setString(&arguments[0], name);
  Machine_Value_setBoolean(&arguments[1], false);
  arguments[2] = *value;
  Machine_ClassType* ty = Machine_Binding_Node_getClassType();
  Machine_Binding_Node* self = (Machine_Binding_Node*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}

static void Machine_Binding_destruct(Machine_Binding* self)
{}

static void Machine_Binding_visit(Machine_Binding* self) {
  if (self->nodes) {
    Machine_visit(self->nodes);
  }
  if (self->program) {
    Machine_visit(self->program);
  }
  if (self->vertexDescriptor) {
    Machine_visit(self->vertexDescriptor);
  }
  if (self->buffer) {
    Machine_visit(self->buffer);
  }
}

void Machine_Binding_construct(Machine_Binding* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->dirty = true;
  self->program = (Machine_ShaderProgram*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 0, Machine_ShaderProgram_getClassType());
  self->vertexDescriptor = (Machine_VertexDescriptor*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 1, Machine_VertexDescriptor_getClassType());
  self->buffer = (Machine_VideoBuffer*)Machine_Extensions_getObjectArgument(numberOfArguments, arguments, 2, Machine_VideoBuffer_getClassType());
  self->nodes = NULL;
  Machine_setClassType((Machine_Object*)self, Machine_Binding_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Binding, Machine_Object, &Machine_Binding_visit, &Machine_Binding_construct, &Machine_Binding_destruct)

bool Machine_Binding_setVariableBinding(Machine_Binding* self, Machine_String* name, size_t index) {
  return self->setVariableBinding(self, name, index);
}

size_t Machine_Binding_getVariableBinding(Machine_Binding const* self, Machine_String* name) {
  return self->getVariableBinding(self, name);
}

void Machine_Binding_activate(Machine_Binding* self) {
  self->activate(self);
}

void Machine_Binding_bindMatrix4(Machine_Binding* self, Machine_String* name, const Machine_Math_Matrix4* value) {
  self->bindMatrix4(self, name, value);
}

void Machine_Binding_bindVector2(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector2* value) {
  self->bindVector2(self, name, value);
}

void Machine_Binding_bindVector3(Machine_Binding* self, Machine_String* name, Machine_Math_Vector3 const* value) {
  self->bindVector3(self, name, value);
}

void Machine_Binding_bindVector4(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector4* value) {
  self->bindVector4(self, name, value);
}

void Machine_Binding_bindSampler(Machine_Binding* self, Machine_String* name, const size_t value) {
  self->bindSampler(self, name, value);
}
