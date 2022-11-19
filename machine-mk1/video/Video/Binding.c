/// @file Video/Binding.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Binding.h"

#include "Ring1/Intrinsic.h"
#include "Video/Buffer.h"
#include "Video/ShaderProgram.h"
#include "Video/VertexDescriptor.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Binding_Node_visit(Machine_Binding_Node* self);

static void Machine_Binding_Node_construct(Machine_Binding_Node* self, size_t numberOfArguments,
                                           Ring2_Value const* arguments);

MACHINE_DEFINE_CLASSTYPE(Machine_Binding_Node, Machine_Object, Machine_Binding_Node_visit,
                         Machine_Binding_Node_construct, NULL, NULL, NULL)

static void Machine_Binding_Node_construct(Machine_Binding_Node* self, size_t numberOfArguments,
                                           Ring2_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  self->next = NULL;
  self->name = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 0);
  self->isVariable = Machine_Extensions_getBooleanArgument(numberOfArguments, arguments, 1);
  self->value = arguments[2];
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Binding_Node_getType());
}

static void Machine_Binding_Node_visit(Machine_Binding_Node* self) {
  if (self->next) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->next);
  }
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
  Ring2_Value_visit(Ring2_Gc_get(), &self->value);
}

Machine_Binding_Node* Machine_Binding_Node_create(Ring2_String* name, Ring2_Boolean isVariable,
                                                  Ring2_Value const* value) {
  size_t numberOfArguments = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setString(&arguments[0], name);
  Ring2_Value_setBoolean(&arguments[1], isVariable);
  arguments[2] = *value;
  Machine_ClassType* ty = Machine_Binding_Node_getType();
  Machine_Binding_Node* self
      = (Machine_Binding_Node*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}

Machine_Binding_Node* Machine_Binding_Node_createVariable(Ring2_String* name,
                                                          Ring2_Value const* value) {
  return Machine_Binding_Node_create(name, true, value);
}

Machine_Binding_Node* Machine_Binding_Node_createConstant(Ring2_String* name,
                                                          Ring2_Value const* value) {
  return Machine_Binding_Node_create(name, false, value);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Binding_constructClass(Machine_Binding_Class* self);

static void Machine_Binding_destruct(Machine_Binding* self);

static void Machine_Binding_visit(Machine_Binding* self);

static void Machine_Binding_addUpdateConstantImpl(Machine_Binding* self, Ring2_String* name,
                                                  Ring2_Value const* value);

static void Machine_Binding_destruct(Machine_Binding* self) { /*Intentionally empty.*/
}

static void Machine_Binding_visit(Machine_Binding* self) {
  if (self->nodes) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->nodes);
  }
  if (self->program) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->program);
  }
  if (self->vertexDescriptor) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->vertexDescriptor);
  }
  if (self->buffer) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->buffer);
  }
}

void Machine_Binding_construct(Machine_Binding* self, size_t numberOfArguments,
                               Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->dirty = true;
  self->program = (Machine_ShaderProgram*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 0, Machine_ShaderProgram_getType());
  self->vertexDescriptor = (Machine_VertexDescriptor*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 1, Machine_VertexDescriptor_getType());
  self->buffer = (Machine_VideoBuffer*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 2, Machine_VideoBuffer_getType());
  self->nodes = NULL;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Binding_getType());
}

static void Machine_Binding_addUpdateConstantImpl(Machine_Binding* self, Ring2_String* name,
                                                  Ring2_Value const* value) {
  Machine_Binding_Node* node = self->nodes;
  while (NULL != node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->name, name)) {
      break;
    }
    node = node->next;
  }
  if (!node) {
    node = Machine_Binding_Node_createConstant(name, value);
    node->next = self->nodes;
    self->nodes = node;
  } else {
    node->name = name;
    node->value = *value;
    node->isVariable = false;
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_Binding, Machine_Object, &Machine_Binding_visit,
                         &Machine_Binding_construct, &Machine_Binding_destruct,
                         &Machine_Binding_constructClass, NULL)

static void Machine_Binding_constructClass(Machine_Binding_Class* self) {
  self->addUpdateConstant = &Machine_Binding_addUpdateConstantImpl;
}

Ring2_Boolean Machine_Binding_setVariableBinding(Machine_Binding* self, Ring2_String* name,
                                                 size_t index) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Binding, setVariableBinding, name, index);
}

size_t Machine_Binding_getVariableBinding(Machine_Binding const* self, Ring2_String* name) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Binding, getVariableBinding, name);
}

void Machine_Binding_activate(Machine_Binding* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Binding, activate);
}

void Machine_Binding_addUpdateConstant(Machine_Binding* self, Ring2_String* name,
                                       Ring2_Value const* value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Binding, addUpdateConstant, name, value);
}

void Machine_Binding_bindMatrix4(Machine_Binding* self, Ring2_String* name,
                                 Ring3_Math_Matrix4 const* value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Binding, bindMatrix4, name, value);
}

void Machine_Binding_bindVector2(Machine_Binding* self, Ring2_String* name,
                                 Ring3_Math_Vector2 const* value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Binding, bindVector2, name, value);
}

void Machine_Binding_bindVector3(Machine_Binding* self, Ring2_String* name,
                                 Ring3_Math_Vector3 const* value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Binding, bindVector3, name, value);
}

void Machine_Binding_bindVector4(Machine_Binding* self, Ring2_String* name,
                                 Ring3_Math_Vector4 const* value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Binding, bindVector4, name, value);
}

void Machine_Binding_bindSampler(Machine_Binding* self, Ring2_String* name, const size_t value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Binding, bindSampler, name, value);
}
