#include "Binding.h"



#include "GL/ShaderProgram.h"



typedef struct Machine_Binding_Node Machine_Binding_Node;

struct Machine_Binding_Node {
  Machine_Binding_Node* next;
  bool isVariable;
  Machine_String* name;
  Machine_Value value;
};

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
  if (index < 0 || index > Machine_Integer_Greatest || index == (size_t)(-1)) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Binding_Node* self = Machine_allocate(sizeof(Machine_Binding_Node), (void (*)(void*)) & Machine_Binding_Node_visit, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->next = NULL;
  self->name = name;
  self->isVariable = true;
  Machine_Value_setInteger(&self->value, index);
  return self;

}

Machine_Binding_Node* Machine_Binding_Node_createConstant(Machine_String* name, Machine_Value const *value) {
  Machine_Binding_Node* self = Machine_allocate(sizeof(Machine_Binding_Node), (void (*)(void*)) & Machine_Binding_Node_visit, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->next = NULL;
  self->name = name;
  self->isVariable = false;
  self->value = *value;
  return self;
}

struct Machine_Binding {
  Machine_Object parent;
  Machine_Binding_Node* nodes;
  Machine_ShaderProgram* program;
  Machine_VertexDescriptor* vertexDescriptor;
  Machine_VideoBuffer* buffer;
  GLuint id;
  bool dirty;
};

static void Machine_Binding_finalize(Machine_Binding* self) {
  if (self->id) {
    glDeleteVertexArrays(1, &self->id);
    self->id = 0;
  }
}

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

Machine_Binding* Machine_Binding_create(Machine_ShaderProgram *program, Machine_VertexDescriptor *vertexDescriptor, Machine_VideoBuffer* buffer) {
  Machine_Binding* self = Machine_allocate(sizeof(Machine_Binding), (void (*)(void*)) & Machine_Binding_visit, (void (*)(void *))&Machine_Binding_finalize);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->dirty = true;
  self->id = 0;
  self->program = program;
  self->vertexDescriptor = vertexDescriptor;
  self->buffer = buffer;
  self->nodes = NULL;
  return self;
}

bool Machine_Binding_setVariableBinding(Machine_Binding* self, Machine_String* name, size_t index) {
  if (index < 0 || index > Machine_Integer_Greatest || index == (size_t)(-1)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Binding_Node* node = self->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name)) {
      Machine_Value_setInteger(&node->value, index);
      node->isVariable = true;
      self->dirty = true;
      return true;
    }
    node = node->next;
  }
  self->dirty = true;
  node = Machine_Binding_Node_create(name, index);
  node->next = self->nodes; self->nodes = node;
  return false;
}

size_t Machine_Binding_getVariableBinding(Machine_Binding const* self, Machine_String* name) {
  Machine_Binding_Node* node = self->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name) && node->isVariable) {
      return Machine_Value_getInteger(&node->value);
    }
    node = node->next;
  }
  return (size_t)-1;
}

static void bindVar(Machine_Binding const* self, size_t inputIndex, Machine_ProgramInput const* input) {
  MACHINE_ASSERT_NOTNULL(input);
  MACHINE_ASSERT(input->kind == Machine_ProgramInputKind_Variable, Machine_Status_InvalidArgument);
  
  // Get the index of the corresponding vertex element.
  size_t vertexElementIndex = Machine_Binding_getVariableBinding(self, input->name);
  if (vertexElementIndex == (size_t)-1) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "input %s not supported by program", Machine_String_getBytes(input->name));
    return;
  }
  GLint attributeLocation = glGetAttribLocation(((Machine_GL_ShaderProgram*)(self->program))->programId, Machine_String_getBytes(input->name));
  if (attributeLocation == -1) {
    Machine_log(Machine_LogFlags_ToWarnings, __FILE__, __LINE__, "input %s optimized out\n", Machine_String_getBytes(input->name));
    return;
  }
  size_t vertexSize = Machine_VertexDescriptor_getVertexSize(self->vertexDescriptor);
  Machine_VertexElementSemantics semantics = Machine_VertexDescriptor_getElementSemantics(self->vertexDescriptor, vertexElementIndex);
  size_t offset = Machine_VertexDescriptor_getElementOffset(self->vertexDescriptor, vertexElementIndex);
  Machine_UtilitiesGl_call(glEnableVertexAttribArray(inputIndex));
  Machine_UtilitiesGl_call(glBindBuffer(GL_ARRAY_BUFFER, *((GLuint*)Machine_VideoBuffer_getId(self->buffer))));
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

void Machine_Binding_activate(Machine_Binding* self) {
  if (self->dirty) {
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

    for (size_t i = 0, j = 0, n = Machine_ShaderProgram_getNumberOfInputs(self->program); i < n;) {
      Machine_ProgramInput const* input = Machine_ShaderProgram_getInputAt(self->program, i);
      if (input->kind == Machine_ProgramInputKind_Variable) {
        bindVar(self, j, input);
        j++;
      }
      i++;
    }
    self->dirty = false;
  }
  else
  {
    glBindVertexArray(self->id);
  }
}

void Machine_Binding_bindMatrix4x4(Machine_Binding* self, Machine_String* name, const mat4x4 value) {
  GLint location = glGetUniformLocation(((Machine_GL_ShaderProgram *)(self->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  Machine_UtilitiesGl_call(glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat const*)*value));
}

void Machine_Binding_bindVector2(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector2* value) {
  Machine_Binding_Node* node = self->nodes;
  while (node) {
    if (Machine_String_isEqualTo(node->name, name) && node->isVariable == false) {
      Machine_Value_setObject(&node->value, (Machine_Object*)value);
      break;
    } else {
      node = node->next;
    }
  }
  if (node == NULL) {
    Machine_Value temporary;
    Machine_Value_setObject(&temporary, (Machine_Object*)value);
    node = Machine_Binding_Node_createConstant(name, &temporary);
    node->next = self->nodes; self->nodes = node;
  }


  GLint location = glGetUniformLocation(((Machine_GL_ShaderProgram*)(self->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Machine_Math_Vector2_getX(value), Machine_Math_Vector2_getY(value) };
  Machine_UtilitiesGl_call(glUniform2fv(location, 1, temporary));
}

void Machine_Binding_bindVector3(Machine_Binding* self, Machine_String* name, Machine_Math_Vector3 const* value) {
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

  GLint location = glGetUniformLocation(((Machine_GL_ShaderProgram*)(self->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Machine_Math_Vector3_getX(value), Machine_Math_Vector3_getY(value), Machine_Math_Vector3_getZ(value) };
  Machine_UtilitiesGl_call(glUniform3fv(location, 1, temporary));
}

void Machine_Binding_bindVector4(Machine_Binding* self, Machine_String* name, const Machine_Math_Vector4* value) {
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

  GLint location = glGetUniformLocation(((Machine_GL_ShaderProgram*)(self->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  const GLfloat temporary[] = { Machine_Math_Vector4_getX(value), Machine_Math_Vector4_getY(value), Machine_Math_Vector4_getZ(value), Machine_Math_Vector4_getW(value) };
  Machine_UtilitiesGl_call(glUniform4fv(location, 1, temporary));
}

void Machine_Binding_bindSampler(Machine_Binding* self, Machine_String* name, const size_t value) {
  GLint location = glGetUniformLocation(((Machine_GL_ShaderProgram*)(self->program))->programId, Machine_String_getBytes(name));
  if (location == -1) {
    return;
  }
  Machine_UtilitiesGl_call(glUniform1i(location, value));
}
