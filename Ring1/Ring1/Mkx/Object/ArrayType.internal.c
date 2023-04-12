#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/ArrayType.internal.h"
#include "Mkx/Object/Type.internal.h"
#undef MKX_OBJECT_INTERNAL


#include <string.h> /// @todo Move into "Mkx/Object/Common.internal.h".
#include <malloc.h> /// @todo Move into "Mkx/Object/Common.internal.h".


Ring1_NonNull(1, 3) int
Mkx_ArrayType_construct
  (
    Mkx_ArrayType* self,
    void (*notifyShutdown)(),
    Mkx_Type *elementType
  )
{
  char* p;
  int64_t n;
  if (Ring1_Unlikely(Ring1_Atom_getBytes(&p, elementType->name) || Ring1_Atom_getNumberOfBytes(&n, elementType->name)))
  { return 1; }
  char *name = malloc(strlen("[") + (size_t)n + strlen("]") + 1);
  if (Ring1_Unlikely(!name)) return 1;
  strcpy(name, "[");
  strncat(name, p, (size_t)n);
  strcat(name, "]");
  if (Mkx_Type_construct(MKX_TYPE(self), name, notifyShutdown, Mkx_Type_Flags_ArrayType))
  {
    free(name);
    return 1;
  }
  self->elementType = elementType;
  return 0;
}

Ring1_NonNull() void
Mkx_ArrayType_destruct
  (
    Mkx_ArrayType* self
  )
{ Mkx_Type_destruct(MKX_TYPE(self)); }

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ArrayType_ensureInitialized
  (
    Mkx_ArrayType* self
  )
{ return Mkx_Type_ensureInitialized(self->elementType); }

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ArrayType_ensureUninitialized
  (
    Mkx_ArrayType* self
  )
{ return 0; }

Ring1_CheckReturn() int
Mkx_ArrayType_isUserOf
  (
    bool *result,
    const Mkx_ArrayType *a,
    const Mkx_Type *b
  )
{
  if (Ring1_Unlikely(!result || !a || !b)) return 1;
  *result = (a->elementType == b);
  return 0;
}
