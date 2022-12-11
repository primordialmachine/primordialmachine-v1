// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerDeque.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_COLLECTIONS_PRIVATE (1)
#include "Ring1/Collections/PointerDeque.h"
#undef RING1_COLLECTIONS_PRIVATE


#include "Ring1/Memory.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Memory)
Ring1_EndDependencies()

static Ring1_Result
initializeModule
  (
  )
{ return startupDependencies(); }

static void
uninitializeModule
  (
  )
{ shutdownDependencies(); }

Ring1_Module_Define(Ring1, PointerDeque, initializeModule, uninitializeModule)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// A naive pointer deque implemention would be a pointer array.
// The problem with a naive implementation is the pop front operation.
// Everytime an element is removed at the front, we would need to shift down all its subsequent elements by 1 i.e. "remove front" is O(n) in all cases.
// This is the motivation for a more elaborated implementation which removes in O(1) in the average case.
//
// First note that if we access a normal pointer array with a proper index 0 <= i < capacity,
// the i % capacity is equivalent to i for any i (as i is smaller than capacity). For example,
// a capacity of 5 the valid indices are in {0, 1, 2, 3, 4} and i % capacity is in {0,1,2,3,4}.
//
// Now this allows for adjusting any array access to i % capacity without any change.

typedef struct Impl {
  /// @brief A pointer to an array of @a capacity @a (void *) elements.
  void **elements;
  /// @brief The capacity, in elements, of the array pointed to by @a array.
  int64_t capacity;
  /// @brief The position to read from.
  int64_t read;
  /// @brief The number of elements in this array.
  int64_t size;
  /// @brief A pointer to a "added" callback function or a null pointer.
  Ring1_AddedCallback *added;
  /// @brief A pointer to a "removed" callback or  a null pointer.
  Ring1_RemovedCallback *removed;
} Impl; // struct Impl


static inline int64_t
MOD
  (
    int64_t index,
    int64_t capacity
  );

static inline int64_t
MOD
  (
    int64_t index,
    int64_t capacity
  )
{ return index % capacity; }

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
increaseCapacity
  (
    Impl *pimpl,
    int64_t requiredAdditionalCapacity
  )
{
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(requiredAdditionalCapacity < 0)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  int64_t oldCapacity = pimpl->capacity,
          newCapacity;
  if (Ring1_Memory_recomputeSize_u64(Ring1_PointerDeque_Capacity_Least, Ring1_PointerDeque_Capacity_Greatest, oldCapacity, requiredAdditionalCapacity, &newCapacity, false)) {
    return Ring1_Result_Failure;
  }
  void **oldElements = pimpl->elements, **newElements = NULL;
  if (Ring1_Unlikely(Ring1_Memory_allocateArray((void **)&newElements, (size_t)newCapacity, sizeof(void*)))) {
    return Ring1_Result_Failure;
  }

  // When resizing, this is the perfect opportunity to set "read" to "0".
  for (int64_t i = 0, n = pimpl->size, oldRead = pimpl->read; i < n; ++i) {
    // The i-th elements source position is (oldRead + i) % oldCapacity.
    // The i-th elements target position is
    //   (newRead + i) % newCapacity   | as newRead is 0.
    // ~ i % newCapacity               | as i < oldCapacity <= newCapacity.
    // ~ i 
    newElements[i] = oldElements[MOD(oldRead + i, oldCapacity)];
  }
  Ring1_Memory_deallocate(oldElements);
  pimpl->read = 0;
  pimpl->elements = newElements;
  pimpl->capacity = newCapacity;

  return Ring1_Result_Success;
}

static inline Ring1_Result
clear
  (
    Impl *pimpl
  )
{
  if (pimpl->removed) {
    Ring1_RemovedCallback *removed = pimpl->removed;
    const int64_t capacity = pimpl->capacity;
    while (pimpl->size > 0) {
      void *element = pimpl->elements[MOD(pimpl->read + pimpl->size - 1, capacity)];
      (*removed)(element);
      pimpl->size--;
    }
  } else {
    pimpl->size = 0;
  }
  return Ring1_Result_Success;
}

