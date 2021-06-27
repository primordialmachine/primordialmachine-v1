/// @file Video/ShaderProgram.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "./../Video/ShaderProgram.h"



static void Machine_ShaderProgram_visit(Machine_ShaderProgram* self)
{/*Intentionally empty.*/}

static void Machine_ShaderProgram_destruct(Machine_ShaderProgram* self)
{/*Intentionally empty.*/}

void Machine_ShaderProgram_construct(Machine_ShaderProgram* self, size_t numberOfArguments, Machine_Value const* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_ShaderProgram_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_ShaderProgram, Machine_Object, Machine_ShaderProgram_visit, Machine_ShaderProgram_construct, Machine_ShaderProgram_destruct)

size_t Machine_ShaderProgram_getNumberOfInputs(Machine_ShaderProgram const* self) {
  return self->getNumberOfInputs(self);
}

Machine_ProgramInput* Machine_ShaderProgram_getInputAt(Machine_ShaderProgram const* self, size_t index) {
  return self->getInputAt(self, index);
}

bool Machine_ShaderProgram_addUpdateInput(Machine_ShaderProgram* self, Machine_String* name, Machine_ProgramInputType type, Machine_ProgramInputKind kind) {
  return self->addUpdateInput(self, name, type, kind);
}
