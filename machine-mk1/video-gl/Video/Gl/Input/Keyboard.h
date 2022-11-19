/// @file Video/Gl/Input/Keyboard.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_INPUT_KEYBOARD_H_INCLUDED)
#define MACHINE_VIDEO_GL_INPUT_KEYBOARD_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/Input/Keyboard.h` directly, include `_Video_Gl.h` instead.")
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Ring3/Input/_Include.h"

/// @brief
/// @param key The GLFW key.
/// @param scancode The GLFW scancode.
/// @param action The GLFW action.
/// @param modifiers The GLFW modifiers.
/// @return The keyboard key event.
Machine_KeyboardKeyEvent* Machine_Video_Gl_Input_mapKeyboardKeyEvent(GLFWwindow* window, int key,
                                                                     int scancode, int action,
                                                                     int modifiers);

#endif // MACHINE_VIDEO_GL_INPUT_KEYBOARD_H_INCLUDED
