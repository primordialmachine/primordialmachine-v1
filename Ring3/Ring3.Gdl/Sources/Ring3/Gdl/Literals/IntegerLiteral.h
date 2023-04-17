// @file Ring3/Gdl/Literals/IntegerLiteral.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LITERAL_INTEGERLITERAL_H_INCLUDED)
#define RING3_GDL_LITERAL_INTEGERLITERAL_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Literals/IntegerLiteral.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"
#include "Ring3/Gdl/Literal.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_IntegerLiteral)

struct Ring3_Gdl_IntegerLiteral_Class {
  Ring3_Gdl_Literal_Class parent;
};

struct Ring3_Gdl_IntegerLiteral {
  Ring3_Gdl_Literal parent;
  Ring2_String* literalString;
};

void
Ring3_Gdl_IntegerLiteral_construct
  (
    Ring3_Gdl_IntegerLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gdl_IntegerLiteral*
Ring3_Gdl_IntegerLiteral_create
  (
    Ring2_String* literalString
  );

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_Gdl_IntegerLiteral_toInteger
  (
    Ring3_Gdl_IntegerLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Gdl_IntegerLiteral_toReal32
  (
    Ring3_Gdl_IntegerLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_Real64
Ring3_Gdl_IntegerLiteral_toReal64
  (
    Ring3_Gdl_IntegerLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_IntegerLiteral_toString
  (
    Ring3_Gdl_IntegerLiteral* self
  );

#endif // RING3_GDL_LITERAL_INTEGERLITERAL_H_INCLUDED
