// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/ArrayDeque.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/ArrayDeque.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#include "Ring2/Library/Collections/CollectionUtilities.h"
#include "Ring2/Library/Collections/Deque.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE
#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"


struct Ring2_Collections_ArrayDeque_Class {
  Machine_Object_Class parent;
};

struct Ring2_Collections_ArrayDeque {
  Machine_Object parent;
  /// @brief The size of the queue.
  int64_t size;
  /// @brief The capacity of the queue.
  /// @initial @a 0.
  int64_t capacity;
  /// @brief The head of the queue.
  /// @initial @a 0.
  int64_t head;
  /// @brief The tail of the queue.
  /// @initial @a 0.
  int64_t tail;
  /// @brief A pointer to an array of @a capacity Ring2_Value elements.
  Ring2_Value* elements;
};

/// @brief Modular @a mod increment of @a i by @a 1.
/// Same as
/// <code>
/// add(mod, i, 1)
/// </code>
/// @pre mod > 0
/// @pre 0 <= i < mod
/// @post 0 <= i < mod
static size_t
Machine_modIncrement1_sz
  (
    size_t mod,
    size_t i
  )
{
  assert(mod > 0);
  assert(0 <= i && i < mod);
  if (++i >= mod)
    return 0;
  return i;
}

static int64_t
Machine_modIncrement1_s64
  (
    int64_t mod,
    int64_t i
  )
{
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
static size_t
Machine_modDecrement1_sz
  (
    size_t mod,
    size_t i
  )
{
  assert(mod > 0);
  assert(0 <= i && i < mod);
  if (i == 0)
    return mod - 1;
  else
    return --i;
}

static int64_t
Machine_modDecrement1_s64
  (
    int64_t mod,
    int64_t i
  )
{
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
static size_t
Machine_modAdd_sz
  (
    size_t mod,
    size_t i,
    size_t j
  )
{
  return (i + j) % mod;
}

static int64_t
Machine_modAdd_s64
  (
    int64_t mod,
    int64_t i,
    int64_t j
  )
{
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
static size_t
Machine_modSub_sz
  (
    size_t mod,
    size_t i,
    size_t j
  )
{
  if (i < j) {
    j -= i;
    i = mod - j;
  } else {
    i -= j;
  }
}

static int64_t
Machine_modSub_s64
  (
    int64_t mod,
    int64_t i,
    int64_t j
  )
{
  if (i < j) {
    j -= i;
    i = mod - j;
  } else {
    i -= j;
  }
}

static int64_t const maximalCapacity = (INT64_MAX < SIZE_MAX ? INT64_MAX : SIZE_MAX) / sizeof(Ring2_Value);

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_ArrayDeque* self
  );

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_ArrayDeque const* self
  );

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_ArrayDeque const* self
  );

// Ring2.Collections.Deque
static void
pushFront
  (
    Ring2_Collections_ArrayDeque* self,
    Ring2_Value value
  );

// Ring2.Collections.Deque
static Ring2_Value
popFront
  (
    Ring2_Collections_ArrayDeque* self
  );

// Ring2.Collections.Deque
static void
pushBack
  (
    Ring2_Collections_ArrayDeque* self,
    Ring2_Value value
  );

// Ring2.Collections.Deque
static Ring2_Value
popBack
  (
    Ring2_Collections_ArrayDeque* self
  );

static void
Ring2_Collections_ArrayDeque_visit
  (
    Ring2_Collections_ArrayDeque* self
  );

static void
Ring2_Collections_ArrayDeque_destruct
  (
    Ring2_Collections_ArrayDeque* self
  );

static void
Ring2_Collections_ArrayDeque_implement_Ring2_Collections_Collection
  (
    Ring2_Collections_Collection_Dispatch* self
  )
{
  self->clear = Ring1_cast(void (*)(Ring2_Collections_Collection*), & clear);
  self->getSize = Ring1_cast(int64_t (*)(Ring2_Collections_Collection const*), & getSize);
  self->isEmpty = Ring1_cast(bool (*)(Ring2_Collections_Collection const*), & isEmpty);
}

static void
Ring2_Collections_ArrayDeque_implement_Ring2_Collections_Deque
  (
    Ring2_Collections_Deque_Dispatch* self
  )
{
  self->pushFront = Ring1_cast(void (*)(Ring2_Collections_Deque*, Ring2_Value), &pushFront);
  self->popFront = Ring1_cast(Ring2_Value(*)(Ring2_Collections_Deque*), &popFront);
  self->pushBack = Ring1_cast(void (*)(Ring2_Collections_Deque*, Ring2_Value), &pushBack);
  self->popBack = Ring1_cast(Ring2_Value(*)(Ring2_Collections_Deque*), &popBack);
}

static void
Ring2_Collections_ArrayDeque_constructClass
  (
    Ring2_Collections_ArrayDeque_Class* self
  )
{ }

static void
Ring2_Collections_ArrayDeque_visit
  (
    Ring2_Collections_ArrayDeque* self
  )
{
  for (int64_t i = 0, n = self->size; i < n; ++i) {
    Ring2_Value_visit(Ring2_Gc_get(), &(self->elements[i]));
  }
}

