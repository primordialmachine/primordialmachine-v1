#include "ShaderProgram.h"



#include <malloc.h>
#include <string.h>



static void Machine_Input_visit(Machine_Input* self) {
  if (self->name) {
    Machine_visit(self->name);
  }
}

Machine_Input* Machine_Input_create(Machine_String* name, Machine_InputType type) {
  Machine_Input* self = Machine_allocate(sizeof(Machine_Input), (void (*)(void*)) & Machine_Input_visit, NULL);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->name = name;
  self->type = type;
  return self;
}

static void Machine_ShaderProgram_visit(Machine_ShaderProgram* self) {
  for (size_t i = 0, n = self->inputs.n; i < n; ++i) {
    Machine_Input* input = self->inputs.e[i];
    Machine_visit(input);
  }
}

static void Machine_ShaderProgram_finalize(Machine_ShaderProgram* self) {
  if (self->programId) {
    glDeleteProgram(self->programId);
    self->programId = 0;
  }
  if (self->vertexProgramId) {
    glDeleteShader(self->vertexProgramId);
    self->vertexProgramId = 0;
  }
  if (self->fragmentProgramId) {
    glDeleteShader(self->fragmentProgramId);
    self->fragmentProgramId = 0;
  }
  if (self->inputs.e) {
    free(self->inputs.e);
    self->inputs.e = NULL;
  }
}

Machine_ShaderProgram* Machine_ShaderProgram_create(GLuint programId, GLuint vertexProgramId, GLuint fragmentProgramId) {
  Machine_ShaderProgram* self = Machine_allocate(sizeof(Machine_ShaderProgram), (void (*)(void*)) & Machine_ShaderProgram_visit,
                                                 (void (*)(void*)) & Machine_ShaderProgram_finalize);
  if (!self) {
    return NULL;
  }
  self->programId = programId;
  self->vertexProgramId = vertexProgramId;
  self->fragmentProgramId = fragmentProgramId;
  self->inputs.n = 0;
  self->inputs.e = NULL;
  return self;
}

Machine_ShaderProgram* Machine_ShaderProgram_create2(const char* vertexProgramText, const char* fragmentProgramText) {
  GLuint vertexShaderId = 0, fragmentShaderId = 0, programId = 0;

  GLint result;

  vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShaderId, 1, &vertexProgramText, NULL);
  glCompileShader(vertexShaderId);
  glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    if (programId) {
      glDeleteProgram(programId);
      programId = 0;
    }
    if (vertexShaderId) {
      glDeleteShader(vertexShaderId);
      vertexShaderId = 0;
    }
    if (fragmentShaderId) {
      glDeleteShader(fragmentShaderId);
      fragmentShaderId = 0;
    }
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "shader compilation failed\n");
    return NULL;
  }

  fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShaderId, 1, &fragmentProgramText, NULL);
  glCompileShader(fragmentShaderId);
  glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    if (programId) {
      glDeleteProgram(programId);
      programId = 0;
    }
    if (vertexShaderId) {
      glDeleteShader(vertexShaderId);
      vertexShaderId = 0;
    }
    if (fragmentShaderId) {
      glDeleteShader(fragmentShaderId);
      fragmentShaderId = 0;
    }
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "shader compilation failed\n");
    return NULL;
  }

  programId = glCreateProgram();
  glAttachShader(programId, vertexShaderId);
  glAttachShader(programId, fragmentShaderId);
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  if (result == GL_FALSE) {
    if (programId) {
      glDeleteProgram(programId);
      programId = 0;
    }
    if (vertexShaderId) {
      glDeleteShader(vertexShaderId);
      vertexShaderId = 0;
    }
    if (fragmentShaderId) {
      glDeleteShader(fragmentShaderId);
      fragmentShaderId = 0;
    }
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "program linking failed\n");
    return NULL;
  }

  Machine_ShaderProgram* program = Machine_ShaderProgram_create(programId, vertexShaderId, fragmentShaderId);
  if (!program) {
    if (programId) {
      glDeleteProgram(programId);
      programId = 0;
    }
    if (vertexShaderId) {
      glDeleteShader(vertexShaderId);
      vertexShaderId = 0;
    }
    if (fragmentShaderId) {
      glDeleteShader(fragmentShaderId);
      fragmentShaderId = 0;
    }
  }
  return program;
}

size_t Machine_ShaderProgram_getNumberOfInputs(Machine_ShaderProgram* self) {
  return self->inputs.n;
}

Machine_Input* Machine_ShaderProgram_getInput(Machine_ShaderProgram* self, size_t index) {
  return self->inputs.e[index];
}

