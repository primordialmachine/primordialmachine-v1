#include "Ring1/TypeName/_Include.h"

#include "Ring1/Atom/_Include.h"
#include "Ring1/Intrinsic.h"
#include "Ring1/Memory.h"
#include "Ring1/ByteBuffer.h"
#include "Ring1/Collections/_Include.h"
#include "Ring1/TypeName/validate.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// Type flag indicating TypeNameKey object represents the name of an array type.
#define Flags_Array (1)

/// Type flag indicating a TypeNameKey object represents the name of a pointer type.
/// #define Flags_Pointer (2)

/// Masks the category. Currently, the only category is Flags_Array.
#define FlagsMask_Category (Flags_Array)

/// The dimensionality is resides in the bits above the 2 lowest bits.
#define Dimensionality_Shift (3)

/// The greatest dimensionality is UINT8_MAX >> 3.
#define Dimensionality_Greatest (UINT8_MAX >> 3)

typedef struct TypeNameKey {
  /// @brief The name of the innermost underlaying type.
  Ring1_Atom *name;
  /// @brief The flags.
  /// If RING1_TYPE_FLAGS_ARRAY is set,
  /// then the upper bits represent the dimensionality.
  /// If RING1_TYPE_FLAGS_POINTEr is set,
  /// then the upper bits represent the indirections.
  uint8_t flags;
} TypeNameKey;

typedef struct TypeName {
  Ring1_ReferenceCounter referenceCount;
  TypeNameKey key;
} TypeName;

static Ring1_CheckReturn() Ring1_Result
initializeModule
  (
  );

static void
uninitializeModule
  (
  );

static Ring1_CheckReturn() Ring1_Result
hashTypeKey
  (
    int64_t* result,
    TypeNameKey* x
  );

static Ring1_CheckReturn() Ring1_Result
isTypeKeyEqualTo
  (
    bool* result,
    TypeNameKey const* x,
    TypeNameKey const* y
  );

static Ring1_CheckReturn() Ring1_Result
removeEntryIf
  (
    bool* result,
    void* context,
    TypeNameKey* key,
    TypeName* value
  );

