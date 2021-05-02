#include "UtilitiesGL.h"

const char* Machine_UtilitiesGl_toString(GLenum error);

Machine_StatusValue Machine_UtilitiesGl_toStatus(GLenum error);

const char* Machine_UtilitiesGl_toString(GLenum error) {
  switch (error) {
  case GL_INVALID_ENUM: {
    static const char* STRING = "GL_INVALID_ENUM";
    return STRING;
  }
  case GL_INVALID_VALUE: {
    static const char* STRING = "GL_INVALID_VALUE";
    return STRING;
  }
  case GL_INVALID_OPERATION: {
    static const char* STRING = "GL_INVALID_OPERATION";
    return STRING;
  }
  case GL_INVALID_FRAMEBUFFER_OPERATION: {
    static const char* STRING = "GL_INVALID_FRAMEBUFFER_OPERATION";
    return STRING;
  }
  case GL_OUT_OF_MEMORY: {
    static const char* STRING = "GL_OUT_OF_MEMORY";
    return STRING;
  }
  case GL_STACK_UNDERFLOW: {
    static const char* STRING = "GL_STACK_UNDERFLOW";
    return STRING;
  }
  case GL_STACK_OVERFLOW: {
    static const char* STRING = "GL_STACK_OVERFLOW";
    return STRING;
  }
  case GL_NO_ERROR: {
    static const char* STRING = "GL_NO_ERROR";
    return STRING;
  }
  default: {
    static const char* STRING = "<unknown>";
    return STRING;
  }
  };
}

Machine_StatusValue Machine_UtilitiesGl_toStatus(GLenum error) {
  switch (error) {
  case GL_INVALID_ENUM:
    return Machine_Status_InvalidArgument;
  case GL_INVALID_VALUE:
    return Machine_Status_InvalidArgument;
  case GL_INVALID_OPERATION:
    return Machine_Status_InvalidOperation;
  case GL_INVALID_FRAMEBUFFER_OPERATION:
    return Machine_Status_InvalidOperation;
  case GL_OUT_OF_MEMORY:
    return Machine_Status_AllocationFailed;
  case GL_STACK_UNDERFLOW:
  case GL_STACK_OVERFLOW:
    return Machine_Status_AllocationFailed;
  case GL_NO_ERROR:
  default:
    return Machine_Status_Success;
  };
}

void Machine_UtilitiesGl_postCall(const char *file, int line, const char *function) {
  GLenum errorCode = glGetError();
  if (errorCode) {
    const char* error = Machine_UtilitiesGl_toString(errorCode);
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "%s failed with %s\n", function, error);
    Machine_setStatus(Machine_UtilitiesGl_toStatus(errorCode));
    Machine_jump();
  }
}
