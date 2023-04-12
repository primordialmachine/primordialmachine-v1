/// @file Ring3/Gui/Signals/Context.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_SIGNALS_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_SIGNALS_CONTEXT_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "Ring3/Signals/_Include.h"

/// @brief A GUI signals context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Signals_Context)

struct Machine_Gui_Signals_Context_Class {
  Machine_Object_Class parent;
};

struct Machine_Gui_Signals_Context {
  Machine_Object parent;

#define DEFINE(NAME, STRING) Ring2_String* NAME;
#include "Ring3/Gui/Signals/Context.i"
#undef DEFINE
};

/// @brief Create a GUI <-> Signals context.
/// @return The context.
Ring1_NoDiscardReturn() Machine_Gui_Signals_Context*
Machine_Gui_Signals_Context_create
  (
  );

#endif // MACHINE_GUI_SIGNALS_CONTEXT_H_INCLUDED
