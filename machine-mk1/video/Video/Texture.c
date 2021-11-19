/// @file Video/Texture.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Texture.h"



static void Machine_Texture_destruct(Machine_Texture* self)
{/*Intentionally empty.*/}

void Machine_Texture_construct(Machine_Texture* self, size_t numberOfArguments, const Machine_Value* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { {Machine_ValueFlag_Void, Machine_Void_Void} };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_Texture_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Texture, Machine_Object, NULL, &Machine_Texture_construct, &Machine_Texture_destruct, NULL)
