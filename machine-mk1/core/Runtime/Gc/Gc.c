/// @file Runtime/Gc/Gc.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Gc/Gc.h"

#include "Ring2/Gc.h"
#include "Ring1/Memory.h"
#include "Ring1/Status.h"
#include <assert.h>

#define WITH_NEW_GC (1)

static Ring2_Gc_Tag* g_objects = NULL;

#if defined(WITH_NEW_GC) && 1 == WITH_NEW_GC
static Ring2_Gc_PreMarkCallbackId g_preMarkCallbackId = Ring2_Gc_PreMarkCallbackId_Invalid;
static Ring2_Gc_SweepCallbackId g_sweepCallbackId = Ring2_Gc_SweepCallbackId_Invalid;
#endif

Ring1_CheckReturn() Ring1_Result
Machine_Gc_startup() {
  if (Ring2_Gc_startup()) {
    return Ring1_Result_Failure;
  }
  g_preMarkCallbackId = Ring2_Gc_addPreMarkCallback(Ring2_Gc_get(), NULL, &Machine_Gc_preMarkCallback);
  if (g_preMarkCallbackId == Ring2_Gc_PreMarkCallbackId_Invalid) {
    Ring2_Gc_shutdown();
    return Ring1_Result_Failure;
  }
  g_sweepCallbackId = Ring2_Gc_addSweepCallback(Ring2_Gc_get(), NULL, &Machine_Gc_sweepCallback);
  if (g_sweepCallbackId == Ring2_Gc_SweepCallbackId_Invalid) {
    Ring2_Gc_shutdown();
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void 
Machine_Gc_shutdown() {
  Ring2_Gc_shutdown();
}

void* Machine_Gc_allocate(Machine_Gc_AllocationArguments const* arguments) {
  void *p = Ring2_Gc_allocate(Ring2_Gc_get(), arguments->suffixSize, arguments->type, &g_objects);
  if (!p) {
    return NULL;
  }
  return p;
}

void Machine_Gc_visit(void* object) {
  Ring2_Gc_visit(Ring2_Gc_get(), object);
}

void Machine_Gc_preMarkCallback(Ring2_Gc *gc, void *context) {
  for (Ring2_Gc_Tag* object = g_objects; NULL != object; object = object->objectNext) {
    Ring2_Gc_Tag_setWhite(object);
    if (Ring2_Gc_Tag_getLockCount(object) > 0) {
      Ring2_Gc_visit(Ring2_Gc_get(), Ring2_Gc_toAddress(object));
    }
  }
}

void Machine_Gc_sweepCallback(Ring2_Gc *gc, void* context, Ring2_Gc_SweepStatistics *statistics) {
  Ring2_Gc_Tag **previous = &g_objects, *current = g_objects;
  while (current) {
    if (Ring2_Gc_Tag_isWhite(current)) {
      // Remove object from list.
      Ring2_Gc_Tag* tag = current;
      *previous = current->objectNext;
      current = current->objectNext;
      // Finalize.
      if (tag->type) {
        if (tag->type && tag->type->finalize) {
          tag->type->finalize(Ring2_Gc_get(), Ring2_Gc_toAddress(tag));
        }
      }
      // Notify weak reference.
      Ring2_Gc_Tag_notifyWeakReferences(tag);
      // Deallocate.
      Ring2_Gc_Tag_uninitialize(tag);
      Ring1_Memory_deallocate(tag);
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

void Machine_Gc_run(Ring2_Gc_RunStatistics *statistics) {
  if (statistics) {
    statistics->sweep.live = 0;
    statistics->sweep.dead = 0;
  }
  Ring2_Gc_run(Ring2_Gc_get(), statistics);
}
