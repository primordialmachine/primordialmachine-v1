/// @file Video/Gl/ShaderProgram.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Video/Gl/ShaderProgram.h"



#include <malloc.h>
#include <string.h>



static void Machine_Gl_ShaderProgram_visit(Machine_Gl_ShaderProgram* self) {
  if (self->inputs) {
    Machine_Gc_visit(self->inputs);
  }
}

static void Machine_Gl_ShaderProgram_destruct(Machine_Gl_ShaderProgram* self) {
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
  if (self->programId) {
    glDeleteProgram(self->programId);
    self->programId = 0;
  }
}

static size_t Machine_Gl_ShaderProgram_getNumberOfInputsImpl(Machine_Gl_ShaderProgram const* self) {
  return Machine_Collection_getSize((Machine_Collection*)self->inputs);
}

static Machine_ProgramInput* Machine_Gl_ShaderProgram_getInputAtImpl(Machine_Gl_ShaderProgram const* self, size_t index) {
  Machine_Value temporary = Machine_List_getAt(self->inputs, index);
  return (Machine_ProgramInput*)Machine_Value_getObject(&temporary);
}

static Machine_Boolean Machine_Gl_ShaderProgram_addUpdateInputImpl(Machine_Gl_ShaderProgram* self, Machine_String* name, Machine_ProgramInputType type, Machine_ProgramInputKind kind) {
  for (size_t i = 0, n = Machine_ShaderProgram_getNumberOfInputs((Machine_ShaderProgram *)self); i < n; ++i) {
    Machine_ProgramInput* input = Machine_ShaderProgram_getInputAt((Machine_ShaderProgram *)self, i);
    if (Machine_String_isEqualTo(input->name, name)) {
      input->type = type;
      input->kind = kind;
      return true;
    }
  }
  Machine_ProgramInput* input = Machine_ProgramInput_create(name, type, kind);
  Machine_Value temporary;
  Machine_Value_setObject(&temporary, (Machine_Object*)input);
  Machine_List_append(self->inputs, temporary);
  return false;
}

static GLuint compileShader(const char* programText, Machine_ProgramKind programKind) {
  GLuint id;

  switch (programKind) {
  case Machine_ProgramKind_Fragment:
    id = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  case Machine_ProgramKind_Geometry:
    id = glCreateShader(GL_GEOMETRY_SHADER);
    break;
  case Machine_ProgramKind_Vertex:
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
    char* buffer = malloc(sizeof(char) * log_length + 1);
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

static void constructFromText(Machine_Gl_ShaderProgram* self, const char* vertexProgramText, const char* geometryProgramText, const char* fragmentProgramText) {
  GLuint vertexShaderId = 0, geometryShaderId = 0, fragmentShaderId = 0, programId = 0;

#define ON_ERROR() \
  if (programId) { \
    glDeleteProgram(programId); \
    programId = 0; \
  } \
\
  if (fragmentShaderId) { \
    glDeleteShader(fragmentShaderId); \
    fragmentShaderId = 0; \
  } \
\
  if (geometryShaderId) { \
    glDeleteShader(geometryShaderId); \
    geometryShaderId = 0; \
  } \
\
  if (vertexShaderId) { \
    glDeleteShader(vertexShaderId); \
    vertexShaderId = 0; \
  } \
\
  Machine_setStatus(Machine_Status_EnvironmentFailed); \
  Machine_jump();

  GLint result;

  vertexShaderId = compileShader(vertexProgramText, Machine_ProgramKind_Vertex);
  if (vertexShaderId == 0) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "vertex shader compilation failed\n");
    ON_ERROR();
  }

  if (geometryProgramText) {
    geometryShaderId = compileShader(geometryProgramText, Machine_ProgramKind_Geometry);
    if (geometryShaderId == 0) {
      Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "geometry shader compilation failed\n");
      ON_ERROR();
    }
  }

  fragmentShaderId = compileShader(fragmentProgramText, Machine_ProgramKind_Fragment);
  if (fragmentShaderId == 0) {
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "fragment shader compilation failed\n");
    ON_ERROR();
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
    ON_ERROR();
  }

  self->programId = programId;
  self->vertexProgramId = vertexShaderId;
  self->geometryProgramId = geometryShaderId;
  self->fragmentProgramId = fragmentShaderId;
  self->inputs = Machine_List_create();
}

