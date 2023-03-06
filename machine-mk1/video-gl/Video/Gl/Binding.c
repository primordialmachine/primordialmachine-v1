/// @file Video/Gl/Binding.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Binding.h"


#include "Ring1/All/_Include.h"
#include "Video/Gl/ShaderProgram.h"


static void
Machine_Gl_Binding_constructClass
  (
    Machine_Gl_Binding_Class* self
  );

static void
Machine_Gl_Binding_visit
  (
    Machine_Gl_Binding* self
  );

static void
Machine_Gl_Binding_destruct
  (
    Machine_Gl_Binding* self
  );

static void
Machine_Gl_Binding_construct
  (
    Machine_Gl_Binding* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_Binding,
                         Ring3_Binding,
                         &Machine_Gl_Binding_visit,
                         &Machine_Gl_Binding_construct,
                         &Machine_Gl_Binding_destruct,
                         &Machine_Gl_Binding_constructClass,
                         NULL)

static void
Machine_Gl_Binding_visit
  (
    Machine_Gl_Binding* self
  )
{/*Intentionally empty.*/}

static void
Machine_Gl_Binding_destruct
  (
    Machine_Gl_Binding* self
  )
{
  if (self->id) {
    glDeleteVertexArrays(1, &self->id);
    self->id = 0;
  }
}

static Ring3_Binding_Node *
getNode
  (
    Machine_Gl_Binding const* self,
    Ring2_String *targetName,
    bool isVariable
  )
{
  Ring3_Binding_Node* node = ((Ring3_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->targetName, targetName) &&
        node->isVariable == isVariable) {
      return node;
    } else {
      node = node->next;
    }
  }
  return NULL;
}

static GLuint
getProgramId
  (
    Machine_Gl_Binding const* self
  )
{
  Machine_Gl_ShaderProgram* program = (Machine_Gl_ShaderProgram*)((Ring3_Binding*)self)->program;
  return program->programId;
}

static void
uploadConstant
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    Ring2_Value const* value
  )
{
  GLint location = glGetUniformLocation(getProgramId(self), Ring2_String_getBytes(targetName));
  if (location == -1) {
    return;
  }
  switch (targetType) {
  case Ring3_GpuProgramLocationType_Vector2Constant: {
    if (!Ring2_Value_isObject(value)) {
      return;
    }
    Machine_Object* objectValue = Ring2_Value_getObject(value);
    if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(objectValue),
                                  (Machine_Type*)Ring3_Math_Vector2f32_getType())) {
      return;
    }
    Ring3_Math_Vector2f32* vectorValue = (Ring3_Math_Vector2f32*)objectValue;
    const GLfloat temporary[] = { Ring3_Math_Vector2f32_getX(vectorValue),
                                  Ring3_Math_Vector2f32_getY(vectorValue) };
    Machine_UtilitiesGl_call(glUniform2fv(location, 1, temporary));
  } break;
  case Ring3_GpuProgramLocationType_Vector3Constant: {
    if (!Ring2_Value_isObject(value)) {
      return;
    }
    Machine_Object* objectValue = Ring2_Value_getObject(value);
    if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(objectValue),
                                  (Machine_Type*)Ring3_Math_Vector3f32_getType())) {
      return;
    }
    Ring3_Math_Vector3f32* vectorValue = (Ring3_Math_Vector3f32*)objectValue;
    const GLfloat temporary[] = { Ring3_Math_Vector3f32_getX(vectorValue),
                                  Ring3_Math_Vector3f32_getY(vectorValue),
                                  Ring3_Math_Vector3f32_getZ(vectorValue) };
    Machine_UtilitiesGl_call(glUniform3fv(location, 1, temporary));
  } break;
  case Ring3_GpuProgramLocationType_Vector4Constant: {
    if (!Ring2_Value_isObject(value)) {
      return;
    }
    Machine_Object* objectValue = Ring2_Value_getObject(value);
    if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(objectValue),
                                  (Machine_Type*)Ring3_Math_Vector4f32_getType())) {
      return;
    }
    Ring3_Math_Vector4f32* vectorValue = (Ring3_Math_Vector4f32*)objectValue;
    const GLfloat temporary[] = { Ring3_Math_Vector4f32_getX(vectorValue),
                                  Ring3_Math_Vector4f32_getY(vectorValue),
                                  Ring3_Math_Vector4f32_getZ(vectorValue),
                                  Ring3_Math_Vector4f32_getW(vectorValue) };
    Machine_UtilitiesGl_call(glUniform4fv(location, 1, temporary));
  } break;
  case Ring3_GpuProgramLocationType_Matrix4x4Constant: {
    if (!Ring2_Value_isObject(value)) {
      return;
    }
    Machine_Object* objectValue = Ring2_Value_getObject(value);
    if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(objectValue),
                                  (Machine_Type*)Ring3_Math_Matrix4x4f32_getType())) {
      return;
    }
    Ring3_Math_Matrix4x4f32* matrixValue = (Ring3_Math_Matrix4x4f32*)objectValue;
    Machine_UtilitiesGl_call(glUniformMatrix4fv(location, 1, GL_TRUE,
                                                (GLfloat const*)Ring3_Math_Matrix4x4f32_getData(matrixValue)));
  } break;
  case Ring3_GpuProgramLocationType_SamplerConstant: {
    if (!Ring2_Value_isInteger(value)) {
      return;
    }
    Ring2_Integer integerValue = Ring2_Value_getInteger(value);
    Machine_UtilitiesGl_call(glUniform1i(location, integerValue));
  } break;
  default: {
    return;
  } break;
  };
}

