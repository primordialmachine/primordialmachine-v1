/// @file Ring3/Graphics2/Shape2.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GRAPHICS2_PRIVATE (1)
#include "Ring3/Graphics2/Shape2.h"
#undef RING3_GRAPHICS2_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_Shape2_visit
  (
    Ring3_Shape2* self
  )
{/*Intentionally empty.*/}

void
Ring3_Shape2_construct
  (
    Ring3_Shape2* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Shape2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Shape2,
                         Machine_Object,
                         &Ring3_Shape2_visit,
                         &Ring3_Shape2_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Shape2_render
  (
    Ring3_Shape2* self,
    Ring3_Context2* context
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Shape2, render, context); }