static inline int
ensureFreeCapacity
  (
    Impl *pimpl,
    int64_t requiredFreeCapacity
  )
{
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(requiredFreeCapacity < 0)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!requiredFreeCapacity)) {
    return Ring1_Result_Success;
  }
  int64_t actualFreeCapacity = pimpl->capacity - pimpl->size;
  if (actualFreeCapacity < requiredFreeCapacity) {
    return increaseCapacity(pimpl, requiredFreeCapacity - actualFreeCapacity);
  }
  return Ring1_Result_Success;
}

Ring1_NonNull() static inline int
getSize
  (
    int64_t *size,
    Impl* pimpl
  )
{
  if (Ring1_Unlikely(!size || !pimpl)) return Ring1_Status_InvalidArgument;
  *size = pimpl->size;
  return Ring1_Status_Success;
}

Ring1_NonNull() static inline int
getCapacity
  (
    int64_t *capacity,
    Impl* pimpl
  )
{
  if (Ring1_Unlikely(!capacity || !pimpl)) return Ring1_Status_InvalidArgument;
  *capacity = pimpl->capacity;
  return Ring1_Status_Success;
}

static inline int64_t
getFreeCapacity
  (
    Impl* pimpl
  )
{ return pimpl->capacity - pimpl->size; }

static inline void
uninitialize
  (
    Impl* pimpl
  )
{
  clear(pimpl);
  Ring1_Memory_deallocate(pimpl->elements);
  pimpl->elements = NULL;
  pimpl->capacity = 0;
}

static inline int
insertAt
  (
    Impl *pimpl,
    int64_t index,
    bool invokeAddedCallback,
    void *pointer
  )
{
  // The pointer to the deque must not be a null pointer.
  if (Ring1_Unlikely(!pimpl)) return 1;
  //
  // "index" must be non-negative and smaller than or equal to the size of the deque.
  if (Ring1_Unlikely(index < 0 || index > pimpl->size)) return 1;

  // Ensure there is room for one more element.
  if (ensureFreeCapacity(pimpl, 1)) return 1;

  const int64_t capacity = pimpl->capacity; // The capacity does not change anymore for the rest of this
                                            // function but is frequently referenced, hence it is cached
                                           // here.

  // The goal of the following algorithm is to minimize the number of shift operations when inserting into an index
  // smaller than size.

  // Assume the deque is not empty.
  // Treating the deque as an infinite array,
  // ..., a[0],...,a[read],...,a[read+index], ..., a[read+size-1]
  // then
  // a) the index of the first element is "read" and
  // b) the index of the last element is "read + size - 1" and
  // c) "read <= index <= read + size".
  //
  // So to insert at index "index", one can either shift up the elements
  // "a[read + index],... a[read+size-1]" or
  // shift down the elements
  // "a[read] ... a[read + index-1]"
  // to make room for the new element.
  //
  // The choice made here is to minimize the number of shifts:
  // if "index < size / 2" then "a[read] ... a[read + index - 1]" is shifted down
  // and otherwise "a[read + index],... a[read+size-1]" is shifted up.
  if (index < pimpl->size / 2)
  {
    // If a' ist the new queue and a is the old queue, then the operation
    // can be described as follows:
    // - a'[read-1] = a[read], ..., a'[read - 1 + index] = a[read + index]
    // - a'[read+index] = newElement
    // - read' = read - 1
    // - size' = size + 1
    // As read' = read - 1, one can also write
    // - a'[read'] = a[read' + 1], ..., a'[read + index] = a[read' + index + 1]
    // which is the form used here.
    int64_t offset = MOD(pimpl->read - 1, capacity);
    for (int64_t j = 0; j < index; ++j)
    {
      pimpl->elements[MOD(offset + j, capacity)] = pimpl->elements[MOD(offset + j + 1, capacity)];
    }
    pimpl->read = MOD(pimpl->read - 1, capacity);
  }
  else
  {
    // If a' ist the new queue and a is the old queue, then the operation
    // can be described as follows:
    // - a'[read + size] = a[read + size - 1], ..., a'[read + index + 1] = a[read + index]
    // - a'[read + index] = newElement
    // - read' = read
    // - size' = size+1
    int64_t offset = pimpl->read;
    for (int64_t j = pimpl->size; j > index; --j)
    {
      pimpl->elements[MOD(offset + j, capacity)] = pimpl->elements[MOD(offset + j - 1, capacity)];
    }
  }
  pimpl->elements[MOD(pimpl->read + index, capacity)] = pointer;
  pimpl->size++;

  if (invokeAddedCallback && pimpl->added)
  {
    (*pimpl->added)(pointer);
  }

  return Ring1_Status_Success;
}

