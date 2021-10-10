/// @file Video/Font.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "./../Video/Font.h"

static void Machine_Font_destruct(Machine_Font* self)
{/*Intentionally empty.*/}

void Machine_Font_construct(Machine_Font* self, size_t numberOfArguments, const Machine_Value* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { {Machine_ValueFlag_Void, Machine_Void_Void} };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_Font_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Font, Machine_Object, NULL, &Machine_Font_construct, &Machine_Font_destruct)

Machine_Real Machine_Font_getBaselineDistance(Machine_Font* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Font, getBaselineDistance);
}

Machine_Boolean Machine_Font_getCodePointInfo(Machine_Font* self, uint32_t codepoint, Machine_Math_Rectangle2* bounds, Machine_Math_Vector2* advance, Machine_Texture** texture) {
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
