#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/InterfaceType.internal.h"
#undef MKX_OBJECT_INTERNAL

#include "Ring1/Memory/_Include.h"

Ring1_NonNull(1, 2) int
Mkx_InterfaceType_construct
  (
    Mkx_InterfaceType *self,
    const char* name,
    void (*notifyTypeRemoved)(),
    int (*addPrerequisites)(Mkx_InterfaceType* self),
    size_t dispatchSize
  )
{ 
  //
  if (Mkx_Type_construct(MKX_TYPE(self), name, notifyTypeRemoved, Mkx_Type_Flags_InterfaceType)) return 1;
  //
  self->extensions.size = 0;
  self->extensions.elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&self->extensions.elements, 0, sizeof(Mkx_Type*)))
  {
    Mkx_Type_destruct(MKX_TYPE(self));
    return 1;
  }
  //
  self->addPrerequisites = addPrerequisites;
  //
  self->dispatchSize = dispatchSize;
  //
  return 0;
}

Ring1_NonNull(1) void
Mkx_InterfaceType_destruct
  (
    Mkx_InterfaceType* self
  )
{
  //
  self->dispatchSize = 0;
  //
  Ring1_Memory_deallocate(self->extensions.elements);
  self->extensions.elements = NULL;
  //
  Mkx_Type_destruct(MKX_TYPE(self));
}

/// @todo Use procedure style.
Ring1_CheckReturn() int
Mkx_InterfaceType_isUserOf
  (
    bool *result,
    const Mkx_InterfaceType *a,
    const Mkx_Type *b
  )
{
  if (Ring1_Unlikely(!result || !a || !b)) return 1;
  // Only interfaces can be prerequisites of interfaces.
  bool isInterfaceType;
  if (Ring1_Unlikely(Mkx_Type_isInterfaceType(&isInterfaceType, b))) return 1;
  if (!isInterfaceType)
  {
    *result = false;
    return 0;
  }
  *result = Mkx_InterfaceType_isDirectPrerequisite(MKX_INTERFACETYPE(b), a);
  return 0;
}
