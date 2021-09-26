#if !defined(MACHINE_GLFW_CANVAS_H_INCLUDED)
#define MACHINE_GLFW_CANVAS_H_INCLUDED



#include "_Collections.h"
#include "_Runtime.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/glad.h>



/// @brief Startup canvas.
/// An undefined-op if the canvas is already started.
void Machine_GLFW_startupCanvas();

/// @brief Shutdown canvas.
/// An undefined-op if the canvas is not yet started.
void Machine_GLFW_shutdownCanvas();

/// @brief Get the canvas.
/// @return The canvas.
GLFWwindow* Machine_GLFW_getWindow();

void Machine_GLFW_maximizeCanvas();

void Machine_GLFW_getFrameBufferSize(Machine_Integer* width, Machine_Integer* height);

void Machine_GLFW_swapBuffers();

void Machine_GLFW_setCanvasIcons(Machine_List* images);



#endif // MACHINE_GLFW_CANVAS_H_INCLUDED