static void Machine_Gl_ShaderProgram_constructClass(Machine_Gl_ShaderProgram_Class* self) {
  ((Machine_ShaderProgram_Class*)self)->getNumberOfInputs = (size_t(*)(Machine_ShaderProgram const*)) & Machine_Gl_ShaderProgram_getNumberOfInputsImpl;
  ((Machine_ShaderProgram_Class*)self)->getInputAt = (Machine_ProgramInput * (*)(Machine_ShaderProgram const*, size_t)) & Machine_Gl_ShaderProgram_getInputAtImpl;
  ((Machine_ShaderProgram_Class*)self)->addUpdateInput = (Machine_Boolean(*)(Machine_ShaderProgram*, Machine_String*, Machine_ProgramInputType, Machine_ProgramInputKind)) & Machine_Gl_ShaderProgram_addUpdateInputImpl;
}

void Machine_Gl_ShaderProgram_construct(Machine_Gl_ShaderProgram* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_ShaderProgram_construct((Machine_ShaderProgram*)self, numberOfArguments, arguments);
  if (numberOfArguments != 3) {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
  Machine_String* v = NULL, * g = NULL, * f = NULL;
  if (!Machine_Value_isVoid(arguments + 0)) {
    v = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 0);
  }
  if (!Machine_Value_isVoid(arguments + 1)) {
    g = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 1);
  }
  if (!Machine_Value_isVoid(arguments + 2)) {
    f = Machine_Extensions_getStringArgument(numberOfArguments, arguments, 2);
  }
  constructFromText(self, v ? Machine_String_getBytes(v) : NULL,
                          g ? Machine_String_getBytes(g) : NULL,
                          f ? Machine_String_getBytes(f) : NULL);
  Machine_setClassType((Machine_Object*)self, Machine_Gl_ShaderProgram_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_ShaderProgram, Machine_ShaderProgram, Machine_Gl_ShaderProgram_visit, Machine_Gl_ShaderProgram_construct, Machine_Gl_ShaderProgram_destruct, &Machine_Gl_ShaderProgram_constructClass)

Machine_Gl_ShaderProgram* Machine_Gl_ShaderProgram_create(Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText) {
  Machine_ClassType* ty = Machine_Gl_ShaderProgram_getClassType();

  static const size_t numberOfArguments = 3;
  Machine_Value arguments[3];

  if (vertexProgramText != NULL)
    Machine_Value_setString(&arguments[0], vertexProgramText);
  else
    Machine_Value_setVoid(&arguments[0], Machine_Void_Void);

  if (geometryProgramText != NULL)
    Machine_Value_setString(&arguments[1], geometryProgramText);
  else
    Machine_Value_setVoid(&arguments[1], Machine_Void_Void);

  if (fragmentProgramText != NULL)
    Machine_Value_setString(&arguments[2], fragmentProgramText);
  else
    Machine_Value_setVoid(&arguments[2], Machine_Void_Void);

  Machine_Gl_ShaderProgram* self = (Machine_Gl_ShaderProgram*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}

/// The shader version string (for fragment, geometry, and vertex shaders).
#define GLSL_VERSION_STRING "#version 330 core"

static void defineFloatConstants(Machine_StringBuffer* code) {
#define T(t) t, strlen(t)
  Machine_StringBuffer_appendBytes(code, T("#define FLT_MAX 3.402823466e+38" "\n"));
  Machine_StringBuffer_appendBytes(code, T("#define FLT_MIN 1.175494351e-38" "\n"));
  Machine_StringBuffer_appendBytes(code, T("#define DBL_MAX 1.7976931348623158e+308" "\n"));
  Machine_StringBuffer_appendBytes(code, T("#define DBL_MIN 2.2250738585072014e-308" "\n"));
#undef T
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


Machine_ShaderProgram*
Machine_Gl_ShaderProgram_generateDefaultShader
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
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));

  defineFloatConstants(code);
  defineMatrixUniforms(code, false, false, false, true);

  Machine_StringBuffer_appendBytes(code, T("attribute vec2 vertex_position;\n"));


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
  v = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  // Geometry program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  g = Machine_Object_toString((Machine_Object *)code);
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
  }
  else {
    Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = vec4(color, 1.0);\n"));
  }
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = (Machine_ShaderProgram *)Machine_Gl_ShaderProgram_create(v, NULL, f);
  Machine_ShaderProgram_addUpdateInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                       Machine_ProgramInputType_Vector2, Machine_ProgramInputKind_Variable);
  if (withVertexColor) {
    Machine_ShaderProgram_addUpdateInput(shaderProgram, Machine_String_create(TZ("vertex_color")),
                                          Machine_ProgramInputType_Vector3, Machine_ProgramInputKind_Variable);
  }
  if (withTextureCoordinate) {
    Machine_ShaderProgram_addUpdateInput(shaderProgram, Machine_String_create(TZ("vertex_texture_coordinate_1")),
                                          Machine_ProgramInputType_Vector2, Machine_ProgramInputKind_Variable);
  }
  return shaderProgram;

