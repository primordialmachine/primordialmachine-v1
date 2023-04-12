#define MKX_OBJECT_INTERNAL (1)

#include "Mkx/Object/Utilities/error.h"
#include "Mkx/Object/ClassType.internal.h"
#include "Mkx/Object/Dispatch.h"
#include "Mkx/Object/InterfaceType.internal.h"
#include "Mkx/Object/Type.internal.h"
#undef MKX_OBJECT_INTERNAL

#include "Ring1/Status.h"
#include "Ring1/Memory/_Include.h" /// @todo Move into "Mkx/Object/Common.internal.h".

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() int
Mkx_Dispatch_create
  (
    Mkx_Dispatch **result,
    Mkx_Type *type
  )
{
  if (Ring1_Unlikely(!result || !type)) return 1;
  bool isInterfaceType;
  if (Ring1_Unlikely(Mkx_Type_isInterfaceType(&isInterfaceType, type))) return 1;
  if (Ring1_Unlikely(!isInterfaceType)) return 1;
  Mkx_Dispatch* dispatch;
  if (Ring1_Memory_allocate(&dispatch, MKX_INTERFACETYPE(type)->dispatchSize)) return 1;
  Ring1_Memory_zeroFill(dispatch, MKX_INTERFACETYPE(type)->dispatchSize);
  MKX_DISPATCH(dispatch)->type = type;
  *result = dispatch;
  return 0;
}

Ring1_CheckReturn() int 
Mkx_Dispatch_clone
  (
    Mkx_Dispatch **result,
    Mkx_Dispatch *self
  )
{
  if (Ring1_Unlikely(!result || !self)) return 1;
  Mkx_Dispatch* clone;
  if (Ring1_Unlikely(Ring1_Memory_allocate(&clone, MKX_INTERFACETYPE(MKX_DISPATCH(self)->type)->dispatchSize))) return 1;
  if (Ring1_Unlikely(Ring1_Memory_copyFast(clone, self, MKX_INTERFACETYPE(MKX_DISPATCH(self)->type)->dispatchSize))) {
    Ring1_Status_set(Ring1_Status_Success);
    Ring1_Memory_deallocate(clone);
    return 1;
  }
  *result = clone;
  return 0;
}

void
Mkx_Dispatch_destroy
  (
    Mkx_Dispatch *self
  )
{ Ring1_Memory_deallocate(self); }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() int
Mkx_Dispatches_getOrCreateEntry
  (
    int64_t* result,
    Mkx_Dispatches* self,
    Mkx_Type* type,
    bool create
  )
{
  if (Ring1_Unlikely(!result || !self)) return 1;
  for (int64_t i = 0, n = self->size; i < n; ++i)
  {
    if (MKX_DISPATCH(self->elements[i])->type == type)
    {
      *result = i;
      return 0;
    }
  }
  if (create)
  {
    Mkx_Dispatch* dispatch = NULL;
    if (Ring1_Unlikely(Mkx_Dispatch_create(&dispatch, type)))
    { return 1; }
    Mkx_Dispatch** elements = NULL;
    if (Ring1_Memory_allocateArray((void **)&elements, (size_t)self->size + 1, sizeof(Mkx_Dispatch*)))
    {
      Mkx_Dispatch_destroy(dispatch);
      return 1;
    }
    if (Ring1_Memory_copyArrayFast(elements,
                                   self->elements,
                                   (size_t)self->size,
                                   sizeof(Mkx_Dispatch*))) {
      Ring1_Status_set(Ring1_Status_Success);
      Ring1_Memory_deallocate(elements);
      Mkx_Dispatch_destroy(dispatch);
      return 1;
    }
    Ring1_Memory_deallocate(self->elements);
    self->elements = elements;
    self->elements[self->size++] = dispatch;
    *result = self->size - 1;
  }
  else
  {
    *result = -1;
  }
  return 0;
}

Ring1_CheckReturn() int
Mkx_Dispatches_getEntryAt
  (
    Mkx_Dispatch** result,
    Mkx_Dispatches* self,
    int64_t index
  )
{
  if (Ring1_Unlikely(!result || !self || index < 0)) return 1;
  if (Ring1_Unlikely(index >= self->size)) return 1;
  *result = self->elements[index];
  return 0;
}

Ring1_CheckReturn() int
Mkx_Dispatches_clone
  (
    Mkx_Dispatches** result,
    Mkx_Dispatches* self
  )
{
  if (Ring1_Unlikely(!result || !self)) return 1;
  Mkx_Dispatches* clone;
  if (Ring1_Unlikely(Ring1_Memory_allocate(&clone, sizeof(Mkx_Dispatches)))) return 1;
  clone->size = 0;
  clone->elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&clone->elements, (size_t)self->size, sizeof(Mkx_Dispatch*)))
  {
    Ring1_Memory_deallocate(clone);
    return 1;
  }
  for (int64_t i = 0, n = self->size; i < n; ++i)
  {
    Mkx_Dispatch* dispatch = NULL;
    if (Ring1_Unlikely(Mkx_Dispatch_clone(&dispatch, self->elements[i])))
    {
      while (clone->size > 0)
      {
        Mkx_Dispatch_destroy(clone->elements[--clone->size]);
      }
      Ring1_Memory_deallocate(clone->elements);
      Ring1_Memory_deallocate(clone);
      return 1;
    }
    clone->elements[clone->size++] = dispatch;
  }
  *result = clone;
  return 0;
}

Ring1_CheckReturn() int
Mkx_Dispatches_create
  (
    Mkx_Dispatches** result
  )
{
  if (Ring1_Unlikely(!result)) return 1;
  Mkx_Dispatches* self;
  if (Ring1_Unlikely(Ring1_Memory_allocate(&self, sizeof(Mkx_Dispatches)))) return 1;
  self->size = 0;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&self->elements, 0, sizeof(Mkx_Dispatch*)))
  {
    Ring1_Memory_deallocate(self);
    return 1;
  }
  *result = self;
  return 0;
}

Ring1_CheckReturn() int
Mkx_Dispatches_destroy
  (
    Mkx_Dispatches* self
  )
{
  if (Ring1_Unlikely(!self)) {
    return 1;
  }
  while (self->size > 0) {
    Mkx_Dispatch *element = self->elements[--self->size];
    char* p; int64_t n;
    if (Ring1_Likely(!Ring1_Atom_getBytes(&p, MKX_DISPATCH(element)->type->name) &&
                     !Ring1_Atom_getNumberOfBytes(&n, MKX_DISPATCH(element)->type->name))) {
      error_f("%s:%d: dispatch `%.*s`: destroy\n", __FILE__, __LINE__, (int)n, p);
    }
    Mkx_Dispatch_destroy(element);
  }
  Ring1_Memory_deallocate(self->elements);
  self->elements = NULL;
  Ring1_Memory_deallocate(self);
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
