/// @file Video/Gl/ShaderProgram.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/ShaderProgram.h"


#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"


static void Machine_Gl_ShaderProgram_visit(Machine_Gl_ShaderProgram* self) {
  if (self->inputs) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->inputs);
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

/// @brief Get the program info log of a shader program.
/// @param id The OpenGL ID of s ahder program.
/// @return The log string on success, null on failure.
/// This function sets the by-thread status variable. 
static Ring2_String* getLog_noraise(GLuint id) {
  GLint n;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &n);
  if (n == SIZE_MAX) {
    return NULL;
  }
  char* p = NULL;
  if (Ring1_Memory_allocateArray(&p, n + 1, sizeof(char))) {
    return NULL;
  }
  glGetProgramInfoLog(id, n, NULL, p);
  if (glGetError() != GL_NO_ERROR) {
    return NULL;
  }
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_String* string = Ring2_String_create(p, n);
    Ring2_popJumpTarget();
    Ring1_Memory_deallocate(p);
    return string;
  } else {
    Ring2_popJumpTarget();
    Ring1_Memory_deallocate(p);
    Ring2_jump();
  }
}

static int64_t Machine_Gl_ShaderProgram_getNumberOfInputsImpl(Machine_Gl_ShaderProgram const* self) {
  return Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->inputs);
}

static Ring3_GpuProgramInputDescriptor* Machine_Gl_ShaderProgram_getInputAtImpl(Machine_Gl_ShaderProgram const* self, int64_t index) {
  Ring2_Value temporary = Ring2_Collections_List_getAt(self->inputs, index);
  return (Ring3_GpuProgramInputDescriptor*)Ring2_Value_getObject(&temporary);
}

static Ring2_Boolean Machine_Gl_ShaderProgram_addUpdateInputImpl(Machine_Gl_ShaderProgram* self, Ring2_String* name, Ring3_GpuProgramInputType type, Ring3_GpuProgramInputKind kind) {
  for (int64_t i = 0, n = Ring3_GpuProgram_getNumberOfInputs((Ring3_GpuProgram*)self); i < n; ++i) {
    Ring3_GpuProgramInputDescriptor* input = Ring3_GpuProgram_getInputAt((Ring3_GpuProgram*)self, i);
    if (Ring2_String_isEqualTo(Ring2_Context_get(), input->name, name)) {
      input->type = type;
      input->kind = kind;
      return true;
    }
  }
  Ring3_GpuProgramInputDescriptor* input = Ring3_GpuProgramInputDescriptor_create(name, type, kind);
  Ring2_Value temporary;
  Ring2_Value_setObject(&temporary, (Machine_Object*)input);
  Ring2_Collections_List_append(self->inputs, temporary);
  return false;
}

static GLuint compileShader(char const* programText, Ring3_GpuProgramKind programKind) {
  GLuint id;

  switch (programKind) {
  case Ring3_GpuProgramKind_Fragment:
    id = glCreateShader(GL_FRAGMENT_SHADER);
    break;
  case Ring3_GpuProgramKind_Geometry:
    id = glCreateShader(GL_GEOMETRY_SHADER);
    break;
  case Ring3_GpuProgramKind_Vertex:
    id = glCreateShader(GL_VERTEX_SHADER);
    break;
  default:
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "shader compilation failed\n");
    return 0;
  };
  glShaderSource(id, 1, &programText, NULL);
  glCompileShader(id);
  GLint result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
  #define SHADER_EMIT_LOG_IF_COMPILATION_FAILED

  #if defined(SHADER_EMIT_LOG_IF_COMPILATION_FAILED)
    Ring2_String* log = getLog_noraise(id);
  #endif

  #undef SHADER_EMIT_LOG_IF_COMPILATION_FAILED

    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "shader compilation failed\n");
    glDeleteProgram(id);
    id = 0;
    return 0;
  }

  return id;
}

