/// @file Collection/List.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/List.h"



#include "Collections/ICollection.h"
#include "Collections/IList.h"
#include "Collections/GrowthStrategy.h"



static const size_t maximalCapacity = SIZE_MAX / sizeof(Machine_Value);

static void append(Machine_List* self, Machine_Value value);

static void prepend(Machine_List* self, Machine_Value value);

static void insertAt(Machine_List* self, size_t index, Machine_Value value);

static Machine_Value getAt(Machine_List const* self, size_t index);

static void removeAt(Machine_List* self, size_t index);

static void removeAtFast(Machine_List* self, size_t index);

static size_t getSize(Machine_List const* self);

static void clear(Machine_List* self);

#if defined(Machine_IList_withReverse) && Machine_IList_withReverse == 1

static void reverse(Machine_List* self);

#endif

#if defined(Machine_IList_withSlice) && Machine_IList_withSlice == 1

static Machine_List* slice(Machine_List* self, size_t start, size_t length);

#endif

static void Machine_List_visit(Machine_List* self);

static void Machine_List_destruct(Machine_List* self);

static void Machine_List_implement_Machine_ICollection(Machine_ICollection_Dispatch* self) {
  self->getSize = (size_t(*)(Machine_ICollection const*)) & getSize;
  self->clear = (void (*)(Machine_ICollection*)) & clear;
}

static void Machine_List_implement_Machine_IList(Machine_IList_Dispatch* self) {
  self->append = (void (*)(Machine_IList*, Machine_Value)) & append;
  self->prepend = (void (*)(Machine_IList*, Machine_Value)) & prepend;
  self->insertAt = (void (*)(Machine_IList*, size_t, Machine_Value)) & insertAt;
  self->getAt = (Machine_Value(*)(Machine_IList const*, size_t)) & getAt;
  self->removeAt = (void (*)(Machine_IList*, size_t)) & removeAt;
  self->removeAtFast = (void (*)(Machine_IList*, size_t)) & removeAtFast;
#if defined(Machine_IList_withReverse) && Machine_IList_withReverse == 1
  self->reverse = (void (*)(Machine_IList *)) & reverse;
#endif
#if defined(Machine_IList_withSlice) && Machine_IList_withSlice == 1
  self->slice = (Machine_IList *(*)(Machine_IList *, size_t, size_t))&slice;
#endif
}

static void Machine_List_implementInterfaces(Machine_ClassType* self) {
  Machine_ClassType_implement(self, Machine_ICollection_getType(),
                              (Machine_InterfaceConstructCallback *)&Machine_List_implement_Machine_ICollection);
  Machine_ClassType_implement(self, Machine_IList_getType(),
                              (Machine_InterfaceConstructCallback*)&Machine_List_implement_Machine_IList);
}

static void Machine_List_constructClass(Machine_List_Class* self) {
  ((Machine_Collection_Class*)self)->getSize = (size_t(*)(Machine_Collection const*)) & getSize;
  ((Machine_Collection_Class*)self)->clear = (void (*)(Machine_Collection*)) & clear;
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
  self->elements = Machine_Eal_Memory_allocate(0);
  if (!self->elements) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_List_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_List, Machine_Collection, &Machine_List_visit,
                         &Machine_List_construct, &Machine_List_destruct,
                         &Machine_List_constructClass, &Machine_List_implementInterfaces)

static void append(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_IList_insertAt((Machine_IList *)self, Machine_Collection_getSize((Machine_Collection*)self), value);
}

static void prepend(Machine_List* self, Machine_Value value) {
  MACHINE_ASSERT_NOTNULL(self);
  Machine_IList_insertAt((Machine_IList *)self, 0, value);
}

static void insertAt(Machine_List* self, size_t index, Machine_Value value) {
  if ((self->capacity - self->size) == 0) {
    size_t newCapacity;
    Machine_StatusValue status = Machine_Collections_getBestCapacity(self->capacity, 1, maximalCapacity, &newCapacity);
    if (status != Machine_Status_Success) {
      Machine_setStatus(status);
      Machine_jump();
    }
    void* newElements = Machine_Eal_Memory_reallocateArray(self->elements, sizeof(Machine_Value), newCapacity);
    if (!newElements) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->elements = newElements;
    self->capacity = newCapacity;
  }
  if (index < self->size) {
    Machine_Eal_Memory_copy(self->elements + index + 1, self->elements + index + 0, sizeof(Machine_Value) * (self->size - index), true);
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
    Machine_Eal_Memory_copy(self->elements + index + 0, self->elements + index + 1,
                            sizeof(Machine_Value) * (self->size - index - 1), true);
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
    Machine_Eal_Memory_deallocate(self->elements);
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
