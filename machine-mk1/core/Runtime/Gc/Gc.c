/// @file Runtime/Gc/Gc.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Gc/Gc.h"

#include "Runtime/WeakReference.h"
#include "Runtime/Object/Object.h"
#include <assert.h>

static Machine_Gc_Tag* g_objects = NULL;
static Machine_Gc_Tag* g_gray = NULL;
static size_t g_objectCount = 0;

Machine_StatusValue Machine_initializeGcModule() {
  return Machine_Status_Success;
}

void Machine_uninitializeGcModule() {
}

Machine_Gc_Tag* Machine_Gc_toTag(void* src) {
  static size_t const N = sizeof(Machine_Gc_Tag);
  char* dst = ((char*)src) - N;
  return (Machine_Gc_Tag*)dst;
}

void* Machine_Gc_toAddress(Machine_Gc_Tag* src) {
  static size_t const N = sizeof(Machine_Gc_Tag);
  char* dst = ((char*)src) + N;
  return (void*)dst;
}

void Machine_Gc_lock(void* object) {
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  Machine_Gc_Tag_lock(tag);
}

void Machine_Gc_unlock(void* object) {
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  Machine_Gc_Tag_unlock(tag);
}

void Machine_Gc_setRoot(void* object, bool isRoot) {
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  Machine_Gc_Tag_setRoot(tag, isRoot);
}

bool Machine_Gc_isRoot(void* object) {
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  return Machine_Gc_Tag_isRoot(tag);
}

void* Machine_Gc_allocate(Machine_Gc_AllocationArguments const* arguments) {
  void* pt = Machine_Eal_Memory_allocate(arguments->prefixSize + sizeof(Machine_Gc_Tag)
                                         + arguments->suffixSize);
  if (!pt) {
    return NULL;
  }
  g_objectCount++;
  Machine_Eal_Memory_zero(pt,
                          arguments->prefixSize + sizeof(Machine_Gc_Tag) + arguments->suffixSize);
  Machine_Gc_Tag* t = (Machine_Gc_Tag*)(((char*)pt) + arguments->prefixSize);
  Machine_Gc_Tag_initialize(t);
  t->visit = arguments->visit;
  t->finalize = arguments->finalize;
  t->next = g_objects;
  g_objects = t;
  return ((char*)(t)) + sizeof(Machine_Gc_Tag);
}

void Machine_Gc_Tag_visit(Machine_Gc_Tag* tag) {
  if (Machine_Gc_Tag_isGrey(tag) || Machine_Gc_Tag_isBlack(tag)) {
    return;
  }
  tag->gray = g_gray;
  g_gray = tag;
  Machine_Gc_Tag_setGrey(tag);
}

void Machine_Gc_visit(void* object) {
  Machine_Gc_Tag* tag = Machine_Gc_toTag(object);
  Machine_Gc_Tag_visit(tag);
}

void Machine_Gc_run(size_t* live, size_t* dead) {
  (*live) = 0;
  (*dead) = 0;

  // Color all objects white. Add root objects or objects with a lock count greater than 0 to the
  // gray list.
  for (Machine_Gc_Tag* object = g_objects; NULL != object; object = object->next) {
    Machine_Gc_Tag_setWhite(object);
    if (Machine_Gc_Tag_isRoot(object) || object->lockCount > 0) {
      object->gray = g_gray;
      g_gray = object;
      Machine_Gc_Tag_setGrey(object);
    }
  }
  // Pop objects from gray list, visit them, color them black.
  while (g_gray) {
    assert(g_gray != NULL);
    Machine_Gc_Tag* object = g_gray;
    g_gray = object->gray;
    assert(object != NULL);
    if (object->visit) {
      object->visit(Machine_Gc_toAddress(object));
    }
    Machine_Gc_Tag_setBlack(object);
  }
  // Separate dead (white) and live (black) objects.
  Machine_Gc_Tag **previous = &g_objects, *current = g_objects;
  while (current) {
    if (Machine_Gc_Tag_isWhite(current)) {
      *previous = current->next;
      Machine_Gc_Tag* tag = current;
      current = current->next;
      // Finalize.
      if (tag->finalize) {
        tag->finalize(Machine_Gc_toAddress(tag));
      }
      // Notify weak references.
      while (tag->weakReferences) {
        Machine_WeakReference* weakReference = tag->weakReferences;
        tag->weakReferences = weakReference->next;
        weakReference->next = NULL;
        Machine_Value_isVoid(&weakReference->value);
      }
      // Deallocate.
      if ((tag->flags & Machine_Flag_Class) == Machine_Flag_Class) {
        Machine_ClassObjectTag* classObjectTag = t2cot(tag);
        Machine_Gc_Tag_uninitialize(tag);
        Machine_Eal_Memory_deallocate(classObjectTag);
      } else {
        Machine_Gc_Tag_uninitialize(tag);
        Machine_Eal_Memory_deallocate(tag);
      }
      g_objectCount--;
      (*dead)++;
    } else {
      previous = &current->next;
      current = current->next;
      (*live)++;
    }
  }
}
