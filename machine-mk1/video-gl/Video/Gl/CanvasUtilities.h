/// @file Video/Gl/CanvasUtilities.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_CANVASUTILITIES_INPUT_H_INCLUDED)
#define MACHINE_VIDEO_GL_CANVASUTILITIES_INPUT_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_Gl.h` instead.")
#endif
#include "Video/Gl/Canvas.h"

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