#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/EnumerationType.internal.h"
#include "Mkx/Object/Type.internal.h"
#undef MKX_OBJECT_INTERNAL

Ring1_NonNull(1, 2) int
Mkx_EnumerationType_construct
  (
    Mkx_EnumerationType* self,
    const char* name,
    void (*notifyTypeRemoved)(),
    size_t size
  )
{
  if (Mkx_Type_construct(MKX_TYPE(self), name, notifyTypeRemoved, Mkx_Type_Flags_EnumerationType)) return 1;
  self->size = size;
  MKX_TYPE(self)->flags |= Mkx_Type_Flags_Initialized;
  return 0;
}

Ring1_NonNull() void
Mkx_EnumerationType_destruct
  (
    Mkx_EnumerationType* self
  )
{ Mkx_Type_destruct(MKX_TYPE(self)); }

Ring1_CheckReturn() int
Mkx_EnumerationType_isUserOf
  (
    bool *result,
    const Mkx_EnumerationType *a,
    const Mkx_Type *b
  )
{ 
  if (Ring1_Unlikely(!result || !a || !b)) return 1;
  *result = false;
  return 0;
}
