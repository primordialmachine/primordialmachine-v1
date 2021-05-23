/// @file Input/MouseButtonEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "./../Input/MouseButtonEvent.h"

static void Machine_MouseButtonEvent_visit(Machine_MouseButtonEvent* self) {
  /*Intentionally empty.*/
}

static void Machine_MouseButtonEvent_construct(Machine_MouseButtonEvent* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->button = Machine_Value_getInteger(&arguments[0]);
  self->action = Machine_Value_getInteger(&arguments[1]);
  self->x = Machine_Value_getReal(&arguments[2]);
  self->y = Machine_Value_getReal(&arguments[3]);
  Machine_setClassType(self, Machine_MouseButtonEvent_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_MouseButtonEvent)
MACHINE_DEFINE_CLASSTYPE_EX(Machine_MouseButtonEvent, Machine_Object, &Machine_MouseButtonEvent_visit, &Machine_MouseButtonEvent_construct, NULL)

Machine_MouseButtonEvent* Machine_MouseButtonEvent_create(int button, int action, float x, float y) {
  Machine_ClassType* ty = Machine_MouseButtonEvent_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 4;
  Machine_Value ARGUMENTS[4];
  Machine_Value_setInteger(&ARGUMENTS[0], button);
  Machine_Value_setInteger(&ARGUMENTS[1], action);
  Machine_Value_setReal(&ARGUMENTS[2], x);
  Machine_Value_setReal(&ARGUMENTS[3], y);
  Machine_MouseButtonEvent* self = (Machine_MouseButtonEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
