// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArrayDeque.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ArrayDeque.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#include "Ring2/Library/CollectionUtilities.h"
#include "Ring2/Library/Deque.h"
#undef RING2_LIBRARY_PRIVATE


/// @brief Modular @a mod increment of @a i by @a 1.
/// Same as
/// <code>
/// add(mod, i, 1)
/// </code>
/// @pre mod > 0
/// @pre 0 <= i < mod
/// @post 0 <= i < mod
static size_t Machine_modIncrement1_sz(size_t mod, size_t i) {
  assert(mod > 0);
  assert(0 <= i && i < mod);
  if (++i >= mod)
    return 0;
  return i;
}

/// @brief Modular @a mod decrement of @a i by @a 1.
/// Same as
/// <code>
/// subtract(mod, i, 1)
/// </code>
/// @pre mod > 0
/// @pre 0 <= i < mod
/// @post 0 <= i < mod
static size_t Machine_modDecrement1_sz(size_t mod, size_t i) {
  assert(mod > 0);
  assert(0 <= i && i < mod);
  if (i == 0)
    return mod - 1;
  else
    return --i;
}

/// <code>
/// (i + j) MOD mod
/// </code>
/// @pre mod > 0
/// @pre 0 <= i, j < n
/// @post 0 <= i < n
static size_t Machine_modAdd_sz(size_t mod, size_t i, size_t j) {
  return (i + j) % mod;
}

/// <code>
/// (i - j) MOD mod
/// </code>
/// @example
/// <code>
/// i = 2, j = 5, mod = 7
/// 2 - 5 % 7 = -3 % 7 = 4
/// </code>
/// @pre mod > 0
/// @pre 0 <= i, j < n,
/// @post 0 <= i < n
static size_t Machine_modSub_sz(size_t mod, size_t i, size_t j) {
  if (i < j) {
    j -= i;
    i = mod - j;
  } else {
    i -= j;
  }
}

static int64_t const maximalCapacity = (INT64_MAX < SIZE_MAX ? INT64_MAX : SIZE_MAX) / sizeof(Ring2_Value);

// Ring2.Collection
static void
clear
  (
    Machine_ArrayDeque* self
  );

// Ring2.Collection
static int64_t
getSize
  (
    Machine_ArrayDeque const* self
  );

// Ring2.Collection
static bool
isEmpty
  (
    Machine_ArrayDeque const* self
  );

static void pushFront(Machine_ArrayDeque* self, Ring2_Value value);

static Ring2_Value popFront(Machine_ArrayDeque* self);

static void pushBack(Machine_ArrayDeque* self, Ring2_Value value);

static Ring2_Value popBack(Machine_ArrayDeque* self);

static void Machine_ArrayDeque_visit(Machine_ArrayDeque* self);

static void Machine_ArrayDeque_destruct(Machine_ArrayDeque* self);

static void Machine_ArrayDeque_implement_Machine_Collection(Machine_Collection_Dispatch* self) {
  self->clear = (void (*)(Machine_Collection*)) & clear;
  self->getSize = (int64_t (*)(Machine_Collection const*)) & getSize;
  self->isEmpty = (bool (*)(Machine_Collection const*)) & isEmpty;
}

static void Machine_ArrayDeque_implement_Machine_Deque(Machine_Deque_Dispatch* self) {
  self->pushFront = (void (*)(Machine_Deque*, Ring2_Value)) & pushFront;
  self->popFront = (Ring2_Value(*)(Machine_Deque*)) & popFront;
  self->pushBack = (void (*)(Machine_Deque*, Ring2_Value)) & pushBack;
  self->popBack = (Ring2_Value(*)(Machine_Deque*)) & popBack;
}

static void Machine_ArrayDeque_constructClass(Machine_ArrayDeque_Class* self) {
}

static void Machine_ArrayDeque_visit(Machine_ArrayDeque* self) {
  for (int64_t i = 0, n = self->size; i < n; ++i) {
    Ring2_Value_visit(Ring2_Gc_get(), &(self->elements[i]));
  }
}

static void Machine_ArrayDeque_implementInterfaces(Machine_ClassType* self) {
  Machine_ClassType_implement(
      self, Machine_Collection_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_ArrayDeque_implement_Machine_Collection);
  Machine_ClassType_implement(
      self, Machine_Deque_getType(),
      (Machine_InterfaceConstructCallback*)&Machine_ArrayDeque_implement_Machine_Deque);
}

