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

/// @brief Get the number of events in the event queue.
/// @return The number of events in the event queue.
Machine_Integer Machine_Glfw_getNumberOfEvents();

/// @brief Peek at the most recent event in the event queue.
/// @return Pointer to the most recent event in the event queue.
/// The null pointer is returned if the event queue is empty.
Machine_Object* Machine_Glfw_peekEvent();

/// @brief Pop the most recent event in the event queue.
/// @return Pointer to the most recent event in the event queue.
/// The null pointer is returned if the event queue is empty.
Machine_Object* Machine_Glfw_popEvent();



#endif // MACHINE_VIDEO_GL_CANVASUTILITIES_INPUT_H_INCLUDED
