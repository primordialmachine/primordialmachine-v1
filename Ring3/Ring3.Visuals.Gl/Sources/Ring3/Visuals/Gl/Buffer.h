/// @file Ring3/Visuals/Gl/Buffer.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GL_BUFFER_H_INCLUDED)
#define RING3_VISUALS_GL_BUFFER_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Visuals/Gl/Buffer.h` directly. Include `Ring3/Visuals/Gl/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"
#include "Ring3/Visuals/Gl/UtilitiesGL.h"


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


#endif // RING3_VISUALS_GL_BUFFER_H_INCLUDED
