/// @file Video/Gl/CanvasUtilities.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_VIDEO_GL_CANVASUTILITIES_INPUT_H_INCLUDED)
#define MACHINE_VIDEO_GL_CANVASUTILITIES_INPUT_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/CanvasUtilities.h` directly, include `_Video_Gl.h` instead.")
#endif
#include "Video/Gl/Canvas.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

/// @brief Get the GLFW window.
/// @return The GLFW window.
GLFWwindow* Machine_Glfw_getWindow();

/// @brief Startup canvas input (mouse, keyboard).
/// An undefined-op
/// - if the canvas is not started
/// - if the canvas input is already started.
void Machine_Glfw_startupCanvasInput();

/// @brief Shutdown canvas input (mouse, keyboard).
/// An undefined op if the canvas input is not yet start.
void Machine_Glfw_shutdownCanvasInput();

/// @brief Poll events from all sources and add them to the event queue.
void Machine_Glfw_pollEvents();

#endif // MACHINE_VIDEO_GL_CANVASUTILITIES_INPUT_H_INCLUDED
