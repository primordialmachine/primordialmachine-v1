/// @file Video/ProgramInput.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/ProgramInput.h"

static void Machine_ProgramInput_visit(Machine_ProgramInput* self) {
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
}

static void Machine_ProgramInput_construct(Machine_ProgramInput* self, size_t numberOfArguments,
                                           Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->name = Ring2_Value_getString(&arguments[0]);
  self->type = Ring2_Value_getInteger(&arguments[1]);
  self->kind = Ring2_Value_getInteger(&arguments[2]);
  Machine_setClassType((Machine_Object*)self, Machine_ProgramInput_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_ProgramInput, Machine_Object, &Machine_ProgramInput_visit,
                         &Machine_ProgramInput_construct, NULL, NULL, NULL)

Machine_ProgramInput* Machine_ProgramInput_create(Ring2_String* name,
                                                  Machine_ProgramInputType type,
                                                  Machine_ProgramInputKind kind) {
  Machine_ClassType* ty = Machine_ProgramInput_getType();
  Ring2_Value arguments[3];
  Ring2_Value_setString(&arguments[0], name);
  Ring2_Value_setInteger(&arguments[1], type);
  Ring2_Value_setInteger(&arguments[2], kind);
  Machine_ProgramInput* self = (Machine_ProgramInput*)Machine_allocateClassObject(ty, 3, arguments);
  return self;
}
