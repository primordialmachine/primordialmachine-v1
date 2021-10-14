/// @file GDL/Context.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GDL/Context.h"


#include <string.h>


static void Machine_GDL_Context_visit(Machine_GDL_Context* self) {
  if (self->trueLiteral) {
    Machine_visit(self->trueLiteral);
  }
  if (self->falseLiteral) {
    Machine_visit(self->falseLiteral);
  }
  if (self->voidLiteral) {
    Machine_visit(self->voidLiteral);
  }
}

static void Machine_GDL_Context_construct(Machine_GDL_Context* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->trueLiteral = Machine_String_create("true", strlen("true"));
  self->falseLiteral = Machine_String_create("false", strlen("false"));
  self->voidLiteral = Machine_String_create("void", strlen("void"));
  Machine_setClassType((Machine_Object*)self, Machine_GDL_Context_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_GDL_Context, Machine_Object, &Machine_GDL_Context_visit, &Machine_GDL_Context_construct, NULL, NULL)

Machine_GDL_Context* Machine_GDL_Context_create(Machine_String* inputName, Machine_ByteBuffer* inputBytes) {
  Machine_ClassType* ty = Machine_GDL_Context_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GDL_Context* self = (Machine_GDL_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
