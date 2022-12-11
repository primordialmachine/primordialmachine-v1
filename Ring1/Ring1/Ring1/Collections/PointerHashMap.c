// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerHashMap.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING1_COLLECTIONS_PRIVATE (1)
#include "Ring1/Collections/PointerHashMap.h"
#undef RING1_COLLECTIONS_PRIVATE


#include "Ring1/Memory.h"
#include "Ring1/Collections/PointerHashMap/Variant1.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Handles {
  Ring1_Memory_ModuleHandle memory;
} Handles;

static Handles g_handles = { .memory = Ring1_Memory_ModuleHandle_Invalid };

static Ring1_Result
initializeModule
  (
  )
{ 
  g_handles.memory = Ring1_Memory_ModuleHandle_acquire();
  if (!g_handles.memory) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  Ring1_Memory_ModuleHandle_relinquish(g_handles.memory);
  g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
}


Ring1_Module_Define(Ring1, PointerHashMap, initializeModule, uninitializeModule)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_initialize
  (
    Ring1_PointerHashMap *hashMap,
    int64_t initialCapacity,
    Ring1_AddedCallback* keyAdded,
    Ring1_RemovedCallback* keyRemoved,
    Ring1_GetHashCallback* hashKey,
    Ring1_IsEqualToCallback* areKeysEqual,
    Ring1_AddedCallback* valueAdded,
    Ring1_RemovedCallback* valueRemoved
  )
{
  // Validate arguments.
  if (Ring1_Unlikely(!hashMap)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // Allocate implementation.
  Impl* pimpl;
  if (Ring1_Memory_allocate(&pimpl, sizeof(Impl))) {
    return Ring1_Result_Failure;
  }
  if (initialize(pimpl, initialCapacity, keyAdded, keyRemoved, hashKey, areKeysEqual, valueAdded, valueRemoved)) {
    Ring1_Memory_deallocate(pimpl);
    return Ring1_Result_Failure;
  }

  // Assign the implementation.
  hashMap->pimpl = pimpl;
  
  // Return success.
  return Ring1_Result_Success;
}

void
Ring1_PointerHashMap_uninitialize
  (
    Ring1_PointerHashMap *hashMap
  )
{
  uninitialize(hashMap->pimpl);
  Ring1_Memory_deallocate(hashMap->pimpl);
  hashMap->pimpl = NULL;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_getSize
  (
    int64_t *result,
    Ring1_PointerHashMap *hashMap
  )
{ return getSize(result, hashMap->pimpl); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_getCapacity
  (
    int64_t *result,
    Ring1_PointerHashMap *hashMap
  )
{ return getCapacity(result, hashMap->pimpl); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_getFreeCapacity
  (
    int64_t *result,
    Ring1_PointerHashMap* hashMap
  )
{ return getFreeCapacity(result, hashMap->pimpl); }

void
Ring1_PointerHashMap_clear
  (
    Ring1_PointerHashMap *hashMap
  )
{ clear(hashMap->pimpl); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_add
  (
    Ring1_PointerHashMap* hashMap,
    void* key,
    void* value
  )
{ return add(hashMap->pimpl, key, value, true, true, true, true, true); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_set
  (
    Ring1_PointerHashMap* hashMap,
    void* key,
    void* value
  )
{ return add(hashMap->pimpl, key, value, false, true, true, true, true); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_get
  (
    Ring1_PointerHashMap* hashMap,
    void* key,
    void* *value
  )
{ return get(hashMap->pimpl, key, value); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_remove
  (
    Ring1_PointerHashMap *hashMap,
    void *key
  )
{ return remove(hashMap->pimpl, key, true, true); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_removeIf
  (
    Ring1_PointerHashMap* pointerHashMap,
    void* context,
    Ring1_PointerHashMap_RemoveIfCallback* removeIf
  )
{
  Ring1_PointerHashMap_Iterator iterator;
  Ring1_PointerHashMap_Iterator_initialize(&iterator, pointerHashMap);
  bool hasValue;
  if (Ring1_PointerHashMap_Iterator_hasValue(&hasValue, &iterator)) {
    return Ring1_Result_Failure;
  }
  while (hasValue) {
    void *key, *value;
    Ring1_PointerHashMap_Iterator_getValue(&iterator, &key, &value);
    bool result;
    if ((*removeIf)(&result, context, key, value)) {
      Ring1_PointerHashMap_Iterator_uninitialize(&iterator);
      return Ring1_Result_Failure;
    }
    if (result) {
      Ring1_PointerHashMap_Iterator_remove(&iterator);
    } else {
      Ring1_PointerHashMap_Iterator_increment(&iterator);
    }
    if (Ring1_PointerHashMap_Iterator_hasValue(&hasValue, &iterator)) {
      return Ring1_Result_Failure;
    }
  }
  Ring1_PointerHashMap_Iterator_uninitialize(&iterator);
  return Ring1_Result_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_initialize
  (
    Ring1_PointerHashMap_Iterator* iterator,
    Ring1_PointerHashMap* target
  )
{
  IteratorImpl* pimpl;
  if (Ring1_Unlikely(Ring1_Memory_allocate(&pimpl, sizeof(IteratorImpl)))) {
    return Ring1_Result_Failure;
  }
  if (Iterator_initialize(pimpl, target->pimpl)) {
    Ring1_Memory_deallocate(pimpl);
    return Ring1_Result_Failure;
  }
  iterator->pimpl = pimpl;
  return Ring1_Result_Success;
}

void
Ring1_PointerHashMap_Iterator_uninitialize
  (
    Ring1_PointerHashMap_Iterator *iterator
  )
{
  Ring1_Memory_deallocate(iterator->pimpl);
  iterator->pimpl = NULL;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_hasValue
  (
    bool *result,
    Ring1_PointerHashMap_Iterator* iterator
  )
{ return Iterator_hasValue(result, iterator->pimpl); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_getValue
  (
    Ring1_PointerHashMap_Iterator* iterator,
    void** key,
    void** value
  )
{ return Iterator_getValue(iterator->pimpl, key, value); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_increment
  (
    Ring1_PointerHashMap_Iterator* iterator
  )
{ return Iterator_increment(iterator->pimpl); }

Ring1_Result
Ring1_PointerHashMap_Iterator_remove
  (
    Ring1_PointerHashMap_Iterator* iterator
  )
{ return Iterator_remove(iterator->pimpl); }
