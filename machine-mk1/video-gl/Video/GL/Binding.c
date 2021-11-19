#include "./../GL/Binding.h"



#include "./../GL/ShaderProgram.h"



static void Machine_Gl_Binding_constructClass(Machine_Gl_Binding_Class* self);

static void Machine_Gl_Binding_visit(Machine_Gl_Binding* self);

static void Machine_Gl_Binding_destruct(Machine_Gl_Binding* self);

static void Machine_Gl_Binding_construct(Machine_Gl_Binding* self, size_t numberOfArguments, const Machine_Value* arguments);

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_Binding, Machine_Binding, &Machine_Gl_Binding_visit, &Machine_Gl_Binding_construct, &Machine_Gl_Binding_destruct, &Machine_Gl_Binding_constructClass)

static void Machine_Gl_Binding_visit(Machine_Gl_Binding* self)
{/*Intentionally empty.*/}

static void Machine_Gl_Binding_destruct(Machine_Gl_Binding* self) {
  if (self->id) {
    glDeleteVertexArrays(1, &self->id);
    self->id = 0;
  }
}

static void bindVar(Machine_Gl_Binding const* self, size_t inputIndex, Machine_ProgramInput const* input) {
  MACHINE_ASSERT_NOTNULL(input);
  MACHINE_ASSERT(input->kind == Machine_ProgramInputKind_Variable, Machine_Status_InvalidArgument);

  // Get the index of the corresponding vertex element.
  size_t vertexElementIndex = Machine_Binding_getVariableBinding((Machine_Binding*)self, input->name);
  if (vertexElementIndex == (size_t)-1) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "input %s not supported by program", Machine_String_getBytes(input->name));
    return;
  }
  GLint attributeLocation = glGetAttribLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Machine_String_getBytes(input->name));
  if (attributeLocation == -1) {
    Machine_log(Machine_LogFlags_ToWarnings, __FILE__, __LINE__, "input %s optimized out\n", Machine_String_getBytes(input->name));
    return;
  }
  size_t vertexSize = Machine_VertexDescriptor_getVertexSize(((Machine_Binding*)self)->vertexDescriptor);
  Machine_VertexElementSemantics semantics = Machine_VertexDescriptor_getElementSemantics(((Machine_Binding*)self)->vertexDescriptor, vertexElementIndex);
  size_t offset = Machine_VertexDescriptor_getElementOffset(((Machine_Binding*)self)->vertexDescriptor, vertexElementIndex);
  Machine_UtilitiesGl_call(glEnableVertexAttribArray(inputIndex));
  Machine_UtilitiesGl_call(glBindBuffer(GL_ARRAY_BUFFER, *((GLuint*)Machine_VideoBuffer_getId(((Machine_Binding*)self)->buffer))));
  switch (semantics) {
  case Machine_VertexElementSemantics_XfYf:
    Machine_UtilitiesGl_call(glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset));
    break;
  case Machine_VertexElementSemantics_RfGfBf:
    Machine_UtilitiesGl_call(glVertexAttribPointer(attributeLocation, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset));
    break;
  case Machine_VertexElementSemantics_UfVf:
    Machine_UtilitiesGl_call(glVertexAttribPointer(attributeLocation, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)offset));
    break;
  };
}

static bool Machine_Binding_setVariableBindingImpl(Machine_Gl_Binding* self, Machine_String* name, size_t index) {
  if (index < 0 || index > Machine_Integer_Greatest || index == (size_t)(-1)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name)) {
      Machine_Value_setInteger(&node->value, index);
      node->isVariable = true;
      ((Machine_Binding*)self)->dirty = true;
      return true;
    }
    node = node->next;
  }
  ((Machine_Binding*)self)->dirty = true;
  Machine_Value temporary;
  Machine_Value_setInteger(&temporary, (Machine_Integer)index);
  node = Machine_Binding_Node_createVariable(name, &temporary);
  node->next = ((Machine_Binding*)self)->nodes; ((Machine_Binding*)self)->nodes = node;
  return false;
}

static size_t Machine_Binding_getVariableBindingImpl(Machine_Gl_Binding const* self, Machine_String* name) {
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name) && node->isVariable) {
      return Machine_Value_getInteger(&node->value);
    }
    node = node->next;
  }
  return (size_t)-1;
}

static void Machine_Binding_bindMatrix4Impl(Machine_Gl_Binding* self, Machine_String* name, const Machine_Math_Matrix4* value) {
  Machine_Value temporary2;
  Machine_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);
  
  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  Machine_UtilitiesGl_call(glUniformMatrix4fv(location, 1, GL_TRUE, (GLfloat const*)value->e));
}

