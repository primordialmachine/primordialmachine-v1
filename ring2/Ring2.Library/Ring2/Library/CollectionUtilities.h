// Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/CollectionUtilities.h
/// @copyright Copyright (c) 2020-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_LIBRARY_COLLECTIONUTILITIES_H_INCLUDED)
#define RING2_LIBRARY_COLLECTIONUTILITIES_H_INCLUDED

#if !defined(RING2_LIBRARY_PRIVATE) || 1 != RING2_LIBRARY_PRIVATE
#error("Do not include `Ring2/Library/CollectionUtilities.h` directly, include `Ring2/Library/_Include.h` instead.")
#endif

#include "Ring1/Status.h"
#include "Ring2/_Include.h"
#include "Ring1/Memory.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>


#define MIN_CAPACITY ((int64_t)1)
static_assert(MIN_CAPACITY <= INT64_MAX, "MIN_CAPACITY must be smaller than or equal to INT64_MAX");
static_assert(0 <= MIN_CAPACITY, "MIN_CAPACITY must be greater than or equal to 0");

#define MAX_CAPACITY (INT64_MAX / ((int64_t)sizeof(Ring2_Value)))
static_assert(MAX_CAPACITY <= INT64_MAX, "MAX_CAPACITY must be smaller than or equal to INT64_MAX");
static_assert(0 <= MAX_CAPACITY, "MAX_CAPACITY must be greater than or equal to 0");

static_assert(MIN_CAPACITY <= MAX_CAPACITY, "MIN_CAPACITY must be smaller than or equal to MAX_CAPACITY");

static void
CollectionUtilities_grow
  (
    Ring2_Context* context,
    Ring2_Value** values,
    int64_t* size,
    int64_t* capacity,
    int64_t required
  )
{
  assert(NULL != context);
  assert(NULL != values);

  int64_t oldCapacity = *capacity,
          newCapacity = 0;
  if (Ring1_Memory_recomputeSize_s64(MIN_CAPACITY, MAX_CAPACITY, oldCapacity, required, &newCapacity, true)) {
    fprintf(stderr, "unable to increase capacity");
    Ring2_jump();
  }
  // Perform reallocation.
  Ring2_Value* oldValues = *values;
  Ring2_Value* newValues = NULL;
  if (Ring1_Memory_allocateArray(&newValues, (size_t)newCapacity, sizeof(Ring2_Value))) {
    Ring2_jump();
  }
  Ring1_Memory_copyFast(newValues, oldValues, sizeof(Ring2_Value) * (size_t)oldCapacity);
  Ring1_Memory_deallocate(oldValues);
  *capacity = newCapacity;
  *values = newValues;
  for (int64_t i = oldCapacity, n = newCapacity; i < n; ++i) {
    Ring2_Value_setVoid((*values) + i, Ring2_Void_Void);
  }
}

static void
CollectionUtilities_ensureFreeCapacity
  (
    Ring2_Context* context,
    Ring2_Value** values,
    int64_t* size,
    int64_t* capacity,
    int64_t required
  )
{
  assert(NULL != context);
  assert(NULL != values);

  if (!required)
  { return; }
  if (required < 0) {
    fprintf(stderr, "invalid argument");
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  int64_t actual = *capacity - *size;
  if (actual > required)
  { return; }
  CollectionUtilities_grow(context, values, size, capacity, required - actual);
}

static void
CollectionUtilities_insertAt
  (
    Ring2_Context* context,
    Ring2_Value**values,
    int64_t* size,
    int64_t* capacity,
    Ring2_Value value,
    int64_t index
  )
{
  assert(NULL != context);
  assert(NULL != values);
  if (index < 0 || index > *size) {
    fprintf(stderr, "index out of bounds");
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  CollectionUtilities_ensureFreeCapacity(context, values, size, capacity, 1);
  if (index < *size) {
    Ring1_Memory_copyArraySlow((*values) + (size_t)index + 1, (*values) + (size_t)index + 0, (size_t)(*size) - (size_t)index, sizeof(Ring2_Value));
  }
  *((*values) + index) = value;
  ++(*size);
}

static void
CollectionUtilities_removeAt
  (
    Ring2_Context* context,
    Ring2_Value** values,
    int64_t* size,
    int64_t* capacity,
    int64_t index 
  )
{
  assert(NULL != context);
  assert(NULL != values);
  if (index < 0 || index >= *size) {
    fprintf(stderr, "index out of bounds");
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (index + 1 < *size) {
    Ring1_Memory_copyArraySlow((*values) + (size_t)index + 0, (*values) + (size_t)index + 1, (size_t)(*size) - (size_t)index - 1, sizeof(Ring2_Value));
  }
  --(*size);
}

static void
CollectionUtilities_removeAtFast
  (
    Ring2_Context* context,
    Ring2_Value** values,
    int64_t* size,
    int64_t* capacity,
    int64_t index 
  )
{
  assert(NULL != context);
  assert(NULL != values);
  if (index < 0 || index >= *size) {
    fprintf(stderr, "index out of bounds");
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  (*values)[index] = (*values)[(*size) - 1];
  --(*size);
}

/// @brief
/// Create a copy of the old array.
/// @param sizeNew
/// The size of the new array.
/// @param arrayOld
/// The old array.
/// @param sizeold
/// The size of the old array.
/// @param deallocate
/// If @a true the old array is deallocated if this function succeeds.
/// @return
/// The new array.
/// @remark
/// The first min(sizeNew,sizeOld) elements of the old and the new array are equal.
/// Furthermore, if sizeNew > sizeOld the elements in the new array at the indices [sizeOld, sizeNew - 1] are assigned the <code>Void</code> value.
static inline Ring2_Value*
CollectionUtilities_copyOfArray
  (
    size_t sizeNew,
    Ring2_Value* arrayOld,
    size_t sizeOld,
    bool deallocate
  )
{
  if (deallocate) {
    Ring2_Value* arrayNew = NULL;
    if (Ring1_Memory_reallocateArray(&arrayNew, arrayOld, sizeNew, sizeof(Ring2_Value))) {
      Ring2_jump();
    }
    for (size_t i = sizeOld, n = sizeNew; i < n; ++i) {
      Ring2_Value_setVoid(&(arrayNew[i]), Ring2_Void_Void);
    }
    return arrayNew;
  } else {
    Ring2_Value* arrayNew = NULL;
    if (Ring1_Memory_allocateArray(&arrayNew, sizeNew, sizeof(Ring2_Value))) {
      Ring2_jump();
    }
    for (size_t i = 0, n = sizeOld; i < n; ++i) {
      arrayNew[i] = arrayNew[i];
    }
    for (size_t i = sizeOld, n = sizeNew; i < n; ++i) {
      Ring2_Value_setVoid(&(arrayNew[i]), Ring2_Void_Void);
    }
    return arrayNew;
  }
}

#endif // RING2_LIBRARY_COLLECTIONUTILITIES_H_INCLUDED
