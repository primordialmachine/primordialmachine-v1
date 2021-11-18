/// @file Gui/Signals/Context.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_SIGNALS_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_SIGNALS_CONTEXT_H_INCLUDED



#include "_Signals.h"



/// @brief A context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Signals_Context)

struct Machine_Gui_Signals_Context_Class {
  Machine_Object_Class parent;
};

struct Machine_Gui_Signals_Context {
  Machine_Object parent;
  
#define DEFINE(NAME,STRING) \
  Machine_String *NAME;
#include "Gui/Signals/Context.i"
#undef DEFINE

};

/// @brief Create a GUI <-> Signals context.
/// @return The context.
Machine_Gui_Signals_Context* Machine_Gui_Signals_Context_create();

#endif // MACHINE_GUI_SIGNALS_CONTEXT_H_INCLUDED
