#if !defined(RING3_GDL_LITERAL_VOIDLITERAL_H_INCLUDED)
#define RING3_GDL_LITERAL_VOIDLITERAL_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Literals/VoidLiteral.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"
#include "Ring3/Gdl/Literal.h"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_VoidLiteral)

struct Ring3_Gdl_VoidLiteral_Class {
  Ring3_Gdl_Literal_Class parent;
};

struct Ring3_Gdl_VoidLiteral {
  Ring3_Gdl_Literal parent;
  Ring2_String* literalString;
};

void
Ring3_Gdl_VoidLiteral_construct
  (
    Ring3_Gdl_VoidLiteral* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Gdl_VoidLiteral*
Ring3_Gdl_VoidLiteral_create
  (
    Ring2_String* literalString
  );

Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gdl_VoidLiteral_toString
  (
    Ring3_Gdl_VoidLiteral* self
  );

#endif // RING3_GDL_LITERAL_VOIDLITERAL_H_INCLUDED
