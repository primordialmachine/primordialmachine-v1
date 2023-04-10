/// @file Ring3/Visuals/Gl/Texture.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GL_TEXTURE_H_INCLUDED)
#define RING3_VISUALS_GL_TEXTURE_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Visuals/Gl/Texture.h` directly. Include `Ring3/Visuals/Gl/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"
#include "Ring3/Visuals/Gl/UtilitiesGl.h"


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


#endif // RING3_VISUALS_GL_TEXTURE_H_INCLUDED
