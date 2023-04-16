#if !defined(MKX_MEMORYMANAGER_H_INCLUDED)
#define MKX_MEMORYMANAGER_H_INCLUDED

#if !defined(MKX_OBJECT_INTERNAL) || 1 != MKX_OBJECT_INTERNAL
#error("Do not include 'Mkx/Object/MemoryManager.h' directly, include 'Mkx/Object.h' instead.")
#endif

#include <stddef.h>

typedef struct Mkx_MemoryManager Mkx_MemoryManager;

static inline Mkx_MemoryManager *
MKX_MEMORYMANAGER
  (  
    void *p
  )
{ return (Mkx_MemoryManager*)p; }

struct Mkx_MemoryManager
{
  int (*allocate)(void** memory, Mkx_MemoryManager *self, size_t size);
  void (*deallocate)(Mkx_MemoryManager *self, void* memory);
};

typedef struct Mkx_DefaultMemoryManager
{
  Mkx_MemoryManager parent;
} Mkx_DefaultMemoryManager;

Mkx_DefaultMemoryManager*
Mkx_DefaultMemoryManager_get
  (
  );

#endif // MKX_MEMORYMANAGER_H_INCLUDED
