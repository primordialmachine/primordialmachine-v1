#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/MemoryManager.h"
#undef MKX_OBJECT_INTERNAL

#include "Ring1/Annotations/_Include.h"
#include "Ring1/Memory/_Include.h" /// @todo Move into "Mkx/Object/Common.internal.h".

Ring1_CheckReturn() static int
Mkx_DefaultMemoryManager_allocate
  (
    void** memory,
    Mkx_DefaultMemoryManager *self,
    size_t size
  )
{
  if (Ring1_Unlikely(!memory)) return 1;
  void* temporary;
  if (Ring1_Memory_allocate(&temporary, size)) return 1;
  *memory = temporary;
  return 0;
}

static void
Mkx_DefaultMemoryManager_deallocate
  (
    Mkx_DefaultMemoryManager *self,
    void* memory
  )
{
  Ring1_Memory_deallocate(memory);
}

Mkx_DefaultMemoryManager*
Mkx_DefaultMemoryManager_get
  (
  )
{
  static const Mkx_DefaultMemoryManager instance =
  {
    .parent.allocate = (int (*)(void **, Mkx_MemoryManager *, size_t))&Mkx_DefaultMemoryManager_allocate,
    .parent.deallocate = (void (*)(Mkx_MemoryManager *, void *))&Mkx_DefaultMemoryManager_deallocate,
  };
  return (Mkx_DefaultMemoryManager *)&instance;
}
