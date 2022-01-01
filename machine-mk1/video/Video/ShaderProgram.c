/// @file Video/ShaderProgram.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/ShaderProgram.h"

static void Machine_ShaderProgram_visit(Machine_ShaderProgram* self) { /*Intentionally empty.*/
}

static void Machine_ShaderProgram_destruct(Machine_ShaderProgram* self) { /*Intentionally empty.*/
}

void Machine_ShaderProgram_construct(Machine_ShaderProgram* self, size_t numberOfArguments,
                                     Machine_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_ShaderProgram_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_ShaderProgram, Machine_Object, Machine_ShaderProgram_visit,
                         Machine_ShaderProgram_construct, Machine_ShaderProgram_destruct, NULL,
                         NULL)

size_t Machine_ShaderProgram_getNumberOfInputs(Machine_ShaderProgram const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_ShaderProgram, getNumberOfInputs);
}

Machine_ProgramInput* Machine_ShaderProgram_getInputAt(Machine_ShaderProgram const* self,
                                                       size_t index) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_ShaderProgram, getInputAt, index);
}

Machine_Boolean Machine_ShaderProgram_addUpdateInput(Machine_ShaderProgram* self,
                                                     Machine_String* name,
                                                     Machine_ProgramInputType type,
                                                     Machine_ProgramInputKind kind) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_ShaderProgram, addUpdateInput, name, type, kind);
}
