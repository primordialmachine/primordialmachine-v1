/// @file Ring3/Visuals/GpuProgramBinding.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/GpuProgramBinding.h"

#include "Ring3/Visuals/GpuBuffer.h"
#include "Ring3/Visuals/GpuProgram.h"
#include "Ring3/Visuals/VertexDescriptor.h"
#undef RING3_VISUALS_PRIVATE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Ring3_Binding_Node_visit
  (
    Ring3_Binding_Node* self
  );

static void
Ring3_Binding_Node_construct
  (
    Ring3_Binding_Node* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_Binding_Node,
                         Machine_Object,
                         Ring3_Binding_Node_visit,
                         Ring3_Binding_Node_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Ring3_Binding_Node_construct
  (
    Ring3_Binding_Node* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  self->next = NULL;
  self->targetName = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  self->isVariable = Ring2_CallArguments_getBooleanArgument(numberOfArguments, arguments, 1);
  self->targetType = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 2);
  self->value = arguments[3];
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Binding_Node_getType());
}

static void
Ring3_Binding_Node_visit
  (
    Ring3_Binding_Node* self
  )
{
  if (self->next) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->next);
  }
  if (self->targetName) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->targetName);
  }
  Ring2_Value_visit(Ring2_Gc_get(), &self->value);
}

Ring3_Binding_Node*
Ring3_Binding_Node_create
  (
    Ring2_String* targetName,
    Ring2_Boolean isVariable,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  )
{
  size_t numberOfArguments = 4;
  Ring2_Value arguments[4];
  Ring2_Value_setString(&arguments[0], targetName);
  Ring2_Value_setBoolean(&arguments[1], isVariable);
  Ring2_Value_setInteger(&arguments[2], targetType);
  arguments[3] = *value;
  Machine_ClassType* ty = Ring3_Binding_Node_getType();
  Ring3_Binding_Node* self = (Ring3_Binding_Node*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}

Ring3_Binding_Node*
Ring3_Binding_Node_createVariable
  (
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  )
{ return Ring3_Binding_Node_create(targetName, true, targetType, value); }

Ring3_Binding_Node*
Ring3_Binding_Node_createConstant
  (
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  )
{ return Ring3_Binding_Node_create(targetName, false, targetType, value); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Ring3_Binding_constructClass
  (
    Ring3_Binding_Class* self
  );

static void
Ring3_Binding_destruct
  (
    Ring3_Binding* self
  );

static void
Ring3_Binding_visit
  (
    Ring3_Binding* self
  );

static void
Ring3_Binding_addUpdateConstantImpl
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  );

static void
Ring3_Binding_destruct
  (
    Ring3_Binding* self
  )
{/*Intentionally empty.*/}

static void
Ring3_Binding_visit
  (
    Ring3_Binding* self
  )
{
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

void
Ring3_Binding_construct
  (
    Ring3_Binding* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->dirty = true;
  self->program = (Ring3_GpuProgram*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                           arguments,
                                                                           0,
                                                                           Ring3_GpuProgram_getType());
  self->vertexDescriptor = (Ring3_VertexDescriptor*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                                          arguments,
                                                                                          1,
                                                                                          Ring3_VertexDescriptor_getType());
  self->buffer = (Ring3_GpuBuffer*)Ring2_CallArguments_getObjectArgument(numberOfArguments,
                                                                         arguments,
                                                                         2,
                                                                         Ring3_GpuBuffer_getType());
  self->nodes = NULL;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Binding_getType());
}

static void
Ring3_Binding_addUpdateConstantImpl
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  )
{
  Ring3_Binding_Node* node = self->nodes;
  while (NULL != node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->targetName, targetName)) {
      break;
    }
    node = node->next;
  }
  if (!node) {
    node = Ring3_Binding_Node_createConstant(targetName, targetType, value);
    node->next = self->nodes;
    self->nodes = node;
  } else {
    node->targetName = targetName;
    node->targetType = targetType;
    node->value = *value;
    node->isVariable = false;
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Binding,
                         Machine_Object,
                         &Ring3_Binding_visit,
                         &Ring3_Binding_construct,
                         &Ring3_Binding_destruct,
                         &Ring3_Binding_constructClass,
                         NULL)

static void
Ring3_Binding_constructClass
  (
    Ring3_Binding_Class* self
  )
{
  self->addUpdateConstant = &Ring3_Binding_addUpdateConstantImpl;
}

Ring2_Boolean
Ring3_Binding_setVariableBinding
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    size_t index
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_Binding, setVariableBinding, targetName, targetType, index); }

size_t
Ring3_Binding_getVariableBinding
  (
    Ring3_Binding const* self,
    Ring2_String* name
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_Binding, getVariableBinding, name); }

void
Ring3_Binding_activate
  (
    Ring3_Binding* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Ring3_Binding, activate); }

void
Ring3_Binding_addUpdateConstant
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Binding, addUpdateConstant, targetName, targetType, value); }

void
Ring3_Binding_bindMatrix4
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Matrix4x4f32 const* value
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Binding, bindMatrix4, targetName, value); }

void
Ring3_Binding_bindVector2
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector2f32 const* value
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Binding, bindVector2, targetName, value); }

void
Ring3_Binding_bindVector3
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector3f32 const* value
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Binding, bindVector3, targetName, value); }

void
Ring3_Binding_bindVector4
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector4f32 const* value
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Binding, bindVector4, targetName, value); }

void
Ring3_Binding_bindSampler
  (
    Ring3_Binding* self,
    Ring2_String* targetName,
    const size_t value
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Binding, bindSampler, targetName, value); }
