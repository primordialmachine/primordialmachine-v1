/// @file Collection/ArrayList.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/ArrayList.h"

#include "Ring1/Status.h"
#include "Collections/Collection.h"
#include "Collections/GrowthStrategy.h"
#include "Collections/List.h"

static size_t const maximalCapacity = SIZE_MAX / sizeof(Machine_Value);

static void append(Machine_ArrayList* self, Machine_Value value);

static void prepend(Machine_ArrayList* self, Machine_Value value);

static void insertAt(Machine_ArrayList* self, size_t index, Machine_Value value);

static Machine_Value getAt(Machine_ArrayList const* self, size_t index);

static void removeAt(Machine_ArrayList* self, size_t index);

static void removeAtFast(Machine_ArrayList* self, size_t index);

static size_t getSize(Machine_ArrayList const* self);

static void clear(Machine_ArrayList* self);

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

static void reverse(Machine_ArrayList* self);

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

static Machine_List* slice(Machine_ArrayList* self, size_t start, size_t length);

#endif

static void Machine_ArrayList_visit(Machine_ArrayList* self);

static void Machine_ArrayList_destruct(Machine_ArrayList* self);

static void Machine_ArrayList_implement_Machine_Collection(Machine_Collection_Dispatch* self) {
  self->getSize = (size_t(*)(Machine_Collection const*)) & getSize;
  self->clear = (void (*)(Machine_Collection*)) & clear;
}

static void Machine_ArrayList_implement_Machine_List(Machine_List_Dispatch* self) {
  self->append = (void (*)(Machine_List*, Machine_Value)) & append;
  self->prepend = (void (*)(Machine_List*, Machine_Value)) & prepend;
  self->insertAt = (void (*)(Machine_List*, size_t, Machine_Value)) & insertAt;
  self->getAt = (Machine_Value(*)(Machine_List const*, size_t)) & getAt;
  self->removeAt = (void (*)(Machine_List*, size_t)) & removeAt;
  self->removeAtFast = (void (*)(Machine_List*, size_t)) & removeAtFast;
#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1
  self->reverse = (void (*)(Machine_List*)) & reverse;
#endif
#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1
  self->slice = (Machine_List * (*)(Machine_List*, size_t, size_t)) & slice;
#endif
}

static void Machine_ArrayList_implementInterfaces(Machine_ClassType* self) {
  Machine_ClassType_implement(
      self, Machine_Collection_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_ArrayList_implement_Machine_Collection);
  Machine_ClassType_implement(
      self, Machine_List_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_ArrayList_implement_Machine_List);
}

static void Machine_ArrayList_constructClass(Machine_ArrayList_Class* self) {
}

void Machine_ArrayList_construct(Machine_ArrayList* self, size_t numberOfArguments,
                                 Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->size = 0;
  self->capacity = 0;
  self->elements = NULL;
  if (Ring1_Memory_allocate(&self->elements, 0)) {
    Ring1_Status_set(Ring1_Status_Success);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_ArrayList_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_ArrayList, Machine_Object, &Machine_ArrayList_visit,
                         &Machine_ArrayList_construct, &Machine_ArrayList_destruct,
                         &Machine_ArrayList_constructClass, &Machine_ArrayList_implementInterfaces)

static void append(Machine_ArrayList* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_List_insertAt((Machine_List*)self, Machine_Collection_getSize((Machine_Collection*)self),
                        value);
}

static void prepend(Machine_ArrayList* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_List_insertAt((Machine_List*)self, 0, value);
}

static void insertAt(Machine_ArrayList* self, size_t index, Machine_Value value) {
  if ((self->capacity - self->size) == 0) {
    size_t newCapacity;
    Machine_StatusValue status
        = Machine_Collections_getBestCapacity(self->capacity, 1, maximalCapacity, &newCapacity);
    if (status != Machine_Status_Success) {
      Machine_setStatus(status);
      Machine_jump();
    }
    void* newElements = NULL;
    if (Ring1_Memory_reallocateArray(&newElements, self->elements, newCapacity, sizeof(Machine_Value))) {
      Ring1_Status_set(Ring1_Status_Success);
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    Machine_Eal_Memory_copy(self->elements + index + 1, self->elements + index + 0,
                            sizeof(Machine_Value) * (self->size - index), true);
  }
  self->elements[index] = value;
  self->size++;
}

static size_t getSize(Machine_ArrayList const* self) {
  return self->size;
}

static void clear(Machine_ArrayList* self) {
  self->size = 0;
}

static Machine_Value getAt(Machine_ArrayList const* self, size_t index) {
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return self->elements[index];
}

static void removeAt(Machine_ArrayList* self, size_t index) {
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  if (index < self->size - 1) {
    Machine_Eal_Memory_copy(self->elements + index + 0, self->elements + index + 1,
                            sizeof(Machine_Value) * (self->size - index - 1), true);
  }
  self->size--;
}

static void removeAtFast(Machine_ArrayList* self, size_t index) {
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  self->elements[index] = self->elements[self->size - 1];
  self->size--;
}

static void Machine_ArrayList_visit(Machine_ArrayList* self) {
  for (size_t i = 0, n = self->size; i < n; ++i) {
    Machine_Value_visit(&(self->elements[i]));
  }
}

static void Machine_ArrayList_destruct(Machine_ArrayList* self) {
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

Machine_ArrayList* Machine_ArrayList_create() {
  Machine_ClassType* ty = Machine_ArrayList_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_ArrayList* self
      = (Machine_ArrayList*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
