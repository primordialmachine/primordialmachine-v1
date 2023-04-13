// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/TypeFlags.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/TypeSystem.h"
#undef RING2_PRIVATE


#include <assert.h>
#include "Ring1/All/_Include.h"
#define RING2_PRIVATE (1)
#include "Ring2/Gc.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/TypeSystem/Type.h"
#undef RING2_PRIVATE


typedef struct Ring2_TypeSystem {
  Ring2_Gc_Tag* types;
  Ring1_Memory_ModuleHandle memoryModuleHandle;
} Ring2_TypeSystem;

static Ring2_TypeSystem*
Ring2_TypeSystem_create
  (
  );

static void
Ring2_TypeSystem_destroy
  (
    Ring2_TypeSystem* typeSystem
  );

static Ring2_TypeSystem *
Ring2_TypeSystem_create
  (
  )
{ 
  Ring1_Memory_ModuleHandle memoryModuleHandle = Ring1_Memory_ModuleHandle_acquire();
  if (!memoryModuleHandle) {
    return NULL;
  }
  Ring2_TypeSystem* typeSystem;
  if (Ring1_Memory_allocate(&typeSystem, sizeof(Ring2_TypeSystem))) {
    Ring1_Memory_ModuleHandle_relinquish(memoryModuleHandle);
    memoryModuleHandle = Ring1_Memory_ModuleHandle_Invalid;
    return NULL;
  }
  typeSystem->types = NULL;
  typeSystem->memoryModuleHandle = memoryModuleHandle;
  return typeSystem;
}

static void
Ring2_TypeSystem_destroy
  (
    Ring2_TypeSystem *typeSystem
  )
{
  Ring1_Memory_ModuleHandle handle = typeSystem->memoryModuleHandle;
  typeSystem->types = NULL;
  Ring1_Memory_deallocate(typeSystem);
  Ring1_Memory_ModuleHandle_relinquish(handle);
}

/*PREMARK*/ static void
Ring2_TypeSystem_preMark
  (
    Ring2_Gc* gc,
    void* context
  );

/*SWEEP*/ static void
Ring2_TypeSystem_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  );

static Ring2_TypeSystem* g_typeSystem = NULL;

static Ring2_Gc_PreMarkCallbackId g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

static Ring2_Gc_SweepCallbackId g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

/*PREMARK*/ static void
Ring2_TypeSystem_preMark
  (
    Ring2_Gc* gc,
    void* context
  )
{
  Ring2_Gc_Tag* current = g_typeSystem->types;
  while (current) {
    if (Ring2_Gc_Tag_getLockCount(current) > 0) {
      Ring2_Gc_visit(gc, Ring2_Gc_toAddress(current));
    }
    current = current->objectNext;
  }
}

/*SWEEP*/ static void
Ring2_TypeSystem_sweep
  (
    Ring2_Gc* gc,
    void* context,
    Ring2_Gc_SweepStatistics* statistics
  )
{
  statistics->dead = 0;
  statistics->live = 0;
  Ring2_Gc_Tag** previous = &(g_typeSystem->types),
               * current = g_typeSystem->types;
  while (current) {
    if (Ring2_Gc_Tag_isWhite(current)) {
      Ring2_Gc_Tag* object = current;
      *previous = current->objectNext;
      current = current->objectNext;
      Ring2_Gc_Tag_notifyWeakReferences(object);
      if (object->type->finalize) {
        object->type->finalize(gc, Ring2_Gc_toAddress(object));
      }
      Ring1_Memory_deallocate(object);
      statistics->dead++;
    } else {
      Ring2_Gc_Tag_setWhite(current);
      previous = &current->objectNext;
      current = current->objectNext;
      statistics->live++;
    }
  }
}

Ring1_CheckReturn() Ring1_Result
Ring2_TypeSystemModule_startup
  (
  )
{
  assert(NULL == g_typeSystem);
  g_typeSystem = Ring2_TypeSystem_create();
  if (!g_typeSystem) {
    return Ring1_Result_Failure;
  }
  g_preMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL,
                                                    (Ring2_Gc_PreMarkCallback*)&Ring2_TypeSystem_preMark);
  if (!g_preMarkCallbackId) {
    Ring2_TypeSystem_destroy(g_typeSystem);
    g_typeSystem = NULL;
    
    return Ring1_Result_Failure;
  }

  g_sweepCallbackId = Ring2_Gc_addSweepCallback(Ring2_Gc_get(), NULL,
                                                (Ring2_Gc_SweepCallback*)&Ring2_TypeSystem_sweep);
  if (!g_sweepCallbackId) {
    Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), g_preMarkCallbackId);
    g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

    Ring2_TypeSystem_destroy(g_typeSystem);
    g_typeSystem = NULL;

    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void
Ring2_TypeSystemModule_shutdown
  (
  )
{ 
  assert(Ring2_Gc_SweepCallbackId_Invalid != g_sweepCallbackId);
  Ring2_Gc_removeSweepCallback(Ring2_Gc_get(), g_sweepCallbackId);
  g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;

  assert(Ring2_Gc_PreMarkCallbackId_Invalid != g_preMarkCallbackId);
  Ring2_Gc_removePreMarkCallback(Ring2_Gc_get(), g_preMarkCallbackId);
  g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;

  assert(NULL != g_typeSystem);
  Ring2_TypeSystem_destroy(g_typeSystem);
  g_typeSystem = NULL;
}

Ring1_CheckReturn() Machine_Type*
Ring2_Type_allocate
  (
    size_t size,
    Ring2_Gc_Type const *type
  )
{
  if (Ring1_Unlikely(size < 0)) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  Machine_Type *self = Ring2_Gc_allocate(Ring2_Gc_get(),
                                         (size_t)size, type, 
                                         &g_typeSystem->types);
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  return self;
}

Ring1_Module_Define(Ring2, TypeSystemModule, Ring2_TypeSystemModule_startup, Ring2_TypeSystemModule_shutdown)
