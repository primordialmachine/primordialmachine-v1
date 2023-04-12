/// @file Ring3/Visuals/CanvasSizeChangedEvent.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/CanvasSizeChangedEvent.h"
#undef RING2_VISUALS_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_CanvasSizeChangedEvent_visit
  (
    Ring3_CanvasSizeChangedEvent* self
  )
{/*Intentionally empty.*/}

static void
Ring3_CanvasSizeChangedEvent_construct
  (
    Ring3_CanvasSizeChangedEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->width = Ring2_Value_getReal32(&arguments[0]);
  self->height = Ring2_Value_getReal32(&arguments[1]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_CanvasSizeChangedEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_CanvasSizeChangedEvent,
                         Machine_Object,
                         &Ring3_CanvasSizeChangedEvent_visit,
                         &Ring3_CanvasSizeChangedEvent_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_CheckReturn() Ring3_CanvasSizeChangedEvent*
Ring3_CanvasSizeChangedEvent_create
  (
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  Machine_Type* ty = Ring3_CanvasSizeChangedEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setReal32(&arguments[0], width);
  Ring2_Value_setReal32(&arguments[1], height);
  Ring3_CanvasSizeChangedEvent* self = Ring1_cast(Ring3_CanvasSizeChangedEvent*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
