#if !defined(RING3_VISUALS_GL_INPUT__INCLUDE_H_INCLUDED)
#define RING3_VISUALS_GL_INPUT__INCLUDE_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Visuals/Gl/Input/_Include.h` directly. Include `Ring3/Visuals/Gl/_Include.h` instead.")
#endif

#include "Ring3/Visuals/Gl/Configuration.h"


/// @brief Create or increment the reference count the input callbacks registration.
/// @undefined window does not exist
/// @undefined reference counter overflows
void
Ring3_Visuals_Gl_Glfw_startupInput
  (
  );

/// @brief Decrement the reference count or destroy the input callbacks registration.
/// @undefined window does not exist
/// @undefined reference counter underflows
void
Ring3_Visuals_Gl_Glfw_shutdownInput
  (
  );

/// @brief Poll events from all sources and add them to the event queue.
void
Ring3_Visuals_Gl_Glfw_pollEvents
  (
  );


#endif // RING3_VISUALS_GL_INPUT__INCLUDE_H_INCLUDED
