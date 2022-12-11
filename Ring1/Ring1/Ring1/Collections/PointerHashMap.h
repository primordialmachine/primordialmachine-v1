// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Collections/PointerHashMap.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_COLLECTIONS_POINTERHASHMAP_H_INCLUDED)
#define RING1_COLLECTIONS_POINTERHASHMAP_H_INCLUDED


#include "Ring1/Collections/Callbacks.h"
#include "Ring1/Module.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_Module_Declare(Ring1, PointerHashMap)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The maximum capacity of a pointer hash map.
#define Ring1_PointerHashMap_Capacity_Greatest ((SIZE_MAX < INT64_MAX ? SIZE_MAX : INT64_MAX) / sizeof(void *))

/// @brief The minimum capacity of a pointer hash map.
/// Must not be @a 0.
#define Ring1_PointerHashMap_Capacity_Least (8)

/// @brief The default capacity of a pointer hash map.
#define Ring1_PointerHashMap_Capacity_Default (8)

/// @brief A hash map of pointers.
/// @remark Implemented using the PIMPL idiom.
/// Supports null pointers.
typedef struct Ring1_PointerHashMap { void *pimpl; } Ring1_PointerHashMap;

/// @brief A forward iterator for a hash map of pointers.
/// @remark Implemented using the PIMPL idiom.
typedef struct Ring1_PointerHashMap_Iterator { void* pimpl; } Ring1_PointerHashMap_Iterator;

/// @brief The type of a callback function invoked during the "REMOVE IF" operation on a map.
/// This callback is invoked for each key/value pair in the map exactly once with the specified opaque context pointer as its 1st argument and the key and the value as the 2nd and 3rd arguments.
/// @param context The opaque context pointer.
/// @param key The key.
/// @param value The value.
/// @return @a true if the key/value pair shall be removed, @a false otherwise.
/// @remark The function must not mutate the list.
typedef int (Ring1_PointerHashMap_RemoveIfCallback)(bool *result, void* context, void *key, void *value);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Initialize a pointer hash map.
/// @param hashMap A pointer to an uninitialized pointer hash map.
/// @param initialCapacity The initial capacity hint.
/// If lower than minimum capacity, the initial capacity is set to the minimum capacity.
/// If greater than maximal capacity, the initial capacity is set to the maximal capacity.
/// @param keyAdded A pointer to an key added callback function or a null pointer.
/// @param keyRemoved A pointer to a key removed callback function or a null pointer.
/// @param hashKey A pointer a hash key callback function.
/// @param areKeysEqual A pointer to the are keys equal function.
/// @param valueAdded A pointer to an value added callback function or a null pointer.
/// @param valueRemoved A pointer to a value removed callback function or a null pointer.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_initialize
  (
    Ring1_PointerHashMap *hashMap,
    int64_t initialCapacity,
    Ring1_AddedCallback *keyAdded,
    Ring1_RemovedCallback *keyRemoved,
    Ring1_GetHashCallback *hashKey,
    Ring1_IsEqualToCallback *areKeysEqual,
    Ring1_AddedCallback *valueAdded,
    Ring1_RemovedCallback *valueRemoved
  );

/// @brief Uninitialize a pointer hash map.
/// @param hashMap A pointer to an initialized pointer hash map.
void
Ring1_PointerHashMap_uninitialize
  (
    Ring1_PointerHashMap *hashMap
  );

// https://primordialmachine.com/api/ring1-library/collections-library/ring1_pointerhashmap_getsize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_getSize
  (
    int64_t *result,
    Ring1_PointerHashMap *hashMap
  );

// https://primordialmachine.com/api/ring1-library/collections-library/ring1_pointerhashmap_getcapacity
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_getCapacity
  (
    int64_t *result,
    Ring1_PointerHashMap *hashMap
  );

// https://primordialmachine.com/api/ring1-library/collections-library/ring1_pointerhashmap_getfreecapacity
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_getFreeCapacity
  (
    int64_t *result,
    Ring1_PointerHashMap* hashMap
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerHashMap_clear
void
Ring1_PointerHashMap_clear
  (
    Ring1_PointerHashMap *hashMap
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerHashMap_add
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_add
  (
    Ring1_PointerHashMap* hashMap,
    void *key,
    void *value
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerHashMap_set
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_set
  (
    Ring1_PointerHashMap* hashMap,
    void* key,
    void* value
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerHashMap_get
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_get
  (
    Ring1_PointerHashMap *hashMap,
    void *key,
    void **value
  );

// https://primordialmachine.com/api/ring1-library/collections-library/Ring1_PointerHashMap_removeIf
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_removeIf
  (
    Ring1_PointerHashMap* pointerHashMap,
    void *context,
    Ring1_PointerHashMap_RemoveIfCallback* removeIf
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// https://primordialmachine.com/api/ring1-library/pointerhashmap-library/ring1_pointerhashmap_iterator_initialize
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_initialize
  (
    Ring1_PointerHashMap_Iterator* iterator,
    Ring1_PointerHashMap *target
  );

// https://primordialmachine.com/api/ring1-library/pointerhashmap-library/ring1_pointerhashmap_iterator_uninitialize
void
Ring1_PointerHashMap_Iterator_uninitialize
  (
    Ring1_PointerHashMap_Iterator *iterator
  );

/// @brief Get if an iterator has a value i.e. has not reached the end of its iteration.
/// @param iterator A pointer to the iterator.
/// @return @a true if the iterator has a value, @a false otherwise
/// @undefined @a iterator does not point to an iterator
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_hasValue
  (
    bool *result,
    Ring1_PointerHashMap_Iterator* iterator
  );

/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @error #Ring1_Status_InvalidOperation the iterator reached the end of its iteration
/// @error #Ring1_Status_InvalidArgument @a iterator, @a key, or @a value is a null pointer.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_getValue
  (
    Ring1_PointerHashMap_Iterator *iterator,
    void **key,
    void **value
  );

/// @brief Increment the iterator if it has not reached the end of its iteration.
/// @param iterator A pointer to the iterator.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_increment
  (
    Ring1_PointerHashMap_Iterator* iterator
  );

/// @brief If the iterator has not reached the end of its iteration, remove the current element.
/// @param iterator A pointer to the iterator.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @error #Ring1_Status_InvalidOperation the iterator reached the end of its iteration
/// @error #Ring1_Status_InvalidArgument @a iterator, @a key, or @a value is a null pointer.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_PointerHashMap_Iterator_remove
  (
    Ring1_PointerHashMap_Iterator *iterator
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // RING1_COLLECTIONS_POINTERHASHMAP_H_INCLUDED