static inline int
insertBack
  (
    Impl* pimpl,
    void* pointer
  )
{
  if (Ring1_Unlikely(!pimpl)) return 1;
  return insertAt(pimpl, pimpl->size, true, pointer);
}

static inline int
insertFront
  (
    Impl* pimpl,
    void* pointer
  )
{
  if (Ring1_Unlikely(!pimpl)) return 1;
  return insertAt(pimpl, 0, true, pointer);
}

static inline int
removeAt
  (
    Impl *pimpl,
    int64_t index,
    bool invokeRemovedCallback,
    void **element
  )
{
  // The pointer to the dequeue must not be a null pointer and the index must be non-negative.
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // If the queue must not be empty.
  if (pimpl->size == 0) {
    Ring1_Status_set(Ring1_Status_IsEmpty);
    return Ring1_Result_Failure;
  }
  // The index must be non-negative.
  if (Ring1_Unlikely(index < 0)) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    return Ring1_Result_Failure;
  }
  // The index must be non-negative and smaller than the size of the queue.
  if (Ring1_Unlikely(index >= pimpl->size)) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    return Ring1_Result_Failure;
  }

  void* pointer = pimpl->elements[MOD(pimpl->read + index, pimpl->capacity)];
  const int64_t capacity = pimpl->capacity;
  if (index < pimpl->size / 2)
  {  
    // - a'[read] = a[read-1], ..., a'[read + index] = a[read + index - 1] 
    // - read' = read + 1
    // - size' = size - 1
    int64_t offset = pimpl->read;
    for (int64_t j = index; j > 0; --j)
    {
      pimpl->elements[MOD(offset + j, capacity)] = pimpl->elements[MOD(offset + j - 1, capacity)];
    }
    pimpl->read = MOD(pimpl->read + 1, capacity);
  }
  else
  {
    // - a'[read+index] = a[read+index+1], ..., a'[read+size-2] = a[read+size-1]
    // - read' = read
    // - size' = size - 1
    // shift a[i+1],..,a[n-1] left one position
    for (int64_t j = index; j < pimpl->size - 1; ++j)
    {
      pimpl->elements[MOD(pimpl->read + j, capacity)] = pimpl->elements[MOD(pimpl->read + j + 1, capacity)];
    }
  }
  pimpl->size--;
 
  if (element)
  {
    *element = pointer;
  }
  
  if (invokeRemovedCallback && pimpl->removed)
  {
    (*pimpl->removed)(pointer);
  }

  return Ring1_Status_Success;
}

static inline int
getAt
  (
    Impl *pimpl,
    int64_t index,
    void **element
  )
{
  if (Ring1_Unlikely(!pimpl || !element || index < 0)) return 1;
  if (Ring1_Unlikely(index >= pimpl->size)) return 1;
  *element = pimpl->elements[MOD(pimpl->read + index, pimpl->capacity)];
  return Ring1_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_initialize
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t initialCapacity,
    Ring1_AddedCallback *added,
    Ring1_RemovedCallback *removed
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(initialCapacity < Ring1_PointerDeque_Capacity_Least)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(initialCapacity > Ring1_PointerDeque_Capacity_Greatest)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }

  Impl* pimpl;
  if (Ring1_Memory_allocate(&pimpl, sizeof(Impl))) {
    return Ring1_Result_Failure;
  }

  if (initialCapacity < 0) {
    initialCapacity = Ring1_PointerDeque_Capacity_Default;
  }
  pimpl->elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&pimpl->elements, (size_t)initialCapacity, sizeof(void*))) {
    Ring1_Memory_deallocate(pimpl);
    pimpl = NULL;
    return Ring1_Result_Failure;
  }
  pimpl->read = 0;
  pimpl->size = 0;
  pimpl->capacity = initialCapacity;
  pimpl->added = added;
  pimpl->removed = removed;
  pointerDeque->pimpl = pimpl;
  return Ring1_Result_Success;
}

