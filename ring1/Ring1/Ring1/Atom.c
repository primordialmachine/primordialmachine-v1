// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Atom.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Atom.h"


#include "Ring1/Memory.h"
#include "Ring1/Collections/PointerHashMap.h"
#include "Ring1/ReferenceCounter.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A key of the atom hash map.
#define KEY(pointer) ((Key *)(pointer))
typedef struct Key Key;

/// @brief A value of the atom hash map.
#define VALUE(pointer) ((Value *)(pointer))
typedef struct Value Value;

/// @brief Callback invoked if a value is removed from the hash map.
Ring1_NonNull(1) static void
valueRemoved
  (
    Value* value
  );

/// @brief Callback invoked to determine if an entry is removed from the hash map.
Ring1_NonNull(1, 2) static int
removeEntryIf
  (
    bool *result,
    void *context,
    Key *key,
    Value *value
  );

/// @brief Computes the hash value of an array of Bytes.
/// @param bytes A pointer to an array of Bytes.
/// @param numberOfBytes The number of Bytes in the array.
/// @return The hash value, guaranteed to be non-negative.
Ring1_NonNull(1) static inline int64_t
computeHashValue
  (
    const char* bytes,
    size_t numberOfBytes
  );

static Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

struct Key
{
  int64_t hashValue;
  size_t numberOfBytes;
  char* bytes;
};

struct Value
{
  Ring1_ReferenceCounter referenceCount;
  Key key;
};

Ring1_NonNull(1) static int
Key_getHashValue
  (
    int64_t *result,
    Key *x
  )
{ 
  *result = x->hashValue;
  return 0;
}

Ring1_NonNull(1, 2) static int
Key_equalTo
  (
    bool *result,
    Key* x,
    Key* y
  )
{
  bool temporary1 = x->hashValue == y->hashValue
                 && x->numberOfBytes == y->numberOfBytes;
  if (!temporary1) {
    *result = false;
    return 0;
  }
  int temporary2;
  Ring1_Memory_compare(&temporary2, x->bytes, x->numberOfBytes, y->bytes, y->numberOfBytes, Ring1_Memory_Compare_Lexicographic);
  *result = !temporary2;
  return 0;
}

Ring1_NonNull(1) static void
valueRemoved
  (
    Value* value
  )
{
  Ring1_Memory_deallocate(value->key.bytes);
  value->key.bytes = NULL;
  Ring1_Memory_deallocate(value);
}

