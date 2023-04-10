/// @file Video/Gl/Binding.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GL_BINDING_H_INCLUDED)
#define MACHINE_GL_BINDING_H_INCLUDED



#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#include "Ring3/Visuals/_Include.h"
#include "Video/Gl/UtilitiesGl.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Gl_Binding)

struct Machine_Gl_Binding_Class {
  Ring3_Binding_Class __parent;
};

struct Machine_Gl_Binding {
  Ring3_Binding __parent;

  GLuint id;
};

Machine_Gl_Binding*
Machine_Gl_Binding_create
  (
    Ring3_GpuProgram* program,
    Ring3_VertexDescriptor* vertexDescriptor,
    Ring3_GpuBuffer* buffer
  );



#endif // MACHINE_GL_BINDING_H_INCLUDED
