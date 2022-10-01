/// @file Video/Gl/ShaderProgram.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GL_SHADERPROGRAM_H_INCLUDED)
#define MACHINE_GL_SHADERPROGRAM_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/ShaderProgram.h` directly, include `_Video_Gl.h` instead.")
#endif
#include "Ring2/Library/_Include.h"
#include "Video/Gl/UtilitiesGL.h"
#include "_Video.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Gl_ShaderProgram)

struct Machine_Gl_ShaderProgram_Class {
  Machine_ShaderProgram_Class parent;
};

struct Machine_Gl_ShaderProgram {
  Machine_ShaderProgram parent;
  /// @brief The OpenGL program ID.
  GLuint programId;
  /// @brief The OpenGL vertex program ID.
  GLuint vertexProgramId;
  /// @brief The OpenGL geometry program ID.
  GLuint geometryProgramId;
  /// @brief The OpenGL fragment program ID.
  GLuint fragmentProgramId;
  /// @brief List of Machine.ProgramInput objects.
  Machine_List* inputs;
};

void Machine_Gl_ShaderProgram_construct(Machine_Gl_ShaderProgram* self, size_t numberOfArguments,
                                        Ring2_Value const* arguments);

Machine_Gl_ShaderProgram* Machine_Gl_ShaderProgram_create(Ring2_String* vertexProgramText,
                                                          Ring2_String* geometryProgramText,
                                                          Ring2_String* fragmentProgramText);

/// @param withMeshColor <code>uniform vec3 mesh_color</code>
/// @param withVertexColor <code>attribute vec3 vertex_color</code>
/// @param withTextureCoordinate <code>attribute vec2 vertex_texture_coordinate</code>
/// @param withTexture <code>uniform sampler2D texture;</code>. @a withTextureCoordinate must be @a
/// true if this is @a true.
Machine_ShaderProgram* Machine_Gl_ShaderProgram_generateDefaultShader(
    Ring2_Boolean withMeshColor, Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate, Ring2_Boolean withTexture);

/// @brief Create a shader program for rendering an untextured, colored, rectangle.
/// @return The shader program.
Machine_ShaderProgram* Machine_Gl_ShaderProgram_generateShape2Shader();

/// @brief Create a shader program for rendering 2D text.
/// Provides <code>vec3 mesh_color</code> to colorize the text.
/// @return The shader program.
Machine_ShaderProgram* Machine_Gl_ShaderProgram_generateText2Shader(Ring2_Boolean highPrecision);

#endif // MACHINE_GL_SHADERPROGRAM_H_INCLUDED
