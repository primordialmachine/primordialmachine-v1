/// @file Ring3/Gui/ArrayWidgetList.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_ARRAYWIDGETLIST_H_INCLUDED)
#define MACHINE_GUI_ARRAYWIDGETLIST_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/ArrayWidgetList.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/WidgetList.h"
typedef struct Ring3_Gui_Widget Ring3_Gui_Widget;


/// @brief A label to display a text.
/// @remarks The preferred size of a panel is computed by combining the rectangles of its child
/// nodes.
/// @extends Machine.Object
/// @implements Ring3.Gui.WidgetList
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_ArrayWidgetList)

/// @brief Create an empty panel.
/// @return The panel.
Ring1_NoDiscardReturn() Machine_Gui_ArrayWidgetList*
Machine_Gui_ArrayWidgetList_create
  (
  );

#endif // MACHINE_GUI_ARRAYWIDGETLIST_H_INCLUDED
