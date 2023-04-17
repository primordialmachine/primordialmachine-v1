// @file Ring3/Gdl/Literals/BooleanLiteral.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GDL_LITERAL_BOOLEANLITERAL_H_INCLUDED)
#define RING3_GDL_LITERAL_BOOLEANLITERAL_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Literals/BooleanLiteral.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"
#include "Ring3/Gdl/Literal.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_BooleanLiteral)

struct Ring3_Gdl_BooleanLiteral_Class {
  Ring3_Gdl_Literal_Class parent;
};

struct Ring3_Gdl_BooleanLiteral {
  Ring3_Gdl_Literal parent;
  Ring2_String* literalString;
};

void
Ring3_Gdl_BooleanLiteral_construct
  (
    Ring3_Gdl_BooleanLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gdl_BooleanLiteral*
Ring3_Gdl_BooleanLiteral_create
  (
    Ring2_String* literalString
  );

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Gdl_BooleanLiteral_toBoolean
  (
    Ring3_Gdl_BooleanLiteral* self
  );

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_BooleanLiteral_toString
  (
    Ring3_Gdl_BooleanLiteral* self
  );

#endif // RING3_GDL_LITERAL_BOOLEANLITERAL_H_INCLUDED
