/// @file Video/Gl/Input/MousePointer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_INPUT_MOUSEPOINTER_H_INCLUDED)
#define MACHINE_VIDEO_GL_INPUT_MOUSEPOINTER_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/Input/MousePointer.h`, include `_Video_Gl.h` instead.")
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Ring3/Input/_Include.h"

/// @brief
/// @param window The GLFW window.
/// @param entered The GLFW information of the pointer entered the window.
/// @return The mouse pointer event.
Machine_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerEnterExitEvent(GLFWwindow* window,
                                                                                int entered);

/// @brief
/// @param x The GLFW position of the mouse pointer along the GLFW x-axis.
/// @param y The GLFW position of the mouse pointer along the GLFW y-axis.
/// @return The mouse pointer event.
Machine_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerMoveEvent(GLFWwindow* window,
                                                                           double x, double y);

#endif // MACHINE_VIDEO_GL_INPUT_MOUSEPOINTER_H_INCLUDED