static void constructFromText(Machine_Gl_ShaderProgram* self, char const* vertexProgramText, char const* geometryProgramText, char const* fragmentProgramText) {
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
  Ring1_Status_set(Ring1_Status_EnvironmentFailed); \
  Ring2_jump();

  GLint result;

  vertexShaderId = compileShader(vertexProgramText, Ring3_GpuProgramKind_Vertex);
  if (vertexShaderId == 0) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "vertex shader compilation failed\n");
    ON_ERROR();
  }

  if (geometryProgramText) {
    geometryShaderId = compileShader(geometryProgramText, Ring3_GpuProgramKind_Geometry);
    if (geometryShaderId == 0) {
      Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "geometry shader compilation failed\n");
      ON_ERROR();
    }
  }

  fragmentShaderId = compileShader(fragmentProgramText, Ring3_GpuProgramKind_Fragment);
  if (fragmentShaderId == 0) {
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "fragment shader compilation failed\n");
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
    Ring2_String *log = getLog_noraise(programId);
  #endif

  #undef PROGRAM_EMIT_LOG_IF_LINKING_FAILED

    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "program linking failed\n");
    ON_ERROR();
  }

  self->programId = programId;
  self->vertexProgramId = vertexShaderId;
  self->geometryProgramId = geometryShaderId;
  self->fragmentProgramId = fragmentShaderId;
  self->inputs = Ring1_cast(Ring2_Collections_List *, Ring2_Collections_ArrayList_create());
}

static void Machine_Gl_ShaderProgram_constructClass(Machine_Gl_ShaderProgram_Class* self) {
  ((Ring3_GpuProgram_Class*)self)->getNumberOfInputs = (int64_t (*)(Ring3_GpuProgram const*)) & Machine_Gl_ShaderProgram_getNumberOfInputsImpl;
  ((Ring3_GpuProgram_Class*)self)->getInputAt = (Ring3_GpuProgramInputDescriptor* (*)(Ring3_GpuProgram const*, int64_t)) & Machine_Gl_ShaderProgram_getInputAtImpl;
  ((Ring3_GpuProgram_Class*)self)->addUpdateInput = (Ring2_Boolean (*)(Ring3_GpuProgram*, Ring2_String*, Ring3_GpuProgramInputType, Ring3_GpuProgramInputKind)) & Machine_Gl_ShaderProgram_addUpdateInputImpl;
}

void Machine_Gl_ShaderProgram_construct(Machine_Gl_ShaderProgram* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Ring3_GpuProgram_construct((Ring3_GpuProgram*)self, numberOfArguments, arguments);
  if (numberOfArguments != 3) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  Ring2_String *v = NULL, *g = NULL, *f = NULL;
  if (!Ring2_Value_isVoid(arguments + 0)) {
    v = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  }
  if (!Ring2_Value_isVoid(arguments + 1)) {
    g = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 1);
  }
  if (!Ring2_Value_isVoid(arguments + 2)) {
    f = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 2);
  }
  constructFromText(self, v ? Ring2_String_getBytes(v) : NULL,
                          g ? Ring2_String_getBytes(g) : NULL,
                          f ? Ring2_String_getBytes(f) : NULL);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gl_ShaderProgram_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_ShaderProgram,
                         Ring3_GpuProgram,
                         &Machine_Gl_ShaderProgram_visit,
                         &Machine_Gl_ShaderProgram_construct,
                         &Machine_Gl_ShaderProgram_destruct,
                         &Machine_Gl_ShaderProgram_constructClass,
                         NULL)

