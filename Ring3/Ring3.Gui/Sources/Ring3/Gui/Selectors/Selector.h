#if !defined(RING3_GUI_SELECTORS_SELECTOR_H_INCLUDED)
#define RING3_GUI_SELECTORS_SELECTOR_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Selectors/Selector.h` directly, include `Ring/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/Selectors/SelectorKind.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_Selector)

struct Ring3_Gui_Selector_Class {
  Machine_Object_Class parent;
};

struct Ring3_Gui_Selector {
  Machine_Object parent;
};

void
Ring3_Gui_Selector_construct
  (
    Ring3_Gui_Selector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

#endif // RING3_GUI_SELECTORS_SELECTOR_H_INCLUDED
