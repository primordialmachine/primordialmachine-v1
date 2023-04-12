/// @file Ring3/Visuals/Texture.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Texture.h"
#undef RING3_VISUALS_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_Texture_destruct
  (
    Ring3_Texture* self
  )
{/*Intentionally empty.*/}

void
Ring3_Texture_construct
  (
    Ring3_Texture* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Texture_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Texture,
                         Machine_Object,
                         NULL,
                         &Ring3_Texture_construct,
                         &Ring3_Texture_destruct,
                         NULL,
                         NULL)
