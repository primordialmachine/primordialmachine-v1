/// @file Video/Gl/Input/MousePointer.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_INPUT_MOUSEPOINTER_H_INCLUDED)
#define MACHINE_VIDEO_GL_INPUT_MOUSEPOINTER_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "_Input.h"

/// @brief 
/// @param x The GLFW position of the mouse pointer along the GLFW x-axis.
/// @param y The GLFW position of the mouse pointer along the GLFW y-axis.
/// @return The mouse pointer event. 
Machine_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerEvent(GLFWwindow* window, double x,
                                                                       double y);

#endif // MACHINE_VIDEO_GL_INPUT_MOUSEPOINTER_H_INCLUDED
