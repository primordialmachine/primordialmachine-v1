#include "ShaderProgram.h"



#include <malloc.h>
#include <string.h>



/// The shader version string (for fragment, geometry, and vertex shaders).
#define GLSL_VERSION_STRING "#version 330 core"

static void Machine_Input_visit(Machine_Input* self) {
  if (self->name) {
    Machine_visit(self->name);
  }
}

/// @brief Write code for selected uniforms.
/// @param code The target string buffer.
/// @param modelToWorld Add uniform <code>uniform mat4 modelToWorldMatrix</code>.
/// @param worldToView Add uniform <code>uniform mat4 worldToViewMatrix</code>.
/// @param viewToProjection Add uniform <code>uniform mat4 viewToProjectionMatrix</code>.
/// @param modelToProjection Add uniform <code>uniform mat4 modelToProjectionMatrix</code>.
static void defineMatrixUniforms(Machine_StringBuffer* code, bool modelToWorld, bool worldToView, bool viewToProjection, bool modelToProjection) {
#define T(t) t, strlen(t)
  // model -> world
  if (modelToWorld) {
    Machine_StringBuffer_appendBytes(code, T("uniform mat4 modelToWorldMatrix;\n"));
  }
  // world -> view
  if (worldToView) {
    Machine_StringBuffer_appendBytes(code, T("uniform mat4 worldToViewMatrix;\n"));
  }
  // view -> projection
  if (viewToProjection) {
    Machine_StringBuffer_appendBytes(code, T("uniform mat4 viewToProjectionMatrix;\n"));
  }
  if (modelToProjection) {
    //Machine_StringBuffer_appendBytes(code, T("uniform mat4 modelToProjectionMatrix;\n"));
    Machine_StringBuffer_appendBytes(code, T("uniform mat4 modelToProjectionMatrix = mat4(1);\n"));
  }
#undef T
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
  if (self->fragmentProgramId) {
    glDeleteShader(self->fragmentProgramId);
    self->fragmentProgramId = 0;
  }
  if (self->geometryProgramId) {
    glDeleteShader(self->geometryProgramId);
    self->geometryProgramId = 0;
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

Machine_ShaderProgram* Machine_ShaderProgram_create(GLuint programId, GLuint vertexProgramId, GLuint geometryProgramId, GLuint fragmentProgramId) {
  Machine_ShaderProgram* self = Machine_allocate(sizeof(Machine_ShaderProgram),
                                                 (Machine_VisitCallback*)&Machine_ShaderProgram_visit,
                                                 (Machine_FinalizeCallback*)&Machine_ShaderProgram_finalize);
  if (!self) {
    return NULL;
  }
  self->programId = programId;
  self->vertexProgramId = vertexProgramId;
  self->geometryProgramId = geometryProgramId;
  self->fragmentProgramId = fragmentProgramId;
  self->inputs.n = 0;
  self->inputs.e = NULL;
  return self;
}

static GLuint compileShader(const char* programText, Machine_ProgramKind programKind) {
  GLuint id;

  switch (programKind) {
  case Machine_ProgramKind_FRAGMENT:
    id = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  case Machine_ProgramKind_GEOMETRY:
    id = glCreateShader(GL_GEOMETRY_SHADER);
    break;
  case Machine_ProgramKind_VERTEX:
    id = glCreateShader(GL_VERTEX_SHADER);
    break;
  default:
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "shader compilation failed\n");
    return 0;
  };
  glShaderSource(id, 1, &programText, NULL);
  glCompileShader(id);
  GLint result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
  #define SHADER_EMIT_LOG_IF_COMPILATION_FAILED

  #if defined(SHADER_EMIT_LOG_IF_COMPILATION_FAILED)
    GLint log_length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);
    char *buffer = malloc(sizeof(char) * log_length + 1);
    if (buffer) {
      glGetShaderInfoLog(id, log_length, NULL, buffer);
      free(buffer);
    }
  #endif

  #undef SHADER_EMIT_LOG_IF_COMPILATION_FAILED

    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "shader compilation failed\n");
    glDeleteProgram(id);
    id = 0;
    return 0;
  }

  return id;
}

