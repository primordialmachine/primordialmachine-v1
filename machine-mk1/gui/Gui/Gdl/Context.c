/// @file Gui/Gdl/Context.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Gdl/Context.h"

#include <string.h>

static void Machine_Gui_Gdl_Context_visit(Machine_Gui_Gdl_Context* self) {
  if (self->context) {
    Machine_Gc_visit(self->context);
  }
#define DEFINE(NAME, STRING)                                                                       \
  if (self->NAME) {                                                                                \
    Machine_Gc_visit(self->NAME);                                                                  \
  }
#include "Gui/Gdl/Context.h"
#undef DEFINE
}

static void Machine_Gui_Gdl_Context_construct(Machine_Gui_Gdl_Context* self,
                                              size_t numberOfArguments,
                                              Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  self->context = (Machine_Gdl_Context*)Machine_Value_getObject(&arguments[0]);

#define DEFINE(NAME, STRING) self->NAME = Ring2_String_create(STRING, strlen(STRING));
#include "Gui/Gdl/Context.i"
#undef DEFINE

  Machine_setClassType((Machine_Object*)self, Machine_Gui_Gdl_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Gdl_Context, Machine_Object, &Machine_Gui_Gdl_Context_visit,
                         &Machine_Gui_Gdl_Context_construct, NULL, NULL, NULL)

Machine_Gui_Gdl_Context* Machine_Gui_Gdl_Context_create(Machine_Gdl_Context* context) {
  Machine_ClassType* ty = Machine_Gui_Gdl_Context_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value ARGUMENTS[1];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context);
  Machine_Gui_Gdl_Context* self
      = (Machine_Gui_Gdl_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
