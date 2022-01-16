/// @file Video/Gl/Input/MouseButton.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_INPUT_MOUSEBUTTON_H_INCLUDED)
#define MACHINE_VIDEO_GL_INPUT_MOUSEBUTTON_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "_Input.h"

/// @brief 
/// @param button The GLFW mouse button.
/// @param action The GLFW mouse button action.
/// @param modifiers The GLFW modifiers.
/// @return The mouse button event.
Machine_MouseButtonEvent* Machine_Video_Gl_Input_mapMouseButtonEvent(GLFWwindow* window, int button,
                                                                     int action, int modifiers);

#endif // MACHINE_VIDEO_GL_INPUT_MOUSEBUTTON_H_INCLUDED
