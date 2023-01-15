#define RING3_GDL_PRIVATE (1)
#include "Ring3/Gdl/Literals/StringLiteral.h"
#undef RING3_GDL_PRIVATE

#include "Ring3/Gdl/parse.h"
#include "Ring1/Conversion.h"

static void
Ring3_Gdl_StringLiteral_visit
  (
    Ring3_Gdl_StringLiteral* self
  )
{
  if (self->literalString) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->literalString);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Gdl_StringLiteral /*type*/,
                         Ring3_Gdl_Literal /*parentType*/,
                         &Ring3_Gdl_StringLiteral_visit /*visit*/,
                         &Ring3_Gdl_StringLiteral_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

void
Ring3_Gdl_StringLiteral_construct
  (
    Ring3_Gdl_StringLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_Gdl_Literal_construct(Ring1_cast(Ring3_Gdl_Literal*, self), numberOfArguments, arguments);
  self->literalString = Ring2_CallArguments_getStringArgument(numberOfArguments, arguments, 0);
  parseString(Ring2_String_getBytes(self->literalString),
              Ring2_String_getBytes(self->literalString) + Ring2_String_getNumberOfBytes(self->literalString));
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Gdl_StringLiteral_getType());
}

Ring1_NoDiscardReturn() Ring3_Gdl_StringLiteral*
Ring3_Gdl_StringLiteral_create
  (
    Ring2_String * literalString
  )
{
  Machine_ClassType* ty = Ring3_Gdl_StringLiteral_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setString(&arguments[0], literalString);
  Ring3_Gdl_StringLiteral* self = (Ring3_Gdl_StringLiteral*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
  return self;
}

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_StringLiteral_toString
  (
    Ring3_Gdl_StringLiteral* self,
    bool canonicalize
  )
{
  Ring2_assertNotNull(self);
  if (canonicalize) {
    return Ring2_String_substring(Ring2_Context_get(), self->literalString,
                                                       1,
                                                       Ring2_String_getNumberOfBytes(self->literalString) - 2);
  } else {
    return self->literalString;
  }
}