bool Machine_ShaderProgram_setInput(Machine_ShaderProgram* self, Machine_String* name, Machine_InputType type) {
  for (size_t i = 0, n = self->inputs.n; i < n; ++i) {
    Machine_Input* input = self->inputs.e[i];
    if (Machine_String_equalTo(input->name, name)) {
      input->type = type;
      return true;
    }
  }
  Machine_Input* input = Machine_Input_create(name, type);
  Machine_Input** e = realloc(self->inputs.e, (self->inputs.n + 1) * sizeof(Machine_Input*));
  if (!e) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  self->inputs.e = e;
  e[self->inputs.n] = input;
  self->inputs.n++;
  return false;
}

Machine_ShaderProgram*
Machine_ShaderProgram_generate
  (
    bool withVertexColor,
    bool withTextureCoordinate,
    bool withTexture
  )
{
  Machine_StringBuffer* code = Machine_StringBuffer_create();
  Machine_String* v, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex shader.
  Machine_StringBuffer_appendBytes(code, T("#version 150\n"
                                           "uniform mat4 mvp;\n"
                                           "attribute vec2 vertex_position;\n"));
  if (withVertexColor) {
    Machine_StringBuffer_appendBytes(code, T("attribute vec3 vertex_color;\n"));
  }
  if (withTextureCoordinate) {
    Machine_StringBuffer_appendBytes(code, T("attribute vec2 vertex_texture_coordinate_1;\n"));
  }

  Machine_StringBuffer_appendBytes(code, T("varying vec3 color;\n"));

  if (withTextureCoordinate) {
    Machine_StringBuffer_appendBytes(code, T("varying vec2 texture_coordinate_1;\n"));
  }
  
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    gl_Position = mvp * vec4(vertex_position, 0.0, 1.0);\n"));

  if (withVertexColor) {
    Machine_StringBuffer_appendBytes(code, T("    color = vertex_color;\n"));
  } else {
    Machine_StringBuffer_appendBytes(code, T("    color = vec3(1.0, 1.0, 1.0);\n"));
  }
  if (withTextureCoordinate) {
    Machine_StringBuffer_appendBytes(code, T("    texture_coordinate_1 = vertex_texture_coordinate_1;\n"));
  }

  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Fragment shader.
  Machine_StringBuffer_appendBytes(code, T("#version 150\n"));
  Machine_StringBuffer_appendBytes(code, T("varying vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("varying vec2 texture_coordinate_1;\n"));
  if (withTextureCoordinate && withTexture) {
    Machine_StringBuffer_appendBytes(code, T("uniform sampler2D texture_1;\n"));
  }
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  if (withTextureCoordinate && withTexture) {
    Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = texture2D(texture_1, texture_coordinate_1);\n"));
  } else {
    Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = vec4(color, 1.0);\n"));
  }
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = Machine_ShaderProgram_create2(Machine_String_getBytes(v), Machine_String_getBytes(f));
  Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                 Machine_InputType_Vector2);
  if (withVertexColor) {
    Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_color")),
                                   Machine_InputType_Vector3);
  }
  if (withTextureCoordinate) {
    Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_texture_coordinate_1")),
                                   Machine_InputType_Vector2);
  }
  return shaderProgram;

#undef TZ
#undef T
}

Machine_ShaderProgram*
Machine_ShaderProgram_generateTextShader
  (
  )
{
  Machine_StringBuffer* code = Machine_StringBuffer_create();
  Machine_String* v, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex shader.
  Machine_StringBuffer_appendBytes(code, T("#version 150\n"));

  Machine_StringBuffer_appendBytes(code, T("uniform mat4 mvp;\n"));
  Machine_StringBuffer_appendBytes(code, T("attribute vec2 vertex_position;\n"));
  Machine_StringBuffer_appendBytes(code, T("attribute vec2 vertex_texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("varying vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("varying vec3 mesh_color;\n"));

  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    gl_Position = mvp * vec4(vertex_position, 0.0, 1.0);\n"));
  Machine_StringBuffer_appendBytes(code, T("    texture_coordinate_1 = vertex_texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Fragment shader.
  Machine_StringBuffer_appendBytes(code, T("#version 150\n"));
  
  Machine_StringBuffer_appendBytes(code, T("varying vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("uniform sampler2D texture_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("varying vec3 mesh_color;\n"));
  
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Machine_StringBuffer_appendBytes(code, T("    float a = texture2D(texture_1, texture_coordinate_1).r;\n"));
  Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = vec4(mesh_color.r, mesh_color.g, mesh_color.b, a);\n"));
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = Machine_ShaderProgram_create2(Machine_String_getBytes(v), Machine_String_getBytes(f));
  Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                 Machine_InputType_Vector2);
  Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_texture_coordinate_1")),
                                 Machine_InputType_Vector2);
  return shaderProgram;

#undef TZ
#undef T
}
