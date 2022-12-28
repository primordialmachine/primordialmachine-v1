/// @file Ring3/Visuals/Image.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Image.h"
#undef RING3_VISUALS_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_Image_destruct
  (
    Ring3_Image* self
  )
{/*Intentionally empty.*/}

void
Ring3_Image_construct
  (
    Ring3_Image* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Image_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Image,
                         Machine_Object,
                         NULL,
                         &Ring3_Image_construct,
                         &Ring3_Image_destruct,
                         NULL,
                         NULL)

void const*
Ring3_Image_getPixels
  (
    Ring3_Image const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Image, getPixels); }

void
Ring3_Image_getSize
  (
    Ring3_Image const* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Image, getSize, width, height); }

Ring1_NoDiscardReturn() Ring3_PixelFormat
Ring3_Image_getPixelFormat
  (
    Ring3_Image const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Image, getPixelFormat); }
