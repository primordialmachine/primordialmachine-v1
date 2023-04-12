#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/ScalarTypes.h"

#include "Mkx/Object/Types.h"
#undef MKX_OBJECT_INTERNAL

#define Define(name) \
  static Mkx_Type *g_##name##_type = NULL; \
\
  static void \
  name##_typeRemoved \
    ( \
    ) \
  { \
    g_##name##_type = NULL; \
  } \
\
  Mkx_Type * \
  __##name##_getType__ \
    ( \
    ) \
  { \
    if (!g_##name##_type) \
    { \
      g_##name##_type = Mkx_registerScalarType(#name, &name##_typeRemoved, sizeof(name)); \
    } \
    return g_##name##_type; \
  }

#include "Mkx/Object/ScalarTypes.i"

#undef Define
