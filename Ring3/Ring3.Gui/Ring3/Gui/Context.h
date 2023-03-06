/// @file Ring3/Gui/Context.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_CONTEXT_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Context.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/header.h.i"
#include "Ring3/Gui/Gdl/Context.h"
#include "Ring3/Gui/GroupNode.h"
#include "Ring3/Gui/Signals/Context.h"

/// @brief A GUI context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Context)

struct Machine_Gui_Context_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gui_Context {
  Machine_Object __parent;
  Ring3_Context2* context2;
  Machine_Gui_Widget* rootWidget;
  Machine_Gui_Signals_Context* signalsContext;
  Ring3_Gui_Gdl_Context* gdlContext;

  /// @brief The path of the file of the default font.
  Ring2_String* defaultFontFile;
  /// @brief The size, in points, of the default font.
  Ring2_Integer defaultFontSize;
};

/// @brief Create a GUI context.
/// @param gdlContext The underlying GDL context.
/// @param context2 The underlying 2D context.
/// @return The GUI context.
Ring1_NoDiscardReturn() Machine_Gui_Context*
Machine_Gui_Context_create
  (
    Machine_Gdl_Context* gdlContext,
    Ring3_Context2* context2
  );

void
Machine_Gui_Context_onCanvasSizechanged
  (
    Machine_Gui_Context* self,
    Ring3_CanvasSizeChangedEvent* event
  );

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Context_getCanvasWidth
  (
    Machine_Gui_Context* self
  );

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_Context_getCanvasHeight
  (
    Machine_Gui_Context* self
  );

/// @brief Set the root widget.
/// @param self This GUI context.
/// @param rootWidge The root widget or null.
void
Machine_Gui_Context_setRootWidget
  (
    Machine_Gui_Context* self,
    Machine_Gui_Widget* rootWidget
  );

/// @brief Get the root widget.
/// @param self This GUI context.
/// @return The root widget or null.
Ring1_NoDiscardReturn() Machine_Gui_Widget*
Machine_Gui_Context_getRootWidget
  (
    Machine_Gui_Context const* self
  );

void
Machine_Gui_Context_onRender
  (
    Machine_Gui_Context* self
  );

#endif // MACHINE_GUI_CONTEXT_H_INCLUDED
