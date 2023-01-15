#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Literals/IntegerLiteral.h"
#undef RING3_GDL_PRIVATE

#include "Ring3/Gdl/parse.h"
#include "Ring1/Conversion.h"

static void
Ring3_Gdl_IntegerLiteral_visit
  (
    Ring3_Gdl_IntegerLiteral* self
  )
{
  if (self->literalString) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->literalString);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_IntegerLiteral /*type*/,
                         Ring3_Gdl_Literal /*parentType*/,
                         &Ring3_Gdl_IntegerLiteral_visit /*visit*/,
                         &Ring3_Gdl_IntegerLiteral_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

void
Ring3_Gdl_IntegerLiteral_construct
  (
    Ring3_Gdl_IntegerLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Gdl_Literal_construct(Ring1_cast(Ring3_Gdl_Literal*, self), numberOfArguments, arguments);
  self->literalString = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  parseInteger(Ring2_String_getBytes(self->literalString),
               Ring2_String_getBytes(self->literalString) + Ring2_String_getNumberOfBytes(self->literalString));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gdl_IntegerLiteral_getType());
}

Ring1_NoDiscardReturn() Ring3_Gdl_IntegerLiteral*
Ring3_Gdl_IntegerLiteral_create
  (
    Ring2_String* literalString
  )
{
  Machine_ClassType* ty = Ring3_Gdl_IntegerLiteral_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setString(&arguments[0], literalString);
  Ring3_Gdl_IntegerLiteral* self = (Ring3_Gdl_IntegerLiteral*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_IntegerLiteral_toInteger
  (
    Ring3_Gdl_IntegerLiteral* self
  )
{
  Ring2_assertNotNull(self);
  int64_t value;
  if (Ring1_Conversion_stringToInt64(&value,
                                     Ring2_String_getBytes(self->literalString),
                                     Ring2_String_getBytes(self->literalString) +
                                     Ring2_String_getNumberOfBytes(self->literalString))) {
    Ring2_jump();
  }
  return value;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gdl_IntegerLiteral_toReal32
  (
    Ring3_Gdl_IntegerLiteral* self
  )
{
  Ring2_assertNotNull(self);
  float value;
  if (Ring1_Conversion_stringToFloat(&value,
                                     Ring2_String_getBytes(self->literalString),
                                     Ring2_String_getBytes(self->literalString) +
                                     Ring2_String_getNumberOfBytes(self->literalString))) {
    Ring2_jump();
  }
  return value;
}

Ring1_NoDiscardReturn() Ring2_Real64
Ring3_Gdl_IntegerLiteral_toReal64
  (
    Ring3_Gdl_IntegerLiteral* self
  )
{
  Ring2_assertNotNull(self);
  double value;
  if (Ring1_Conversion_stringToDouble(&value,
                                      Ring2_String_getBytes(self->literalString),
                                      Ring2_String_getBytes(self->literalString) +
                                      Ring2_String_getNumberOfBytes(self->literalString))) {
    Ring2_jump();
  }
  return value;
}

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_IntegerLiteral_toString
  (
    Ring3_Gdl_IntegerLiteral* self
  )
{ return self->literalString; }
