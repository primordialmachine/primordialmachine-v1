// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerList.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_COLLECTIONS_PRIVATE (1)
#include "Ring1/Collections/PointerList.h"
#undef RING1_COLLECTIONS_PRIVATE


#include "Ring1/Memory/_Include.h"


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

Ring1_Module_Define(Ring1, PointerList, initializeModule, uninitializeModule)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Impl {
  void **elements;
  int64_t size, capacity;
  Ring1_AddedCallback *added;
  Ring1_RemovedCallback *removed;
} Impl;


static inline Ring1_NoDiscardReturn() Ring1_Result
clear
  (
    Impl *pimpl
  )
{
  if (pimpl->removed)
  {
    while (pimpl->size > 0)
    {
      void *element = pimpl->elements[--pimpl->size];
      pimpl->removed(&element);
    }
  }
  else
  {
    pimpl->size = 0;
  }
  return Ring1_Result_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
getAt
  (
    const Impl *pimpl,
    int64_t index,
    void **element
  )
{
  if (Ring1_Unlikely(index < 0 || index >= pimpl->size)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!element)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *element = pimpl->elements[index];
  return Ring1_Result_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
getSize
  (
    int64_t *size,
    const Impl *pimpl
  )
{
  if (Ring1_Unlikely(!size || !pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *size = pimpl->size;
  return Ring1_Result_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
insertAt
  (
    Impl* pimpl,
    int64_t index,
    void* element
  )
{
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(index < 0 || index > pimpl->size)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  if (pimpl->size == pimpl->capacity) {
    int64_t oldCapacity = pimpl->capacity,
            newCapacity;
    if (Ring1_Memory_recomputeSize_s64(Ring1_PointerList_Capacity_Least, Ring1_PointerList_Capacity_Greatest, oldCapacity, 1, &newCapacity, false)) {
      return Ring1_Result_Failure;
    }
    // Safe as PointerList_Capacity_Maximum <= size_t.
    void **oldElements = pimpl->elements,
         **newElements = NULL;
    if (Ring1_Unlikely(Ring1_Memory_allocateArray((void**)&newElements, (size_t)newCapacity, sizeof(void*)))) {
      return Ring1_Result_Failure;
    }
    if (Ring1_Memory_copyArrayFast(newElements, oldElements, (size_t)pimpl->size, sizeof(void *))) {
      Ring1_Memory_deallocate(newElements);
      return Ring1_Result_Failure;
    }
    Ring1_Memory_deallocate(oldElements);
    pimpl->elements = newElements;
    pimpl->capacity = newCapacity;
  }
  if (index != pimpl->size) {
    Ring1_Memory_copyArraySlow(pimpl->elements + (size_t)index + 1, pimpl->elements + (size_t)index, (size_t)pimpl->size - (size_t)index, sizeof(void *));
  }
  pimpl->elements[index] = element;
  pimpl->size++;
  if (pimpl->added) {
    pimpl->added(&element);
  }
  return Ring1_Result_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
insertFront
  (
    Impl* pimpl,
    void* element
  )
{ return insertAt(pimpl, 0, element); }

static inline Ring1_NoDiscardReturn() Ring1_Result
insertBack
  (
    Impl *pimpl,
    void* element
  )
{ return insertAt(pimpl, pimpl->size, element); }

static inline Ring1_NoDiscardReturn() Ring1_Result
find
  (
    Impl* pimpl,
    int64_t start,
    void* context,
    Ring1_PointerList_FindCallback* predicate,
    int64_t* firstOccurrence
  )
{
  if (!pimpl || start < 0 || !predicate || !firstOccurrence) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;;
  }
  if (pimpl->size == 0) {
    *firstOccurrence = -1;
    return Ring1_Status_Success;
  }
  if (start >= pimpl->size) return 1;
  for (int64_t i = start, n = (int64_t)pimpl->size; i < n; ++i)
  {
    void* element = pimpl->elements[i];
    bool result;
    if ((*predicate)(&result, context, element))
    { return Ring1_Result_Failure; }
    if (result) {
      *firstOccurrence = i;
      return Ring1_Status_Success;
    }
  }
  *firstOccurrence = -1;
  return Ring1_Status_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
initialize
  (
    Impl* pimpl,
    Ring1_AddedCallback* added,
    Ring1_RemovedCallback* removed
  )
{
  pimpl->added = added;
  pimpl->removed = removed;
  pimpl->size = 0;
  pimpl->capacity = Ring1_PointerList_Capacity_Default;
  pimpl->elements = NULL;
  if (Ring1_Unlikely(Ring1_Memory_allocateArray((void **)&pimpl->elements, Ring1_PointerList_Capacity_Default, sizeof(void*))))
    return Ring1_Result_Failure;
  return Ring1_Result_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
removeAt
  (
    Impl* pimpl,
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
    Ring1_Status_set(Ring1_Status_CollectionEmpty);
    return Ring1_Result_Failure;
  }
  // The index must be non-negative.
  if (Ring1_Unlikely(index < 0)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  // The index must be non-negative and smaller than the size of the queue.
  if (Ring1_Unlikely(index >= pimpl->size)) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  // Remember the element.
  void* pointer = pimpl->elements[index];
  // If any other element than the last element is removed, shift the subsequent elements down.
  if (index + 1 < pimpl->size) {
    Ring1_Memory_copyArraySlow(pimpl->elements + index + 0, pimpl->elements + index + 1, (size_t)(pimpl->size - index - 1), sizeof(void*));
  }

  pimpl->size--;

  if (element) {
    *element = pointer;
  }

  if (invokeRemovedCallback && pimpl->removed) {
    (*pimpl->removed)(&pointer);
  }

  return Ring1_Result_Success;
}

static inline Ring1_NoDiscardReturn() Ring1_Result
removeBack
  (
    Impl* pimpl,
    bool invokeRemovedCallback,
    void** element
  )
{
  // The pointer to the dequeue must not be a null pointer and the index must be non-negative.
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // If the queue must not be empty.
  if (pimpl->size == 0) {
    Ring1_Status_set(Ring1_Status_CollectionEmpty);
    return Ring1_Result_Failure;
  }
  // Remember the element.
  void* pointer = pimpl->elements[pimpl->size - 1];

  pimpl->size--;

  if (element) {
    *element = pointer;
  }

  if (invokeRemovedCallback && pimpl->removed) {
    (*pimpl->removed)(&pointer);
  }

  return Ring1_Status_Success;
}


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_initialize
  (
    Ring1_PointerList* pointerList,
    Ring1_AddedCallback *added,
    Ring1_RemovedCallback *removed
  )
{
  Impl* pimpl = NULL;
  if (Ring1_Memory_allocate(&pimpl, sizeof(Impl))) {
    return Ring1_Result_Failure;
  }
  if (initialize(pimpl, added, removed)) {
    Ring1_Memory_deallocate(pimpl);
    return Ring1_Result_Failure;
  }
  pointerList->pimpl = pimpl;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_uninitialize
  (
    Ring1_PointerList* pointerList
  )
{
  Impl *pimpl = pointerList->pimpl;
  clear(pimpl);
  Ring1_Memory_deallocate(pimpl->elements);
  pimpl->elements = NULL;
  Ring1_Memory_deallocate(pimpl);
  pointerList->pimpl = NULL;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_find
  (
    Ring1_PointerList* pointerList,
    int64_t start,
    void *context,
    Ring1_PointerList_FindCallback* predicate,
    int64_t* found
  )
{ return find(pointerList->pimpl, start, context, predicate, found); }

void
Ring1_PointerList_visit
  (
    Ring1_PointerList* pointerList,
    void* context,
    Ring1_PointerList_VisitCallback *function
  )
{
  Impl* pimpl = pointerList->pimpl;
  for (int64_t i = 0, n = pimpl->size; i < n; ++i) {
    void* element = pimpl->elements[i];
    (*function)(context, element);
  }
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_filter
  (
    Ring1_PointerList* pointerList,
    Ring1_WhereContext* whereContext,
    Ring1_WhereCallback* whereCallback
  )
{
  Impl* pimpl = pointerList->pimpl;
  void** temporary = NULL;
  if (Ring1_Memory_allocateArray((void **)&temporary, (size_t)pimpl->size, sizeof(void*))) {
    return Ring1_Result_Failure;
  }
  size_t i = 0, j = 0, n = (size_t)pimpl->size;
  while (i < n) {
    void* element = pimpl->elements[i];
    bool result;
    if ((*whereCallback)(&result, whereContext, i, element))
    { return Ring1_Result_Failure; }
    if (result) {
      temporary[j++] = element;
    } else {
      if (pimpl->removed) {
        (*pimpl->removed)(&element);
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
Ring1_PointerList_clear
  (
    Ring1_PointerList* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return clear((Impl *)self->pimpl);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_getAt
  (
    Ring1_PointerList* self,
    int64_t index,
    void** element
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return getAt((Impl *)self->pimpl, index, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_getSize
  (
    int64_t *size,
    Ring1_PointerList* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return getSize(size, self->pimpl);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_insertAt
  (
    Ring1_PointerList* pointerList,
    int64_t index,
    void* element
  )
{ return insertAt((Impl *)pointerList->pimpl, index, element); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_insertBack
  (
    Ring1_PointerList* pointerList,
    void* element
  )
{ return insertBack((Impl *)pointerList->pimpl, element); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_insertFront
  (
    Ring1_PointerList* pointerList,
    void* element
  )
{ return insertFront((Impl *)pointerList->pimpl, element ); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_removeAt
  (
    Ring1_PointerList* self,
    int64_t index,
    void** element
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeAt(self->pimpl, index, false, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_stealAt
  (
    Ring1_PointerList* self,
    int64_t index,
    void** element
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeAt(self->pimpl, index, false, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_removeBack
  (
    Ring1_PointerList* self,
    void** element
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeBack(self->pimpl, true, element);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerList_stealBack
  (
    Ring1_PointerList* self,
    void** element
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  return removeBack(self->pimpl, false, element);
}
