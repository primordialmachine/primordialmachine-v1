#if !defined(RING3_GDL_LITERAL_H_INCLUDED)
#define RING3_GDL_LITERAL_H_INCLUDED

#if !defined(RING3_GDL_PRIVATE) || 1 != RING3_GDL_PRIVATE
#error("Do not include `Ring3/Gdl/Literal.h` directly. Include `Ring3/Gdl/_Include.h` instead.")
#endif
#include "Ring3/Gdl/header.h.i"

MACHINE_DECLARE_CLASSTYPE(Ring3_Gdl_Literal)

struct Ring3_Gdl_Literal_Class {
  Machine_Object_Class parent;
};

struct Ring3_Gdl_Literal {
  Machine_Object parent;
  Ring2_String* literalString;
};

void
Ring3_Gdl_Literal_construct
  (
    Ring3_Gdl_Literal* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

#endif // RING3_GDL_LITERAL_H_INCLUDED
