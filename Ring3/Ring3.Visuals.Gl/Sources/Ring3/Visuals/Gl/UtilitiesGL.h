/// @file Ring3/Visuals/Gl/UtilitiesGl.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GL_UTILITIESGL_H_INCLUDED)
#define RING3_VISUALS_GL_UTILITIESGL_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Video/Gl/UtilitiesGl.h` directly. Include `Ring3/Video/Gl/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE
#include <glad/glad.h>


void
Machine_UtilitiesGl_postCall
  (
    const char* file,
    int line,
    const char* function
  );

#define Machine_UtilitiesGl_call(CALL)                                                             \
  CALL;                                                                                            \
  { Machine_UtilitiesGl_postCall(__FILE__, __LINE__, #CALL); }


#endif // RING3_VISUALS_GL_UTILITIESGL_H_INCLUDED