#undef TZ
#undef T
}

Machine_ShaderProgram*
Machine_Gl_ShaderProgram_generateShape2Shader
  (
  )
{
  Machine_StringBuffer* code = Machine_StringBuffer_create();
  Machine_String* v, * g, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));

  defineFloatConstants(code);
  defineMatrixUniforms(code, false, false, false, true);

  Machine_StringBuffer_appendBytes(code, T("attribute vec2 vertex_position;\n"));


  Machine_StringBuffer_appendBytes(code, T("uniform vec4 mesh_color = vec4(1.f, 1.f, 1.f, 1.f);\n"));


  Machine_StringBuffer_appendBytes(code, T("out vec4 color;\n"));

  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    gl_Position = modelToProjectionMatrix * vec4(vertex_position, 0.0, 1.0);\n"));

  Machine_StringBuffer_appendBytes(code, T("    color = mesh_color;\n"));

  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  // Geometry program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  g = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  // Fragment program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec4 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Machine_StringBuffer_appendBytes(code, T("    gl_FragColor = color;\n"));
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_create(v, NULL, f);
  Machine_ShaderProgram_addUpdateInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                       Machine_ProgramInputType_Vector2, Machine_ProgramInputKind_Variable);
  return shaderProgram;

#undef TZ
#undef T
}

