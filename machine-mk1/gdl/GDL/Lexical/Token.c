/// @file Gdl/Lexical/Token.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../../GDL/Lexical/Token.h"

static void Machine_GDL_Token_visit(Machine_GDL_Token *self) {
  if (self->text) {
    Machine_Gc_visit(self->text);
  }
}

static void Machine_GDL_Token_construct(Machine_GDL_Token* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->kind = Machine_Value_getInteger(&arguments[0]);
  self->text = Machine_Value_getString(&arguments[1]);
  self->offset = Machine_Value_getInteger(&arguments[2]);
  Machine_setClassType((Machine_Object*)self, Machine_GDL_Token_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_GDL_Token, Machine_Object, &Machine_GDL_Token_visit,
                         &Machine_GDL_Token_construct, NULL, NULL, NULL)

Machine_GDL_Token* Machine_GDL_Token_create(Machine_GDL_TokenKind kind, Machine_String* text, Machine_Integer offset) {
  Machine_ClassType* ty = Machine_GDL_Token_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 3;
  Machine_Value ARGUMENTS[3];
  Machine_Value_setInteger(&ARGUMENTS[0], kind);
  Machine_Value_setString(&ARGUMENTS[1], text);
  Machine_Value_setInteger(&ARGUMENTS[2], offset);
  Machine_GDL_Token* self = (Machine_GDL_Token*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_GDL_TokenKind Machine_GDL_Token_getKind(const Machine_GDL_Token* self) {
  return self->kind;
}

Machine_String* Machine_GDL_Token_getText(const Machine_GDL_Token* self) {
  return self->text;
}

Machine_Integer Machine_GDL_Token_getOffset(const Machine_GDL_Token* self) {
  return self->offset;
}