Machine_Gl_ShaderProgram* Machine_Gl_ShaderProgram_create(Ring2_String* vertexProgramText, Ring2_String* geometryProgramText, Ring2_String* fragmentProgramText) {
  Machine_ClassType* ty = Machine_Gl_ShaderProgram_getType();

  static size_t const numberOfArguments = 3;
  Ring2_Value arguments[3];

  if (vertexProgramText != NULL)
    Ring2_Value_setString(&arguments[0], vertexProgramText);
  else
    Ring2_Value_setVoid(&arguments[0], Ring2_Void_Void);

  if (geometryProgramText != NULL)
    Ring2_Value_setString(&arguments[1], geometryProgramText);
  else
    Ring2_Value_setVoid(&arguments[1], Ring2_Void_Void);

  if (fragmentProgramText != NULL)
    Ring2_Value_setString(&arguments[2], fragmentProgramText);
  else
    Ring2_Value_setVoid(&arguments[2], Ring2_Void_Void);

  Machine_Gl_ShaderProgram* self = (Machine_Gl_ShaderProgram*)Machine_allocateClassObject(ty, numberOfArguments, arguments);
  return self;
}

/// The shader version string (for fragment, geometry, and vertex shaders).
#define GLSL_VERSION_STRING "#version 330 core"

static void defineFloatConstants(Ring2_StringBuffer* code) {
#define T(t) t, crt_strlen(t)
  Ring2_StringBuffer_appendBytes(code, T("#define FLT_MAX 3.402823466e+38" "\n"));
  Ring2_StringBuffer_appendBytes(code, T("#define FLT_MIN 1.175494351e-38" "\n"));
  Ring2_StringBuffer_appendBytes(code, T("#define DBL_MAX 1.7976931348623158e+308" "\n"));
  Ring2_StringBuffer_appendBytes(code, T("#define DBL_MIN 2.2250738585072014e-308" "\n"));
#undef T
}

/// @brief Write code for selected uniforms.
/// @param code The target string buffer.
/// @param modelToWorld Add uniform <code>uniform mat4 modelToWorldMatrix</code>.
/// @param worldToView Add uniform <code>uniform mat4 worldToViewMatrix</code>.
/// @param viewToProjection Add uniform <code>uniform mat4 viewToProjectionMatrix</code>.
/// @param modelToProjection Add uniform <code>uniform mat4 modelToProjectionMatrix</code>.
static void defineMatrixUniforms(Ring2_StringBuffer* code, Ring2_Boolean modelToWorld, Ring2_Boolean worldToView, Ring2_Boolean viewToProjection, Ring2_Boolean modelToProjection) {
#define T(t) t, crt_strlen(t)
  // model -> world
  if (modelToWorld) {
    Ring2_StringBuffer_appendBytes(code, T("uniform mat4 modelToWorldMatrix;\n"));
  }
  // world -> view
  if (worldToView) {
    Ring2_StringBuffer_appendBytes(code, T("uniform mat4 worldToViewMatrix;\n"));
  }
  // view -> projection
  if (viewToProjection) {
    Ring2_StringBuffer_appendBytes(code, T("uniform mat4 viewToProjectionMatrix;\n"));
  }
  if (modelToProjection) {
    //Ring2_StringBuffer_appendBytes(code, T("uniform mat4 modelToProjectionMatrix;\n"));
    Ring2_StringBuffer_appendBytes(code, T("uniform mat4 modelToProjectionMatrix = mat4(1);\n"));
  }
#undef T
}


