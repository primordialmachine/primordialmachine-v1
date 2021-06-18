/// @file Runtime/List.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/List.h"


#include <malloc.h>
#include <memory.h>

static const size_t maximalCapacity = SIZE_MAX / sizeof(Machine_Value);

static void append(Machine_List* self, Machine_Value value);

static void prepend(Machine_List* self, Machine_Value value);

static void insertAt(Machine_List* self, size_t index, Machine_Value value);

static Machine_Value getAt(const Machine_List* self, size_t index);

static void removeAt(Machine_List* self, size_t index);

static void removeAtFast(Machine_List* self, size_t index);

static size_t getSize(const Machine_List* self);

static void clear(Machine_List* self);

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

static void reverse(Machine_List* self);

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

static Machine_List* slice(Machine_List* self, size_t start, size_t length);

#endif

static void Machine_List_visit(Machine_List* self);

static void Machine_List_destruct(Machine_List* self);

static void Machine_List_construct(Machine_List* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Collection_construct((Machine_Collection*)self, numberOfArguments, arguments);
  ((Machine_Collection*)self)->getSize = (size_t(*)(const Machine_Collection*)) & getSize;
  ((Machine_Collection*)self)->clear = (void (*)(Machine_Collection*)) & clear;
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
  self->size = 0;
  self->capacity = 0;
  self->elements = NULL;
  Machine_setClassType((Machine_Object*)self, Machine_List_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_List, Machine_Collection, &Machine_List_visit, &Machine_List_construct, &Machine_List_destruct)

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
    if (self->capacity == maximalCapacity) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    size_t newCapacity = self->capacity + 1;
    if (self->capacity < maximalCapacity / 2) {
      newCapacity = self->capacity > 0 ? self->capacity * 2 : 8;
    }
    void* newElements = realloc(self->elements, sizeof(Machine_Value) * newCapacity);
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

static size_t getSize(const Machine_List* self) {
  return self->size;
}

static void clear(Machine_List* self) {
  self->size = 0;
}

static Machine_Value getAt(const Machine_List* self, size_t index) {
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
    free(self->elements);
    self->elements = NULL;
  }
}

Machine_List* Machine_List_create() {
  Machine_ClassType* ty = Machine_List_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_List* self = (Machine_List*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Value Machine_List_getAt(const Machine_List* self, size_t index) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->getAt(self, index);
}

void Machine_List_prepend(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->prepend(self, value);
}

void Machine_List_append(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->append(self, value);
}

void Machine_List_insertAt(Machine_List* self, size_t index, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  self->insertAt(self, index, value);
}

void Machine_List_removeAt(Machine_List* self, size_t index) {
  MACHINE_ASSERT_NOTNULL(self);
  self->removeAt(self, index);
}

void Machine_List_removeAtFast(Machine_List* self, size_t index) {
  MACHINE_ASSERT_NOTNULL(self);
  self->removeAtFast(self, index);
}

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

void Machine_List_reverse(Machine_List* self) {
  MACHINE_ASSERT_NOTNULL(self);
  self->reverse(self);
}

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

Machine_List* Machine_List_slice(Machine_List* self, size_t start, size_t length) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->slice(self, start, index);
}

#endif
