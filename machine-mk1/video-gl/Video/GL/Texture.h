#if !defined(MACHINE_GL_TEXTURE_H_INCLUDED)
#define MACHINE_GL_TEXTURE_H_INCLUDED



#include "_Video.h"
#include "./../GL/UtilitiesGL.h"



MACHINE_DECLARE_CLASSTYPE(Machine_Gl_Texture);

struct Machine_Gl_Texture_Class {
  Machine_Texture_Class parent;
};

struct Machine_Gl_Texture {
  Machine_Texture __parent;
  GLuint id;
};

/// @brief Create an OpenGL texture from an image.
/// @param image A pointer to the image.
/// @return A pointer to the OpenGL texture.
Machine_Gl_Texture* Machine_Gl_Texture_create(Machine_Image* image);



#endif // MACHINE_GL_TEXTURE_H_INCLUDED
