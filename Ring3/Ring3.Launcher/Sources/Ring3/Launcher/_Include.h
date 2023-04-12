#if !defined(RING3_LAUNCHER___INCLUDE_H_INCLUDED)
#define RING3_LAUNCHER___INCLUDE_H_INCLUDED

#include "Ring3/Math/_Include.h"
#include "Ring3/Visuals/_Include.h"


/// @brief Startup the launcher.
void
Ring3_Launcher_startup
  (
  );

/// @brief Shutdown the launcher.
void
Ring3_Launcher_shutdown
  (
  );

/// @brief Get the canvas.
/// @return The canvas.
Ring1_NoDiscardReturn() Ring3_Canvas*
Ring3_Launcher_getCanvas
  (
  );

/// @brief Get the visuals context.
/// @return The visuals context.
Ring1_NoDiscardReturn() Ring3_VisualsContext*
Ring3_Launcher_getVisualsContext
  (
  );

/// @brief Get the images context.
/// @return The images context.
Ring1_NoDiscardReturn() Ring3_ImagesContext*
Ring3_Launcher_getImagesContext
  (
  );

/// @brief Get the fonts context.
/// @return The fonts context.
Ring1_NoDiscardReturn() Ring3_FontsContext*
Ring3_Launcher_getFontsContext
  (
  );


#endif // RING3_LAUNCHER___INCLUDE_H_INCLUDED
