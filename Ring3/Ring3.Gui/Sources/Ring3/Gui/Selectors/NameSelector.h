#if !defined(RING3_GUI_SELECTORS_NAMESELECTOR_H_INCLUDED)
#define RING3_GUI_SELECTORS_NAMESELECTOR_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Selectors/NameSelector.h` directly, include `Ring/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/Selectors/Selector.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_NameSelector)

struct Ring3_Gui_NameSelector_Class {
  Ring3_Gui_Selector_Class _parent;
};

struct Ring3_Gui_NameSelector {
  Ring3_Gui_Selector _parent;
  /// @brief The name.
  Ring2_String *name;
};

void
Ring3_Gui_NameSelector_construct
  (
    Ring3_Gui_NameSelector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gui_NameSelector*
Ring3_Gui_NameSelector_create
  (
    Ring2_String* name
  );

#endif // RING3_GUI_SELECTORS_NAMESELECTOR_H_INCLUDED
