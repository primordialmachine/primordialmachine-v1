/// @file Video/Gl/Texture.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GL_TEXTURE_H_INCLUDED)
#define MACHINE_GL_TEXTURE_H_INCLUDED


#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/Texture.h` directly. Include `Video/Gl/_Include.h` instead.")
#endif
#include "Ring3/Visuals/_Include.h"
#include "Video/Gl/UtilitiesGl.h"


MACHINE_DECLARE_CLASSTYPE(Machine_Gl_Texture);

struct Machine_Gl_Texture_Class {
  Ring3_Texture_Class parent;
};

struct Machine_Gl_Texture {
  Ring3_Texture __parent;
  GLuint id;
};

/// @brief Create an OpenGL texture from an image.
/// @param image A pointer to the image.
/// @return A pointer to the OpenGL texture.
Machine_Gl_Texture*
Machine_Gl_Texture_create
  (
    Ring3_Image* image
  );


#endif // MACHINE_GL_TEXTURE_H_INCLUDED
