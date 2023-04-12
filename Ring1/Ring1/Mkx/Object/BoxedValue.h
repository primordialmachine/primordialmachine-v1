#if !defined(MKX_OBJECT_BOXEDVALUE_H_INCLUDED)
#define MKX_OBJECT_BOXEDVALUE_H_INCLUDED


#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/BoxedValue.h' directly, include 'Mkx/Object.h' instead.")
#endif


#include "Mkx/Object/ScalarTypes.h"
#include "Mkx/Object/Object.h"


Mkx_Type_DeclareClassType("Mkx.BoxedValue", Mkx_BoxedValue, MKX_BOXEDVALUE)


struct Mkx_BoxedValue {
  Mkx_Object parent;
  Mkx_Type* type;
  union {
    #define Define(CNAME) \
      CNAME m_##CNAME;
    #include "Mkx/Object/BoxedValue.i"
    #undef Define
  };
};

struct Mkx_BoxedValue_Dispatch {
  Mkx_Object_Dispatch parent;
};

#define Define(CNAME) \
  int \
  Mkx_BoxedValue_construct##CNAME \
    ( \
      Mkx_BoxedValue* self, \
      CNAME value \
    ); \
\
  int \
  Mkx_BoxedValue_create##CNAME \
    ( \
      Mkx_BoxedValue **result, \
      CNAME value \
    ); \
\
  int \
  Mkx_BoxedValue_set##CNAME \
    ( \
      Mkx_BoxedValue *self, \
      CNAME value \
    ); \
\
  int \
  Mkx_BoxedValue_get##CNAME \
    ( \
      CNAME *result, \
      Mkx_BoxedValue *self \
    );

#include "Mkx/Object/BoxedValue.i"

#undef Define


#endif // MKX_OBJECT_BOXEDVALUE_H_INCLUDED
