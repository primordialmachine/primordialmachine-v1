/// @file Input/MousePointerEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "./../Input/MousePointerEvent.h"

static void Machine_MousePointerEvent_visit(Machine_MousePointerEvent* self) {
  /*Intentionally empty.*/
}

static void Machine_MousePointerEvent_construct(Machine_MousePointerEvent* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->x = Machine_Value_getReal(&arguments[0]);
  self->y = Machine_Value_getReal(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Machine_MousePointerEvent_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_MousePointerEvent, Machine_Object, &Machine_MousePointerEvent_visit, &Machine_MousePointerEvent_construct, NULL)

Machine_MousePointerEvent* Machine_MousePointerEvent_create(float x, float y) {
  Machine_ClassType* ty = Machine_MousePointerEvent_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setReal(&ARGUMENTS[0], x);
  Machine_Value_setReal(&ARGUMENTS[1], y);
  Machine_MousePointerEvent* self = (Machine_MousePointerEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