/// @brief Callback invoked if a value is removed from the hash map.
static void
valueRemoved
  (
    TypeName** value
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// A read-write lock is sufficient as recursive locking is not possible.
static Ring1_ReadWriteLock g_lock = Ring1_ReadWriteLock_Initializer;

/// @brief The hash map.
static Mkx_PointerHashMap* g_types = NULL;

/// @brief The number of dead type names.
static int64_t g_dead = 0;

/// @brief The number of live type names.
static int64_t g_live = 0;

Ring1_BeginDependencies()
  Ring1_Dependency(Ring1, Memory)
  Ring1_Dependency(Ring1, Atom)
  Ring1_Dependency(Ring1, Collections)
Ring1_EndDependencies()

Ring1_Module_Define(Ring1, TypeName, initializeModule, uninitializeModule)

static Ring1_CheckReturn() Ring1_Result
initializeModule
  (
  )
{
  g_types = NULL;
  //
  if (startupDependencies()) {
    return Ring1_Result_Failure;    
  }
  //
  if (Ring1_Memory_allocate(&g_types, sizeof(Mkx_PointerHashMap))) {
    shutdownDependencies();
    return Ring1_Result_Failure;
  }
  if (Mkx_PointerHashMap_initialize(g_types,
                                    Ring1_PointerHashMap_Capacity_Default,
                                    NULL,
                                    NULL,
                                    &hashTypeKey,
                                    &isTypeKeyEqualTo,
                                    NULL,
                                    &valueRemoved)) {
    Ring1_Memory_deallocate(g_types);
    g_types = NULL;
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
  Mkx_PointerHashMap_uninitialize(g_types);
  Ring1_Memory_deallocate(g_types);
  g_types = NULL;
  shutdownDependencies();
}

static Ring1_CheckReturn() Ring1_Result
hashTypeKey
  (
    int64_t *result,
    TypeNameKey *x
  )
{ 
  int64_t a;
  if (Ring1_Atom_getHashValue(&a, x->name)) {
    return Ring1_Result_Failure;
  }
  uint64_t hv = (Ring1_cast(uint64_t, a) * 256) | x->flags;
  *result = (int64_t)hv;
  return Ring1_Result_Success;
}

static Ring1_CheckReturn() Ring1_Result
isTypeKeyEqualTo
  (
    bool *result,
    TypeNameKey const *x,
    TypeNameKey const *y
  )
{
  *result = x->flags == y->flags
         && x->name == y->name;
  return Ring1_Result_Success;
}

static Ring1_CheckReturn() Ring1_Result
removeEntryIf
  (
    bool *result,
    void *context,
    TypeNameKey* key,
    TypeName* value
  )
{
  *result = 0 == Ring1_ReferenceCounter_get(&value->referenceCount);
  return Ring1_Result_Success;
}

static void
valueRemoved
  (
    TypeName* *value
  )
{
  Ring1_Atom_unreference((*value)->key.name);
  (*value)->key.name = NULL;
  Ring1_Memory_deallocate(*value);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Ring1_TypeName_ref
  (
    Ring1_TypeName* typeName
  )
{
  Ring1_ReferenceCounter_increment(&Ring1_cast(TypeName*, typeName)->referenceCount);
}

void
Ring1_TypeName_unref
  (
    Ring1_TypeName *typeName
  )
{
  // If a reference counter of a type name seems to reach zero,
  // then Ring1_TypeName_unreference needs to acquire a lock to
  // be mutually exclusive with
  // - Ring1_TypeName_getOrCreate and
  // - Ring1_TypeName_getOrCreateScalar
  // and re-evaluate the reference count.
  //
  // Reason is:
  // Assume Thread 1 decrements the reference count of an atom to 0.
  // Thread 2 increments the reference count of that atom to 1 again.
  if (!Ring1_ReferenceCounter_decrement(&Ring1_cast(TypeName *, typeName)->referenceCount)) {
    Ring1_TypeName_Module_lock(); // LOCK THE MODULE.
    if (!Ring1_ReferenceCounter_get(&Ring1_cast(TypeName *, typeName)->referenceCount)) {// Imposes a full memory barrier.
      // Update the dead/live counters.
      g_live--;
      g_dead++;
      // Should we remove dead atoms?
      // We remove dead atoms if there are more than 8 atoms
      // and if there is a certain ratio of dead and live atoms
      // exceeded.
      if (g_dead / 2 > g_live && g_dead + g_live > 8) {
        // Remove dead atoms.
        Mkx_PointerHashMap_removeIf(g_types, NULL, &removeEntryIf);
      }
    }
    Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
  }
}

Ring1_CheckReturn() Ring1_Result
Ring1_TypeName_getOrCreateArray
  (
    Ring1_TypeName** result,
    int64_t dimensionality,
    Ring1_TypeName* underlaying
  )
{
  if (dimensionality < 0 || dimensionality > UINT8_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure; 
  }
  TypeNameKey typeNameKey = { 0 };
  typeNameKey.name = Ring1_cast(TypeName *, underlaying)->key.name;
  typeNameKey.flags = Flags_Array;
  // Do we have an array type here?
  if ((Ring1_cast(TypeName*, underlaying)->key.flags & Flags_Array) == Flags_Array) {
    // Get its dimensionality.
    uint8_t oldDimensionality = Ring1_cast(TypeName*, underlaying)->key.flags >> Dimensionality_Shift;
    // Add the dimensionality. However, check for overflow first.
    if (Dimensionality_Greatest - oldDimensionality < dimensionality) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      return Ring1_Result_Failure;
    }
    uint8_t newDimensionality = oldDimensionality + dimensionality;
    typeNameKey.flags |= newDimensionality << Dimensionality_Shift;
  } else {
    // Add the dimensionality. However, check for overflow first.
    if (Dimensionality_Greatest < dimensionality) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
      return Ring1_Result_Failure;
    }
    typeNameKey.flags |= dimensionality << Dimensionality_Shift;
  }
  TypeName* typeName;
  Ring1_TypeName_Module_lock(); // LOCK THE MODULE.
  if (Mkx_PointerHashMap_get(g_types, &typeNameKey, &typeName)) {
    if (Ring1_Status_get() != Ring1_Status_NotExists) {
      Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
      return Ring1_Result_Failure;
    }
    Ring1_Status_set(Ring1_Status_Success);
    if (Ring1_Memory_allocate(&typeName, sizeof(TypeName))) {
      Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
      return Ring1_Result_Failure;
    }
    typeName->referenceCount = 1;
    typeName->key = typeNameKey;
    if (Mkx_PointerHashMap_set(g_types, &typeName->key, typeName)) {
      Ring1_Memory_deallocate(typeName);
      typeName = NULL;
      Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
      return Ring1_Result_Failure;
    }
    Ring1_Atom_reference(typeName->key.name);
    g_live++;
  } else {
    Ring1_ReferenceCounter_increment(&typeName->referenceCount);
    // If the atom was resurrected, update the dead/live counters.
    if (1 == Ring1_ReferenceCounter_get(&typeName->referenceCount)) {
      g_dead--;
      g_live++;
    }
  }
  *result = Ring1_cast(Ring1_TypeName *, typeName);
  Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_TypeName_getOrCreateScalar
  (
    Ring1_TypeName** result,
    const char* name
  )
{
  if (isScalarTypeName(name)) {
    return Ring1_Result_Failure;
  }
  Ring1_Atom* nameAtom;
  if (Ring1_Atom_getOrCreate(&nameAtom, name, crt_strlen(name))) {
    return Ring1_Result_Failure;
  }
  TypeNameKey typeNameKey = { 0 };
  typeNameKey.name = nameAtom;
  typeNameKey.flags = 0;

  TypeName* typeName;
  Ring1_TypeName_Module_lock(); // LOCK THE MODULE.
  if (Mkx_PointerHashMap_get(g_types, &typeNameKey, &typeName)) {
    if (Ring1_Status_get() != Ring1_Status_NotExists) {
      Ring1_Atom_unreference(nameAtom);
      Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
      return Ring1_Result_Failure;
    }
    Ring1_Status_set(Ring1_Status_Success);
    if (Ring1_Memory_allocate(&typeName, sizeof(TypeName))) {
      Ring1_Atom_unreference(nameAtom);
      Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
      return Ring1_Result_Failure;
    }
    typeName->referenceCount = 1;
    typeName->key = typeNameKey;
    if (Mkx_PointerHashMap_set(g_types, &typeName->key, typeName)) {
      Ring1_Memory_deallocate(typeName);
      typeName = NULL;
      Ring1_Atom_unreference(nameAtom);
      Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
      return Ring1_Result_Failure;
    }
    g_live++;
  } else {
    Ring1_ReferenceCounter_increment(&typeName->referenceCount);
    // If the atom was resurrected, update the dead/live counters.
    if (1 == Ring1_ReferenceCounter_get(&typeName->referenceCount)) {
      g_dead--;
      g_live++;
    }
    Ring1_Atom_unreference(nameAtom);
  } 
  *result = Ring1_cast(Ring1_TypeName *, typeName);
  Ring1_TypeName_Module_unlock(); // UNLOCK THE MODULE.
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_TypeName_toString
  (
    char **result,
    Ring1_TypeName *typeName
  )
{
  if (Flags_Array == (Ring1_cast(TypeName *, typeName)->key.flags & FlagsMask_Category)) {
    int64_t dimensionality = Ring1_cast(TypeName *, typeName)->key.flags >> Dimensionality_Shift;
    int64_t l = 0;
    if (Ring1_Intrinsic_multiply_s64(&l, dimensionality, 2)) {
      return Ring1_Result_Failure;
    }
    int64_t numberOfNameBytes;
    if (Ring1_Atom_getNumberOfBytes(&numberOfNameBytes, Ring1_cast(TypeName *, typeName)->key.name)) {
      return Ring1_Result_Failure;
    }
    if (Ring1_Intrinsic_add_s64(&l, l, numberOfNameBytes)) {
      return Ring1_Result_Failure;
    }
    if (Ring1_Intrinsic_add_s64(&l, l, 1)) {
      return Ring1_Result_Failure;
    }

    char* buffer;
    if (Ring1_Memory_allocate(&buffer, l)) {
      return Ring1_Result_Failure;
    }
    int64_t bufferIndex = 0;
    for (int64_t j = 0; j < dimensionality; ++j) {
      buffer[bufferIndex++] = '[';
    }
    char* nameBytes;
    if (Ring1_Atom_getBytes(&nameBytes, Ring1_cast(TypeName*, typeName)->key.name)) {
      Ring1_Memory_deallocate(buffer);
      return Ring1_Result_Failure;
    }
    crt_memcpy(&(buffer[bufferIndex]), nameBytes, numberOfNameBytes);
    bufferIndex += numberOfNameBytes;
    for (int64_t j = 0; j < dimensionality; ++j) {
      buffer[bufferIndex++] = ']';
    }
    buffer[bufferIndex++] = '\0';
    // Return the buffer.
    *result = buffer;
    return Ring1_Result_Success;
  } else {
    // Get the length - in Bytes - of the name text.
    int64_t n;
    if (Ring1_Atom_getNumberOfBytes(&n, Ring1_cast(TypeName*, typeName)->key.name)) {
      return Ring1_Result_Failure;
    }
    // Allocate a buffer.
    char* buffer;
    if (Ring1_Memory_allocate(&buffer, n + 1)) {
      return Ring1_Result_Failure;
    }
    // Write the name text into the buffer.
    char* p;
    if (Ring1_Atom_getBytes(&p, Ring1_cast(TypeName*, typeName)->key.name)) {
      Ring1_Memory_deallocate(buffer);
      buffer = NULL;
      return Ring1_Result_Failure;
    }
    crt_memcpy(&(buffer[0]), p, n);
    buffer[n] = '\0';
    // Return the buffer.
    *result = buffer;
    return Ring1_Result_Success;
  }
}
