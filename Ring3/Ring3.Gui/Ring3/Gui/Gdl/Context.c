/// @file Ring3/Gui/Gdl/Context.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Gdl/Context.h"
#undef RING3_GUI_PRIVATE


static void
Ring3_Gui_Gdl_Context_visit
  (
    Ring3_Gui_Gdl_Context* self
  )
{
  if (self->context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->context);
  }
#define DEFINE(NAME, STRING)                                                                       \
  if (self->NAME) {                                                                                \
    Ring2_Gc_visit(Ring2_Gc_get(), self->NAME);                                                    \
  }
#include "Ring3/Gui/Gdl/Context.i"
#undef DEFINE
}

static void
Ring3_Gui_Gdl_Context_construct
  (
    Ring3_Gui_Gdl_Context* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  self->context = (Machine_Gdl_Context*)Ring2_Value_getObject(&arguments[0]);

#define DEFINE(NAME, STRING) self->NAME = Ring2_String_fromC(false, STRING);
#include "Ring3/Gui/Gdl/Context.i"
#undef DEFINE

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Gui_Gdl_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gui_Gdl_Context,
                         Machine_Object,
                         &Ring3_Gui_Gdl_Context_visit,
                         &Ring3_Gui_Gdl_Context_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Gui_Gdl_Context*
Ring3_Gui_Gdl_Context_create
  (
    Machine_Gdl_Context* context
  )
{
  Machine_ClassType* ty = Ring3_Gui_Gdl_Context_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context);
  Ring3_Gui_Gdl_Context* self = (Ring3_Gui_Gdl_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
