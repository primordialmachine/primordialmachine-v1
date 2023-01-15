#if !defined(RING3_GDL_LITERAL_REALLITERAL_H_INCLUDED)
#define RING3_GDL_LITERAL_REALLITERAL_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Literals/RealLiteral.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"
#include "Ring3/Gdl/Literal.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_RealLiteral)

struct Ring3_Gdl_RealLiteral_Class {
  Ring3_Gdl_Literal_Class parent;
};

struct Ring3_Gdl_RealLiteral {
  Ring3_Gdl_Literal parent;
  Ring2_String* literalString;
};

void
Ring3_Gdl_RealLiteral_construct
  (
    Ring3_Gdl_RealLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gdl_RealLiteral*
Ring3_Gdl_RealLiteral_create
  (
    Ring2_String* literalString
  );

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_RealLiteral_toInteger
  (
    Ring3_Gdl_RealLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gdl_RealLiteral_toReal32
  (
    Ring3_Gdl_RealLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_Real64
Ring3_Gdl_RealLiteral_toReal64
  (
    Ring3_Gdl_RealLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_RealLiteral_toString
  (
    Ring3_Gdl_RealLiteral* self
  );

#endif // RING3_GDL_LITERAL_REALLITERAL_H_INCLUDED
