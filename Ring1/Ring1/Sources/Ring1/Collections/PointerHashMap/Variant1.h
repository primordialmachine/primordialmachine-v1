#if !defined(RING1_COLLECTIONS_POINTERHASHMAP_VARIANT1_H_INCLUDED)
#define RING1_COLLECTIONS_POINTERHASHMAP_VARIANT1_H_INCLUDED

#include "Ring1/Collections/PointerHashMap.h"
#include "Ring1/Memory/_Include.h"

typedef struct Node Node;

typedef Node* Bucket;

typedef struct Impl Impl;
typedef struct IteratorImpl IteratorImpl;

struct Node {
  Node* next;
  int64_t hashValue;
  void* key;
  void* value;
}; // struct Node

struct Impl {
  /// @brief A pointer to an array of @a capacity @a (void *) elements.
  Bucket *buckets;
  /// @brief The capacity of this hash map, in elements, of the array pointed to by @a buckets.
  int64_t capacity;
  /// @brief The size of this hash map i.e. the number of sum of the sizes of the overflow lists.
  int64_t size;
  /// @brief A pointer to an "added" callback function or a null pointer.
  Ring1_AddedCallback *keyAdded;
  /// @brief A pointer to a "removed" callback function or a null pointer.
  Ring1_RemovedCallback *keyRemoved;
  /// @brief A pointer to a "hash" callback function or a null pointer.
  Ring1_GetHashCallback* hashKey;
  /// @brief A pointer to an "equal" callback function or a null pointer.
  Ring1_IsEqualToCallback* areKeysEqual;
  /// @brief A pointer to a "value added" callback function or a null pointer.
  Ring1_AddedCallback* valueAdded;
  /// @brief A pointer to a "value removed" callback function or a null pointer.
  Ring1_RemovedCallback* valueRemoved;
}; // struct Impl

