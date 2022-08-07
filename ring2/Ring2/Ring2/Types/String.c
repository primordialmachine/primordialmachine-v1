// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/String.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types/String.h"

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

#include "Ring2/Gc.h"
#include "Ring2/JumpTarget.h"
#include "Ring1/Status.h"
#include "Ring1/Memory.h"

static size_t
hashBytesToSz
  (
    char const* p,
    size_t n
  );

struct Ring2_String {
  size_t hashValue;
  size_t numberOfBytes;
  char bytes[];
};

typedef struct Ring2_StringHeap {
  Ring1_Memory_ModuleHandle memoryModuleHandle;
  Ring2_Gc_Tag** buckets;
  int64_t size;
  int64_t capacity;
} Ring2_StringHeap;


/// @brief The minimum length of the bucket array.
#define BucketArray_MinimumLength ((int64_t)1)

/// @brief The maximum length of the bucket array.
#define BucketArray_MaximumLength ((SIZE_MAX < INT64_MAX ? SIZE_MAX : INT64_MAX) / (int64_t)sizeof(Ring2_String*))

static_assert(0 <= BucketArray_MinimumLength,
              "BucketArray_MinimumLength must be greater than or equal to 0");
static_assert(BucketArray_MinimumLength <= BucketArray_MaximumLength,
              "BucketArray_MinimumLength must be smaller than or equal to BucketArray_MaximumLength");

static_assert(BucketArray_MaximumLength <= INT64_MAX,
              "BucketArray_MaximumLength must be smaller than or equal to INT64_MAX");
static_assert(BucketArray_MaximumLength <= SIZE_MAX,
              "BucketArray_MaximumLength must be greater than or equal to SIZE_MAX");

static_assert(Ring2_Gc_MaximumAllocatableSize >= sizeof(Ring2_String),
              "sizeof(Ring2_String) is greater than Ring2_Gc_MaximumAlloctableSize");


/// @brief The maximal length of a string.
#define Ring2_String_MaximumLength  \
  (Ring2_Gc_MaximumAllocatableSize - (int64_t)sizeof(Ring2_String))

static_assert(Ring2_String_MaximumLength > 0,
              "Ring2_String_MaximumLength must be greater than 0");


static int g_referenceCount = 0;

static Ring2_StringHeap* g_stringHeap = NULL;


Ring1_CheckReturn() Ring1_Result
Ring2_StringModule_startup
  (
  )
{
  if (g_referenceCount == 0) {
    Ring1_Memory_ModuleHandle memoryModuleHandle =
      Ring1_Memory_ModuleHandle_acquire();
    if (!memoryModuleHandle) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      return Ring1_Result_Failure;
    }
    if (Ring1_Memory_allocate(&g_stringHeap, sizeof(Ring2_StringHeap))) {
      Ring1_Memory_ModuleHandle_relinquish(memoryModuleHandle);
      memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
      return Ring1_Result_Failure;
    }
    g_stringHeap->memoryModuleHandle = memoryModuleHandle;
    memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
    g_stringHeap->size = 0;
    g_stringHeap->capacity = 8;
    if (Ring1_Memory_allocate((void**)&(g_stringHeap->buckets),
                              (size_t)g_stringHeap->capacity *
                              sizeof(Ring2_String*))) {
      Ring1_Memory_ModuleHandle_relinquish(g_stringHeap->memoryModuleHandle);
      g_stringHeap->memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
      Ring1_Memory_deallocate(g_stringHeap);
      g_stringHeap = NULL;
      return Ring1_Result_Failure;
    }
    for (uint64_t i = 0, n = g_stringHeap->capacity; i < n; ++i) {
      g_stringHeap->buckets[i] = NULL;
    }
  }
  g_referenceCount++;
  return Ring1_Result_Success;
}

void
Ring2_StringModule_shutdown
  (
  )
{
  if (1 == g_referenceCount) {
    Ring1_Memory_ModuleHandle memoryModuleHandle =
      g_stringHeap->memoryModuleHandle;

    Ring1_Memory_deallocate(g_stringHeap->buckets);
    g_stringHeap->buckets = NULL;

    Ring1_Memory_deallocate(g_stringHeap);
    g_stringHeap = NULL;

    Ring1_Memory_ModuleHandle_relinquish(memoryModuleHandle);
  }
  g_referenceCount--;
}

void
Ring2_StringModule_preMarkCallback
  (
    Ring2_Gc* gc,
    void* context
  )
{
  for (int64_t i = 0, n = g_stringHeap->capacity; i < n; ++i) {
    Ring2_Gc_Tag *current = g_stringHeap->buckets[i];
    while (current) {
      if (Ring2_Gc_Tag_getLockCount(current) > 0) {
        Ring2_Gc_visit(gc, Ring2_Gc_toAddress(current));
      }
      current = current->objectNext;
    }
  }
}

