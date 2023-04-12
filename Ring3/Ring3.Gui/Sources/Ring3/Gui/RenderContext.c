/// @file Ring3/Gui/RenderContext.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/RenderContext.h"
#undef RING3_GUI_PRIVATE


MACHINE_DEFINE_INTERFACETYPE(Ring3_Gui_RenderContext, NULL)

Ring1_NoDiscardReturn() Ring3_Graphics2_Context*
Ring3_Gui_RenderContext_getContext2
  (
    Ring3_Gui_RenderContext* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_RenderContext, getContext2, return, self); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_RenderContext_getCanvasWidth
  (
    Ring3_Gui_RenderContext* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_RenderContext, getCanvasWidth, return, self); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gui_RenderContext_getCanvasHeight
  (
    Ring3_Gui_RenderContext* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_RenderContext, getCanvasHeight, return, self); }