Ring3_GpuProgram*
Machine_Gl_ShaderProgram_generateDefaultShader
  (
    Ring2_Boolean withMeshColor,
    Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate,
    Ring2_Boolean withTexture
  )
{
  Ring2_StringBuffer* code = Ring2_StringBuffer_create();
  Ring2_String *v, *g, *f;
#define T(t) t, crt_strlen(t)
#define TZ(t) t, crt_strlen(t) + 1

  // Vertex program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));

  defineFloatConstants(code);
  defineMatrixUniforms(code, false, false, false, true);

  Ring2_StringBuffer_appendBytes(code, T("attribute vec2 vertexPosition;\n"));


  if (withMeshColor) {
    Ring2_StringBuffer_appendBytes(code, T("uniform vec3 meshColor = vec3(1.f, 1.f, 1.f);\n"));
  }
  if (withVertexColor) {
    Ring2_StringBuffer_appendBytes(code, T("attribute vec3 vertexColor;\n"));
  }
  if (withTextureCoordinate) {
    Ring2_StringBuffer_appendBytes(code, T("attribute vec2 vertexTextureCoordinate1;\n"));
  }

  Ring2_StringBuffer_appendBytes(code, T("out vec3 color;\n"));

  if (withTextureCoordinate) {
    Ring2_StringBuffer_appendBytes(code, T("out vec2 texture_coordinate_1;\n"));
  }

  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                         "{\n"
                                         "    gl_Position = modelToProjectionMatrix * vec4(vertexPosition, 0.0, 1.0);\n"));

  Ring2_StringBuffer_appendBytes(code, T("    color = vec3(1.0, 1.0, 1.0);\n"));
  if (withMeshColor) {
    Ring2_StringBuffer_appendBytes(code, T("    color = meshColor;\n"));
  }
  if (withVertexColor) {
    Ring2_StringBuffer_appendBytes(code, T("    color = vertexColor;\n"));
  }
  if (withTextureCoordinate) {
    Ring2_StringBuffer_appendBytes(code, T("    texture_coordinate_1 = vertexTextureCoordinate1;\n"));
  }

  Ring2_StringBuffer_appendBytes(code, T("}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  v = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  // Geometry program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  g = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  // Fragment program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Ring2_StringBuffer_appendBytes(code, T("in vec3 color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("in vec2 texture_coordinate_1;\n"));
  if (withTextureCoordinate && withTexture) {
    Ring2_StringBuffer_appendBytes(code, T("uniform sampler2D texture_1;\n"));
  }
  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  if (withTextureCoordinate && withTexture) {
    Ring2_StringBuffer_appendBytes(code, T("    gl_FragColor = texture2D(texture_1, texture_coordinate_1);\n"));
  }
  else {
    Ring2_StringBuffer_appendBytes(code, T("    gl_FragColor = vec4(color, 1.0);\n"));
  }
  Ring2_StringBuffer_appendBytes(code, T("}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  f = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  Ring3_GpuProgram* shaderProgram = (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_create(v, NULL, f);
  Ring3_GpuProgram_addUpdateInput(shaderProgram, Ring2_String_create(TZ("vertexPosition")),
                                  Ring3_GpuProgramInputType_Vector2, Ring3_GpuProgramInputKind_Variable);
  if (withVertexColor) {
    Ring3_GpuProgram_addUpdateInput(shaderProgram, Ring2_String_create(TZ("vertexColor")),
                                    Ring3_GpuProgramInputType_Vector3, Ring3_GpuProgramInputKind_Variable);
  }
  if (withTextureCoordinate) {
    Ring3_GpuProgram_addUpdateInput(shaderProgram, Ring2_String_create(TZ("vertexTextureCoordinate1")),
                                    Ring3_GpuProgramInputType_Vector2, Ring3_GpuProgramInputKind_Variable);
  }
  return shaderProgram;

#undef TZ
#undef T
}

Ring3_GpuProgram*
Machine_Gl_ShaderProgram_generateShape2Shader
  (
  )
{
  Ring2_StringBuffer* code = Ring2_StringBuffer_create();
  Ring2_String *v, *g, *f;
#define T(t) t, crt_strlen(t)
#define TZ(t) t, crt_strlen(t) + 1

  // Vertex program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));

  defineFloatConstants(code);
  defineMatrixUniforms(code, false, false, false, true);

  Ring2_StringBuffer_appendBytes(code, T("attribute vec2 vertexPosition;\n"));


  Ring2_StringBuffer_appendBytes(code, T("uniform vec4 meshColor = vec4(1.f, 1.f, 1.f, 1.f);\n"));


  Ring2_StringBuffer_appendBytes(code, T("out vec4 color;\n"));

  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                         "{\n"
                                         "    gl_Position = modelToProjectionMatrix * vec4(vertexPosition, 0.0, 1.0);\n"));

  Ring2_StringBuffer_appendBytes(code, T("    color = meshColor;\n"));

  Ring2_StringBuffer_appendBytes(code, T("}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  v = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  // Geometry program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  g = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  // Fragment program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  Ring2_StringBuffer_appendBytes(code, T("in vec4 color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Ring2_StringBuffer_appendBytes(code, T("    gl_FragColor = color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  f = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  Ring3_GpuProgram* shaderProgram = (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_create(v, NULL, f);
  Ring3_GpuProgram_addUpdateInput(shaderProgram, Ring2_String_create(TZ("vertexPosition")),
                                  Ring3_GpuProgramInputType_Vector2, Ring3_GpuProgramInputKind_Variable);
  return shaderProgram;

#undef TZ
#undef T
}

Ring3_GpuProgram*
Machine_Gl_ShaderProgram_generateText2Shader
  (
    Ring2_Boolean highPrecision
  )
{
  Ring2_StringBuffer* code = Ring2_StringBuffer_create();
  Ring2_String *v, *g, *f;
#define T(t) t, crt_strlen(t)
#define TZ(t) t, crt_strlen(t) + 1

  // Vertex shader.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  if (highPrecision) {
    Ring2_StringBuffer_appendBytes(code, T("precision highp float;\n"));
  }

  defineFloatConstants(code);

  static Ring2_Boolean const withClipDistance = true;

  Ring2_StringBuffer_appendBytes(code, T("out struct VS2GS {\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("} vertex;\n"));

  defineMatrixUniforms(code, true, false, false, true);
  Ring2_StringBuffer_appendBytes(code, T("uniform vec3 meshColor;\n"));

  Ring2_StringBuffer_appendBytes(code, T("in vec2 vertexPosition;\n"));
  Ring2_StringBuffer_appendBytes(code, T("in vec2 vertexTextureCoordinate1;\n"));

  if (withClipDistance) {
    Ring2_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane0;\n"));
    Ring2_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane1;\n"));
    Ring2_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane2;\n"));
    Ring2_StringBuffer_appendBytes(code, T("uniform vec4 clipPlane3;\n"));
    Ring2_StringBuffer_appendBytes(code, T("out float gl_ClipDistance[4];\n"));
  }

  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                         "{\n"
                                         "    vec4 worldPosition = modelToWorldMatrix * vec4(vertexPosition, 0.0, 1.0);\n"
                                         "    gl_Position = modelToProjectionMatrix * vec4(vertexPosition, 0.0, 1.0);\n"));
  Ring2_StringBuffer_appendBytes(code, T("    vertex.texture_coordinate_1 = vertexTextureCoordinate1;\n"));
  Ring2_StringBuffer_appendBytes(code, T("    vertex.color = meshColor;\n"));
  if (withClipDistance) {
    Ring2_StringBuffer_appendBytes(code, T("    gl_ClipDistance[0] = +dot(worldPosition, clipPlane0);\n"));
    Ring2_StringBuffer_appendBytes(code, T("    gl_ClipDistance[1] = +dot(worldPosition, clipPlane1);\n"));
    Ring2_StringBuffer_appendBytes(code, T("    gl_ClipDistance[2] = +dot(worldPosition, clipPlane2);\n"));
    Ring2_StringBuffer_appendBytes(code, T("    gl_ClipDistance[3] = +dot(worldPosition, clipPlane3);\n"));
  }

  Ring2_StringBuffer_appendBytes(code, T("}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  v = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  // Geometry program.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  if (highPrecision) {
    Ring2_StringBuffer_appendBytes(code, T("precision highp float;\n"));
  }
  Ring2_StringBuffer_appendBytes(code, T("in struct VS2GS {\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("} vertex[];\n"));
  Ring2_StringBuffer_appendBytes(code, T("out struct GS2FS {\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("} fragment;\n"));
  Ring2_StringBuffer_appendBytes(code, T("layout(triangles) in;"));
  Ring2_StringBuffer_appendBytes(code, T("layout(triangle_strip, max_vertices = 3) out;"));
  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                         "{for(int i = 0; i < 3; i++) {\n"));
  Ring2_StringBuffer_appendBytes(code, T("    gl_Position = gl_in[i].gl_Position;\n"));
  Ring2_StringBuffer_appendBytes(code, T("    fragment.texture_coordinate_1 = vertex[i].texture_coordinate_1;\n"));
  Ring2_StringBuffer_appendBytes(code, T("    fragment.color = vertex[i].color;\n"));
  if (withClipDistance) {
    Ring2_StringBuffer_appendBytes(code, T("  gl_ClipDistance[0] = gl_in[i].gl_ClipDistance[0];\n"));
    Ring2_StringBuffer_appendBytes(code, T("  gl_ClipDistance[1] = gl_in[i].gl_ClipDistance[1];\n"));
    Ring2_StringBuffer_appendBytes(code, T("  gl_ClipDistance[2] = gl_in[i].gl_ClipDistance[2];\n"));
    Ring2_StringBuffer_appendBytes(code, T("  gl_ClipDistance[3] = gl_in[i].gl_ClipDistance[3];\n"));
  }

  Ring2_StringBuffer_appendBytes(code, T(" EmitVertex(); } EndPrimitive();}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  g = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  // Fragment shader.
  Ring2_StringBuffer_appendBytes(code, T(GLSL_VERSION_STRING "\n"));
  if (highPrecision) {
    Ring2_StringBuffer_appendBytes(code, T("precision highp float;\n"));
  }
  Ring2_StringBuffer_appendBytes(code, T("in struct GS2FS {\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec2 texture_coordinate_1;\n"));
  Ring2_StringBuffer_appendBytes(code, T("  vec3 color;\n"));
  Ring2_StringBuffer_appendBytes(code, T("} fragment;\n"));

  Ring2_StringBuffer_appendBytes(code, T("uniform sampler2D texture_1;\n"));

  Ring2_StringBuffer_appendBytes(code, T("void main()\n"
                                           "{\n"));
  Ring2_StringBuffer_appendBytes(code, T("    if (gl_ClipDistance[0] < 0 || gl_ClipDistance[1] < 0 || gl_ClipDistance[2] < 0 || gl_ClipDistance[3] < 0) {\n"));
  Ring2_StringBuffer_appendBytes(code, T("        discard;"));
  Ring2_StringBuffer_appendBytes(code, T("    } else {\n"));
  Ring2_StringBuffer_appendBytes(code, T("      float a = texture2D(texture_1, fragment.texture_coordinate_1).r;\n"));
  Ring2_StringBuffer_appendBytes(code, T("      gl_FragColor = vec4(fragment.color.r, fragment.color.g, fragment.color.b, a);\n"));
  Ring2_StringBuffer_appendBytes(code, T("    }\n"));
  Ring2_StringBuffer_appendBytes(code, T("}\n"));
  Ring2_StringBuffer_appendBytes(code, "", 1);
  f = Machine_Object_toString(Ring2_Context_get(), (Machine_Object *)code);
  Ring2_StringBuffer_clear(code);

  Ring3_GpuProgram* shaderProgram = (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_create(v, g, f);
  Ring3_GpuProgram_addUpdateInput(shaderProgram, Ring2_String_create(TZ("vertexPosition")),
                                  Ring3_GpuProgramInputType_Vector2, Ring3_GpuProgramInputKind_Variable);
  Ring3_GpuProgram_addUpdateInput(shaderProgram, Ring2_String_create(TZ("vertexTextureCoordinate1")),
                                  Ring3_GpuProgramInputType_Vector2, Ring3_GpuProgramInputKind_Variable);
  return shaderProgram;

#undef TZ
#undef T
}
