// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Atom/_Include.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Atom/_Include.h"


#include "Ring1/Memory/_Include.h"
#include "Ring1/Collections/_Include.h"
#include "Ring1/ReferenceCounter.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief A key of the atom hash map.
#define KEY(pointer) ((Key *)(pointer))
typedef struct Key Key;

/// @brief A value of the atom hash map.
#define VALUE(pointer) ((Value *)(pointer))
typedef struct Value Value;

/// @brief Callback invoked if a value is removed from the hash map.
static void
valueRemoved
  (
    Value** value
  );

/// @brief Callback invoked to determine if an entry is removed from the hash map.
static int
removeEntryIf
  (
    bool *result,
    void *context,
    Key *key,
    Value *value
  );

/// @brief Computes the hash value of an array of Bytes.
/// @param result A pointer to a <code>int64_t</code> variable.
/// @param bytes A pointer to an array of Bytes.
/// @param numberOfBytes The number of Bytes in the array.
/// @return #Ring1_Result_Success on success. #Ring1_Result_Failure on failure.
/// @success <code>*result</code> was assigned the hash value.
/// That hash value is guaranteed to be non-negative.
static inline Ring1_Result
computeHashValue
  (
    int64_t *result,
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

struct Key {
  int64_t hashValue;
  size_t numberOfBytes;
  char* bytes;
};

struct Value {
  Ring1_ReferenceCounter referenceCount;
  Key key;
};

static Ring1_Result
Key_getHashValue
  (
    int64_t *result,
    Key *x
  )
{ 
  *result = x->hashValue;
  return Ring1_Result_Success;
}

static Ring1_Result
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
    return Ring1_Result_Success;
  } else {
    int temporary2;
    Ring1_Memory_compare(&temporary2, x->bytes, x->numberOfBytes, y->bytes, y->numberOfBytes, Ring1_Memory_Compare_Lexicographic);
    *result = !temporary2;
    return Ring1_Result_Success;
  }
}

static void
valueRemoved
  (
    Value** value
  )
{
  Ring1_Memory_deallocate((*value)->key.bytes);
  (*value)->key.bytes = NULL;
  Ring1_Memory_deallocate(*value);
}

static Ring1_Result
removeEntryIf
  (
    bool *result,
    void *context,
    Key* key,
    Value* value
  )
{
  *result = 0 == Ring1_ReferenceCounter_get(&value->referenceCount);
  return Ring1_Result_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// A read-write lock is sufficient as recursive locking is not possible.
static Ring1_ReadWriteLock g_lock = Ring1_ReadWriteLock_Initializer;

/// @brief The hash map.
static Ring1_PointerHashMap* g_hashMap = NULL;

/// @brief The number of dead atoms.
static int64_t g_dead = 0;

/// @brief The number of live atoms.
static int64_t g_live = 0;

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Memory)
  Ring1_Dependency(Ring1, Collections)
Ring1_EndDependencies()

Ring1_Module_Define(Ring1, Atom, initializeModule, uninitializeModule)

