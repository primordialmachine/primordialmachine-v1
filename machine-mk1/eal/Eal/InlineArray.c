#define MACHINE_EAL_PRIVATE (1)
#include "Eal/InlineArray.h"



#include "Ring1/Status.h"
#include "Ring1/Memory.h"



Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_initialize(
    Machine_Eal_InlineArray* self, Machine_Eal_InlineArrayDispatch const* dispatch) {
  if (!self || !dispatch) {
    return Machine_Eal_InlineArray_InvalidArgument;
  }
  self->dispatch = dispatch;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray(&self->elements, self->dispatch->elementSize, 0)) {
    Ring1_Status_set(Ring1_Status_Success);
    return 1;
  }
  self->size = 0;
  return Machine_Eal_InlineArray_Success;
}

void Machine_Eal_InlineArray_uninitialize(Machine_Eal_InlineArray *self) {
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_append(Machine_Eal_InlineArray* self,
                                                            void* data) {
  return Machine_Eal_InlineArray_insert(self, self->size, data);
}

Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_prepend(Machine_Eal_InlineArray* self,
                                                             void* data) {
  return Machine_Eal_InlineArray_insert(self, 0, data);
}

Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_insert(Machine_Eal_InlineArray* self,
                                                            size_t index, void* data) {
  if (self->size == self->capacity) {
    size_t newCapacity = 0;
    if (Ring1_Memory_recomputeSize_sz(0, SIZE_MAX / self->dispatch->elementSize, self->capacity, 1, &newCapacity, true)) {
      return Machine_Eal_InlineArray_AllocationFailed;
    }
    
    void* newElements = NULL;
    if (Ring1_Memory_reallocateArray(&newElements, self->elements, newCapacity, self->dispatch->elementSize)) {
      Ring1_Status_set(Ring1_Status_Success);
      return Machine_Eal_InlineArray_AllocationFailed;
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
  return Machine_Eal_InlineArray_Success;
}

void* Machine_Eal_InlineArray_getAt(Machine_Eal_InlineArray* self, size_t index) {
  return ((char*)self->elements) + self->dispatch->elementSize * index;
}