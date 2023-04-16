#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/DefaultMatcher.h"

#include "Ring3/Gui/Widget.h"
#undef RING3_GUI_PRIVATE

#include "Ring2/Library/_Include.h"

static void
Ring3_Gui_DefaultMatcher_visit
  (
    Ring3_Gui_DefaultMatcher* self
  );

static void
Ring3_Gui_DefaultMatcher_constructClass
  ( 
    Ring3_Gui_DefaultMatcher_Class* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_DefaultMatcher,
                         Machine_Object,
                         &Ring3_Gui_DefaultMatcher_visit,
                         &Ring3_Gui_DefaultMatcher_construct,
                         NULL,
                         &Ring3_Gui_DefaultMatcher_constructClass,
                         NULL)

static void
Ring3_Gui_DefaultMatcher_visit
  (
    Ring3_Gui_DefaultMatcher* self
  )
{}

static void
Ring3_Gui_DefaultMatcher_constructClass
  (
    Ring3_Gui_DefaultMatcher_Class* self
  )
{}

void
Ring3_Gui_DefaultMatcher_construct
  (
    Ring3_Gui_DefaultMatcher* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->root = (Ring3_Gui_Widget*)Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Ring1_cast(Machine_Type *,Ring3_Gui_Widget_getType()));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gui_DefaultMatcher_getType());
}

Ring1_NoDiscardReturn() Ring3_Gui_DefaultMatcher*
Ring3_Gui_DefaultMatcher_create
  (
    Ring3_Gui_Widget* widget
  )
{
  Machine_Type* ty = Ring3_Gui_DefaultMatcher_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerObject((Machine_Object*)widget) };
  Ring3_Gui_DefaultMatcher* self = (Ring3_Gui_DefaultMatcher*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
