/// @file Video/Gl/UtilitiesGl.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_VIDEO_GL_UTILITIESGL_H_INCLUDED)
#define MACHINE_VIDEO_GL_UTILITIESGL_H_INCLUDED


#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/UtilitiesGl.h` directly. Include `Video/Gl/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE
#include <glad/glad.h>


void Machine_UtilitiesGl_postCall(const char* file, int line, const char* function);

#define Machine_UtilitiesGl_call(CALL)                                                             \
  CALL;                                                                                            \
  { Machine_UtilitiesGl_postCall(__FILE__, __LINE__, #CALL); }


#endif // MACHINE_VIDEO_GL_UTILITIESGL_H_INCLUDED
