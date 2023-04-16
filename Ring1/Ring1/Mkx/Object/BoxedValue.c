#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/BoxedValue.h"
#undef MKX_OBJECT_INTERNAL

static Mkx_Type* g_type = NULL;

static inline void
Mkx_BoxedValue_typeRemoved
  (
  )
{ g_type = NULL; }

Mkx_Type*
__Mkx_BoxedValue_getType__
  (
  )
{
  if (!g_type)
  {
    Mkx_ClassTypeRegistrationInfo info =
    {
      .name = "Mkx.BoxedValue",
      //
      .parent = NULL,
      //
      .size = sizeof(Mkx_BoxedValue),
      .destruct = NULL,
      //
      .dispatchSize = sizeof(Mkx_BoxedValue_Dispatch),
      .constructDispatch = NULL,
      .destructDispatch = NULL,
    };
    g_type = Mkx_registerClassType(&Mkx_BoxedValue_typeRemoved, &info);
  }
  return g_type;
}

#define Define(CNAME) \
  int \
  Mkx_BoxedValue_construct##CNAME \
    ( \
      Mkx_BoxedValue *self, \
      CNAME value \
    ) \
  { \
    if (Ring1_Unlikely(!self)) return 1; \
    Mkx_Type *type = MKX_TYPE_GET(Mkx_BoxedValue); \
    if (Ring1_Unlikely(!type)) return 1; \
    if (Ring1_Unlikely(Mkx_Object_construct(MKX_OBJECT(self)))) return 1; \
    self->m_##CNAME = value; \
    MKX_OBJECT(self)->type = type; \
    return 0; \
  } \
\
  int \
  Mkx_BoxedValue_create##CNAME \
    ( \
      Mkx_BoxedValue **result, \
      CNAME value \
    ) \
  { \
    if (Ring1_Unlikely(!result)) return 1; \
    Mkx_Type *type = MKX_TYPE_GET(Mkx_BoxedValue); \
    if (Ring1_Unlikely(!type)) return 1; \
    Mkx_BoxedValue *self = Mkx_Object_allocate(type); \
    if (Ring1_Unlikely(!self)) return 1; \
    if (Ring1_Unlikely(Mkx_BoxedValue_construct##CNAME(self, value))) \
    { \
      Mkx_Object_unreference(MKX_OBJECT(self)); \
      return 1; \
    } \
    *result = self; \
    return 0; \
  } \
\
  int \
  Mkx_BoxedValue_set##CNAME \
    ( \
      Mkx_BoxedValue *self, \
      CNAME value \
    ) \
  { \
    if (Ring1_Unlikely(!self)) return 1; \
    Mkx_Type *type = MKX_TYPE_GET(CNAME); \
    if (Ring1_Unlikely(!type)) return 1; \
    self->m_##CNAME = value; \
    return 0; \
  } \
\
  int \
  Mkx_BoxedValue_get##CNAME \
    ( \
      CNAME *result, \
      Mkx_BoxedValue *self \
    ) \
  { \
    if (Ring1_Unlikely(!result || !self)) return 1; \
    if (self->type != MKX_TYPE_GET(CNAME)) return 1; \
    *result = self->m_##CNAME; \
    return 0; \
  }

#include "Mkx/Object/BoxedValue.i"

#undef Define