static void
Ring2_Collections_ArrayDeque_implementInterfaces
  (
    Machine_ClassType* self
  )
{
  Machine_ClassType_implement(self, Ring2_Collections_Collection_getType(),
                              (Machine_InterfaceConstructCallback*)&Ring2_Collections_ArrayDeque_implement_Ring2_Collections_Collection);
  Machine_ClassType_implement(self, Ring2_Collections_Deque_getType(),
                              (Machine_InterfaceConstructCallback*)&Ring2_Collections_ArrayDeque_implement_Ring2_Collections_Deque);
}

static void
Ring2_Collections_ArrayDeque_destruct
  (
    Ring2_Collections_ArrayDeque* self
  )
{
  if (self->elements) {
    Ring1_Memory_deallocate(self->elements);
    self->elements = NULL;
  }
}

static void
Ring2_Collections_ArrayDeque_construct
  (
    Ring2_Collections_ArrayDeque* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->capacity = 0;
  self->size = 0;
  self->head = 0;
  self->tail = 0;
  self->elements = NULL;
  if (Ring1_Memory_allocateArray(&self->elements, self->capacity, sizeof(Ring2_Value))) {
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_Collections_ArrayDeque_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring2_Collections_ArrayDeque /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring2_Collections_ArrayDeque_visit /*visit*/,
                         &Ring2_Collections_ArrayDeque_construct /*construct*/,
                         &Ring2_Collections_ArrayDeque_destruct /*destruct*/,
                         &Ring2_Collections_ArrayDeque_constructClass /*constructClasses*/,
                         &Ring2_Collections_ArrayDeque_implementInterfaces /*implementInterfaces*/)

// Ring2.Collections.Collection
static void
clear
  (
    Ring2_Collections_ArrayDeque* self
  )
{ self->size = 0; }

// Ring2.Collections.Collection
static int64_t
getSize
  (
    Ring2_Collections_ArrayDeque const* self
  )
{ return self->size; }

// Ring2.Collections.Collection
static bool
isEmpty
  (
    Ring2_Collections_ArrayDeque const* self
  )
{ return 0 == self->size; }

/// @brief This is the less optimized but more intuitive version of "grow".
/// @param self A pointer to this queue.
static void
grow1
  (
    Ring2_Collections_ArrayDeque* self,
    size_t requiredAdditionalCapacity
  )
{
  // Nothing to do.
  if (requiredAdditionalCapacity == 0) {
    return;
  }
  int64_t oldCapacity = self->capacity;
  int64_t newCapacity;
  if (Ring1_Memory_recomputeSize_s64(0, maximalCapacity, oldCapacity, requiredAdditionalCapacity, 
                                     &newCapacity, true)) {
    Ring2_jump();
  }
  Ring2_Value* oldElements = self->elements;
  // Make a copy of the old array.
  Ring2_Value* newElements = CollectionUtilities_copyOfArray(newCapacity, oldElements, oldCapacity, true);
  if (self->tail < self->head || (self->tail == self->head && self->size > 0)) {
    // We must preserve the invariant that the 1st, 2nd, 3rd, ... elements
    // pushed to the front reside at the indices capacity-1, capacity-2, capacity-3, ...
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
    int64_t deltaCapacity = newCapacity - oldCapacity;
    Ring1_Memory_copySlow(newElements + self->head + deltaCapacity, newElements + self->head,
                          (oldCapacity - self->head) * sizeof(Ring2_Value));
    self->head += deltaCapacity;
  }
  self->elements = newElements;
  self->capacity = newCapacity;
}

/// @brief This is the less optimized but more intuitive version of "maybeGrow".
/// @param self A pointer to this queue.
static void
maybeGrow1
  (
    Ring2_Collections_ArrayDeque* self
  )
{
  if (self->size == self->capacity) {
    grow1(self, 1);
  }
}

// Ring2.Collections.Deque
static Ring2_Value
popBack
  (
    Ring2_Collections_ArrayDeque* self
  )
{
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

// Ring2.Deque
static void
pushBack
  (
    Ring2_Collections_ArrayDeque* self,
    Ring2_Value value
  )
{
  maybeGrow1(self);
  int64_t newTail = Machine_modIncrement1_sz(self->capacity, self->tail);
  int64_t newSize = self->size + 1;
  self->elements[self->tail] = value; // Do not use newTail.
  self->tail = newTail;
  self->size = newSize;
}

// Ring2.Collections.Deque
static Ring2_Value
popFront
  (
    Ring2_Collections_ArrayDeque* self
  )
{
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

// Ring2.Deque
static void
pushFront
  (
    Ring2_Collections_ArrayDeque* self,
    Ring2_Value value
  )
{
  maybeGrow1(self);
  int64_t newHead = Machine_modDecrement1_sz(self->capacity, self->head);
  int64_t newSize = self->size + 1;
  self->elements[newHead] = value; // Do use newHead.
  self->head = newHead;
  self->size = newSize;
}

Ring2_Collections_ArrayDeque*
Ring2_Collections_ArrayDeque_create
  (
  )
{
  Machine_ClassType* ty = Ring2_Collections_ArrayDeque_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Collections_ArrayDeque* self = (Ring2_Collections_ArrayDeque*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
