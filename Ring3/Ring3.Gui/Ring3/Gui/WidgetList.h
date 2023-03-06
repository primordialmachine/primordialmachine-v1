#if !defined(RING3_GUI_WIDGETLIST_H_INCLUDED)
#define RING3_GUI_WIDGETLIST_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE) || 1 != RING3_GUI_PRIVATE
#error("Do not include `Ring3/Gui/WidgetList.h` directly. Include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Math/_Include.h"

/// @extends Ring2.Collections.List
MACHINE_DECLARE_INTERFACETYPE(Ring3_Gui_WidgetList)

struct Ring3_Gui_WidgetList_Dispatch {
  Machine_InterfaceDispatch parent;

  void (*translate)(Ring3_Gui_WidgetList*, Ring3_Math_Vector2f32 const*);
};

/// @brief Translate the widgets in this widget list.
/// @param self This widget list.
/// @param t The translation vector.
void
Ring3_Gui_WidgetList_translate
  (
    Ring3_Gui_WidgetList* self,
    Ring3_Math_Vector2f32 const* t
  );

#endif // RING3_GUI_WIDGETLIST_H_INCLUDED
