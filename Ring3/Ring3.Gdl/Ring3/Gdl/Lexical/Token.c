/// @file Ring3/Gdl/Lexical/Token.c
/// @copyright Copyright (c) 2021 - 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Lexical/Token.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"


static void Machine_Gdl_Token_visit(Machine_Gdl_Token *self) {
  if (self->text) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->text);
  }
}

static void Machine_Gdl_Token_construct(Machine_Gdl_Token* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->kind = Ring2_Value_getInteger(&arguments[0]);
  self->text = Ring2_Value_getString(&arguments[1]);
  self->offset = Ring2_Value_getInteger(&arguments[2]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gdl_Token_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gdl_Token /*type*/,
                         Machine_Object /*parentType*/,
                         &Machine_Gdl_Token_visit /*visit*/,
                         &Machine_Gdl_Token_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

Ring1_NoDiscardReturn() Machine_Gdl_Token*
Machine_Gdl_Token_create
  (
    Machine_Gdl_TokenKind kind,
    Ring2_String* text,
    Ring2_Integer offset
  )
{
  Machine_ClassType* ty = Machine_Gdl_Token_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3];
  Ring2_Value_setInteger(&ARGUMENTS[0], kind);
  Ring2_Value_setString(&ARGUMENTS[1], text);
  Ring2_Value_setInteger(&ARGUMENTS[2], offset);
  Machine_Gdl_Token* self = (Machine_Gdl_Token*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_NoDiscardReturn() Machine_Gdl_TokenKind
Machine_Gdl_Token_getKind
  (
    Machine_Gdl_Token const* self
  )
{ return self->kind; }

Ring1_NoDiscardReturn() Ring2_String*
Machine_Gdl_Token_getText
  (
    Machine_Gdl_Token const* self
  )
{ return self->text; }

Ring1_NoDiscardReturn() Ring2_Integer
Machine_Gdl_Token_getOffset
  (
    Machine_Gdl_Token const* self
  )
{ return self->offset; }
