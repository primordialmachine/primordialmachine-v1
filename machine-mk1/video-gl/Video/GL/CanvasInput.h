#if !defined(MACHINE_GLFW_INPUT_H_INCLUDED)
#define MACHINE_GLFW_INPUT_H_INCLUDED



#include "./../GL/Canvas.h"



/// @brief Startup canvas input (mouse, keyboard).
/// An undefined-op
/// - if the canvas is not started
/// - if the canvas input is already started.
void Machine_GLFW_startupCanvasInput();

/// @brief Shutdown canvas input (mouse, keyboard).
/// An undefined op if the canvas input is not yet start.
void Machine_GLFW_shutdownCanvasInput();

/// @brief Poll events from all sources and add them to the event queue.
void Machine_GLFW_pollEvents();

/// @brief Get the number of events in the event queue.
/// @return The number of events in the event queue.
Machine_Integer Machine_GLFW_getNumberOfEvents();

/// @brief Peek at the most recent event in the event queue.
/// @return Pointer to the most recent event in the event queue.
/// The null pointer is returned if the event queue is empty.
Machine_Object* Machine_GLFW_peekEvent();

/// @brief Pop the most recent event in the event queue.
/// @return Pointer to the most recent event in the event queue.
/// The null pointer is returned if the event queue is empty.
Machine_Object* Machine_GLFW_popEvent();



#endif // MACHINE_GLFW_INPUT_H_INCLUDED
