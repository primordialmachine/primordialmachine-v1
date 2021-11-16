/// @file Gui/Context.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_CONTEXT_H_INCLUDED



#include "Gui/Gdl/Context.h"
#include "Gui/Signals/Context.h"
#include "Gui/Group.h"
#include "_Graphics2.h"



/// @brief A GUI context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_Context)

struct Machine_GUI_Context_Class {
  Machine_Object_Class __parent;
};

struct Machine_GUI_Context {
  Machine_Object __parent;
  Machine_Context2* context2;
  Machine_GUI_Group* rootGroup;
  Machine_GUI_Signals_Context* signalsContext;
  Machine_GUI_GDL_Context* gdlContext;
};

/// @brief Create a GUI ontext.
/// @param gdlContext The underlying GDL context.
/// @param context2 The underlying 2D context.
/// @return The GUI context.
Machine_GUI_Context* Machine_GUI_Context_create(Machine_GDL_Context* gdlContext, Machine_Context2* context2);

void Machine_GUI_Context_onCanvasSizechanged(Machine_GUI_Context* self, Machine_CanvasSizeChangedEvent* event);

Machine_Real Machine_GUI_Context_getCanvasWidth(Machine_GUI_Context* self);

Machine_Real Machine_GUI_Context_getCanvasHeight(Machine_GUI_Context* self);

/// @brief Set the root group.
/// @param self This GUI context.
/// @param rootGroup The root group or null.
void Machine_GUI_Context_setRootGroup(Machine_GUI_Context* self, Machine_GUI_Group* rootGroup);

/// @brief Get the root group.
/// @param self This GUI context.
/// @return The root group or null.
Machine_GUI_Group* Machine_GUI_Context_getRootGroup(Machine_GUI_Context const* self);

void Machine_GUI_Context_onRender(Machine_GUI_Context* self);

#endif // MACHINE_GUI_CONTEXT_H_INCLUDED
