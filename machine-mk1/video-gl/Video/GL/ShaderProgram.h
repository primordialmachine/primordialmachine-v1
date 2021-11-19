/// @file Video/Gl/ShaderProgram.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GL_SHADERPROGRAM_H_INCLUDED)
#define MACHINE_GL_SHADERPROGRAM_H_INCLUDED



#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#include "_Collections.h"
#include "_Video.h"
#include "Video/Gl/UtilitiesGL.h"



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

void Machine_Gl_ShaderProgram_construct(Machine_Gl_ShaderProgram* self, size_t numberOfArguments, Machine_Value const* arguments);

Machine_Gl_ShaderProgram* Machine_Gl_ShaderProgram_create(Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText);

/// @param withMeshColor <code>uniform vec3 mesh_color</code>
/// @param withVertexColor <code>attribute vec3 vertex_color</code>
/// @param withTextureCoordinate <code>attribute vec2 vertex_texture_coordinate</code>
/// @param withTexture <code>uniform sampler2D texture;</code>. @a withTextureCoordinate must be @a true if this is @a true.
Machine_ShaderProgram*
Machine_Gl_ShaderProgram_generateDefaultShader
  (
    Machine_Boolean withMeshColor,
    Machine_Boolean withVertexColor,
    Machine_Boolean withTextureCoordinate,
    Machine_Boolean withTexture
  );

/// @brief Create a shader program for rendering an untextured, colored, rectangle.
/// @return The shader program.
Machine_ShaderProgram*
Machine_Gl_ShaderProgram_generateShape2Shader
  (
  );

/// @brief Create a shader program for rendering 2D text.
/// Provides <code>vec3 mesh_color</code> to colorize the text.
/// @return The shader program.
Machine_ShaderProgram*
Machine_Gl_ShaderProgram_generateText2Shader
  (
    Machine_Boolean highPrecision
  );



#endif // MACHINE_GL_SHADERPROGRAM_H_INCLUDED
