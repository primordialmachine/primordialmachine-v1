// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerHashMap.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Collections/PointerHashMap.h"


#include "Ring1/Memory.h"
#include "Ring1/Collections/PointerHashMap/Variant1.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_Module_Define(PointerHashMap, initializeModule, uninitializeModule)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Handles
{
  Ring1_Memory_ModuleHandle memory;
} Handles;

static Handles g_handles = { .memory = Ring1_Memory_ModuleHandle_Invalid };

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Ring1_Result
initializeModule
  (
  )
{
  g_handles.memory = Ring1_Memory_ModuleHandle_acquire();
  if (!g_handles.memory) return Ring1_Result_Failure;
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_initialize
  (
    Mkx_PointerHashMap *hashMap,
    int64_t initialCapacity,
    Mkx_Collection_AddedCallback* keyAdded,
    Mkx_Collection_RemovedCallback* keyRemoved,
    Mkx_Collection_HashCallback* hashKey,
    Mkx_Collection_EqualCallback* areKeysEqual,
    Mkx_Collection_AddedCallback* valueAdded,
    Mkx_Collection_RemovedCallback* valueRemoved
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
Mkx_PointerHashMap_uninitialize
  (
    Mkx_PointerHashMap *hashMap
  )
{
  uninitialize(hashMap->pimpl);
  Ring1_Memory_deallocate(hashMap->pimpl);
  hashMap->pimpl = NULL;
}

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_getSize
  (
    int64_t *result,
    Mkx_PointerHashMap *hashMap
  )
{ return getSize(result, hashMap->pimpl); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_getCapacity
  (
    int64_t *result,
    Mkx_PointerHashMap *hashMap
  )
{ return getCapacity(result, hashMap->pimpl); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_getFreeCapacity
  (
    int64_t *result,
    Mkx_PointerHashMap* hashMap
  )
{ return getFreeCapacity(result, hashMap->pimpl); }

void
Mkx_PointerHashMap_clear
  (
    Mkx_PointerHashMap *hashMap
  )
{ clear(hashMap->pimpl); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_add
  (
    Mkx_PointerHashMap* hashMap,
    void* key,
    void* value
  )
{ return add(hashMap->pimpl, key, value, true, true, true, true, true); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_set
  (
    Mkx_PointerHashMap* hashMap,
    void* key,
    void* value
  )
{ return add(hashMap->pimpl, key, value, false, true, true, true, true); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_get
  (
    Mkx_PointerHashMap* hashMap,
    void* key,
    void* *value
  )
{ return get(hashMap->pimpl, key, value); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_remove
  (
    Mkx_PointerHashMap *hashMap,
    void *key
  )
{ return remove(hashMap->pimpl, key, true, true); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_removeIf
  (
    Mkx_PointerHashMap* pointerHashMap,
    void* context,
    Mkx_PointerHashMap_RemoveIfCallback* removeIf
  )
{
  Mkx_PointerHashMap_Iterator iterator;
  Mkx_PointerHashMap_Iterator_initialize(&iterator, pointerHashMap);
  bool hasValue;
  if (Mkx_PointerHashMap_Iterator_hasValue(&hasValue, &iterator)) {
    return Ring1_Result_Failure;
  }
  while (hasValue) {
    void *key, *value;
    Mkx_PointerHashMap_Iterator_getValue(&iterator, &key, &value);
    bool result;
    if ((*removeIf)(&result, context, key, value)) {
      Mkx_PointerHashMap_Iterator_uninitialize(&iterator);
      return Ring1_Result_Failure;
    }
    if (result) {
      Mkx_PointerHashMap_Iterator_remove(&iterator);
    } else {
      Mkx_PointerHashMap_Iterator_increment(&iterator);
    }
    if (Mkx_PointerHashMap_Iterator_hasValue(&hasValue, &iterator)) {
      return Ring1_Result_Failure;
    }
  }
  Mkx_PointerHashMap_Iterator_uninitialize(&iterator);
  return Ring1_Result_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_Iterator_initialize
  (
    Mkx_PointerHashMap_Iterator* iterator,
    Mkx_PointerHashMap* target
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
Mkx_PointerHashMap_Iterator_uninitialize
  (
    Mkx_PointerHashMap_Iterator *iterator
  )
{
  Ring1_Memory_deallocate(iterator->pimpl);
  iterator->pimpl = NULL;
}

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_Iterator_hasValue
  (
    bool *result,
    Mkx_PointerHashMap_Iterator* iterator
  )
{ return Iterator_hasValue(result, iterator->pimpl); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_Iterator_getValue
  (
    Mkx_PointerHashMap_Iterator* iterator,
    void** key,
    void** value
  )
{ return Iterator_getValue(iterator->pimpl, key, value); }

Ring1_CheckReturn() Ring1_Result
Mkx_PointerHashMap_Iterator_increment
  (
    Mkx_PointerHashMap_Iterator* iterator
  )
{ return Iterator_increment(iterator->pimpl); }

Ring1_Result
Mkx_PointerHashMap_Iterator_remove
  (
    Mkx_PointerHashMap_Iterator* iterator
  )
{ return Iterator_remove(iterator->pimpl); }
