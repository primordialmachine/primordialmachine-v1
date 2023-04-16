#if !defined(RING3_GUI_SELECTORS_SELECTORKIND_H_INCLUDED)
#define RING3_GUI_SELECTORS_SELECTORKIND_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Selectors/SelectorKind.h` directly, include `Ring/Gui/_Include.h` instead.")
#endif
#include "Ring2/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_Gui_SelectorKind)

enum Ring3_Gui_SelectorKind {
  /// @brief "name" selector.
  Ring3_Gui_SelectorKind_Name,
  /// @brief "i-th child" selector.
  Ring3_Gui_SelectorKind_IthChild,
  /// @brief "universal" selector.
  Ring3_Gui_SelectorKind_Universal,
};

#endif // RING3_GUI_SELECTORS_SELECTORKIND_H_INCLUDED
