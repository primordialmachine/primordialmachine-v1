#define MACHINE_EAL_PRIVATE (1)
#include "Eal/InlineArray.h"



#include "Eal/GrowthStrategy.h"
#include "Eal/Memory.h"



Machin_Eal_InlineArrayStatus Machine_Eal_InlineArray_initialize(
    Machine_Eal_InlineArray* self, Machine_Eal_InlineArrayDispatch const* dispatch) {
  if (!self || !dispatch) {
    return Machine_Eal_InlineArray_InvalidArgument;
  }
  self->dispatch = dispatch;
  self->elements = Machine_Eal_Memory_allocateArray(self->dispatch->elementSize, 0);
  if (!self->elements) {
    return 1;
  }
  self->size = 0;
  return Machine_Eal_InlineArray_Success;
}

void Machine_Eal_InlineArray_uninitialize(Machine_Eal_InlineArray *self) {
  if (self->elements) {
    Machine_Eal_Memory_deallocate(self->elements);
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
    if (Machine_Eal_getBestCapacity(self->capacity, 1, SIZE_MAX / self->dispatch->elementSize, &newCapacity)) {
      return Machine_Eal_InlineArray_AllocationFailed;
    }
    
    void *newElements = Machine_Eal_Memory_reallocateArray(self->elements, self->dispatch->elementSize, newCapacity);
    if (NULL == newElements) {
      return Machine_Eal_InlineArray_AllocationFailed;
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    Machine_Eal_Memory_copy(((char*)self->elements) + self->dispatch->elementSize * (index + 1),
                            ((char*)self->elements) + self->dispatch->elementSize * (index + 0),
                            self->dispatch->elementSize * (self->size - index), true);
  }
  Machine_Eal_Memory_copy(((char*)self->elements) + self->dispatch->elementSize * (index + 0), data,
                          self->dispatch->elementSize, false);
  self->size++;
  return Machine_Eal_InlineArray_Success;
}

void* Machine_Eal_InlineArray_getAt(Machine_Eal_InlineArray* self, size_t index) {
  return ((char*)self->elements) + self->dispatch->elementSize * index;
}