void
Ring1_PointerDeque_uninitialize
  (
    Ring1_PointerDeque *pointerDeque
  )
{
  uninitialize(pointerDeque->pimpl);
  Ring1_Memory_deallocate(pointerDeque->pimpl);
  pointerDeque->pimpl = NULL;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_increaseCapacity
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t requiredAdditionalCapacity
  )
{ return increaseCapacity(pointerDeque->pimpl, requiredAdditionalCapacity); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_filter
  (
    Ring1_PointerDeque* pointerDeque,
    Ring1_WhereContext* whereContext,
    Ring1_WhereCallback* whereCallback
  )
{
  Impl* pimpl = pointerDeque->pimpl;
  void** temporary = NULL;
  if (Ring1_Unlikely(Ring1_Memory_allocateArray((void **)&temporary, (size_t)pimpl->capacity, sizeof(void*)))) {
    return Ring1_Result_Failure;
  }
  size_t i = 0, j = 0, n = (size_t)pimpl->size;
  while (i < n) {
    void* element = pimpl->elements[MOD(pimpl->read + i, pimpl->capacity)];
    bool result;
    if (Ring1_Unlikely(whereCallback(&result, whereContext, i, element))) {
      Ring1_Memory_deallocate(temporary);
      return 1;
    }
    if (result) {
      temporary[MOD(pimpl->read + j++, pimpl->capacity)] = element;
    } else {
      if (pimpl->removed) {
        (*pimpl->removed)(element);
      }
    }
    i++;
  }
  Ring1_Memory_deallocate(pimpl->elements);
  pimpl->elements = temporary;
  pimpl->size = j;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_ensureFreeCapacity
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t requiredFreeCapacity
  )
{ return ensureFreeCapacity(pointerDeque->pimpl, requiredFreeCapacity); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_getSize
  (
    int64_t *size,
    Ring1_PointerDeque *pointerDeque
  )
{
  if (Ring1_Unlikely(!size)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return getSize(size, pointerDeque->pimpl);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_getCapacity
  (
    int64_t *capacity,
    Ring1_PointerDeque *pointerDeque
  )
{
  if (Ring1_Unlikely(!pointerDeque)) return Ring1_Status_InvalidArgument;
  return getCapacity(capacity, pointerDeque->pimpl);
}

Ring1_NonNull() int64_t
Ring1_PointerDeque_getFreeCapacity
  (
    Ring1_PointerDeque* pointerDeque
  )
{ return getFreeCapacity(pointerDeque->pimpl); }

Ring1_Result
Ring1_PointerDeque_clear
  (
    Ring1_PointerDeque *pointerDeque
  )
{ 
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return clear(pointerDeque->pimpl);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_insertAt
  (
    Ring1_PointerDeque* pointerDeque,
    int64_t index,
    void* pointer
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return insertAt(pointerDeque->pimpl, index, true, pointer);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_insertBack
  (
    Ring1_PointerDeque *pointerDeque,
    void *pointer
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return insertBack(pointerDeque->pimpl, pointer);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_insertFront
  (
    Ring1_PointerDeque *pointerDeque,
    void *pointer
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return insertFront(pointerDeque->pimpl, pointer);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_getAt
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t index,
    void **element
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return getAt(pointerDeque->pimpl, index, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_removeAt
  (
    Ring1_PointerDeque *pointerDeque,
    int64_t index,
    void **element
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeAt(pointerDeque->pimpl, index, true, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_stealAt
  (
    Ring1_PointerDeque* pointerDeque,
    int64_t index,
    void** element
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeAt(pointerDeque->pimpl, index, false, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_removeFront
  (
    Ring1_PointerDeque* pointerDeque,
    void** element
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeAt(pointerDeque->pimpl, 0, true, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerDeque_stealFront
  (
    Ring1_PointerDeque* pointerDeque,
    void** element
  )
{
  if (Ring1_Unlikely(!pointerDeque)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeAt(pointerDeque->pimpl, 0, false, element);
}
