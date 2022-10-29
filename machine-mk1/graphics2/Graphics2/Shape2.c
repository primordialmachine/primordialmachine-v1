/// @file Graphics2/Shape2.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "Graphics2/Shape2.h"


#include "Ring1/Intrinsic.h"


static void Machine_Shape2_visit(Machine_Shape2* self)
{/*Intentionally empty.*/}

void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Shape2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Shape2, Machine_Object, &Machine_Shape2_visit,
                         &Machine_Shape2_construct, NULL, NULL, NULL)

void Machine_Shape2_render(Machine_Shape2* self, Machine_Context2* context) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Shape2, render, context);
}