void
Ring2_StringModule_sweepCallback
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  )
{
  if (statistics) {
    statistics->dead = 0;
    statistics->live = 0;
  }
  for (int64_t i = 0, n = g_stringHeap->capacity; i < n; ++i) {
    Ring2_Gc_Tag **previous = &(g_stringHeap->buckets[i]),
                  *current = g_stringHeap->buckets[i];
    while (current) {
      if (Ring2_Gc_Tag_isWhite(current)) {
        Ring2_Gc_Tag* object = current;
        *previous = current->objectNext;
        current = current->objectNext;
        Ring2_Gc_Tag_notifyWeakReferences(object);
        Ring1_Memory_deallocate(object);
        g_stringHeap->size--;
        if (statistics) {
          statistics->dead++;
        }
      } else {
        Ring2_Gc_Tag_setWhite(current);
        previous = &current->objectNext;
        current = current->objectNext;
        if (statistics) {
          statistics->live++;
        }
      }
    }
  }
}

static size_t
hashBytesToSz
  (
    char const *p,
    size_t n
  )
{
  size_t hashValue = n;
  for (size_t i = 0; i < n; ++i) {
    hashValue = p[i] + hashValue * 37;
  }
  return hashValue;
}


static Ring2_Gc_Type const g_gcType = {
  .finalize = (Ring2_Gc_FinalizeCallback*)NULL,
  .visit = (Ring2_Gc_VisitCallback*)NULL,
};

Ring1_CheckReturn() Ring2_String *
Ring2_String_create
  (
    char const* bytes,
    size_t numberOfBytes
  )
{
  if (!bytes) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (numberOfBytes < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (numberOfBytes > Ring2_String_MaximumLength) {
    Ring1_Status_set(Ring1_Status_TooLong);
    Ring2_jump();
  }
  size_t hashValue = hashBytesToSz(bytes, numberOfBytes);
  size_t hashIndex = hashValue % g_stringHeap->capacity;
  for (Ring2_Gc_Tag* object = g_stringHeap->buckets[hashIndex];
       NULL != object;
       object = object->objectNext) {
    Ring2_String* string = Ring2_Gc_toAddress(object);
    if (string->hashValue == hashValue && string->numberOfBytes == numberOfBytes) {
      int temporary;
      Ring1_Memory_compare(&temporary,
                           string->bytes,
                           (size_t)string->numberOfBytes,
                           bytes,
                           (size_t)numberOfBytes,
                           Ring1_Memory_Compare_Lexicographic);
      if (!temporary) {
        return string;
      }
    }
  }
  Ring2_String *string = Ring2_Gc_allocate(Ring2_Gc_get(),
                                           sizeof(Ring2_String) + numberOfBytes,
                                           &g_gcType,
                                           &g_stringHeap->buckets[hashIndex]);
  if (!string) {
    Ring2_jump();
  }
  g_stringHeap->size++;
  Ring1_Memory_copyFast(string->bytes, bytes, numberOfBytes);
  string->numberOfBytes = numberOfBytes;
  string->hashValue = hashValue;
  return string;
}

Ring1_CheckReturn() Ring2_String *
Ring2_String_concatenate
  (
    Ring2_String const *self,
    Ring2_String const *other
  )
{
  if (Ring2_String_MaximumLength - Ring2_String_getNumberOfBytes(Ring2_Context_get(), self) <
      Ring2_String_getNumberOfBytes(Ring2_Context_get(), other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  int64_t n = Ring2_String_getNumberOfBytes(Ring2_Context_get(), self)
            + Ring2_String_getNumberOfBytes(Ring2_Context_get(), other);
  char* buffer;
  if (Ring1_Memory_allocate(&buffer, (size_t)n)) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    Ring2_jump();
  }
  Ring1_Memory_copyFast(buffer, Ring2_String_getBytes(Ring2_Context_get(), self),
                        Ring2_String_getNumberOfBytes(Ring2_Context_get(), self));
  Ring1_Memory_copyFast(buffer + Ring2_String_getNumberOfBytes(Ring2_Context_get(), self),
                        Ring2_String_getBytes(Ring2_Context_get(), other),
                        Ring2_String_getNumberOfBytes(Ring2_Context_get(), other));
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring2_String* z = Ring2_String_create(buffer, n);
    Ring2_popJumpTarget();
    Ring1_Memory_deallocate(buffer);
    return z;
  } else {
    Ring2_popJumpTarget();
    Ring1_Memory_deallocate(buffer);
    Ring2_jump();
  }
}

Ring1_CheckReturn() int64_t
Ring2_String_getHashValue
  (
    Ring2_Context* context,
    Ring2_String const* self
  )
{
  uint64_t v = (uint64_t)self->hashValue;
  return (int64_t)(v >> 1);
}

Ring1_CheckReturn() const char *
Ring2_String_getBytes
  (
    Ring2_Context* context,
    Ring2_String const* self
  )
{
  return self->bytes;
}

Ring1_CheckReturn() size_t
Ring2_String_getNumberOfBytes
  (
    Ring2_Context* context,
    Ring2_String const* self
  )
{
  return self->numberOfBytes;
}

#endif // Ring2_Configuration_withString
