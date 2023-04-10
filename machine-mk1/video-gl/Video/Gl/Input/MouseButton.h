/// @file Video/Gl/Input/MouseButton.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_VIDEO_GL_INPUT_MOUSEBUTTON_H_INCLUDED)
#define MACHINE_VIDEO_GL_INPUT_MOUSEBUTTON_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/Input/MouseButton.h` directly, include `_Video_Gl.h` instead.")
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Ring3/Input/_Include.h"

/// @brief
/// @param button The GLFW mouse button.
/// @param action The GLFW mouse button action.
/// @param modifiers The GLFW modifiers.
/// @return The mouse button event.
Ring3_MouseButtonEvent* Machine_Video_Gl_Input_mapMouseButtonEvent(GLFWwindow* window, int button,
                                                                   int action, int modifiers);

#endif // MACHINE_VIDEO_GL_INPUT_MOUSEBUTTON_H_INCLUDED