static void Machine_ArrayDeque_destruct(Machine_ArrayDeque* self) {
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

static void Machine_ArrayDeque_construct(Machine_ArrayDeque* self, size_t numberOfArguments,
                                         Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->capacity = 0;
  self->size = 0;
  self->head = 0;
  self->tail = 0;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray(&self->elements, self->capacity, sizeof(Ring2_Value))) {
    Ring2_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_ArrayDeque_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_ArrayDeque, Machine_Object, &Machine_ArrayDeque_visit,
                         &Machine_ArrayDeque_construct, &Machine_ArrayDeque_destruct,
                         &Machine_ArrayDeque_constructClass,
                         &Machine_ArrayDeque_implementInterfaces)

// Ring2.Collection
static void
clear
  (
    Machine_ArrayDeque* self
  )
{ self->size = 0; }

static int64_t
getSize
  (
    Machine_ArrayDeque const* self
  )
{ return self->size; }

static bool
isEmpty
  (
    Machine_ArrayDeque const* self
  )
{ return 0 == self->size; }

/// @brief This is the less optimized but more intuitive version of "grow".
/// @param self A pointer to this queue.
static void grow1(Machine_ArrayDeque* self, size_t requiredAdditionalCapacity) {
  // Nothing to do.
  if (requiredAdditionalCapacity == 0) {
    return;
  }
  size_t oldCapacity = self->capacity;
  size_t newCapacity;
  if (Ring1_Memory_recomputeSize_sz(0, maximalCapacity, oldCapacity, requiredAdditionalCapacity, 
                                    &newCapacity, true)) {
    Ring2_jump();
  }
  Ring2_Value* oldElements = self->elements;
  // Make a copy of the old array.
  Ring2_Value* newElements
      = CollectionUtilities_copyOfArray(newCapacity, oldElements, oldCapacity, true);
  if (self->tail < self->head || (self->tail == self->head && self->size > 0)) {
    // We must preserve the invariant that the 1st, 2nd, 3rd, ... elements
    // pushed to the front reside at the indices capacity-1, capacity-2, capacity -3, ...
    //
    // ======================================================================
    // Example #1:
    // Assume a queue of c = 4, s = 0, t = 0, h = 0.
    // [--,--,--,--], c = 4, s = 0, t = 0, h = 0
    // addFront(x0)
    // [--,--,--,x0], c = 4, s = 1, t = 0, h = 3
    // addFront(x1)
    // [--,--,x1,x0], c = 4, s = 2, t = 0, h = 2
    // addFront(x2)
    // [--,x2,x1,x0], c = 4, s = 3, t = 0, h = 1
    // addFront(x3)
    // [x3,x2,x1,x0] c = 4, s = 4, t = 0, h = 0
    //
    // If we would add now any element either to the front or the back,
    // we first must grow the queue. Let us grow it by two items.
    // [x3,x2,x1,x0,--,--] c = 6, s = 4, t = 0, h = 0
    // However, this should rather look like
    // [--,--,x3,x2,x1,x0]
    // We must copy
    // ======================================================================
    // Example 2#:
    // Assume the following queue:
    // [--,--,--,--], c = 4, s = 0, t = 0, h = 0
    // We add four elements, two in the front (x0 and x1) and two in the back (y0 and y1).
    //
    // addFront(x0)
    // [--,--,--,x0], c = 4, s = 1, t = 0, h = 3
    //
    // addFront(x1)
    // [--,--,x1,x0], c = 4, s = 2, t = 0, h = 2
    //
    // addBack(y0)
    // [y0,--,x1,x0], c = 4, s = 3, t = 1, h = 2
    //
    // addBack(y1)
    // [y0,y1,x1,x0] c = 4, s = 4, t = 2, h = 2
    //
    // If we try to add another element either to the front or the back,
    // the queue's capacity would be increased before the element was added.
    // Assume the capacity was increased by 2 then we would obtain the following array:
    // [y0,y1,x1,x0,--,--] c = 6, s = 4, t = 2, h = 2
    // However, this should rather look like
    // [y0,y1,--,--,x1,x0] c = 6, s = 4, t = 2, h = 4

    // So we must copy
    // valuemove(a + 4, a + 2, 2)
    // to obtain
    // [y0,y1,--,--,x1,x0] c = 6, s = 4, t = 2, h = 4
    //
    // The target, the source, and the number of elements to copy are computed as follows:
    // a + 2 = a + head
    // a + 4 = a + head + newCapacity - oldCapacity
    // 2 = oldCapacity - head
    size_t deltaCapacity = newCapacity - oldCapacity;
    Ring1_Memory_copySlow(newElements + self->head + deltaCapacity, newElements + self->head,
                          (oldCapacity - self->head) * sizeof(Ring2_Value));
    self->head += deltaCapacity;
  }
  self->elements = newElements;
  self->capacity = newCapacity;
}

/// @brief This is the less optimized but more intuitive version of "maybeGrow".
/// @param self A pointer to this queue.
static void maybeGrow1(Machine_ArrayDeque* self) {
  if (self->size == self->capacity) {
    grow1(self, 1);
  }
}

static Ring2_Value popBack(Machine_ArrayDeque* self) {
  if (self->size == 0) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  int64_t newTail = Machine_modDecrement1_sz(self->capacity, self->tail);
  Ring2_Value value = self->elements[newTail]; // Do use newTail.
  self->tail = newTail;
  self->size--;
  return value;
}

static void pushBack(Machine_ArrayDeque* self, Ring2_Value value) {
  maybeGrow1(self);
  int64_t newTail = Machine_modIncrement1_sz(self->capacity, self->tail);
  int64_t newSize = self->size + 1;
  self->elements[self->tail] = value; // Do not use newTail.
  self->tail = newTail;
  self->size = newSize;
}

static Ring2_Value popFront(Machine_ArrayDeque* self) {
  if (self->size == 0) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  int64_t newHead = Machine_modIncrement1_sz(self->capacity, self->head);
  Ring2_Value value = self->elements[self->head]; // Do not use newHead.
  self->head = newHead;
  self->size--;
  return value;
}

static void pushFront(Machine_ArrayDeque* self, Ring2_Value value) {
  maybeGrow1(self);
  int64_t newHead = Machine_modDecrement1_sz(self->capacity, self->head);
  int64_t newSize = self->size + 1;
  self->elements[newHead] = value; // Do use newHead.
  self->head = newHead;
  self->size = newSize;
}

Machine_ArrayDeque* Machine_ArrayDeque_create() {
  Machine_ClassType* ty = Machine_ArrayDeque_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_ArrayDeque* self
      = (Machine_ArrayDeque*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
