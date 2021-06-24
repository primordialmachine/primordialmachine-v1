#if !defined(MACHINE_GL_BUFFER_H_INCLUDED)
#define MACHINE_GL_BUFFER_H_INCLUDED



#include "./../UtilitiesGL.h"
#include "_Video.h"



MACHINE_DECLARE_CLASSTYPE(Machine_GL_Uint8Buffer)

struct Machine_GL_Uint8Buffer {
  Machine_Uint8Buffer __parent;
  GLuint id;
};

void Machine_GL_Uint8Buffer_construct(Machine_GL_Uint8Buffer* self, size_t numberOfArguments, const Machine_Value* arguments);


/// @brief Create an empty buffer for <code>uint8_t</code> values.
/// @return The buffer.
Machine_GL_Uint8Buffer* Machine_GL_Uint8Buffer_create();



MACHINE_DECLARE_CLASSTYPE(Machine_GL_FloatBuffer)

struct Machine_GL_FloatBuffer {
  Machine_FloatBuffer __parent;
  GLuint id;
};

void Machine_GL_FloatBuffer_construct(Machine_GL_FloatBuffer* self, size_t numberOfArguments, const Machine_Value* arguments);

/// @brief Create an empty buffer for <code>float</code> values.
/// @return The buffer.
Machine_GL_FloatBuffer* Machine_GL_FloatBuffer_create();



#endif // MACHINE_GL_BUFFER_H_INCLUDED
