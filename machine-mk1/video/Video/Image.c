/// @file Video/Image.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Image.h"


#include "Ring1/All/_Include.h"


static void Machine_Image_destruct(Machine_Image* self) { /*Intentionally empty.*/
}

void Machine_Image_construct(Machine_Image* self, size_t numberOfArguments,
                             Ring2_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Image_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Image, Machine_Object, NULL, &Machine_Image_construct,
                         &Machine_Image_destruct, NULL, NULL)

void const* Machine_Image_getPixels(Machine_Image const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Image, getPixels);
}

void Machine_Image_getSize(Machine_Image const* self, Ring2_Integer* width,
                           Ring2_Integer* height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Image, getSize, width, height);
}

Ring3_PixelFormat Machine_Image_getPixelFormat(Machine_Image const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Image, getPixelFormat);
}
