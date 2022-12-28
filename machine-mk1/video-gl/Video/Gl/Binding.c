/// @file Video/Gl/Binding.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Binding.h"


#include "Ring1/All/_Include.h"
#include "Video/Gl/ShaderProgram.h"


static void Machine_Gl_Binding_constructClass(Machine_Gl_Binding_Class* self);

static void Machine_Gl_Binding_visit(Machine_Gl_Binding* self);

static void Machine_Gl_Binding_destruct(Machine_Gl_Binding* self);

static void Machine_Gl_Binding_construct(Machine_Gl_Binding* self, size_t numberOfArguments, Ring2_Value const* arguments);

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_Binding, Machine_Binding, &Machine_Gl_Binding_visit,
                         &Machine_Gl_Binding_construct, &Machine_Gl_Binding_destruct,
                         &Machine_Gl_Binding_constructClass, NULL)

static void Machine_Gl_Binding_visit(Machine_Gl_Binding* self)
{/*Intentionally empty.*/}

static void Machine_Gl_Binding_destruct(Machine_Gl_Binding* self) {
  if (self->id) {
    glDeleteVertexArrays(1, &self->id);
    self->id = 0;
  }
}

static void bindVar(Machine_Gl_Binding const* self, size_t inputIndex, Ring3_GpuProgramInputDescriptor const* input) {
  Ring2_assertNotNull(input);
  Ring2_assert(input->kind == Ring3_GpuProgramInputKind_Variable, Ring1_Status_InvalidArgument);

  // Get the index of the corresponding vertex element.
  size_t vertexElementIndex = Machine_Binding_getVariableBinding((Machine_Binding*)self, input->name);
  if (vertexElementIndex == (size_t)-1) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "input %s not supported by program", Ring2_String_getBytes(input->name));
    return;
  }
  GLint attributeLocation = glGetAttribLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Ring2_String_getBytes(input->name));
  if (attributeLocation == -1) {
    Ring2_log(Ring2_LogFlags_ToWarnings, __FILE__, __LINE__, "input %s optimized out\n", Ring2_String_getBytes(input->name));
    return;
  }
  size_t vertexSize = Ring3_VertexDescriptor_getVertexSize(((Machine_Binding*)self)->vertexDescriptor);
  Ring3_VertexElementSemantics semantics = Ring3_VertexDescriptor_getElementSemantics(((Machine_Binding*)self)->vertexDescriptor, vertexElementIndex);
  size_t offset = Ring3_VertexDescriptor_getElementOffset(((Machine_Binding*)self)->vertexDescriptor, vertexElementIndex);
  Machine_UtilitiesGl_call(glEnableVertexAttribArray(inputIndex));
  Machine_UtilitiesGl_call(glBindBuffer(GL_ARRAY_BUFFER, *((GLuint*)Machine_VideoBuffer_getId(((Machine_Binding*)self)->buffer))));
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

static bool Machine_Binding_setVariableBindingImpl(Machine_Gl_Binding* self, Ring2_String* name, size_t index) {
  if (index < 0 || index > Ring2_Integer_Greatest || index == (size_t)(-1)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->name, name)) {
      Ring2_Value_setInteger(&node->value, index);
      node->isVariable = true;
      ((Machine_Binding*)self)->dirty = true;
      return true;
    }
    node = node->next;
  }
  ((Machine_Binding*)self)->dirty = true;
  Ring2_Value temporary;
  Ring2_Value_setInteger(&temporary, (Ring2_Integer)index);
  node = Machine_Binding_Node_createVariable(name, &temporary);
  node->next = ((Machine_Binding*)self)->nodes; ((Machine_Binding*)self)->nodes = node;
  return false;
}

static size_t Machine_Binding_getVariableBindingImpl(Machine_Gl_Binding const* self, Ring2_String* name) {
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->name, name) && node->isVariable) {
      return Ring2_Value_getInteger(&node->value);
    }
    node = node->next;
  }
  return (size_t)-1;
}

static void Machine_Binding_bindMatrix4Impl(Machine_Gl_Binding* self, Ring2_String* name, Ring3_Math_Matrix4x4f32 const* value) {
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);
  
  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Ring2_String_getBytes(name));
  if (location == -1) {
    return;
  }
  Machine_UtilitiesGl_call(glUniformMatrix4fv(location, 1, GL_TRUE, (GLfloat const*)value->e));
}

static void Machine_Binding_bindVector2Impl(Machine_Gl_Binding* self, Ring2_String* name, Ring3_Math_Vector2f32 const* value) {
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding *)self, name, &temporary2);
  
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->name, name) && node->isVariable == false) {
      Ring2_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    }
    else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = ((Machine_Binding*)self)->nodes; ((Machine_Binding*)self)->nodes = node;
  }

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Ring2_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Ring3_Math_Vector2f32_getX(value), Ring3_Math_Vector2f32_getY(value) };
  Machine_UtilitiesGl_call(glUniform2fv(location, 1, temporary));
}

static void Machine_Binding_bindVector3Impl(Machine_Gl_Binding* self, Ring2_String* name, Ring3_Math_Vector3f32 const* value) {
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);
  
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->name, name) && node->isVariable == false) {
      Ring2_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    }
    else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = ((Machine_Binding*)self)->nodes; ((Machine_Binding*)self)->nodes = node;
  }

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Ring2_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Ring3_Math_Vector3f32_getX(value), Ring3_Math_Vector3f32_getY(value), Ring3_Math_Vector3f32_getZ(value) };
  Machine_UtilitiesGl_call(glUniform3fv(location, 1, temporary));
}

