/// @file Gui/Context.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_CONTEXT_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "Gui/Gdl/Context.h"
#include "Gui/GroupNode.h"
#include "Gui/Signals/Context.h"
#include "_Graphics2.h"

/// @brief A GUI context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Context)

struct Machine_Gui_Context_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gui_Context {
  Machine_Object __parent;
  Machine_Context2* context2;
  Machine_Gui_GroupNode* rootGroup;
  Machine_Gui_Signals_Context* signalsContext;
  Machine_Gui_Gdl_Context* gdlContext;
};

/// @brief Create a GUI context.
/// @param gdlContext The underlying GDL context.
/// @param context2 The underlying 2D context.
/// @return The GUI context.
Machine_Gui_Context* Machine_Gui_Context_create(Machine_GDL_Context* gdlContext,
                                                Machine_Context2* context2);

void Machine_Gui_Context_onCanvasSizechanged(Machine_Gui_Context* self,
                                             Machine_CanvasSizeChangedEvent* event);

Machine_Real Machine_Gui_Context_getCanvasWidth(Machine_Gui_Context* self);

Machine_Real Machine_Gui_Context_getCanvasHeight(Machine_Gui_Context* self);

/// @brief Set the root group.
/// @param self This GUI context.
/// @param rootGroup The root group or null.
void Machine_Gui_Context_setRootGroup(Machine_Gui_Context* self, Machine_Gui_GroupNode* rootGroup);

/// @brief Get the root group.
/// @param self This GUI context.
/// @return The root group or null.
Machine_Gui_GroupNode* Machine_Gui_Context_getRootGroup(Machine_Gui_Context const* self);

void Machine_Gui_Context_onRender(Machine_Gui_Context* self);

#endif // MACHINE_GUI_CONTEXT_H_INCLUDED
