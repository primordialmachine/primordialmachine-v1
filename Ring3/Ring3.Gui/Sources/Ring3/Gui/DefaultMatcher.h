#if !defined(RING3_GUI_DEFAULTMATCHER_H_INCLUDED)
#define RING3_GUI_DEFAULTMATCHER_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/DefaultMatcher.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"
typedef struct Ring3_Gui_Widget Ring3_Gui_Widget;

MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_DefaultMatcher)

struct Ring3_Gui_DefaultMatcher_Class {
  Machine_Object_Class _parent;
};

struct Ring3_Gui_DefaultMatcher {
  Machine_Object _parent;
  /// @brief Pointer to the root widget.
  Ring3_Gui_Widget* root;
};

/// @brief Construct this matcher.
/// @param self This widget.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
/// @remarks
/// Signatures
/// @code
/// (Ring.Gui.Widget root)
/// @endcode
void
Ring3_Gui_DefaultMatcher_construct
  (
    Ring3_Gui_DefaultMatcher* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );
  
Ring1_NoDiscardReturn() Ring3_Gui_DefaultMatcher*
Ring3_Gui_DefaultMatcher_create
  (
    Ring3_Gui_Widget* widget
  );

#endif // RING3_GUI_DEFAULTMATCHER_H_INCLUDED
