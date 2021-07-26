#if !defined(MACHINE_GUI_CONTEXT_H_INCLUDED)
#define MACHINE_GUI_CONTEXT_H_INCLUDED



#include "./../GUI/GDL/Context.h"
#include "./../GUI/Signals/Context.h"



/// @brief A GUI context.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_Context)

struct Machine_GUI_Context {
  Machine_Object parent;
  Machine_GUI_Signals_Context* signalsContext;
  Machine_GUI_GDL_Context* gdlContext;
};

/// @brief Create a GUI ontext.
/// @param context The underlying GDL context.
/// @return The GUI context.
Machine_GUI_Context* Machine_GUI_Context_create(Machine_GDL_Context* context);



#endif // MACHINE_GUI_CONTEXT_H_INCLUDED
