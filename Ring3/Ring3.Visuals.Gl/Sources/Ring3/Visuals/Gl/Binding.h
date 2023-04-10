/// @file Ring3/Visuals/Gl/Binding.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GL_BINDING_H_INCLUDED)
#define RING3_VISUALS_GL_BINDING_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Visuals/Gl/Binding.h` directly. Include `Ring3/Visuals/Gl/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"
#include "Ring3/Visuals/Gl/UtilitiesGl.h"


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


#endif // RING3_VISUALS_GL_BINDING_H_INCLUDED
