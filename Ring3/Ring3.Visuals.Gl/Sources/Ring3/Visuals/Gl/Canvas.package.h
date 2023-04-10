#if !defined(RING3_VISUALS_GL_CANVAS_PACKAGE_H_INCLUDED)
#define RING3_VISUALS_GL_CANVAS_PACKAGE_H_INCLUDED

#include "Ring3/Visuals/Gl/Canvas.h"
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_NONE
#include <glad/glad.h>

/// @{
  
/// @brief Get the GLFW window.
/// @return The GLFW window.
Ring1_NoDiscardReturn() GLFWwindow*
Ring3_Visuals_Gl_Glfw_getWindow
  (
  );

/// @brief Startup canvas.
/// An undefined-op if the canvas is already started.
void
Ring3_Visuals_Gl_Glfw_startupCanvas
  (
  );

/// @brief Shutdown canvas.
/// An undefined-op if the canvas is not yet started.
void
Ring3_Visuals_Gl_Glfw_shutdownCanvas
  (
  );
  
/// @}

#endif // RING3_VISUALS_GL_CANVAS_PACKAGE_H_INCLUDED
