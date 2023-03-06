/// @file Ring3/Gui/Gdl/Context.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_GDL_CONTEXT_H_INCLUDED)
#define RING3_GUI_GDL_CONTEXT_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Gdl/Context.h` directly, include `_Gui.h` instead.")
#endif
#include "Ring3/Gdl/_Include.h"

/// @brief A context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_Gdl_Context)

struct Ring3_Gui_Gdl_Context_Class {
  Machine_Object_Class parent;
};

struct Ring3_Gui_Gdl_Context {
  Machine_Object parent;

  Machine_Gdl_Context* context;

#define DEFINE(NAME, STRING) Ring2_String* NAME;
#include "Ring3/Gui/Gdl/Context.i"
#undef DEFINE
};

/// @brief Create a GUI <-> GDL context.
/// @return The context.
Ring1_NoDiscardReturn() Ring3_Gui_Gdl_Context*
Ring3_Gui_Gdl_Context_create
  (
    Machine_Gdl_Context* context
  );

#endif // RING3_GUI_GDL_CONTEXT_H_INCLUDED
