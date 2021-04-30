#if !defined(MACHINE_VIDEO_H_INCLUDED)
#define MACHINE_VIDEO_H_INCLUDED

#include "Machine.h"
typedef struct Machine_Texture Machine_Texture;
typedef struct Machine_ShaderProgram Machine_ShaderProgram;

/// @brief Increment the video module by @a 1.
/// FAILS if the reference count is INT_MAX.
/// @return @a 0 on success, a non-zero value on failure.
/// @remarks
/// Initializing/Uninitializing the video module also
/// initializes/uninitializes the following modules:
/// - images
/// - fonts
int Machine_Video_startup();

/// @brief Decrement the video module by @a 1.
/// UNDEFINED if the reference count is @a 0.
void Machine_Video_shutdown();

/// @brief Assign a texture unit.
/// @param unit The index of the texture unit.
/// @param texture A pointer to the texture or the null pointer.
void Machine_Video_bindTexture(size_t unit, Machine_Texture* texture);

/// @brief Assign a shader program.
/// @param shaderProgram The shader program.
void Machine_Video_bindShaderProgram(Machine_ShaderProgram *shaderProgram);

#endif // MACHINE_VIDEO_H_INCLUDED
