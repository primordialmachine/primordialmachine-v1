/// @file Video/Gl/Buffer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GL_BUFFER_H_INCLUDED)
#define MACHINE_GL_BUFFER_H_INCLUDED



#include "Video/Gl/UtilitiesGL.h"
#include "_Video.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Gl_VideoBuffer)

struct Machine_Gl_VideoBuffer_Class {
  Machine_VideoBuffer_Class parent;
};

struct Machine_Gl_VideoBuffer {
  Machine_VideoBuffer __parent;
  GLuint id;
};

void Machine_Gl_VideoBuffer_construct(Machine_Gl_VideoBuffer* self, size_t numberOfArguments, const Machine_Value* arguments);


/// @brief Create an empty buffer.
/// @return The buffer.
Machine_Gl_VideoBuffer* Machine_Gl_VideoBuffer_create();



#endif // MACHINE_GL_BUFFER_H_INCLUDED
