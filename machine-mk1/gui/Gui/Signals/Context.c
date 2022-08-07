/// @file Gui/Signals/Context.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Signals/Context.h"

#include <string.h>

static void Machine_Gui_Signals_Context_visit(Machine_Gui_Signals_Context* self) {
#define DEFINE(NAME, STRING)                                                                       \
  if (self->NAME) {                                                                                \
    Machine_Gc_visit(self->NAME);                                                                  \
  }
#include "Gui/Signals/Context.h"
#undef DEFINE
}

static void Machine_Gui_Signals_Context_construct(Machine_Gui_Signals_Context* self,
                                                  size_t numberOfArguments,
                                                  Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
#define DEFINE(NAME, STRING) self->NAME = Ring2_String_create(STRING, strlen(STRING));
#include "Gui/Signals/Context.i"
#undef DEFINE

  Machine_setClassType((Machine_Object*)self, Machine_Gui_Signals_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Signals_Context, Machine_Object,
                         &Machine_Gui_Signals_Context_visit, &Machine_Gui_Signals_Context_construct,
                         NULL, NULL, NULL)

Machine_Gui_Signals_Context* Machine_Gui_Signals_Context_create() {
  Machine_ClassType* ty = Machine_Gui_Signals_Context_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Ring2_Void_Void } };
  Machine_Gui_Signals_Context* self = (Machine_Gui_Signals_Context*)Machine_allocateClassObject(
      ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