static Ring1_Result
initializeModule
  (
  )
{
  g_hashMap = NULL;
  //
  if (startupDependencies()) {
    return Ring1_Result_Failure;    
  }
  //
  if (Ring1_Memory_allocate(&g_hashMap, sizeof(Ring1_PointerHashMap))) {
    shutdownDependencies();
    return Ring1_Result_Failure;
  }
  if (Ring1_Unlikely(Ring1_PointerHashMap_initialize(g_hashMap, Ring1_PointerHashMap_Capacity_Default, NULL, NULL, &Key_getHashValue, &Key_equalTo, NULL, (Ring1_RemovedCallback *)&valueRemoved))) {
    Ring1_Memory_deallocate(g_hashMap);
    g_hashMap = NULL;
    shutdownDependencies();
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
uninitializeModule
  (
  )
{
  Ring1_PointerHashMap_uninitialize(g_hashMap);
  Ring1_Memory_deallocate(g_hashMap);
  g_hashMap = NULL;
  shutdownDependencies();
}

static inline Ring1_Result
computeHashValue
  (
    int64_t *result,
    const char* bytes,
    size_t numberOfBytes
  )
{
  int64_t hashValue = (size_t)numberOfBytes;
  for (size_t i = 0, n = numberOfBytes; i < n; ++i) {
    hashValue |= ((hashValue << 5) | (hashValue >> 3)) ^ bytes[i];
  }
  *result = hashValue & 0x7FFFFFFFFFFFFFFF;
  return Ring1_Result_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getOrCreate
  (
    Ring1_Atom **result,
    const char* bytes,
    size_t numberOfBytes
  )
{
  if (Ring1_Unlikely(!result || !bytes)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // Compute the hash value.
  int64_t hashValue;
  if (computeHashValue(&hashValue, bytes, numberOfBytes)) {
    return Ring1_Result_Failure;
  }
  // Check if an atom for these Bytes already exists.
  Key key = { .bytes = (char*)bytes, .numberOfBytes = numberOfBytes, .hashValue = hashValue };
  Value* value;
  Ring1_Atom_Module_lock(); // LOCK THE MODULE.
  if (!Ring1_PointerHashMap_get(g_hashMap, &key, &value)) {
    // Atom exists. Increment its reference count and return it.
    Ring1_ReferenceCounter_increment(&value->referenceCount);
    // If the atom was resurrected, update the dead/live counters.
    if (1 == Ring1_ReferenceCounter_get(&value->referenceCount)) {
      g_dead--;
      g_live++;
    }
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    *result = (Ring1_Atom *)value;
    return Ring1_Result_Success;
  }
  if (Ring1_Status_get() != Ring1_Status_NotExists) {
    // An error occurred. Fail.
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    return Ring1_Result_Failure;
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
  if (Ring1_PointerHashMap_add(g_hashMap, &value->key, value)) {
    Ring1_Memory_deallocate(value->key.bytes);
    Ring1_Memory_deallocate(value);
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
    return Ring1_Result_Failure;
  }
  // Return the atom.
  Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
  *result = (Ring1_Atom *)value;
  return Ring1_Result_Success;
}

void
Ring1_Atom_reference
  (
    Ring1_Atom* atom
  )
{ Ring1_ReferenceCounter_increment(&VALUE(atom)->referenceCount); }

void
Ring1_Atom_unreference
  (
    Ring1_Atom* atom
  )
{
  // If a reference counter of an atom seems to reach zero,
  // then Ring1_Atom_unreference needs to acquire a lock to
  // be mutually exclusive with Ring1_Atom_getOrCreate and
  // re-evaluate the reference count.
  //
  // Reason is:
  // Assume Thread 1 decrements the reference count of an atom to 0.
  // Thread 2 increments the reference count of that atom to 1 again.
  if (!Ring1_ReferenceCounter_decrement(&VALUE(atom)->referenceCount)) {
    Ring1_Atom_Module_lock(); // LOCK THE MODULE.
    if (!Ring1_ReferenceCounter_get(&VALUE(atom)->referenceCount)) {// Imposes a full memory barrier.
      // Update the dead/live counters.
      g_live--;
      g_dead++;
      // Should we remove dead atoms?
      // We remove dead atoms if there are more than 8 atoms
      // and if there is a certain ratio of dead and live atoms
      // exceeded.
      if (g_dead / 2 > g_live && g_dead + g_live > 8) {
        // Remove dead atoms.
        Ring1_PointerHashMap_removeIf(g_hashMap, NULL, &removeEntryIf);
      }
    }
    Ring1_Atom_Module_unlock(); // UNLOCK THE MODULE.
  }
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getBytes
  (
    const char **result,
    Ring1_Atom* atom
  )
{
  if (Ring1_Unlikely(!result || !atom)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = VALUE(atom)->key.bytes;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getNumberOfBytes
  (
    int64_t *result,
    Ring1_Atom* atom
  )
{
  if (Ring1_Unlikely(!result || !atom)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = VALUE(atom)->key.numberOfBytes;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Atom_getHashValue
  (
    int64_t* result,
    Ring1_Atom* atom
  )
{
  if (Ring1_Unlikely(!result || !atom)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = VALUE(atom)->key.hashValue;
  return Ring1_Result_Success;
}
