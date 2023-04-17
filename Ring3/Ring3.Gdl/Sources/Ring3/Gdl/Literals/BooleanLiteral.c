// @file Ring3/Gdl/Literals/BooleanLiteral.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Literals/BooleanLiteral.h"
#undef RING3_GDL_PRIVATE

#include "Ring3/Gdl/parse.h"
#include "Ring1/Conversion.h"

static void
Ring3_Gdl_BooleanLiteral_visit
  (
    Ring3_Gdl_BooleanLiteral* self
  )
{
  if (self->literalString) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->literalString);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_BooleanLiteral /*type*/,
                         Ring3_Gdl_Literal /*parentType*/,
                         &Ring3_Gdl_BooleanLiteral_visit /*visit*/,
                         &Ring3_Gdl_BooleanLiteral_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

void
Ring3_Gdl_BooleanLiteral_construct
  (
    Ring3_Gdl_BooleanLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Gdl_Literal_construct(Ring1_cast(Ring3_Gdl_Literal*, self), numberOfArguments, arguments);
  self->literalString = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  parseBoolean(Ring2_String_getBytes(self->literalString),
               Ring2_String_getBytes(self->literalString) + Ring2_String_getNumberOfBytes(self->literalString));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gdl_BooleanLiteral_getType());
}

Ring1_NoDiscardReturn() Ring3_Gdl_BooleanLiteral*
Ring3_Gdl_BooleanLiteral_create
  (
    Ring2_String* literalString
  )
{
  Machine_Type* ty = Ring3_Gdl_BooleanLiteral_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setString(&arguments[0], literalString);
  Ring3_Gdl_BooleanLiteral* self = Ring1_cast(Ring3_Gdl_BooleanLiteral*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Gdl_BooleanLiteral_toBoolean
  (
    Ring3_Gdl_BooleanLiteral* self
  )
{
  Ring2_assertNotNull(self);
  bool value;
  if (Ring1_Conversion_stringToBool(&value,
                                    Ring2_String_getBytes(self->literalString),
                                    Ring2_String_getBytes(self->literalString) +
                                    Ring2_String_getNumberOfBytes(self->literalString))) {
    Ring2_jump();
  }
  return value;
}

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_BooleanLiteral_toString
  (
    Ring3_Gdl_BooleanLiteral* self
  )
{ return self->literalString; }
