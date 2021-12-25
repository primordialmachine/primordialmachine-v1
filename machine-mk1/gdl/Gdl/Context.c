/// @file Gdl/Context.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gdl/Context.h"

#include <string.h>

static void Machine_Gdl_Context_visit(Machine_Gdl_Context* self) {
  if (self->trueLiteral) {
    Machine_Gc_visit(self->trueLiteral);
  }
  if (self->falseLiteral) {
    Machine_Gc_visit(self->falseLiteral);
  }
  if (self->voidLiteral) {
    Machine_Gc_visit(self->voidLiteral);
  }
}

static void Machine_Gdl_Context_construct(Machine_Gdl_Context* self, size_t numberOfArguments,
                                          Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->trueLiteral = Machine_String_create("true", strlen("true"));
  self->falseLiteral = Machine_String_create("false", strlen("false"));
  self->voidLiteral = Machine_String_create("void", strlen("void"));
  Machine_setClassType((Machine_Object*)self, Machine_Gdl_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Context, Machine_Object, &Machine_Gdl_Context_visit,
                         &Machine_Gdl_Context_construct, NULL, NULL, NULL)

Machine_Gdl_Context* Machine_Gdl_Context_create(Machine_String* inputName,
                                                Machine_ByteBuffer* inputBytes) {
  Machine_ClassType* ty = Machine_Gdl_Context_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Gdl_Context* self = (Machine_Gdl_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
