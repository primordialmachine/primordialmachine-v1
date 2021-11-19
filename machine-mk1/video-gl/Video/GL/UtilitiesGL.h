/// @file Video/Gl/UtilitiesGl.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_UTILITIESGL_H_INCLUDED)
#define MACHINE_VIDEO_GL_UTILITIESGL_H_INCLUDED



#include "_Runtime.h"

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>



void Machine_UtilitiesGl_postCall(const char *file, int line, const char *function);

#define Machine_UtilitiesGl_call(CALL) \
  CALL; \
  { \
    Machine_UtilitiesGl_postCall(__FILE__, __LINE__, #CALL); \
  }



#endif // MACHINE_VIDEO_GL_UTILITIESGL_H_INCLUDED
