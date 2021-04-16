#if !defined(MACHINE_SHADERPROGRAM_H_INCLUDED)
#define MACHINE_SHADERPROGRAM_H_INCLUDED



#include "Machine.h"
#include "UtilitiesGL.h"



typedef enum Machine_InputType {
  Machine_InputType_Vector2,
  Machine_InputType_Vector3,
} Machine_InputType;

typedef struct Machine_Input Machine_Input;

struct Machine_Input {
  Machine_String* name;
  Machine_InputType type;
};

Machine_Input* Machine_Input_create(Machine_String* name, Machine_InputType type);

typedef struct Machine_ShaderProgram Machine_ShaderProgram;

struct Machine_ShaderProgram {
  GLuint programId;
  GLuint vertexProgramId;
  GLuint fragmentProgramId;
  struct {
    Machine_Input** e;
    size_t n;
  } inputs;
};

Machine_ShaderProgram* Machine_ShaderProgram_create(GLuint programId, GLuint vertexProgramId, GLuint fragmentProgramId);

Machine_ShaderProgram* Machine_ShaderProgram_create2(const char* vertexProgramText, const char* fragmentProgramText);

/**
 * @brief
 * Get the number of inputs to this shader program.
 * @param self
 * This shader program.
 * @return
 * The number of inputs.
 */
size_t Machine_ShaderProgram_getNumberOfInputs(Machine_ShaderProgram* self);

/**
 * @brief
 * Get the input to this shader program at the specified index.
 * @param self
 * This shader program.
 * @param index
 * The index.
 * @return
 * The input.
 */
Machine_Input* Machine_ShaderProgram_getInput(Machine_ShaderProgram* self, size_t index);

/**
 * @brief
 * Add/modify an input to this shader program.
 * @param self
 * This shader program.
 * @param name
 * The name of the input.
 */
bool Machine_ShaderProgram_setInput(Machine_ShaderProgram* self, Machine_String* name, Machine_InputType type);

/**
 * @param withVertexColor <code>attribute vec3 vertex_color</code>
 * @param withTextureCoordinate <code>attribute vec2 vertex_texture_coordinate</code>
 * @param withTexture <code>uniform sampler2D texture;</code>. @a withTextureCoordinate must be @a true if this is @a true.
 */
Machine_ShaderProgram*
Machine_ShaderProgram_generate
  (
    bool withVertexColor,
    bool withTextureCoordinate,
    bool withTexture
  );

Machine_ShaderProgram*
Machine_ShaderProgram_generateTextShader
  (
    bool withMeshColor,
    bool withVertexColor,
    bool withTextureCoordinate,
    bool withTexture
  );

#endif // MACHINE_SHADERPROGRAM_H_INCLUDED
