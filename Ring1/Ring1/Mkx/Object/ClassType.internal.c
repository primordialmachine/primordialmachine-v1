#define MKX_OBJECT_INTERNAL (1)
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/Interface.h"
#include "Mkx/Object/InterfaceType.internal.h"
#include "Mkx/Object/Type.internal.h"
#undef MKX_OBJECT_INTERNAL


#include "Ring1/Status.h"
#include "Ring1/Memory/_Include.h" /// @todo Move into "Mkx/Object/Common.internal.h".


Ring1_CheckReturn() Ring1_NonNull() bool
Mkx_ClassType_isInitialized
  (
    Mkx_ClassType* self
  )
{ return Mkx_Type_Flags_Initialized == (MKX_TYPE(self)->flags & Mkx_Type_Flags_Initialized); }

Ring1_CheckReturn() Ring1_NonNull(1, 3) int
Mkx_ClassType_construct
  (
    Mkx_ClassType *self,
    void (*notifyTypeRemoved)(),
    const Mkx_ClassTypeRegistrationInfo *info
  )
{
  int flags = Mkx_Type_Flags_ClassType;
  if (info->instantiable) flags |= Mkx_Type_Flag_InstantiableType;
  if (Mkx_Type_construct(MKX_TYPE(self), info->name, notifyTypeRemoved, flags)) return 1;
  self->parent = info->parent;
  // The object.
  self->size = info->size;
  self->destruct = info->destruct;
  self->memoryManager = info->memoryManager;
  // The dispatch.
  self->dispatchSize = info->dispatchSize;
  self->constructDispatch = info->constructDispatch;
  self->destructDispatch = info->destructDispatch;
  self->dispatch = NULL;
  // The interface implementations and dispatches.
  self->implementations.size = 0;
  self->implementations.elements = NULL;
  if (Ring1_Memory_allocateArray(&self->implementations.elements, 0, sizeof(Mkx_Type*)))
  {
    Mkx_Type_destruct(MKX_TYPE(self));
    return 1;
  }
  self->interfaceDispatches = NULL;
  // Return success.
  return 0;
}

Ring1_NonNull() void
Mkx_ClassType_destruct
  (
    Mkx_ClassType *self
  )
{
  //
  Ring1_Memory_deallocate(self->implementations.elements);
  self->implementations.elements = NULL;
  //
  Mkx_Type_destruct(MKX_TYPE(self));
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ClassType_ensureInitialized
  (
    Mkx_ClassType* self
  )
{
  // Get the parent class type if any.
  Mkx_ClassType* parent = MKX_CLASSTYPE(self->parent);
  
  // Ensure the parent class type if any is initialized.
  if (parent)
  {
    if (Ring1_Unlikely(Mkx_Type_ensureInitialized(MKX_TYPE(parent))))
    { return 1; }
  }

  // Ensure the dispatch is initialized.
  if (!self->dispatch)
  {
    if (parent != NULL && self->dispatchSize < parent->dispatchSize) return 1;
    if (Ring1_Memory_allocate(&self->dispatch, self->dispatchSize)) return 1;
    Ring1_Memory_zeroFill(self->dispatch, self->dispatchSize);
    if (parent != NULL && parent->dispatch)
    {
      if (Ring1_Memory_copyFast(self->dispatch, parent->dispatch, parent->dispatchSize)) {
        Ring1_Status_set(Ring1_Status_Success);
        Ring1_Memory_deallocate(self->dispatch);
        self->dispatch = NULL;
        return 1;
      }
    }
    if (self->constructDispatch)
    {
      if (self->constructDispatch(self->dispatch))
      {
        Ring1_Memory_deallocate(self->dispatch);
        self->dispatch = NULL;
        return 1;
      }
    }
  }

  // Ensure the interface dispatches are initialized.
  if (!self->interfaceDispatches)
  {
    // Clone the the interface dispatch table from the parent class if any or create a new interface dispatch table.
    if (parent)
    {
      if (Ring1_Unlikely(Mkx_Dispatches_clone(&self->interfaceDispatches, parent->interfaceDispatches)))
      { return 1; }
    }
    else
    {
      if (Ring1_Unlikely(Mkx_Dispatches_create(&self->interfaceDispatches)))
      { return 1; }
    }
    // Allocate the interface dispatches if no interface dispatches from the parent class were re-used.
    for (int64_t i = 0, n = self->implementations.size; i < n; ++i)
    {
      InterfaceImplementation* impl = &(self->implementations.elements[i]);
      
      int64_t dispatchIndex;

      if (Ring1_Unlikely(Mkx_Dispatches_getOrCreateEntry(&dispatchIndex, self->interfaceDispatches, MKX_TYPE(impl->interface), true)))
      {
        Mkx_Dispatches_destroy(self->interfaceDispatches);
        self->interfaceDispatches = NULL;
        return 1;
      }

      if (impl->construct)
      {
        Mkx_Dispatch* dispatch;
        if (Ring1_Unlikely(Mkx_Dispatches_getEntryAt(&dispatch, self->interfaceDispatches, dispatchIndex)))
        {
          Mkx_Dispatches_destroy(self->interfaceDispatches);
          self->interfaceDispatches = NULL;
          return 1;
        }
        impl->construct(MKX_INTERFACE_DISPATCH(dispatch));
      }
    }
  }

  return 0;
}

Ring1_CheckReturn() Ring1_NonNull() int
Mkx_ClassType_ensureUninitialized
  (
    Mkx_ClassType* self
  )
{
  // Destroy the interface dispatch table if any.
  if (self->interfaceDispatches)
  {
    Mkx_Dispatches_destroy(self->interfaceDispatches);
    self->interfaceDispatches = NULL;
  }
  // Destroy the dispatch table if any.
  if (self->dispatch)
  {
    if (self->destructDispatch)
    {
      self->destructDispatch(self->dispatch);
    }
    Ring1_Memory_deallocate(self->dispatch);
    self->dispatch = NULL;
  }
  // Return success.
  return 0;
}

Ring1_CheckReturn() int
Mkx_ClassType_isUserOf
  (
    bool *result,
    const Mkx_ClassType *a,
    const Mkx_Type *b
  )
{
  int kindb;

  if (Ring1_Unlikely(!result || !a || !b)) return 1;
  if (Ring1_Unlikely(getTypeKind(&kindb, b))) return 1;

  if (kindb == Mkx_Type_Flags_ClassType)
  {
    *result = (a->parent == b);
    return 0;
  }
  else if (kindb == Mkx_Type_Flags_InterfaceType)
  {
    return Mkx_ClassType_hasInterfaceImplementation(result, a, MKX_INTERFACETYPE(b));
  }
  else
  {
    *result = false;
    return 0;
  }
}
