/// @file Gui/Gdl/Context.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_GDL_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_GDL_CONTEXT_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "_GDL.h"
#include "_Runtime.h"

/// @brief A context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Gdl_Context)

struct Machine_Gui_Gdl_Context_Class {
  Machine_Object_Class parent;
};

struct Machine_Gui_Gdl_Context {
  Machine_Object parent;

  Machine_GDL_Context* context;

#define DEFINE(NAME, STRING) Machine_String* NAME;
#include "Gui/Gdl/Context.i"
#undef DEFINE
};

/// @brief Create a GUI <-> GDL context.
/// @return The context.
Machine_Gui_Gdl_Context* Machine_Gui_Gdl_Context_create(Machine_GDL_Context* context);

#endif // MACHINE_GUI_GDL_CONTEXT_H_INCLUDED
