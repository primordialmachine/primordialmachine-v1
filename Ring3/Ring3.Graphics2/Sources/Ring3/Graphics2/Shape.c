/// @file Ring3/Graphics2/Shape.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GRAPHICS2_PRIVATE (1)
#include "Ring3/Graphics2/Shape.h"
#undef RING3_GRAPHICS2_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_Graphics2_Shape_visit
  (
    Ring3_Graphics2_Shape* self
  )
{/*Intentionally empty.*/}

void
Ring3_Graphics2_Shape_construct
  (
    Ring3_Graphics2_Shape* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Graphics2_Shape_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Graphics2_Shape,
                         Machine_Object,
                         &Ring3_Graphics2_Shape_visit,
                         &Ring3_Graphics2_Shape_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Graphics2_Shape_render
  (
    Ring3_Graphics2_Shape* self,
    Ring3_Graphics2_Context* context
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Graphics2_Shape, render, context); }