static void Machine_Binding_bindVector4Impl(Machine_Binding* self, Ring2_String* name, Ring3_Math_Vector4f32 const* value) {
  Ring2_Value temporary2;
  Ring2_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);
  
  Machine_Binding_Node* node = self->nodes;
  while (node) {
    if (Ring2_String_isEqualTo(Ring2_Context_get(), node->name, name) && node->isVariable == false) {
      Ring2_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    }
    else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Ring2_Value temporary;
    Ring2_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = self->nodes; self->nodes = node;
  }

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(self->program))->programId, Ring2_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Ring3_Math_Vector4f32_getX(value), Ring3_Math_Vector4f32_getY(value), Ring3_Math_Vector4f32_getZ(value), Ring3_Math_Vector4f32_getW(value) };
  Machine_UtilitiesGl_call(glUniform4fv(location, 1, temporary));
}

static void Machine_Binding_bindSamplerImpl(Machine_Gl_Binding* self, Ring2_String* name, const size_t value) {
  Ring2_Value temporary2;
  Ring2_Value_setInteger(&temporary2, (Ring2_Integer)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Ring2_String_getBytes(name));
  if (location == -1) {
    return;
  }
  Machine_UtilitiesGl_call(glUniform1i(location, value));
}

static void Machine_Binding_activateImpl(Machine_Gl_Binding* self) {
  if (((Machine_Binding*)self)->dirty) {
    if (self->id) {
      glDeleteVertexArrays(1, &self->id);
      self->id = 0;
    }
    glGenVertexArrays(1, &self->id);
    glBindVertexArray(self->id);
    if (glGetError() != GL_NO_ERROR) {
      glDeleteVertexArrays(1, &self->id);
      self->id = 0;
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      Ring2_jump();
    }
    for (size_t i = 0, j = 0, n = Machine_ShaderProgram_getNumberOfInputs(((Machine_Binding*)self)->program); i < n;) {
      Ring3_GpuProgramInputDescriptor const* input = Machine_ShaderProgram_getInputAt(((Machine_Binding*)self)->program, i);
      if (input->kind == Ring3_GpuProgramInputKind_Variable) {
        bindVar(self, j, input);
        j++;
      }
      i++;
    }
    ((Machine_Binding*)self)->dirty = false;
  }
  else {
    glBindVertexArray(self->id);
  }
  // Bind the program.
  Machine_ShaderProgram *program = ((Machine_Binding*)self)->program;
  Machine_UtilitiesGl_call(glUseProgram(((Machine_Gl_ShaderProgram*)program)->programId));
  // @todo: Update the constant variables.
}

static void Machine_Gl_Binding_constructClass(Machine_Gl_Binding_Class* self) {
  ((Machine_Binding_Class*)self)->setVariableBinding = (Ring2_Boolean(*)(Machine_Binding*, Ring2_String*, size_t)) & Machine_Binding_setVariableBindingImpl;
  ((Machine_Binding_Class*)self)->getVariableBinding = (size_t(*)(Machine_Binding const*, Ring2_String*)) & Machine_Binding_getVariableBindingImpl;
  ((Machine_Binding_Class*)self)->bindMatrix4 = (void (*)(Machine_Binding*, Ring2_String*, Ring3_Math_Matrix4x4f32 const*)) & Machine_Binding_bindMatrix4Impl;
  ((Machine_Binding_Class*)self)->bindVector2 = (void (*)(Machine_Binding*, Ring2_String*, Ring3_Math_Vector2f32 const*)) & Machine_Binding_bindVector2Impl;
  ((Machine_Binding_Class*)self)->bindVector3 = (void (*)(Machine_Binding*, Ring2_String*, Ring3_Math_Vector3f32 const*)) & Machine_Binding_bindVector3Impl;
  ((Machine_Binding_Class*)self)->bindVector4 = (void (*)(Machine_Binding*, Ring2_String*, Ring3_Math_Vector4f32 const*)) & Machine_Binding_bindVector4Impl;
  ((Machine_Binding_Class*)self)->bindSampler = (void (*)(Machine_Binding*, Ring2_String*, size_t const)) & Machine_Binding_bindSamplerImpl;
  ((Machine_Binding_Class*)self)->activate = (void (*)(Machine_Binding*)) & Machine_Binding_activateImpl;
}

static void Machine_Gl_Binding_construct(Machine_Gl_Binding* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Binding_construct((Machine_Binding*)self, numberOfArguments, arguments);
  self->id = 0;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gl_Binding_getType());
}

Machine_Gl_Binding* Machine_Gl_Binding_create(Machine_ShaderProgram* program, Ring3_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  Machine_ClassType* ty = Machine_Gl_Binding_getType();
  size_t numberOfArguments = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)program);
  Ring2_Value_setObject(&arguments[1], (Machine_Object*)vertexDescriptor);
  Ring2_Value_setObject(&arguments[2], (Machine_Object*)buffer);
  Machine_Gl_Binding* self = (Machine_Gl_Binding*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}
