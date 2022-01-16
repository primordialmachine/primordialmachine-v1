/// @file Video/Gl/Texture.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GL_TEXTURE_H_INCLUDED)
#define MACHINE_GL_TEXTURE_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#include "Video/Gl/UtilitiesGl.h"
#include "_Video.h"

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