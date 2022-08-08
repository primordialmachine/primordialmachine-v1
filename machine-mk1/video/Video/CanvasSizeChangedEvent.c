/// @file Video/CanvasSizeChangedEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/CanvasSizeChangedEvent.h"

static void Machine_CanvasSizeChangedEvent_visit(Machine_CanvasSizeChangedEvent* self)
{/*Intentionally empty.*/}

static void Machine_CanvasSizeChangedEvent_construct(Machine_CanvasSizeChangedEvent* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->width = Machine_Value_getReal32(&arguments[0]);
  self->height = Machine_Value_getReal32(&arguments[1]);
  Machine_setClassType((Machine_Object *)self, Machine_CanvasSizeChangedEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_CanvasSizeChangedEvent, Machine_Object,
                         &Machine_CanvasSizeChangedEvent_visit,
                         &Machine_CanvasSizeChangedEvent_construct, NULL, NULL, NULL)

Machine_CanvasSizeChangedEvent* Machine_CanvasSizeChangedEvent_create(float width, float height) {
  Machine_ClassType* ty = Machine_CanvasSizeChangedEvent_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setReal32(&ARGUMENTS[0], width);
  Machine_Value_setReal32(&ARGUMENTS[1], height);
  Machine_CanvasSizeChangedEvent* self = (Machine_CanvasSizeChangedEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
