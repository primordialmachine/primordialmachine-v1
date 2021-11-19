#if !defined(MACHINE_GL_BINDING_H_INCLUDED)
#define MACHINE_GL_BINDING_H_INCLUDED



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
