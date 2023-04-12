#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Selectors/Selector.h"
#undef RING3_GUI_PRIVATE

#include "Ring1/All/_Include.h"

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_Selector,
                         Machine_Object,
                         NULL,
                         &Ring3_Gui_Selector_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Gui_Selector_construct
  (
    Ring3_Gui_Selector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gui_Selector_getType());
}
