/// @file Video/Gl/Buffer.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GL_BUFFER_H_INCLUDED)
#define MACHINE_GL_BUFFER_H_INCLUDED



#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#include "Video/Gl/UtilitiesGL.h"
#include "Ring3/Visuals/_Include.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Gl_VideoBuffer)

struct Machine_Gl_VideoBuffer_Class {
  Ring3_GpuBuffer_Class parent;
};

struct Machine_Gl_VideoBuffer {
  Ring3_GpuBuffer __parent;
  size_t n;
  void* p;
  GLuint id;
};

void
Machine_Gl_VideoBuffer_construct
  (
    Machine_Gl_VideoBuffer* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );


/// @brief Create an empty buffer.
/// @return The buffer.
Machine_Gl_VideoBuffer*
Machine_Gl_VideoBuffer_create
  (
  );


#endif // MACHINE_GL_BUFFER_H_INCLUDED
