/// @file Runtime/Gc/Gc.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Gc/Gc.h"

#include "Ring2/_Include.h"
#include "Ring1/Status.h"
#include "Runtime/WeakReference.h"
#include "Runtime/Object/Object.h"
#include <assert.h>

static Ring2_Gc_Tag* g_objects = NULL;
static Ring2_Gc_Tag* g_gray = NULL;
static size_t g_objectCount = 0;

static Ring2_Gc* g_gc = NULL;

Ring1_Result Machine_initializeGcModule() {
  g_gc = Ring2_Gc_create();
  if (!g_gc) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

void Machine_uninitializeGcModule() {
  Ring2_Gc_destroy(g_gc);
  g_gc = NULL;
}

void Machine_Gc_lock(void* object) {
  Ring2_Gc_Tag* tag = Ring2_Gc_toTag(object);
  Ring2_Gc_Tag_lock(tag);
}

void Machine_Gc_unlock(void* object) {
  Ring2_Gc_Tag* tag = Ring2_Gc_toTag(object);
  Ring2_Gc_Tag_unlock(tag);
}

void* Machine_Gc_allocate(Machine_Gc_AllocationArguments const* arguments) {
  void* pt = NULL;
  if (Ring1_Memory_allocate(&pt, sizeof(Ring2_Gc_Tag)
                            + arguments->suffixSize)) {
    return NULL;
  }
  g_objectCount++;
  Ring1_Memory_zeroFill(pt, sizeof(Ring2_Gc_Tag) + arguments->suffixSize);
  Ring2_Gc_Tag* t = (Ring2_Gc_Tag*)(((char*)pt));
  Ring2_Gc_Tag_initialize(t);
  t->type = arguments->type;
  t->objectNext = g_objects;
  g_objects = t;
  return ((char*)(t)) + sizeof(Ring2_Gc_Tag);
}

void Machine_Gc_visit(void* object) {
  Ring2_Gc_Tag* tag = Ring2_Gc_toTag(object);
  if (Ring2_Gc_Tag_isGray(tag) || Ring2_Gc_Tag_isBlack(tag)) {
    return;
  }
  tag->grayNext = g_gray;
  g_gray = tag;
  Ring2_Gc_Tag_setGray(tag);
}

void Machine_Gc_run(Ring2_Gc_RunStatistics *statistics) {
  if (statistics) {
    statistics->sweep.live = 0;
    statistics->sweep.dead = 0;
  }

  // Color all objects white. Add root objects or objects with a lock count greater than 0 to the
  // gray list.
  for (Ring2_Gc_Tag* object = g_objects; NULL != object; object = object->objectNext) {
    Ring2_Gc_Tag_setWhite(object);
    if (Ring2_Gc_Tag_getLockCount(object) > 0) {
      object->grayNext = g_gray;
      g_gray = object;
      Ring2_Gc_Tag_setGray(object);
    }
  }
  // Pop objects from gray list, visit them, color them black.
  while (g_gray) {
    assert(g_gray != NULL);
    Ring2_Gc_Tag* object = g_gray;
    g_gray = object->grayNext;
    assert(object != NULL);
    if (object->type && object->type->visit) {
      object->type->visit(g_gc, Ring2_Gc_toAddress(object));
    }
    Ring2_Gc_Tag_setBlack(object);
  }
  // Separate dead (white) and live (black) objects.
  Ring2_Gc_Tag **previous = &g_objects, *current = g_objects;
  while (current) {
    if (Ring2_Gc_Tag_isWhite(current)) {
      *previous = current->objectNext;
      Ring2_Gc_Tag* tag = current;
      current = current->objectNext;
      // Finalize.
      if (tag->type && tag->type->finalize) {
        tag->type->finalize(g_gc, Ring2_Gc_toAddress(tag));
      }
      // Notify weak references.
      Ring2_Gc_Tag_notifyWeakReferences(tag);
      // Deallocate.
      Ring2_Gc_Tag_uninitialize(tag);
      Ring1_Memory_deallocate(tag);
      g_objectCount--;
      if (statistics) statistics->sweep.dead++;
    } else {
      previous = &current->objectNext;
      current = current->objectNext;
      if (statistics) statistics->sweep.live++;
    }
  }
}
