/// @file Video/Texture.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Texture.h"

static void Machine_Texture_destruct(Machine_Texture* self) { /*Intentionally empty.*/
}

void Machine_Texture_construct(Machine_Texture* self, size_t numberOfArguments,
                               Ring2_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_Texture_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Texture, Machine_Object, NULL, &Machine_Texture_construct,
                         &Machine_Texture_destruct, NULL, NULL)