struct IteratorImpl {
  Impl* source;
  /// The bucket index.
  int64_t index;
  /// The position in the overflow list.
  Node** previous;
  Node* current;
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @return
/// #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success
/// A pointer to an array of @a capacity <code>Node *</code> elements was assigned to <code>*buckets*</code>.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
allocateBuckets
  (
    Bucket **buckets,
    int64_t capacity
  )
{
  if (Ring1_Unlikely(!buckets)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(capacity < 0)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(capacity > SIZE_MAX)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  Bucket* buckets0 = NULL;
  if (Ring1_Unlikely(Ring1_Memory_allocateArray((void**)&buckets0, (size_t)capacity, sizeof(Bucket)))) {
    return Ring1_Result_Failure;
  }
  for (int64_t i = 0, n = capacity; i < n; ++i) {
    buckets0[i] = NULL;
  }
  *buckets = buckets0;
  return Ring1_Result_Success;
}

Ring1_Inline() void
deallocateBuckets
  (
    Bucket* buckets
  )
{
  Ring1_Memory_deallocate(buckets);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Change the capacity of a hash map implementation if required.
/// @param pimpl A pointer to the implementation.
/// @return #Ring1_Resullt_Success on success. #Ring1_Result_Failure on failure.
/// @remark
/// If the hash map is 75% filled and its capacity is below the maximum capacity, we try to increase the capacity.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
maybeResize
  (
    Impl *pimpl
  )
{
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (pimpl->capacity < Ring1_PointerHashMap_Capacity_Greatest &&
      (double)pimpl->capacity < (double)pimpl->capacity * 0.75) {
    Bucket *oldBuckets, *newBuckets;
    int64_t oldCapacity, newCapacity;
    // Compute the new length of the buckets array.
    oldCapacity = pimpl->capacity;
    if (Ring1_Unlikely(Ring1_Memory_recomputeSize_s64(Ring1_PointerHashMap_Capacity_Least,
                                                      Ring1_PointerHashMap_Capacity_Greatest,
                                                      oldCapacity, 1, &newCapacity, true))) {
      return Ring1_Result_Failure;
    }
    // Allocate the new buckets array.
    oldBuckets = pimpl->buckets;
    if (allocateBuckets(&newBuckets, newCapacity)) {
      return Ring1_Result_Failure;
    }
    // Move the nodes from the old buckets array to the new buckets array.
    for (int64_t i = 0, n = oldCapacity; i < n; ++i) {
      Bucket* bucket = &(oldBuckets[i]);
      while (*bucket) {
        Node* node = *bucket; (*bucket) = node->next;
        int64_t newHashIndex = node->hashValue % newCapacity;
        newBuckets[newHashIndex] = node;
        node->next = newBuckets[newHashIndex];
      }
    }
    deallocateBuckets(oldBuckets);
    pimpl->capacity = newCapacity;
    pimpl->buckets = newBuckets;

  }
  return Ring1_Result_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Iterator_hasValue
  (
    bool *result,
    IteratorImpl* pimpl
  )
{
  *result = NULL != pimpl->current;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Iterator_getValue
  (
    IteratorImpl *pimpl,
    void **key,
    void **value
  )
{
  if (Ring1_Unlikely(!pimpl || !key || !value)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  bool hasValue;
  if (Ring1_Unlikely(Iterator_hasValue(&hasValue, pimpl))) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(!hasValue)) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  *key = pimpl->current->key;
  *value = pimpl->current->value;
  return Ring1_Result_Success;
}

/// Utiliy function.
/// - If current is null, then advance to the next non-empty bucket.
/// - If there is no such bucket, index will be equal the number of buckets.
Ring1_Inline() void
Iterator_revalidate
  (
    IteratorImpl* pimpl
  )
{
  if (NULL == pimpl->current) {
    while (pimpl->index < pimpl->source->capacity && NULL == pimpl->current) {
      // ... increment the index (unless the index is equal to capacity) ...
      pimpl->index = (pimpl->index + 1) % (pimpl->source->capacity + 1);
      // ... and if the index refers to a bucket point current to that bucket.
      if (pimpl->index < pimpl->source->capacity) {
        pimpl->previous = &(pimpl->source->buckets[pimpl->index]);
        pimpl->current = pimpl->source->buckets[pimpl->index];
      }
    }
  }
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Iterator_increment
  (
    IteratorImpl* pimpl
  )
{
  // If the end of the singly-linked list is not reached, advance.
  if (NULL != pimpl->current) {
    pimpl->previous = &pimpl->current->next;
    pimpl->current = pimpl->current->next;
  }
  Iterator_revalidate(pimpl);
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Iterator_remove
  (
    IteratorImpl* pimpl
  )
{
  Node* node = pimpl->current;
  *pimpl->previous = pimpl->current->next; // Unlink the current node.
  pimpl->current = pimpl->current->next;
  pimpl->source->size -= 1;
  Iterator_revalidate(pimpl);
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Iterator_initialize
  (
    IteratorImpl* iterator,
    Impl* target
  )
{
  iterator->source = target;

  iterator->index = 0;
  iterator->previous = &target->buckets[0];
  iterator->current = target->buckets[0];
  
  Iterator_revalidate(iterator);
  return Ring1_Result_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

// Auxiliary data structure for looking up a node.
typedef struct Lookup {
  int64_t hashValue;
  int64_t hashIndex;
  void* key;
} Lookup;

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
computeLookup
  (
    Lookup *result,
    Impl* pimpl,
    void* key
  )
{
  if (Ring1_Unlikely(!result || !pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  int64_t hashValue;
  if (Ring1_Unlikely(pimpl->hashKey(&hashValue, key))) {
    return Ring1_Result_Failure;
  }
  result->key = key;
  result->hashValue = hashValue & 0x7FFFFFFFFFFFFFFF; // We set the sign bit to 0 to ensure the hash value is positive.
  result->hashIndex = result->hashValue % pimpl->capacity;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
add
  (
    Impl *pimpl,
    void *key,
    void *value,
    bool add,
    bool invokeKeyAdded,
    bool invokeKeyRemoved,
    bool invokeValueAdded,
    bool invokeValueRemoved
  )
{
  // The pointer to the hash map must not be a null pointer.
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // Compute the hash value and the hash index.
  Lookup lookup;
  if (Ring1_Unlikely(computeLookup(&lookup, pimpl, key))) {
    return Ring1_Result_Failure;
  }

  // Search for an equivalent entry.
  for (Node* node = pimpl->buckets[lookup.hashIndex]; NULL != node; node = node->next) {
    if ((node->key == lookup.key) || (node->hashValue == lookup.hashValue)) {
      bool areKeysEqual;
      if (Ring1_Unlikely(pimpl->areKeysEqual(&areKeysEqual, node->key, lookup.key))) {
        return Ring1_Result_Failure;
      }
      if (areKeysEqual) {
        if (add) {
          Ring1_Status_set(Ring1_Status_AlreadyExists);
          return Ring1_Result_Failure;
        } else {
          if (node->key != lookup.key) {
            if (invokeKeyAdded && pimpl->keyAdded) pimpl->keyAdded(&lookup.key);
            if (invokeKeyRemoved && pimpl->keyRemoved) pimpl->keyRemoved(&node->key);
          }
          if (node->value != value) {
            if (invokeValueAdded && pimpl->valueAdded) pimpl->valueAdded(&value);
            if (invokeValueRemoved && pimpl->valueRemoved) pimpl->valueRemoved(&node->value);
          }
          node->key = lookup.key;
          node->value = value;
          return Ring1_Result_Success;
        }
      }
    }
  }

  Node* node;
  if (Ring1_Memory_allocate(&node, sizeof(Node))) {
    return Ring1_Result_Failure;
  }
  node->key = key;
  node->value = value;
  node->hashValue = lookup.hashValue;
  node->next = pimpl->buckets[lookup.hashIndex];
  pimpl->buckets[lookup.hashIndex] = node;
  pimpl->size++;

  if (invokeKeyAdded && pimpl->keyAdded) {
    (*pimpl->keyAdded)(&lookup.key);
  }
  if (invokeValueAdded && pimpl->valueAdded) {
    (*pimpl->valueAdded)(&value);
  }

  maybeResize(pimpl);

  return Ring1_Result_Success;
}

Ring1_Inline() void
clear
  (
    Impl *pimpl
  )
{
  Ring1_RemovedCallback *keyRemoved = pimpl->keyRemoved;
  Ring1_RemovedCallback* valueRemoved = pimpl->valueRemoved;
  for (int64_t i = 0, n = pimpl->capacity; i < n; ++i) {
    Bucket* bucket = &(pimpl->buckets[i]);
    while (*bucket) {
      // Unlink the head.
      Node* node = *bucket;
      *bucket = node->next;
      // Invoke the key removed and value removed callbacks.
      if (keyRemoved) keyRemoved(&node->key);
      if (valueRemoved) valueRemoved(&node->value);
      // Deallocate the node.
      Ring1_Memory_deallocate(node);
    }
  }
  pimpl->size = 0;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
get
  (
    Impl* pimpl,
    void* key,
    void** value
  )
{
  // The pointer to the deque must not be a null pointer.
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // Compute the hash value and the hash index.
  Lookup lookup;
  if (Ring1_Unlikely(computeLookup(&lookup, pimpl, key))) {
    return Ring1_Result_Failure;
  }
  // Search for an equivalent entry.
  for (Node* node = pimpl->buckets[lookup.hashIndex]; NULL != node; node = node->next) {
    if (node->hashValue == lookup.hashValue) {
      bool areKeysEqual;
      if (Ring1_Unlikely(pimpl->areKeysEqual(&areKeysEqual, node->key, lookup.key))) {
        return Ring1_Result_Failure;
      }
      if (areKeysEqual) {
        *value = node->value;
        return Ring1_Result_Success;
      }
    }
  }
  Ring1_Status_set(Ring1_Status_NotExists);
  return Ring1_Result_Failure;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
getCapacity
  (
    int64_t *result,
    Impl* pimpl
  )
{
  *result = pimpl->capacity;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
getFreeCapacity
  (
    int64_t *result,
    Impl* pimpl
  )
{
  *result = pimpl->capacity - pimpl->size;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
getSize
  (
    int64_t *result,
    Impl* pimpl
  )
{
  *result = pimpl->size;
  return Ring1_Result_Success;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
remove
  (
    Impl* pimpl,
    void* key,
    bool invokeKeyRemoved,
    bool invokeValueRemoved
  )
{
  // The pointer to the deque must not be a null pointer.
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // Compute the hash value and the hash index.
  Lookup lookup;
  if (Ring1_Unlikely(computeLookup(&lookup, pimpl, key))) {
    return Ring1_Result_Failure;
  }
  // Search for an equivalent entry.
  Node **previous = &pimpl->buckets[lookup.hashIndex],
        *current = pimpl->buckets[lookup.hashIndex];
  while (NULL != current) {
    if ((current->key == lookup.key) || (current->hashValue == lookup.hashValue)) {
      bool areKeysEqual;
      if (Ring1_Unlikely(pimpl->areKeysEqual(&areKeysEqual, current->key, lookup.key))) {
        return Ring1_Result_Failure;
      }
      if (areKeysEqual) {
        if (invokeKeyRemoved && pimpl->keyRemoved) {
          pimpl->keyRemoved(&current->key);
        }
        if (invokeValueRemoved && pimpl->valueRemoved) {
          pimpl->valueRemoved(&current->value);
        }
        *previous = current->next;
        pimpl->size--;
        Ring1_Memory_deallocate(current);
        return Ring1_Result_Success;
      }
    }
  }
  Ring1_Status_set(Ring1_Status_NotExists);
  return Ring1_Result_Failure;
}

Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
initialize
  (
    Impl* pimpl,
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
  if (Ring1_Unlikely(!pimpl)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // Validate arguments: Bound the capacity.
  if (Ring1_Unlikely(initialCapacity > Ring1_PointerHashMap_Capacity_Greatest)) {
    initialCapacity = Ring1_PointerHashMap_Capacity_Greatest;
  }
  if (Ring1_Unlikely(initialCapacity < Ring1_PointerHashMap_Capacity_Least)) {
    initialCapacity = Ring1_PointerHashMap_Capacity_Least;
  }

  // Validate arguments.
  if (Ring1_Unlikely(!hashKey || !areKeysEqual)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }

  // Allocate buckets.
  if (Ring1_Unlikely(allocateBuckets(&pimpl->buckets, initialCapacity))) {
    return Ring1_Result_Failure;
  }

  // Store size and capacity.
  pimpl->size = 0;
  pimpl->capacity = initialCapacity;

  // Store callbacks.
  pimpl->keyAdded = keyAdded;
  pimpl->keyRemoved = keyRemoved;
  pimpl->hashKey = hashKey;
  pimpl->areKeysEqual = areKeysEqual;
  pimpl->valueAdded = valueAdded;
  pimpl->valueRemoved = valueRemoved;
 
  return Ring1_Result_Success;
}

Ring1_Inline() void
uninitialize
  (
    Impl* pimpl
  )
{
  clear(pimpl);
  deallocateBuckets(pimpl->buckets);
  pimpl->buckets = NULL;
  pimpl->capacity = 0;
}

#endif // RING1_COLLECTIONS_POINTERHASHMAP_VARIANT1_H_INCLUDED
