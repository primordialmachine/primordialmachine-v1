#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Selectors/NameSelector.h"
#undef RING3_GUI_PRIVATE

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"

static void
Ring3_Gui_NameSelector_visit
  (
    Ring3_Gui_NameSelector* self
  )
{
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_NameSelector,
                         Ring3_Gui_Selector,
                         &Ring3_Gui_NameSelector_visit,
                         &Ring3_Gui_NameSelector_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Gui_NameSelector_construct
  (
    Ring3_Gui_NameSelector* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_Value argument = Ring2_Value_StaticInitializerInteger(Ring3_Gui_SelectorKind_Name);
  Ring3_Gui_Selector_construct((Ring3_Gui_Selector*)self, 1, &argument);
  self->name = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gui_NameSelector_getType());
}

Ring1_NoDiscardReturn() Ring3_Gui_NameSelector*
Ring3_Gui_NameSelector_create
  (
    Ring2_String* name
  )
{
  Machine_Type* ty = Ring3_Gui_NameSelector_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerString(name) };
  Ring3_Gui_NameSelector* self = Ring1_cast(Ring3_Gui_NameSelector*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
