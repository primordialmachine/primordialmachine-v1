#if !defined(MKX_LAUNCHER_H_INCLUDED)
#define MKX_LAUNCHER_H_INCLUDED

#include "Ring3/Math/_Include.h"
#include "Ring3/Visuals/_Include.h"

/// @brief Startup the launcher.
void
Machine_Launcher_startup
  (
  );

/// @brief Shutdown the launcher.
void
Machine_Launcher_shutdown
  (
  );

/// @brief Get the canvas.
/// @return The canvas.
Ring1_NoDiscardReturn() Ring3_Canvas*
Machine_Launcher_getVideoCanvas
  (
  );

/// @brief Get the visuals context.
/// @return The visuals context.
Ring1_NoDiscardReturn() Ring3_VisualsContext*
Machine_Launcher_getVisualsContext
  (
  );

/// @brief Get the images context.
/// @return The images context.
Ring1_NoDiscardReturn() Ring3_ImagesContext*
Machine_Launcher_getImagesContext
  (
  );

/// @brief Get the fonts context.
/// @return The fonts context.
Ring1_NoDiscardReturn() Ring3_FontsContext*
Machine_Launcher_getFontsContext
  (
  );

#endif // MKX_LAUNCHER_H_INCLUDED
