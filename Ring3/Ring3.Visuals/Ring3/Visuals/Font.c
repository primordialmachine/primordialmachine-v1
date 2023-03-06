/// @file Ring3/Visuals/Font.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Font.h"
#undef RING3_VISUALS_PRIVATE

static void
Ring3_Font_destruct
  (
    Ring3_Font* self
  )
{/*Intentionally empty.*/}

void
Ring3_Font_construct
  (
    Ring3_Font* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Font_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Font,
                         Machine_Object,
                         NULL,
                         &Ring3_Font_construct,
                         &Ring3_Font_destruct,
                         NULL,
                         NULL)

Ring2_Real32
Ring3_Font_getBaselineDistance
  (
    Ring3_Font* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Font, getBaselineDistance); }

Ring2_Boolean
Ring3_Font_getCodePointInfo
  (
    Ring3_Font* self,
    uint32_t codepoint,
    Ring3_Math_Rectangle2* bounds,
    Ring3_Math_Vector2f32* advance,
    Ring3_Texture** texture
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_Font, getCodePointInfo, codepoint, bounds, advance, texture); }

Ring3_Binding*
Ring3_Font_getVideoBinding
  (
    Ring3_Font* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Font, getVideoBinding); }

Ring3_GpuProgram*
Ring3_Font_getVideoShaderProgram
  (
    Ring3_Font* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Font, getVideoShaderProgram); }

Ring3_GpuBuffer*
Ring3_Font_getVideoBuffer
  (
    Ring3_Font* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Font, getVideoBuffer); }
