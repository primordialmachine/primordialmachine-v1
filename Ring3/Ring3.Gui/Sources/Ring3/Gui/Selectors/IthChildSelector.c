#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Selectors/IthChildSelector.h"
#undef RING3_GUI_PRIVATE

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_IthChildSelector,
                         Ring3_Gui_Selector,
                         NULL,
                         &Ring3_Gui_IthChildSelector_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Gui_IthChildSelector_construct
  (
    Ring3_Gui_IthChildSelector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_Value argument = Ring2_Value_StaticInitializerInteger(Ring3_Gui_SelectorKind_IthChild);
  Ring3_Gui_Selector_construct((Ring3_Gui_Selector*)self, 1, &argument);
  self->index = Ring2_CallArguments_getIntegerArgument(numberOfArguments, arguments, 0);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gui_IthChildSelector_getType());
}

Ring1_NoDiscardReturn() Ring3_Gui_IthChildSelector*
Ring3_Gui_IthChildSelector_create
  (
    Ring2_Integer index
  )
{
  Machine_Type* ty = Ring3_Gui_IthChildSelector_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerInteger(index) };
  Ring3_Gui_IthChildSelector* self = Ring1_cast(Ring3_Gui_IthChildSelector*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