static void
uploadVariable
  (
    Machine_Gl_Binding const* self,
    size_t inputIndex,
    Ring3_GpuProgramInputDescriptor const* input
  )
{
  Ring2_assertNotNull(input);
  Ring2_assert(input->kind == Ring3_GpuProgramInputKind_Variable, Ring1_Status_InvalidArgument);

  // Get the index of the corresponding vertex element.
  size_t vertexElementIndex = Ring3_Binding_getVariableBinding((Ring3_Binding*)self, input->name);
  if (vertexElementIndex == (size_t)-1) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "input %s not supported by program", Ring2_String_getBytes(input->name));
    return;
  }
  GLint attributeLocation = glGetAttribLocation(getProgramId(self), Ring2_String_getBytes(input->name));
  if (attributeLocation == -1) {
    Ring2_log(Ring2_LogFlags_ToWarnings, __FILE__, __LINE__, "input %s optimized out\n", Ring2_String_getBytes(input->name));
    return;
  }
  size_t vertexSize = Ring3_VertexDescriptor_getVertexSize(((Ring3_Binding*)self)->vertexDescriptor);
  Ring3_VertexElementSemantics semantics = Ring3_VertexDescriptor_getElementSemantics(((Ring3_Binding*)self)->vertexDescriptor, vertexElementIndex);
  size_t offset = Ring3_VertexDescriptor_getElementOffset(((Ring3_Binding*)self)->vertexDescriptor, vertexElementIndex);
  Machine_UtilitiesGl_call(glEnableVertexAttribArray(inputIndex));
  Machine_UtilitiesGl_call(glBindBuffer(GL_ARRAY_BUFFER, *((GLuint*)Ring3_GpuBuffer_getId(((Ring3_Binding*)self)->buffer))));
  switch (semantics) {
  case Ring3_VertexElementSemantics_XfYf:
    Machine_UtilitiesGl_call(glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset));
    break;
  case Ring3_VertexElementSemantics_RfGfBf:
    Machine_UtilitiesGl_call(glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset));
    break;
  case Ring3_VertexElementSemantics_UfVf:
    Machine_UtilitiesGl_call(glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset));
    break;
  };
}

static bool
Ring3_Binding_setVariableBindingImpl
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    Ring3_GpuProgramLocationType targetType,
    size_t index
  )
{
  if (index < 0 || index > Ring2_Integer_Greatest || index == (size_t)(-1)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring3_Binding_Node* node = ((Ring3_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->targetName, targetName)) {
      Ring2_Value_setInteger(&node->value, index);
      node->isVariable = true;
      node->targetType = targetType;
      ((Ring3_Binding*)self)->dirty = true;
      return true;
    }
    node = node->next;
  }
  ((Ring3_Binding*)self)->dirty = true;
  Ring2_Value temporary;
  Ring2_Value_setInteger(&temporary, (Ring2_Integer)index);
  node = Ring3_Binding_Node_createVariable(targetName, targetType, &temporary);
  node->next = ((Ring3_Binding*)self)->nodes; ((Ring3_Binding*)self)->nodes = node;
  return false;
}

static size_t
Ring3_Binding_getVariableBindingImpl
  (
    Machine_Gl_Binding const* self,
    Ring2_String* targetName
  )
{
  Ring3_Binding_Node* node = ((Ring3_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->targetName, targetName) && node->isVariable) {
      return Ring2_Value_getInteger(&node->value);
    }
    node = node->next;
  }
  return (size_t)-1;
}

static void
Ring3_Binding_bindMatrix4Impl
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Matrix4x4f32 const* value
  )
{
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Ring3_Binding_addUpdateConstant((Ring3_Binding*)self, targetName, Ring3_GpuProgramLocationType_Matrix4x4Constant, &temporary2);
  ((Ring3_Binding*)self)->dirty = true;
}

static void
Ring3_Binding_bindVector2Impl
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector2f32 const* value
  )
{
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Ring3_Binding_addUpdateConstant((Ring3_Binding *)self, targetName, Ring3_GpuProgramLocationType_Vector2Constant, &temporary2);
  ((Ring3_Binding*)self)->dirty = true;
}

static void
Ring3_Binding_bindVector3Impl
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector3f32 const* value
  )
{
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Ring3_Binding_addUpdateConstant((Ring3_Binding*)self, targetName, Ring3_GpuProgramLocationType_Vector3Constant, &temporary2);
  ((Ring3_Binding*)self)->dirty = true;
}