static void Machine_Binding_bindVector2Impl(Machine_Gl_Binding* self, Machine_String* name, const Machine_Math_Vector2* value) {
  Machine_Value temporary2;
  Machine_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding *)self, name, &temporary2);
  
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name) && node->isVariable == false) {
      Machine_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    }
    else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = ((Machine_Binding*)self)->nodes; ((Machine_Binding*)self)->nodes = node;
  }

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Machine_Math_Vector2_getX(value), Machine_Math_Vector2_getY(value) };
  Machine_UtilitiesGl_call(glUniform2fv(location, 1, temporary));
}

static void Machine_Binding_bindVector3Impl(Machine_Gl_Binding* self, Machine_String* name, Machine_Math_Vector3 const* value) {
  Machine_Value temporary2;
  Machine_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);
  
  Machine_Binding_Node* node = ((Machine_Binding*)self)->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name) && node->isVariable == false) {
      Machine_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    }
    else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = ((Machine_Binding*)self)->nodes; ((Machine_Binding*)self)->nodes = node;
  }

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Machine_Math_Vector3_getX(value), Machine_Math_Vector3_getY(value), Machine_Math_Vector3_getZ(value) };
  Machine_UtilitiesGl_call(glUniform3fv(location, 1, temporary));
}

static void Machine_Binding_bindVector4Impl(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector4* value) {
  Machine_Value temporary2;
  Machine_Value_setObject(&temporary2, (Machine_Object*)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);
  
  Machine_Binding_Node* node = self->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name) && node->isVariable == false) {
      Machine_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    }
    else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = self->nodes; self->nodes = node;
  }

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(self->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Machine_Math_Vector4_getX(value), Machine_Math_Vector4_getY(value), Machine_Math_Vector4_getZ(value), Machine_Math_Vector4_getW(value) };
  Machine_UtilitiesGl_call(glUniform4fv(location, 1, temporary));
}

static void Machine_Binding_bindSamplerImpl(Machine_Gl_Binding* self, Machine_String* name, const size_t value) {
  Machine_Value temporary2;
  Machine_Value_setInteger(&temporary2, (Machine_Integer)value);
  Machine_Binding_addUpdateConstant((Machine_Binding*)self, name, &temporary2);

  GLint location = glGetUniformLocation(((Machine_Gl_ShaderProgram*)(((Machine_Binding*)self)->program))->programId, Machine_String_getBytes(name));
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
      Machine_setStatus(Machine_Status_InvalidArgument);
      Machine_jump();
    }
    for (size_t i = 0, j = 0, n = Machine_ShaderProgram_getNumberOfInputs(((Machine_Binding*)self)->program); i < n;) {
      Machine_ProgramInput const* input = Machine_ShaderProgram_getInputAt(((Machine_Binding*)self)->program, i);
      if (input->kind == Machine_ProgramInputKind_Variable) {
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
  ((Machine_Binding_Class*)self)->setVariableBinding = (Machine_Boolean(*)(Machine_Binding*, Machine_String*, size_t)) & Machine_Binding_setVariableBindingImpl;
  ((Machine_Binding_Class*)self)->getVariableBinding = (size_t(*)(Machine_Binding const*, Machine_String*)) & Machine_Binding_getVariableBindingImpl;
  ((Machine_Binding_Class*)self)->bindMatrix4 = (void (*)(Machine_Binding*, Machine_String*, Machine_Math_Matrix4 const*)) & Machine_Binding_bindMatrix4Impl;
  ((Machine_Binding_Class*)self)->bindVector2 = (void (*)(Machine_Binding*, Machine_String*, Machine_Math_Vector2 const*)) & Machine_Binding_bindVector2Impl;
  ((Machine_Binding_Class*)self)->bindVector3 = (void (*)(Machine_Binding*, Machine_String*, Machine_Math_Vector3 const*)) & Machine_Binding_bindVector3Impl;
  ((Machine_Binding_Class*)self)->bindVector4 = (void (*)(Machine_Binding*, Machine_String*, Machine_Math_Vector4 const*)) & Machine_Binding_bindVector4Impl;
  ((Machine_Binding_Class*)self)->bindSampler = (void (*)(Machine_Binding*, Machine_String*, size_t const)) & Machine_Binding_bindSamplerImpl;
  ((Machine_Binding_Class*)self)->activate = (void (*)(Machine_Binding*)) & Machine_Binding_activateImpl;
}

static void Machine_Gl_Binding_construct(Machine_Gl_Binding* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Binding_construct((Machine_Binding*)self, numberOfArguments, arguments);
  self->id = 0;
  Machine_setClassType((Machine_Object*)self, Machine_Gl_Binding_getClassType());
}

Machine_Gl_Binding* Machine_Gl_Binding_create(Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  Machine_ClassType* ty = Machine_Gl_Binding_getClassType();
  size_t numberOfArguments = 3;
  Machine_Value arguments[3];
  Machine_Value_setObject(&arguments[0], (Machine_Object*)program);
  Machine_Value_setObject(&arguments[1], (Machine_Object*)vertexDescriptor);
  Machine_Value_setObject(&arguments[2], (Machine_Object*)buffer);
  Machine_Gl_Binding* self = (Machine_Gl_Binding*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}