Ring1_NonNull(1, 2) static int
removeEntryIf
  (
    bool *result,
    void *context,
    Key* key,
    Value* value
  )
{
  *result = 0 == Ring1_ReferenceCounter_get(&value->referenceCount);
  return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// A read-write lock is sufficient as recursive locking is not possible.
static Ring1_ReadWriteLock g_lock = Ring1_ReadWriteLock_Initializer;

/// @brief The hash map.
static Mkx_PointerHashMap* g_hashMap = NULL;

/// @brief The number of dead atoms.
static int64_t g_dead = 0;

/// @brief The number of live atoms.
static int64_t g_live = 0;

typedef struct Handles
{
  Ring1_Memory_ModuleHandle memory;
  Ring1_PointerHashMap_ModuleHandle pointerHashMap;
} Handles;

static Handles g_handles = { .memory = Ring1_Memory_ModuleHandle_Invalid,
                             .pointerHashMap = Ring1_PointerHashMap_ModuleHandle_Invalid };

Ring1_Module_Define(Atom, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{
  g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
  g_handles.pointerHashMap = Ring1_PointerHashMap_ModuleHandle_Invalid;
  g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
  g_hashMap = NULL;
  //
  g_handles.memory = Ring1_Memory_ModuleHandle_acquire();
  if (Ring1_Unlikely(!g_handles.memory)) goto Failure;
  //
  g_handles.pointerHashMap = Ring1_PointerHashMap_ModuleHandle_acquire();
  if (Ring1_Unlikely(!g_handles.pointerHashMap)) goto Failure;
  //
  if (Ring1_Memory_allocate(&g_hashMap, sizeof(Mkx_PointerHashMap))) {
    goto Failure;
  }
  if (Ring1_Unlikely(Mkx_PointerHashMap_initialize(g_hashMap, Mkx_PointerHashMap_Capacity_Default, NULL, NULL, &Key_getHashValue, &Key_equalTo, NULL, (Mkx_Collection_RemovedCallback *)&valueRemoved)))
  {
    Ring1_Memory_deallocate(g_hashMap);
    g_hashMap = NULL;
    goto Failure;
  }
  return Ring1_Result_Success;
Failure:
  if (g_hashMap)
  {
    Mkx_PointerHashMap_uninitialize(g_hashMap);
    Ring1_Memory_deallocate(g_hashMap);
    g_hashMap = NULL;
}
  if (g_handles.pointerHashMap)
  {
    Ring1_PointerHashMap_ModuleHandle_relinquish(g_handles.pointerHashMap);
    g_handles.pointerHashMap = Ring1_PointerHashMap_ModuleHandle_Invalid;
  }
  if (g_handles.memory)
  {
    Ring1_Memory_ModuleHandle_relinquish(g_handles.memory);
    g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
  }
  return Ring1_Result_Failure;
}

static void
uninitializeModule
  (
  )
{
  Mkx_PointerHashMap_uninitialize(g_hashMap);
  Ring1_Memory_deallocate(g_hashMap);
  g_hashMap = NULL;
  Ring1_PointerHashMap_ModuleHandle_relinquish(g_handles.pointerHashMap);
  g_handles.pointerHashMap = Ring1_PointerHashMap_ModuleHandle_Invalid;
  Ring1_Memory_ModuleHandle_relinquish(g_handles.memory);
  g_handles.memory = Ring1_Memory_ModuleHandle_Invalid;
}

Ring1_NonNull(1) static inline int64_t
computeHashValue
  (
    const char* bytes,
    size_t numberOfBytes
  )
{
  int64_t hashValue = (size_t)numberOfBytes;
  for (size_t i = 0, n = numberOfBytes; i < n; ++i)
  {
    hashValue |= ((hashValue << 5) | (hashValue >> 3)) ^ bytes[i];
  }
  return hashValue & 0x7FFFFFFFFFFFFFFF;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_CheckReturn() Ring1_Result
Mkx_Atom_getOrCreate
  (
    Mkx_Atom **result,
    const char* bytes,
    size_t numberOfBytes
  )
{
  if (Ring1_Unlikely(!result || !bytes)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // Compute the hash value.
  int64_t hashValue = computeHashValue(bytes, numberOfBytes);
  // Check if an atom for these Bytes already exists.
  Key key = { .bytes = (char*)bytes, .numberOfBytes = numberOfBytes, .hashValue = hashValue };
  Value* value;
  Ring1_Atom_Module_lock(); // LOCK THE MODULE.
  if (!Mkx_PointerHashMap_get(g_hashMap, &key, &value)) {
    // Atom exists. Increment its reference count and return it.
    Ring1_ReferenceCounter_increment(&value->referenceCount);
    // If the atom was resurrected, update the dead/live counters.
    if (1 == Ring1_ReferenceCounter_get(&value->referenceCount)) {
      g_dead--;
      g_live++;
    }
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    *result = (Mkx_Atom *)value;
    return Ring1_Result_Success;
  }
  if (Ring1_Status_get() != Ring1_Status_NotExists) {
    // An error occurred. Fail.
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    return Ring1_Result_Success;
  }
  Ring1_Status_set(Ring1_Status_Success); // Clear the flag.
  // Atom does not exist. Create the atom with a reference count of 1.
  if (Ring1_Memory_allocate(&value, sizeof(Value))) {
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    return Ring1_Result_Failure;
  }
  value->referenceCount = 1;
  value->key.hashValue = hashValue;
  value->key.numberOfBytes = numberOfBytes;
  value->key.bytes = NULL;
  if (Ring1_Memory_allocateArray(&value->key.bytes, numberOfBytes, sizeof(char))) {
    Ring1_Memory_deallocate(value);
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    return Ring1_Result_Failure;
  }
  Ring1_Memory_copyArrayFast(value->key.bytes, bytes, numberOfBytes, sizeof(char));
  // Add the atom to the hash table.
  if (Mkx_PointerHashMap_add(g_hashMap, &value->key, value)) {
    Ring1_Memory_deallocate(value->key.bytes);
    Ring1_Memory_deallocate(value);
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    return Ring1_Result_Failure;
  }
  // Return the atom.
  Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
  *result = (Mkx_Atom *)value;
  return Ring1_Result_Success;
}

Ring1_NonNull(1) void
Mkx_Atom_reference
  (
    Mkx_Atom* atom
  )
{ Ring1_ReferenceCounter_increment(&VALUE(atom)->referenceCount); }

Ring1_NonNull(1) void
Mkx_Atom_unreference
  (
    Mkx_Atom* atom
  )
{
  // If a reference counter of an atom seems to reach zero,
  // then Mkx_Atom_unreference needs to acquire a lock to
  // be mutually exclusive with Mkx_Atom_getOrCreate and
  // re-evaluate the reference count.
  //
  // Reason is:
  // Assume Thread 1 decrements the reference count of an atom to 0.
  // Thread 2 increments the reference count of that atom to 1 again.
  if (!Ring1_ReferenceCounter_decrement(&VALUE(atom)->referenceCount))
  {
    Ring1_Atom_Module_lock(); // LOCK THE MODULE.
    if (!Ring1_ReferenceCounter_get(&VALUE(atom)->referenceCount)) // Imposes a full memory barrier.
    {
      // Update the dead/live counters.
      g_live--;
      g_dead++;
      // Should we remove dead atoms?
      // We remove dead atoms if there are more than 8 atoms
      // and if there is a certain ratio of dead and live atoms
      // exceeded.
      if (g_dead / 2 > g_live && g_dead + g_live > 8)
      {
        // Remove dead atoms.
        Mkx_PointerHashMap_removeIf(g_hashMap, NULL, &removeEntryIf);
      }
    }
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
  }
}

Ring1_CheckReturn() int
Mkx_Atom_getBytes
  (
    const char **result,
    Mkx_Atom* atom
  )
{
  if (Ring1_Unlikely(!result || !atom))
  { return 1; }
  *result = VALUE(atom)->key.bytes;
  return 0;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Atom_getNumberOfBytes
  (
    int64_t *result,
    Mkx_Atom* atom
  )
{
  if (Ring1_Unlikely(!result || !atom)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = VALUE(atom)->key.numberOfBytes;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Mkx_Atom_getHashValue
  (
    int64_t* result,
    Mkx_Atom* atom
  )
{
  if (Ring1_Unlikely(!result || !atom)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = VALUE(atom)->key.hashValue;
  return Ring1_Result_Success;
}
