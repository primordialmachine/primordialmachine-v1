/// @file Gdl/Lexical/Token.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gdl/Lexical/Token.h"

static void Machine_Gdl_Token_visit(Machine_Gdl_Token *self) {
  if (self->text) {
    Machine_Gc_visit(self->text);
  }
}

static void Machine_Gdl_Token_construct(Machine_Gdl_Token* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->kind = Machine_Value_getInteger(&arguments[0]);
  self->text = Machine_Value_getString(&arguments[1]);
  self->offset = Machine_Value_getInteger(&arguments[2]);
  Machine_setClassType((Machine_Object*)self, Machine_Gdl_Token_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Token, Machine_Object, &Machine_Gdl_Token_visit,
                         &Machine_Gdl_Token_construct, NULL, NULL, NULL)

Machine_Gdl_Token* Machine_Gdl_Token_create(Machine_Gdl_TokenKind kind, Machine_String* text, Machine_Integer offset) {
  Machine_ClassType* ty = Machine_Gdl_Token_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 3;
  Machine_Value ARGUMENTS[3];
  Machine_Value_setInteger(&ARGUMENTS[0], kind);
  Machine_Value_setString(&ARGUMENTS[1], text);
  Machine_Value_setInteger(&ARGUMENTS[2], offset);
  Machine_Gdl_Token* self = (Machine_Gdl_Token*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Gdl_TokenKind Machine_Gdl_Token_getKind(Machine_Gdl_Token const* self) {
  return self->kind;
}

Machine_String* Machine_Gdl_Token_getText(Machine_Gdl_Token const* self) {
  return self->text;
}

Machine_Integer Machine_Gdl_Token_getOffset(Machine_Gdl_Token const* self) {
  return self->offset;
}