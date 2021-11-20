/// @file Collection/List.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/List.h"



#include "Collections/GrowthStrategy.h"
#include <memory.h>



static const size_t maximalCapacity = SIZE_MAX / sizeof(Machine_Value);

static void append(Machine_List* self, Machine_Value value);

static void prepend(Machine_List* self, Machine_Value value);

static void insertAt(Machine_List* self, size_t index, Machine_Value value);

static Machine_Value getAt(Machine_List const* self, size_t index);

static void removeAt(Machine_List* self, size_t index);

static void removeAtFast(Machine_List* self, size_t index);

static size_t getSize(Machine_List const* self);

static void clear(Machine_List* self);

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

static void reverse(Machine_List* self);

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

static Machine_List* slice(Machine_List* self, size_t start, size_t length);

#endif

static void Machine_List_visit(Machine_List* self);

static void Machine_List_destruct(Machine_List* self);

static void Machine_List_constructClass(Machine_List_Class* self) {
  ((Machine_Collection_Class*)self)->getSize = (size_t(*)(Machine_Collection const*)) & getSize;
  ((Machine_Collection_Class*)self)->clear = (void (*)(Machine_Collection*)) & clear;
  self->append = &append;
  self->prepend = &prepend;
  self->insertAt = &insertAt;
  self->getAt = &getAt;
  self->removeAt = &removeAt;
  self->removeAtFast = &removeAtFast;
#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1
  self->reverse = &reverse;
#endif
#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1
  self->slice = &slice;
#endif
}

static void Machine_List_construct(Machine_List* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Collection_construct((Machine_Collection*)self, numberOfArguments, arguments);
  self->size = 0;
  self->capacity = 0;
  self->elements = Machine_Eal_alloc(0);
  if (!self->elements) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_List_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_List, Machine_Collection, &Machine_List_visit, &Machine_List_construct, &Machine_List_destruct, &Machine_List_constructClass)

static void append(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_List_insertAt(self, Machine_Collection_getSize((Machine_Collection*)self), value);
}

static void prepend(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_List_insertAt(self, 0, value);
}

static void insertAt(Machine_List* self, size_t index, Machine_Value value) {
  if ((self->capacity - self->size) == 0) {
    size_t newCapacity;
    Machine_StatusValue status = Machine_Collections_getBestCapacity(self->capacity, 1, maximalCapacity, &newCapacity);
    if (status != Machine_Status_Success) {
      Machine_setStatus(status);
      Machine_jump();
    }
    void* newElements = c_realloc_a(self->elements, sizeof(Machine_Value), newCapacity);
    if (!newElements) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    memmove(self->elements + index + 1, self->elements + index + 0, sizeof(Machine_Value) * (self->size - index));
  }
  self->elements[index] = value;
  self->size++;
}

static size_t getSize(Machine_List const* self) {
  return self->size;
}

static void clear(Machine_List* self) {
  self->size = 0;
}

static Machine_Value getAt(Machine_List const* self, size_t index) {
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return self->elements[index];
}

static void removeAt(Machine_List* self, size_t index) {
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  if (index < self->size - 1) {
    memmove(self->elements + index + 0, self->elements + index + 1, sizeof(Machine_Value) * (self->size - index - 1));
  }
  self->size--;
}

static void removeAtFast(Machine_List* self, size_t index) {
  if (index >= self->size) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  self->elements[index] = self->elements[self->size - 1];
  self->size--;
}

static void Machine_List_visit(Machine_List* self) {
  for (size_t i = 0, n = self->size; i < n; ++i) {
    Machine_Value_visit(&(self->elements[i]));
  }
}

static void Machine_List_destruct(Machine_List* self) {
  if (self->elements) {
    Machine_Eal_dealloc(self->elements);
    self->elements = NULL;
  }
}

Machine_List* Machine_List_create() {
  Machine_ClassType* ty = Machine_List_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_List* self = (Machine_List*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Value Machine_List_getAt(Machine_List const* self, size_t index) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_List, getAt, index);
}

void Machine_List_prepend(Machine_List* self, Machine_Value value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_List, prepend, value);
}

void Machine_List_append(Machine_List* self, Machine_Value value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_List, append, value);
}

void Machine_List_insertAt(Machine_List* self, size_t index, Machine_Value value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_List, insertAt, index, value);
}

void Machine_List_removeAt(Machine_List* self, size_t index) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_List, removeAt, index);
}

void Machine_List_removeAtFast(Machine_List* self, size_t index) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_List, removeAtFast, index);
}

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

void Machine_List_reverse(Machine_List* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_List, reverse);
}

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

Machine_List* Machine_List_slice(Machine_List* self, size_t start, size_t length) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_List, slice, start, length);
}

#endif
