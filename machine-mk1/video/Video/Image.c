/// @file Video/Image.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Image.h"



static void Machine_Image_destruct(Machine_Image* self)
{/*Intentionally empty.*/}

void Machine_Image_construct(Machine_Image* self, size_t numberOfArguments, const Machine_Value* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { {Machine_ValueFlag_Void, Machine_Void_Void} };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_Image_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Image, Machine_Object, NULL, &Machine_Image_construct, &Machine_Image_destruct, NULL)

void const* Machine_Image_getPixels(Machine_Image const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Image, getPixels);
}

void Machine_Image_getSize(Machine_Image const* self, Machine_Integer* width, Machine_Integer* height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Image, getSize, width, height);
}

Machine_PixelFormat Machine_Image_getPixelFormat(Machine_Image const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Image, getPixelFormat);
}
