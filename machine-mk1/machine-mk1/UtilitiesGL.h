#if !defined(MACHINE_UTILITIESGL_H_INCLUDED)
#define MACHINE_UTILITIESGL_H_INCLUDED

#include "Machine.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void Machine_UtilitiesGl_postCall(const char *file, int line, const char *function);

#define Machine_UtilitiesGl_call(CALL) \
  CALL; \
  { \
    Machine_UtilitiesGl_postCall(__FILE__, __LINE__, #CALL); \
  }

#endif // MACHINE_UTILITIESGL_H_INCLUDED
