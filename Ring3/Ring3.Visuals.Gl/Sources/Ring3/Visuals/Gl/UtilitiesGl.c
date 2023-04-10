/// @file Ring3/Visuals/Gl/UtilitiesGl.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/UtilitiesGl.h"
#undef RING3_VISUALS_GL_PRIVATE


char const*
Machine_UtilitiesGl_toString
  (
    GLenum error
  );

Ring1_Status
Machine_UtilitiesGl_toStatus
  (
    GLenum error
  );

char const*
Machine_UtilitiesGl_toString
  (
    GLenum error
  )
{
  switch (error) {
    case GL_INVALID_ENUM: {
      static char const* STRING = "GL_INVALID_ENUM";
      return STRING;
    }
    case GL_INVALID_VALUE: {
      static char const* STRING = "GL_INVALID_VALUE";
      return STRING;
    }
    case GL_INVALID_OPERATION: {
      static char const* STRING = "GL_INVALID_OPERATION";
      return STRING;
    }
    case GL_INVALID_FRAMEBUFFER_OPERATION: {
      static char const* STRING = "GL_INVALID_FRAMEBUFFER_OPERATION";
      return STRING;
    }
    case GL_OUT_OF_MEMORY: {
      static char const* STRING = "GL_OUT_OF_MEMORY";
      return STRING;
    }
    case GL_STACK_UNDERFLOW: {
      static char const* STRING = "GL_STACK_UNDERFLOW";
      return STRING;
    }
    case GL_STACK_OVERFLOW: {
      static char const* STRING = "GL_STACK_OVERFLOW";
      return STRING;
    }
    case GL_NO_ERROR: {
      static char const* STRING = "GL_NO_ERROR";
      return STRING;
    }
    default: {
      static char const* STRING = "<unknown>";
      return STRING;
    }
  };
}

Ring1_Status
Machine_UtilitiesGl_toStatus
  (
    GLenum error
  )
{
  switch (error) {
    case GL_INVALID_ENUM:
      return Ring1_Status_InvalidArgument;
    case GL_INVALID_VALUE:
      return Ring1_Status_InvalidArgument;
    case GL_INVALID_OPERATION:
      return Ring1_Status_InvalidOperation;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return Ring1_Status_InvalidOperation;
    case GL_OUT_OF_MEMORY:
      return Ring1_Status_AllocationFailed;
    case GL_STACK_UNDERFLOW:
    case GL_STACK_OVERFLOW:
      return Ring1_Status_AllocationFailed;
    case GL_NO_ERROR:
    default:
      return Ring1_Status_Success;
  };
}

void
Machine_UtilitiesGl_postCall
  (
    char const* file,
    int line,
    char const* function
  )
{
  GLenum errorCode = glGetError();
  if (errorCode) {
    char const* error = Machine_UtilitiesGl_toString(errorCode);
    Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__, "%s failed with %s\n", function,
              error);
    Ring1_Status_set(Machine_UtilitiesGl_toStatus(errorCode));
    Ring2_jump();
  }
}
