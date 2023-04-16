#if !defined(RING3_GUI_SELECTORS_ITHCHILDSELECTOR_H_INCLUDED)
#define RING3_GUI_SELECTORS_ITHCHILDSELECTOR_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Selectors/IthChildSelector.h` directly, include `Ring/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/Selectors/Selector.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gui_IthChildSelector)

struct Ring3_Gui_IthChildSelector_Class {
  Ring3_Gui_Selector_Class _parent;
};

struct Ring3_Gui_IthChildSelector {
  Ring3_Gui_Selector _parent;
  /// @brief The zero-based index of the child.
  Ring2_Integer index;
};

void
Ring3_Gui_IthChildSelector_construct
  (
    Ring3_Gui_IthChildSelector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gui_IthChildSelector*
Ring3_Gui_IthChildSelector_create
  (
    Ring2_Integer index
  );

#endif // RING3_GUI_SELECTORS_ITHCHILDSELECTOR_H_INCLUDED