static void
Ring3_Binding_bindVector4Impl
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    Ring3_Math_Vector4f32 const* value
  )
{
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Ring3_Binding_addUpdateConstant((Ring3_Binding*)self, targetName, Ring3_GpuProgramLocationType_Vector4Constant, &temporary2);
  ((Ring3_Binding*)self)->dirty = true;
}

static void
Ring3_Binding_bindSamplerImpl
  (
    Machine_Gl_Binding* self,
    Ring2_String* targetName,
    const size_t value
  )
{
  Ring2_Value temporary2;
  Ring2_Value_setInteger(&temporary2, (Ring2_Integer)value);
  Ring3_Binding_addUpdateConstant((Ring3_Binding*)self, targetName, Ring3_GpuProgramLocationType_SamplerConstant, &temporary2);
  ((Ring3_Binding*)self)->dirty = true;
}

static void
Ring3_Binding_activateImpl
  (
    Machine_Gl_Binding* self
  )
{
  // We have to bind the GPU program first, otherwiise glUniform* calls fail.
  Machine_UtilitiesGl_call(glUseProgram(getProgramId(self)));
  if (((Ring3_Binding*)self)->dirty) {
    if (!self->id) {
      glGenVertexArrays(1, &self->id);
    }
    glBindVertexArray(self->id);
    if (glGetError() != GL_NO_ERROR) {
      glDeleteVertexArrays(1, &self->id);
      self->id = 0;
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    // Bind variables.
    for (int64_t i = 0, j = 0, n = Ring3_GpuProgram_getNumberOfInputs(((Ring3_Binding*)self)->program); i < n;) {
      Ring3_GpuProgramInputDescriptor const* input = Ring3_GpuProgram_getInputAt(((Ring3_Binding*)self)->program, i);
      if (input->kind == Ring3_GpuProgramInputKind_Variable) {
        uploadVariable(self, j, input);
        j++;
      }
      i++;
    }
    // Bind constants.
    for (Ring3_Binding_Node* node = ((Ring3_Binding*)self)->nodes; NULL != node; node = node->next) {
      if (!node->isVariable) {
        uploadConstant(self, node->targetName, node->targetType, &node->value);
      }
    }
    ((Ring3_Binding*)self)->dirty = false;
  } else {
    glBindVertexArray(self->id);
  }

}

static void
Machine_Gl_Binding_constructClass
  (
    Machine_Gl_Binding_Class* self
  )
{
  ((Ring3_Binding_Class*)self)->setVariableBinding = (Ring2_Boolean(*)(Ring3_Binding*, Ring2_String*, Ring3_GpuProgramLocationType, size_t)) & Ring3_Binding_setVariableBindingImpl;
  ((Ring3_Binding_Class*)self)->getVariableBinding = (size_t(*)(Ring3_Binding const*, Ring2_String*)) & Ring3_Binding_getVariableBindingImpl;
  ((Ring3_Binding_Class*)self)->bindMatrix4 = (void (*)(Ring3_Binding*, Ring2_String*, Ring3_Math_Matrix4x4f32 const*)) & Ring3_Binding_bindMatrix4Impl;
  ((Ring3_Binding_Class*)self)->bindVector2 = (void (*)(Ring3_Binding*, Ring2_String*, Ring3_Math_Vector2f32 const*)) & Ring3_Binding_bindVector2Impl;
  ((Ring3_Binding_Class*)self)->bindVector3 = (void (*)(Ring3_Binding*, Ring2_String*, Ring3_Math_Vector3f32 const*)) & Ring3_Binding_bindVector3Impl;
  ((Ring3_Binding_Class*)self)->bindVector4 = (void (*)(Ring3_Binding*, Ring2_String*, Ring3_Math_Vector4f32 const*)) & Ring3_Binding_bindVector4Impl;
  ((Ring3_Binding_Class*)self)->bindSampler = (void (*)(Ring3_Binding*, Ring2_String*, size_t const)) & Ring3_Binding_bindSamplerImpl;
  ((Ring3_Binding_Class*)self)->activate = (void (*)(Ring3_Binding*)) & Ring3_Binding_activateImpl;
}

static void
Machine_Gl_Binding_construct
  (
    Machine_Gl_Binding* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Binding_construct((Ring3_Binding*)self, numberOfArguments, arguments);
  self->id = 0;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gl_Binding_getType());
}

Machine_Gl_Binding*
Machine_Gl_Binding_create
  (
    Ring3_GpuProgram* program,
    Ring3_VertexDescriptor* vertexDescriptor,
    Ring3_GpuBuffer* buffer
  )
{
  Machine_ClassType* ty = Machine_Gl_Binding_getType();
  size_t numberOfArguments = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)program);
  Ring2_Value_setObject(&arguments[1], (Machine_Object*)vertexDescriptor);
  Ring2_Value_setObject(&arguments[2], (Machine_Object*)buffer);
  Machine_Gl_Binding* self = (Machine_Gl_Binding*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}
