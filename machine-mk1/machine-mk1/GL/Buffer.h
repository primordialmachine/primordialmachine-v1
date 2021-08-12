#if !defined(MACHINE_GL_BUFFER_H_INCLUDED)
#define MACHINE_GL_BUFFER_H_INCLUDED



#include "./../GL/UtilitiesGL.h"
#include "_Video.h"



MACHINE_DECLARE_CLASSTYPE(Machine_GL_VideoBuffer)

struct Machine_GL_VideoBuffer {
  Machine_VideoBuffer __parent;
  GLuint id;
};

void Machine_GL_VideoBuffer_construct(Machine_GL_VideoBuffer* self, size_t numberOfArguments, const Machine_Value* arguments);


/// @brief Create an empty buffer.
/// @return The buffer.
Machine_GL_VideoBuffer* Machine_GL_VideoBuffer_create();



#endif // MACHINE_GL_BUFFER_H_INCLUDED
