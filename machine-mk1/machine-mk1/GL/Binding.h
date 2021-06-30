#if !defined(MACHINE_GL_BINDING_H_INCLUDED)
#define MACHINE_GL_BINDING_H_INCLUDED



#include "_Video.h"
#include "./../UtilitiesGL.h"



MACHINE_DECLARE_CLASSTYPE(Machine_GL_Binding)

struct Machine_GL_Binding {
  Machine_Binding parent;
  GLuint id;
};

Machine_GL_Binding* Machine_GL_Binding_create(Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer);



#endif // MACHINE_GL_BINDING_H_INCLUDED
