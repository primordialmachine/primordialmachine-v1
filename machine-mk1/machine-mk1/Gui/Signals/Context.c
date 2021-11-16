/// @file Gui/Signals/Context.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/Signals/Context.h"



#include <string.h>



static void Machine_GUI_Signals_Context_visit(Machine_GUI_Signals_Context* self) {
#define DEFINE(NAME, STRING) \
  if (self->NAME) { \
    Machine_Gc_visit(self->NAME); \
  }
#include "Gui/Signals/Context.h"
#undef DEFINE
}

static void Machine_GUI_Signals_Context_construct(Machine_GUI_Signals_Context* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
#define DEFINE(NAME,STRING) \
  self->NAME = Machine_String_create(STRING, strlen(STRING));
#include "Gui/Signals/Context.i"
#undef DEFINE

  Machine_setClassType((Machine_Object*)self, Machine_GUI_Signals_Context_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_GUI_Signals_Context, Machine_Object, &Machine_GUI_Signals_Context_visit, &Machine_GUI_Signals_Context_construct, NULL, NULL)

Machine_GUI_Signals_Context* Machine_GUI_Signals_Context_create() {
  Machine_ClassType* ty = Machine_GUI_Signals_Context_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GUI_Signals_Context* self = (Machine_GUI_Signals_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
