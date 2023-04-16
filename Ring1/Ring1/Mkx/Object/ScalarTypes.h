#if !defined(MKX_OBJECT_SCALARTYPES_H_INCLUDED)
#define MKX_OBJECT_SCALARTYPES_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>

typedef struct Mkx_Type Mkx_Type;

#define Define(name) \
  Mkx_Type * \
  __##name##_getType__ \
    ( \
    );

#include "Mkx/Object/ScalarTypes.i"

#undef Define


#endif
