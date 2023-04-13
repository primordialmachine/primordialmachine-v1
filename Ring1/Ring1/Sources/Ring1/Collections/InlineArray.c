#define RING1_COLLECTIONS_PRIVATE (1)
#include "Ring1/Collections/InlineArray.h"
#undef RING1_COLLECTIONS_PRIVATE


#include "Ring1/Status.h"
#include "Ring1/Memory/_Include.h"


Ring1_NoDiscardReturn() Ring1_Status
Ring1_InlineArray_initialize
  (
    Ring1_InlineArray* self,
    Ring1_InlineArrayDispatch const* dispatch
  )
{
  if (!self || !dispatch) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  self->dispatch = dispatch;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray(&self->elements, self->dispatch->elementSize, 0)) {
    return Ring1_Result_Failure;
  }
  self->size = 0;
  return Ring1_Status_Success;
}

void
Ring1_InlineArray_uninitialize
  (
    Ring1_InlineArray *self
  )
{
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_append
  (
    Ring1_InlineArray* self,
    void* data
  )
{ 
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return Ring1_InlineArray_insert(self, self->size, data);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_prepend
  (
    Ring1_InlineArray* self,
    void* data)
{ return Ring1_InlineArray_insert(self, 0, data); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_InlineArray_insert
  (
    Ring1_InlineArray* self,
    size_t index,
    void* data
  )
{
  if (self->size == self->capacity) {
    size_t newCapacity = 0;
    if (Ring1_Memory_recomputeSize_sz(0, SIZE_MAX / self->dispatch->elementSize, self->capacity, 1, &newCapacity, true)) {
      return Ring1_Status_AllocationFailed;
    }
    
    void* newElements = NULL;
    if (Ring1_Memory_reallocateArray(&newElements, self->elements, newCapacity, self->dispatch->elementSize)) {
      Ring1_Status_set(Ring1_Status_Success);
      return Ring1_Status_AllocationFailed;
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    Ring1_Memory_copySlow(((char*)self->elements) + self->dispatch->elementSize * (index + 1),
                          ((char*)self->elements) + self->dispatch->elementSize * (index + 0),
                          self->dispatch->elementSize * (self->size - index));
  }
  Ring1_Memory_copyFast(((char*)self->elements) + self->dispatch->elementSize * (index + 0), data,
                        self->dispatch->elementSize);
  self->size++;
  return Ring1_Status_Success;
}

void*
Ring1_InlineArray_getAt
  (
    Ring1_InlineArray* self,
    size_t index
  )
{ return ((char*)self->elements) + self->dispatch->elementSize * index; }
