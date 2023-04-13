// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Array.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Types/Array.h"
#undef RINg2_PRIVATE


#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray


#include "Ring1/All/_Include.h"
#define RING2_PRIVATE (1)
#include "Ring2/JumpTarget.h"
#include "Ring2/Types/Value.h"
#undef RING2_PRIVATE
#include <stdio.h>
#include <string.h>


/// @brief The type of an array heap.
typedef struct Ring2_ArrayHeap Ring2_ArrayHeap;

struct Ring2_Array
{
  Ring2_Integer length; // The number of values.
  Ring2_Value values[]; // The values as a flexible array at the end of the struct.
};

static_assert(Ring2_Gc_MaximumAllocatableSize >= sizeof(Ring2_Array),
              "sizeof(Ring2_Array) is greater than Ring2_Gc_MaximumAlloctableSize");

/// @brief The maximal length of an array.
#define Ring2_Array_MaximumLength \
  ((Ring2_Gc_MaximumAllocatableSize - sizeof(Ring2_Array)) / sizeof(Ring2_Value))

static_assert(Ring2_Array_MaximumLength > 0,
              "Ring2_Array_MaximumLength must be greater than 0");

struct Ring2_ArrayHeap {
  Ring1_Memory_ModuleHandle memoryModuleHandle;
  Ring2_Gc_Tag* arrays;
};

static Ring1_CheckReturn() Ring1_Result
Ring2_ArrayModule_startup
  (
  );

static void
Ring2_ArrayModule_shutdown
  (
  );

/*VISIT*/ static void
visit
  (
    Ring2_Gc* gc,
    Ring2_Array* x
  );

/*PREMARK*/ static void
Ring2_ArrayModule_preMark
  (
    Ring2_Gc* gc,
    void* context
  );

/*SWEEP*/ static void
Ring2_ArrayModule_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  );

static Ring2_ArrayHeap*
Ring2_ArrayHeap_create
  (
  );

static void
Ring2_ArrayHeap_destroy
  (
    Ring2_ArrayHeap* arrayHeap
  );

Ring1_Module_Define(Ring2, ArrayModule, Ring2_ArrayModule_startup, Ring2_ArrayModule_shutdown)

static Ring2_ArrayHeap* g_arrayHeap = NULL;

static Ring2_Gc_PreMarkCallbackId g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

static Ring2_Gc_SweepCallbackId g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

/*VISIT*/ static void
visit
  (
    Ring2_Gc* gc,
    Ring2_Array* x
  )
{
  for (int64_t i = 0, n = x->length; i < n; ++i) {
    Ring2_Value_visit(gc, x->values + i);
  }
}

static Ring2_ArrayHeap*
Ring2_ArrayHeap_create
  (
  )
{
  Ring1_Memory_ModuleHandle handle = Ring1_Memory_ModuleHandle_acquire();
  if (!handle)
  {
    return NULL;
  }
  Ring2_ArrayHeap* arrayHeap;
  if (Ring1_Memory_allocate(&arrayHeap, sizeof(Ring2_ArrayHeap)))
  {
    Ring1_Memory_ModuleHandle_relinquish(handle);
    return NULL;
  }
  arrayHeap->arrays = NULL;
  arrayHeap->memoryModuleHandle = handle;
  return arrayHeap;
}

static void
Ring2_ArrayHeap_destroy
  (
    Ring2_ArrayHeap* arrayHeap
  )
{
  Ring1_Memory_ModuleHandle handle = arrayHeap->memoryModuleHandle;
  Ring1_Memory_deallocate(arrayHeap);
  Ring1_Memory_ModuleHandle_relinquish(handle);
}

static Ring1_CheckReturn() Ring1_Result
Ring2_ArrayModule_startup
  (
  )
{
  g_arrayHeap = Ring2_ArrayHeap_create();
  if (!g_arrayHeap) {
    return Ring1_Result_Failure;
  }
  g_sweepCallbackId = Ring2_Gc_addSweepCallback(Ring2_Gc_get(), NULL,
                                                (Ring2_Gc_SweepCallback*)&Ring2_ArrayModule_sweep);
  if (!g_sweepCallbackId) {
    Ring2_ArrayHeap_destroy(g_arrayHeap);
    g_arrayHeap = NULL;
      
    return Ring1_Result_Failure;
  }
  g_preMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL,
                                                    (Ring2_Gc_PreMarkCallback*)&Ring2_ArrayModule_preMark);
  if (!g_preMarkCallbackId) {
    Ring2_Gc_removeSweepCallback(Ring2_Gc_get(), g_sweepCallbackId);
    g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

    Ring2_ArrayHeap_destroy(g_arrayHeap);
    g_arrayHeap = NULL;
      
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

static void
Ring2_ArrayModule_shutdown
  (
  )
{
  Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), g_preMarkCallbackId);
  g_sweepCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

  Ring2_Gc_removeSweepCallback(Ring2_Gc_get(), g_sweepCallbackId);
  g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

  Ring2_ArrayHeap_destroy(g_arrayHeap);
  g_arrayHeap = NULL;
}

