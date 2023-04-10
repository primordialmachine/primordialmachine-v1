/// @file Ring3/Video/Gl/Input/MousePointer.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GL_INPUT_MOUSEPOINTER_H_INCLUDED)
#define RING3_VISUALS_GL_INPUT_MOUSEPOINTER_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Video/Gl/Input/MousePointer.h`. Include `Ring3/Video/Gl/_Include.h` instead.")
#endif

#include "Ring3/Visuals/Gl/Configuration.h"
#if Ring3_Visuals_Backend == Ring3_Visuals_Backend_Glfw
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE
#else
#error("unkown/unsupported/not yet supported backend")
#endif


#if Ring3_Visuals_Backend == Ring3_Visuals_Backend_Glfw
/// @brief A cursor enter GLFW callback.
/// @param window, entered The GLFW arguments to the callback.
void
Ring3_Visuals_Gl_Glfw_cursorEnterCallback
  (
    GLFWwindow* window,
    int entered
  );
#else
#error("unkown/unsupported/not yet supported backend")
#endif

#if Ring3_Visuals_Backend == Ring3_Visuals_Backend_Glfw
/// @brief A cursor position GLFW callback.
/// @param window, x, y The GLFW arguments to the callback.
void
Ring3_Visuals_Gl_Glfw_cursorPositionCallback
  (
    GLFWwindow* window,
    double x,
    double y
  );
#else
#error("unkown/unsupported/not yet supported backend")
#endif


#endif // RING3_VISUALS_GL_INPUT_MOUSEPOINTER_H_INCLUDED