Machine_ShaderProgram*
Machine_Gl_ShaderProgram_generateText2Shader
  (
    bool highPrecision
  )
{
  Machine_StringBuffer* code = Machine_StringBuffer_create();
  Machine_String* v, * g, * f;
#define T(t) t, strlen(t)
#define TZ(t) t, strlen(t) + 1

  // Vertex shader.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  if (highPrecision) {
    Machine_StringBuffer_appendBytes(code, T("precision highp float;\n"));
  }

  defineFloatConstants(code);

  static const bool withClipDistance = true;

  Machine_StringBuffer_appendBytes(code, T("out struct VS2GS {\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("} vertex;\n"));

  defineMatrixUniforms(code, true, false, false, true);
  Machine_StringBuffer_appendBytes(code, T("uniform vec3 mesh_color;\n"));

  Machine_StringBuffer_appendBytes(code, T("in vec2 vertex_position;\n"));
  Machine_StringBuffer_appendBytes(code, T("in vec2 vertex_texture_coordinate_1;\n"));

  if (withClipDistance) {
    Machine_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane0;\n"));
    Machine_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane1;\n"));
    Machine_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane2;\n"));
    Machine_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane3;\n"));
    Machine_StringBuffer_appendBytes(code, T("out float gl_ClipDistance[4];\n"));
  }

  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"
                                           "    vec4 worldPosition = modelToWorldMatrix * vec4(vertex_position, 0.0, 1.0);\n"
                                           "    gl_Position = modelToProjectionMatrix * vec4(vertex_position, 0.0, 1.0);\n"));
  Machine_StringBuffer_appendBytes(code, T("    vertex.texture_coordinate_1 = vertex_texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("    vertex.color = mesh_color;\n"));
  if (withClipDistance) {
    Machine_StringBuffer_appendBytes(code, T("    gl_ClipDistance[0] = +dot(worldPosition, clipPlane0);\n"));
    Machine_StringBuffer_appendBytes(code, T("    gl_ClipDistance[1] = +dot(worldPosition, clipPlane1);\n"));
    Machine_StringBuffer_appendBytes(code, T("    gl_ClipDistance[2] = +dot(worldPosition, clipPlane2);\n"));
    Machine_StringBuffer_appendBytes(code, T("    gl_ClipDistance[3] = +dot(worldPosition, clipPlane3);\n"));
  }

  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  v = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  // Geometry program.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  if (highPrecision) {
    Machine_StringBuffer_appendBytes(code, T("precision highp float;\n"));
  }
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
  if (withClipDistance) {
    Machine_StringBuffer_appendBytes(code, T("  gl_ClipDistance[0] = gl_in[i].gl_ClipDistance[0];\n"));
    Machine_StringBuffer_appendBytes(code, T("  gl_ClipDistance[1] = gl_in[i].gl_ClipDistance[1];\n"));
    Machine_StringBuffer_appendBytes(code, T("  gl_ClipDistance[2] = gl_in[i].gl_ClipDistance[2];\n"));
    Machine_StringBuffer_appendBytes(code, T("  gl_ClipDistance[3] = gl_in[i].gl_ClipDistance[3];\n"));
  }

  Machine_StringBuffer_appendBytes(code, T(" EmitVertex(); } EndPrimitive();}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  g = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  // Fragment shader.
  Machine_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  if (highPrecision) {
    Machine_StringBuffer_appendBytes(code, T("precision highp float;\n"));
  }
  Machine_StringBuffer_appendBytes(code, T("in struct GS2FS {\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Machine_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Machine_StringBuffer_appendBytes(code, T("} fragment;\n"));

  Machine_StringBuffer_appendBytes(code, T("uniform sampler2D texture_1;\n"));

  Machine_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Machine_StringBuffer_appendBytes(code, T("    if (gl_ClipDistance[0] < 0 || gl_ClipDistance[1] < 0 || gl_ClipDistance[2] < 0 || gl_ClipDistance[3] < 0) {\n"));
  Machine_StringBuffer_appendBytes(code, T("        discard;"));
  Machine_StringBuffer_appendBytes(code, T("    } else {\n"));
  Machine_StringBuffer_appendBytes(code, T("      float a = texture2D(texture_1, fragment.texture_coordinate_1).r;\n"));
  Machine_StringBuffer_appendBytes(code, T("      gl_FragColor = vec4(fragment.color.r, fragment.color.g, fragment.color.b, a);\n"));
  Machine_StringBuffer_appendBytes(code, T("    }\n"));
  Machine_StringBuffer_appendBytes(code, T("}\n"));
  Machine_StringBuffer_appendBytes(code, "", 1);
  f = Machine_Object_toString((Machine_Object *)code);
  Machine_StringBuffer_clear(code);

  Machine_ShaderProgram* shaderProgram = (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_create(v, g, f);
  Machine_ShaderProgram_addUpdateInput(shaderProgram, Machine_String_create(TZ("vertex_position")),
                                       Machine_ProgramInputType_Vector2, Machine_ProgramInputKind_Variable);
  Machine_ShaderProgram_addUpdateInput(shaderProgram, Machine_String_create(TZ("vertex_texture_coordinate_1")),
                                       Machine_ProgramInputType_Vector2, Machine_ProgramInputKind_Variable);
  return shaderProgram;

#undef TZ
#undef T
}
