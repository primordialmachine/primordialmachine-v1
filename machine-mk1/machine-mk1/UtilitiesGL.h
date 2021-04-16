#if !defined(MACHINE_UTILITIESGL_H_INCLUDED)
#define MACHINE_UTILITIESGL_H_INCLUDED

#include "Machine.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

const char* Machine_UtilitiesGl_toString(GLenum error);

Machine_StatusValue Machine_UtilitiesGl_toStatus(GLenum error);

#define Machine_UtilitiesGl_call(CALL) \
  CALL; \
  { \
    GLenum error = glGetError(); \
    if (error) { \
      const char *CALL_STRING = #CALL; \
      const char *ERROR_STRING = Machine_UtilitiesGl_toString(error); \
      Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "%s failed with %s\n", CALL_STRING, ERROR_STRING); \
      Machine_setStatus(Machine_UtilitiesGl_toStatus(error)); \
      Machine_jump(); \
    } \
  }

#endif // MACHINE_UTILITIESGL_H_INCLUDED
