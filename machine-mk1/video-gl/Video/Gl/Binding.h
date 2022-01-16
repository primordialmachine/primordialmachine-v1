/// @file Video/Gl/Binding.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GL_BINDING_H_INCLUDED)
#define MACHINE_GL_BINDING_H_INCLUDED



#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#include "_Video.h"
#include "Video/Gl/UtilitiesGl.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Gl_Binding)

struct Machine_Gl_Binding_Class {
  Machine_Binding_Class __parent;
};

struct Machine_Gl_Binding {
  Machine_Binding __parent;

  GLuint id;
};

Machine_Gl_Binding* Machine_Gl_Binding_create(Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer);



#endif // MACHINE_GL_BINDING_H_INCLUDED