/// @file Ring3/Gui/RenderContext.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_RENDERCONTEXT_H_INCLUDED)
#define RING3_GUI_RENDERCONTEXT_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/RenderContext.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Graphics2/_Include.h"

/// @brief The interface of a render context.
MACHINE_DECLARE_INTERFACETYPE(Ring3_Gui_RenderContext)

struct Ring3_Gui_RenderContext_Dispatch {
  Machine_InterfaceDispatch parent;

  Ring1_NoDiscardReturn() Ring3_Context2* (*getContext2)(Ring3_Gui_RenderContext*);
  Ring1_NoDiscardReturn() Ring2_Real32 (*getCanvasWidth)(Ring3_Gui_RenderContext*);
  Ring1_NoDiscardReturn() Ring2_Real32 (*getCanvasHeight)(Ring3_Gui_RenderContext*);
};

/// @brief Get the underlaying 2D context.
/// @param self This default render context.
/// @return The underlaying 2D context.
Ring1_NoDiscardReturn() Ring3_Context2*
Ring3_Gui_RenderContext_getContext2
  (
    Ring3_Gui_RenderContext* self
  );

/// @brief Get the width of the canvas.
/// @param self This default render context.
/// @return The width of the canvas.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_RenderContext_getCanvasWidth
  (
    Ring3_Gui_RenderContext* self
  );

/// @brief Get the width of the canvas.
/// @param self This default render context.
/// @return The width of the canvas.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_RenderContext_getCanvasHeight
  (
    Ring3_Gui_RenderContext* self
  );

#endif // RING3_GUI_RENDERCONTEXT_H_INCLUDED
