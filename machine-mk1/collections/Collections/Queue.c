/// @file Collections/Queue.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/Queue.h"


#include "Collections/GrowthStrategy.h"
#include <assert.h>
#include <string.h>
#include "_Eal.h"

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
  if (++i >= mod) return 0;
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
  if (i == 0) return mod - 1;
  else return --i;
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
  }
  else {
    i -= j;
  }
}

static const size_t maximalCapacity = SIZE_MAX / sizeof(Machine_Value);

static void clear(Machine_Queue* self);

static size_t getSize(Machine_Queue const* self);

static void pushFront(Machine_Queue* self, Machine_Value value);

static Machine_Value popFront(Machine_Queue* self);

static void pushBack(Machine_Queue* self, Machine_Value value);

static Machine_Value popBack(Machine_Queue* self);

static void Machine_Queue_visit(Machine_Queue* self);

static void Machine_Queue_destruct(Machine_Queue* self);

static void Machine_Queue_constructClass(Machine_Queue_Class* self) {
  ((Machine_Collection_Class*)self)->clear = (void (*)(Machine_Collection*)) & clear;
  ((Machine_Collection_Class*)self)->getSize = (size_t(*)(Machine_Collection const*)) & getSize;
  self->pushFront = &pushFront;
  self->popFront = &popFront;
  self->pushBack = &pushBack;
  self->popBack = &popBack;
}

static void Machine_Queue_visit(Machine_Queue* self) {
  for (size_t i = 0, n = self->size; i < n; ++i) {
    Machine_Value_visit(&(self->elements[i]));
  }
}

static void Machine_Queue_destruct(Machine_Queue* self) {
  if (self->elements) {
    Machine_Eal_dealloc(self->elements);
    self->elements = NULL;
  }
}

static void Machine_Queue_construct(Machine_Queue* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Collection_construct((Machine_Collection*)self, numberOfArguments, arguments);
  self->capacity = 0;
  self->size = 0;
  self->head = 0;
  self->tail = 0;
  self->elements = Machine_Eal_alloc_a(self->capacity, sizeof(Machine_Value));
  if (!self->elements) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_setClassType((Machine_Object*)self, Machine_Queue_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Queue, Machine_Collection, &Machine_Queue_visit,
                         &Machine_Queue_construct, &Machine_Queue_destruct,
                         &Machine_Queue_constructClass, NULL)

static void clear(Machine_Queue* self) {
  self->size = 0;
}

static size_t getSize(Machine_Queue const* self) {
  return self->size;
}

/// @brief This is the less optimized but more intuitive version of "grow".
/// @param self A pointer to this queue.
static void grow1(Machine_Queue* self, size_t requiredAdditionalCapacity) {
  // Nothing to do.
  if (requiredAdditionalCapacity == 0) {
    return;
  }
  size_t oldCapacity = self->capacity;
  size_t newCapacity;
  Machine_StatusValue status = Machine_Collections_getBestCapacity(oldCapacity, requiredAdditionalCapacity, SIZE_MAX / sizeof(Machine_Value), &newCapacity);
  if (status != Machine_Status_Success) {
    Machine_setStatus(status);
    Machine_jump();
  }
  Machine_Value* oldElements = self->elements;
  // Make a copy of the old array.
  Machine_Value* newElements = Machine_ArrayUtilities_copyOf(newCapacity, oldElements, oldCapacity, true);
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
    Machine_Eal_copy(newElements + self->head + deltaCapacity, newElements + self->head,
                     (oldCapacity - self->head) * sizeof(Machine_Value), true);
    self->head += deltaCapacity;
  }
  self->elements = newElements;
  self->capacity = newCapacity;
}

/// @brief This is the less optimized but more intuitive version of "maybeGrow".
/// @param self A pointer to this queue.
static void maybeGrow1(Machine_Queue* self) {
  if (self->size == self->capacity) {
    grow1(self, 1);
  }
}

static Machine_Value popBack(Machine_Queue* self) {
  if (self->size == 0) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  size_t newTail = Machine_modDecrement1_sz(self->capacity, self->tail);
  Machine_Value value = self->elements[newTail]; // Do use newTail.
  self->tail = newTail;
  self->size--;
  return value;
}

static void pushBack(Machine_Queue* self, Machine_Value value) {
  maybeGrow1(self);
  size_t newTail = Machine_modIncrement1_sz(self->capacity, self->tail);
  size_t newSize = self->size + 1;
  self->elements[self->tail] = value; // Do not use newTail.
  self->tail = newTail;
  self->size = newSize;
}

static Machine_Value popFront(Machine_Queue* self) {
  if (self->size == 0) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  size_t newHead = Machine_modIncrement1_sz(self->capacity, self->head);
  Machine_Value value = self->elements[self->head]; // Do not use newHead.
  self->head = newHead;
  self->size--;
  return value;
}

static void pushFront(Machine_Queue* self, Machine_Value value) {
  maybeGrow1(self);
  size_t newHead = Machine_modDecrement1_sz(self->capacity, self->head);
  size_t newSize = self->size + 1;
  self->elements[newHead] = value; // Do use newHead.
  self->head = newHead;
  self->size = newSize;
}

Machine_Queue* Machine_Queue_create() {
  Machine_ClassType* ty = Machine_Queue_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Queue* self = (Machine_Queue*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Value Machine_Queue_popBack(Machine_Queue* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Queue, popBack);
}

void Machine_Queue_pushBack(Machine_Queue* self, Machine_Value value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Queue, pushBack, value);
}

Machine_Value Machine_Queue_popFront(Machine_Queue* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Queue, popFront);
}

void Machine_Queue_pushFront(Machine_Queue* self, Machine_Value value) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Queue, pushFront, value);
}