Machine_ShaderProgram* Machine_ShaderProgram_create2(const char* vertexProgramText, const char *geometryProgramText, const char* fragmentProgramText) {
  GLuint vertexShaderId = 0, geometryShaderId = 0, fragmentShaderId = 0, programId = 0;

  GLint result;

  vertexShaderId = compileShader(vertexProgramText, Machine_ProgramKind_VERTEX); 
  if (vertexShaderId == 0) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "vertex shader compilation failed\n");
    goto ERROR;
  }

  if (geometryProgramText) {
    geometryShaderId = compileShader(geometryProgramText, Machine_ProgramKind_GEOMETRY);
    if (geometryShaderId == 0) {
      Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "geometry shader compilation failed\n");
      goto ERROR;
    }
  }

  fragmentShaderId = compileShader(fragmentProgramText, Machine_ProgramKind_FRAGMENT);
  if (fragmentShaderId == 0) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "fragment shader compilation failed\n");
    goto ERROR;
  }

  programId = glCreateProgram();
  if (vertexShaderId) {
    glAttachShader(programId, vertexShaderId);
  }
  if (geometryShaderId) {
    glAttachShader(programId, geometryShaderId);
  }
  if (fragmentShaderId) {
    glAttachShader(programId, fragmentShaderId);
  }
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  if (result == GL_FALSE) {
  #define PROGRAM_EMIT_LOG_IF_LINKING_FAILED

  #if defined(PROGRAM_EMIT_LOG_IF_LINKING_FAILED)
    GLint log_length;
    glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &log_length);
    char* buffer = malloc(sizeof(char) * log_length + 1);
    if (buffer) {
      glGetProgramInfoLog(programId, log_length, NULL, buffer);
      free(buffer);
    }
  #endif

  #undef PROGRAM_EMIT_LOG_IF_LINKING_FAILED

    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "program linking failed\n");
    goto ERROR;
  }

  Machine_ShaderProgram* program = Machine_ShaderProgram_create(programId, vertexShaderId, geometryShaderId, fragmentShaderId);
  if (!program) {
    goto ERROR;
  }
  return program;
