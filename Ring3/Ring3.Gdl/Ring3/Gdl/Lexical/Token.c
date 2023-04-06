/// @file Ring3/Gdl/Lexical/Token.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Lexical/Token.h"
#undef RING3_GDL_PRIVATE


#include "Ring1/All/_Include.h"


static void
Ring3_Gdl_Token_visit
  (
    Ring3_Gdl_Token *self
  )
{
  if (self->text) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->text);
  }
}

static void
Ring3_Gdl_Token_construct
  (
    Ring3_Gdl_Token* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->kind = Ring2_Value_getInteger(&arguments[0]);
  self->text = Ring2_Value_getString(&arguments[1]);
  self->start = Ring2_Value_getInteger(&arguments[2]);
  self->end = Ring2_Value_getInteger(&arguments[3]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Gdl_Token_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_Token /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring3_Gdl_Token_visit /*visit*/,
                         &Ring3_Gdl_Token_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

Ring1_NoDiscardReturn() Ring3_Gdl_Token*
Ring3_Gdl_Token_create
  (
    Ring3_Gdl_TokenKind kind,
    Ring2_String* text,
    Ring2_Integer start,
    Ring2_Integer end
  )
{
  Machine_Type* ty = Ring3_Gdl_Token_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[4];
  Ring2_Value_setInteger(&arguments[0], kind);
  Ring2_Value_setString(&arguments[1], text);
  Ring2_Value_setInteger(&arguments[2], start);
  Ring2_Value_setInteger(&arguments[3], end);
  Ring3_Gdl_Token* self = Ring1_cast(Ring3_Gdl_Token*,
                                     Machine_allocateClassObject(ty,
                                                                 NUMBER_OF_ARGUMENTS,
                                                                 arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Gdl_TokenKind
Ring3_Gdl_Token_getKind
  (
    Ring3_Gdl_Token const* self
  )
{ return self->kind; }

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_Token_getText
  (
    Ring3_Gdl_Token const* self
  )
{ return self->text; }

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_Token_getStart
  (
    Ring3_Gdl_Token const* self
  )
{ return self->start; }

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_Token_getEnd
  (
    Ring3_Gdl_Token const* self
  )
{ return self->end; }
