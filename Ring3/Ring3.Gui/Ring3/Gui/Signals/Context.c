/// @file Ring3/Gui/Signals/Context.c
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/Signals/Context.h"
#undef RING3_GUI_PRIVATE


static void Machine_Gui_Signals_Context_visit(Machine_Gui_Signals_Context* self) {
#define DEFINE(NAME, STRING)                                                                       \
  if (self->NAME) {                                                                                \
    Ring2_Gc_visit(Ring2_Gc_get(), self->NAME);                                                    \
  }
#include "Ring3/Gui/Signals/Context.h"
#undef DEFINE
}

static void Machine_Gui_Signals_Context_construct(Machine_Gui_Signals_Context* self,
                                                  size_t numberOfArguments,
                                                  Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
#define DEFINE(NAME, STRING) self->NAME = Ring2_String_fromC(false, STRING);
#include "Ring3/Gui/Signals/Context.i"
#undef DEFINE

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_Signals_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Signals_Context, Machine_Object,
                         &Machine_Gui_Signals_Context_visit, &Machine_Gui_Signals_Context_construct,
                         NULL, NULL, NULL)

Ring1_NoDiscardReturn() Machine_Gui_Signals_Context*
Machine_Gui_Signals_Context_create
  (
  )
{
  Machine_Type* ty = Machine_Gui_Signals_Context_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gui_Signals_Context* self = Ring1_cast(Machine_Gui_Signals_Context*,Machine_allocateClassObject(
      ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