/*PREMARK*/ static void
Ring2_ArrayModule_preMark
  (
    Ring2_Gc* gc,
    void* context
  )
{
  Ring2_Gc_Tag* current = g_arrayHeap->arrays;
  while (current) {
    if (Ring2_Gc_Tag_getLockCount(current) > 0) {
      Ring2_Gc_visit(gc, Ring2_Gc_toAddress(current));
    }
    current = current->objectNext;
  }
}

/*SWEEP*/ void
Ring2_ArrayModule_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  )
{
  statistics->dead = 0;
  statistics->live = 0;
  Ring2_Gc_Tag** previous = &(g_arrayHeap->arrays),
               * current = g_arrayHeap->arrays;
  while (current)
  {
    if (Ring2_Gc_Tag_isWhite(current))
    {
      Ring2_Gc_Tag* object = current;
      *previous = current->objectNext;
      current = current->objectNext;
      Ring2_Gc_Tag_notifyWeakReferences(object);
      Ring1_Memory_deallocate(object);
      statistics->dead++;
    }
    else
    {
      previous = &current->objectNext;
      current = current->objectNext;
      statistics->live++;
    }
  }
}

Ring1_CheckReturn() Ring2_Array*
Ring2_ArrayHeap_createArray
  (
    Ring2_Context* context,
    int64_t length
  )
{
  // This implies that sizeof(Ring2_Array) + length *
  // sizeof(Mkx_Interpreter_Value) does not overflow and can be
  // cast into INT64_MAX and SIZE_MAX without overflow as well.
  // Proof:
  //  length <= Ring2_Array_MaximumLength
  //  length <= (Ring2_Gc_MaximumAllocatableSize - sizeof(Ring2_Array)) / sizeof(Mkx_Interpreter_Value)
  //  length * sizeof(Mkx_Interpreter_Value) <= Ring2_Gc_MaximumAllocatableSize - sizeof(Ring2_Array)
  //  length * sizeof(Mkx_Interpreter_Value) + sizeof(Ring2_Array) <= Ring2_Gc_MaximumAllocatableSize
  // And as Ring2_Gc_MaximumAllocatableSize is smaller than or equal to INT64_MAX and SIZE_MAX then it follows
  // that length * sizeof(Mkx_Interpreter_Value) + sizeof(Ring2_Array) is smaller than or equal to
  // INT64_MAX and SIZE_MAX.
  // This implies that sizeof(Ring2_Array) + length *
  // sizeof(Mkx_Interpreter_Value) does not overflow and can be
  // cast into INT64_MAX and SIZE_MAX without overflow as well.
  // Qed.
  if (length < 0 || length > Ring2_Array_MaximumLength) {
    return NULL;
  }
  static const Ring2_Gc_Type TYPE = {
    .finalize = NULL,
    .visit = &visit,
  };

  int64_t totalNumberOfBytes = (int64_t)sizeof(Ring2_Array)
                             + length * (int64_t)sizeof(Ring2_Value);

  Ring2_Array* array = Ring2_Gc_allocate(Ring2_Gc_get(), (size_t)totalNumberOfBytes, &TYPE, &g_arrayHeap->arrays);
  if (!array) {
    return NULL;
  }

  for (int64_t i = 0, n = length; i < n; ++i) {
    Ring2_Value_setVoid(array->values + i, Ring2_Void_Void);
  }

  array->length = length;

  return array;
}

Ring1_CheckReturn() Ring2_Value
Ring2_Array_getElement
  (
    Ring2_Context* context,
    Ring2_Array* self,
    Ring2_Integer index
  )
{ return self->values[index]; }

void
Ring2_Array_setElement
  (
    Ring2_Context* context,
    Ring2_Array* self,
    Ring2_Integer index,
    Ring2_Value value
  )
{ self->values[index] = value; }

Ring1_CheckReturn() Ring2_Integer
Ring2_Array_getLength
  (
    Ring2_Context* context,
    Ring2_Array* self
  )
{ return self->length; }

Ring1_CheckReturn() Ring2_String*
Ring2_ArrayModule_toString
  (
    Ring2_Context* context,
    Ring2_Array* self
  )
{
  char buffer[1024];
  int result = snprintf(buffer, 1024, "%p", self);
  if (result < 0 || result > 1024)
  {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  return Ring2_String_create(buffer, strlen(buffer));
}

#endif
