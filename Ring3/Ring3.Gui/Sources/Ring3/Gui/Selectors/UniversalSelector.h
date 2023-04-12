#if !defined(RING3_GUI_SELECTORS_UNIVERSALSELECTOR_H_INCLUDED)
#define RING3_GUI_SELECTORS_UNIVERSALSELECTOR_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Selectors/UniversalSelector.h` directly, include `Ring/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/Selectors/Selector.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_UniversalSelector)

struct Ring3_Gui_UniversalSelector_Class {
  Ring3_Gui_Selector_Class _parent;
};

struct Ring3_Gui_UniversalSelector {
  Ring3_Gui_Selector _parent;
};

void
Ring3_Gui_UniversalSelector_construct
  (
    Ring3_Gui_UniversalSelector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gui_UniversalSelector*
Ring3_Gui_UniversalSelector_create
  (
  );

#endif // RING3_GUI_SELECTORS_UNIVERSALSELECTOR_H_INCLUDED