ERROR:
  if (programId) {
    glDeleteProgram(programId);
    programId = 0;
  }
  if (fragmentShaderId) {
    glDeleteShader(fragmentShaderId);
    fragmentShaderId = 0;
  }
  if (geometryShaderId) {
    glDeleteShader(geometryShaderId);
    geometryShaderId = 0;
  }
  if (vertexShaderId) {
    glDeleteShader(vertexShaderId);
    vertexShaderId = 0;
  }
  return NULL;
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
    bool withMeshColor,
    bool withVertexColor,
    bool withTextureCoordinate,
    bool withTexture
  )
{
  Machine_StringBuffer* code = Machine_StringBuffer_create();
  Machine_String* v, * g, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"
                                           "attribute vec2 vertex_position;\n"));
  defineMatrixUniforms(code, false, false, false, true);
  if (withMeshColor) {
    Machine_StringBuffer_appendBytes(code, T("uniform vec3 mesh_color = vec3(1.f, 1.f, 1.f);\n"));
  }
  if (withVertexColor) {
    Machine_StringBuffer_appendBytes(code, T("attribute vec3 vertex_color;\n"));
  }
  if (withTextureCoordinate) {
    Machine_StringBuffer_appendBytes(code, T("attribute vec2 vertex_texture_coordinate_1;\n"));
  }

  Machine_StringBuffer_appendBytes(code, T("out vec3 color;\n"));

  if (withTextureCoordinate) {
    Machine_StringBuffer_appendBytes(code, T("out vec2 texture_coordinate_1;\n"));
  }
  
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    gl_Position = modelToProjectionMatrix * vec4(vertex_position, 0.0, 1.0);\n"));

  Machine_StringBuffer_appendBytes(code, T("    color = vec3(1.0, 1.0, 1.0);\n"));
  if (withMeshColor) {
    Machine_StringBuffer_appendBytes(code, T("    color = mesh_color;\n"));
  }
  if (withVertexColor) {
    Machine_StringBuffer_appendBytes(code, T("    color = vertex_color;\n"));
  }
  if (withTextureCoordinate) {
    Machine_StringBuffer_appendBytes(code, T("    texture_coordinate_1 = vertex_texture_coordinate_1;\n"));
  }

  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Geometry program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  g = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Fragment program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec2 texture_coordinate_1;\n"));
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

  Machine_ShaderProgram* shaderProgram = Machine_ShaderProgram_create2(Machine_String_getBytes(v), NULL,/*Machine_String_getBytes(g),*/ Machine_String_getBytes(f));
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
  Machine_String* v, * g, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex shader.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));

  Machine_StringBuffer_appendBytes(code, T("out struct VS2GS {\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("} vertex;\n"));

  defineMatrixUniforms(code, false, false, false, true);
  Machine_StringBuffer_appendBytes(code, T("uniform vec3 mesh_color;\n"));

  Machine_StringBuffer_appendBytes(code, T("in vec2 vertex_position;\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec2 vertex_texture_coordinate_1;\n"));

  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    gl_Position = modelToProjectionMatrix * vec4(vertex_position, 0.0, 1.0);\n"));
  Machine_StringBuffer_appendBytes(code, T("    vertex.texture_coordinate_1 = vertex_texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("    vertex.color = mesh_color;\n"));

  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Geometry program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Machine_StringBuffer_appendBytes(code, T("in struct VS2GS {\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("} vertex[];\n"));
  Machine_StringBuffer_appendBytes(code, T("out struct GS2FS {\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("} fragment;\n"));
  Machine_StringBuffer_appendBytes(code, T("layout(triangles) in;"));
  Machine_StringBuffer_appendBytes(code, T("layout(triangle_strip, max_vertices = 3) out;"));
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{for(int i = 0; i < 3; i++) {\n"));
  Machine_StringBuffer_appendBytes(code, T("    gl_Position = gl_in[i].gl_Position;\n"));
  Machine_StringBuffer_appendBytes(code, T("    fragment.texture_coordinate_1 = vertex[i].texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("    fragment.color = vertex[i].color;\n"));
  Machine_StringBuffer_appendBytes(code, T(" EmitVertex(); } EndPrimitive();}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  g = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Fragment shader.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Machine_StringBuffer_appendBytes(code, T("in struct GS2FS {\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("} fragment;\n"));

  Machine_StringBuffer_appendBytes(code, T("uniform sampler2D texture_1;\n"));
  
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Machine_StringBuffer_appendBytes(code, T("    float a = texture2D(texture_1, fragment.texture_coordinate_1).r;\n"));
  Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = vec4(fragment.color.r, fragment.color.g, fragment.color.b, a);\n"));
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = Machine_ShaderProgram_create2(Machine_String_getBytes(v), Machine_String_getBytes(g), Machine_String_getBytes(f));
  Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                 Machine_InputType_Vector2);
  Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_texture_coordinate_1")),
                                 Machine_InputType_Vector2);
  return shaderProgram;

#undef TZ
#undef T
}

Machine_ShaderProgram*
Machine_ShaderProgram_generateRectangleShader
  (
  )
{
  Machine_StringBuffer* code = Machine_StringBuffer_create();
  Machine_String* v, * g, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex shader.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));

  defineMatrixUniforms(code, false, false, false, true);
  Machine_StringBuffer_appendBytes(code, T("uniform vec3 mesh_color;\n"));
  Machine_StringBuffer_appendBytes(code, T("out vec3 fragment_color;\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec2 vertex_position;\n"));


  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    gl_Position = modelToProjectionMatrix * vec4(vertex_position, 0.0, 1.0);\n"));
  Machine_StringBuffer_appendBytes(code, T("    fragment_color = mesh_color;\n"));

  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  // Fragment shader.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec3 fragment_color;\n"));
 
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = vec4(fragment_color, 1.f);\n"));
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_StringBuffer_toString(code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = Machine_ShaderProgram_create2(Machine_String_getBytes(v), NULL, Machine_String_getBytes(f));
  Machine_ShaderProgram_setInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                 Machine_InputType_Vector2);
  return shaderProgram;

#undef TZ
#undef T
}
