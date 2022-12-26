/// @file Video/Font.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Font.h"


#include "Ring1/All/_Include.h"


static void Machine_Font_destruct(Machine_Font* self)
{/*Intentionally empty.*/}

void Machine_Font_construct(Machine_Font* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Font_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Font, Machine_Object, NULL, &Machine_Font_construct,
                         &Machine_Font_destruct, NULL, NULL)

Ring2_Real32 Machine_Font_getBaselineDistance(Machine_Font* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Font, getBaselineDistance);
}

Ring2_Boolean Machine_Font_getCodePointInfo(Machine_Font* self, uint32_t codepoint, Ring3_Math_Rectangle2* bounds, Ring3_Math_Vector2f32* advance, Machine_Texture** texture) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_Font, getCodePointInfo, codepoint, bounds, advance, texture);
}

Machine_Binding* Machine_Font_getVideoBinding(Machine_Font* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Font, getVideoBinding);
}

Machine_ShaderProgram* Machine_Font_getVideoShaderProgram(Machine_Font* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Font, getVideoShaderProgram);
}

Machine_VideoBuffer* Machine_Font_getVideoBuffer(Machine_Font* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Font, getVideoBuffer);
}
