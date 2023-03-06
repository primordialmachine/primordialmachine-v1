/// @file Ring3/Gui/WidgetList.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/WidgetList.h"
#undef RING3_GUI_PRIVATE

static void
addPrerequisites
  (
    Machine_InterfaceType* self
  )
{
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collections_List_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring3_Gui_WidgetList, &addPrerequisites)

void
Ring3_Gui_WidgetList_translate
  (
    Ring3_Gui_WidgetList* self,
    Ring3_Math_Vector2f32 const* t
  )
{
  MACHINE_VIRTUALIFACECALL_IMPL(Ring3_Gui_WidgetList, translate, ,self, t);
}
