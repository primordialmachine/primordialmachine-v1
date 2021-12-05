#define MACHINE_RUNTIME_PRIVATE (1)
#include "Machine.h"



#include "Runtime/String.h"



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static Machine_Tag* g_objects = NULL;
static Machine_Tag* g_gray = NULL;
static size_t g_objectCount = 0;

static const struct {
  Machine_StatusValue(*initialize)();
  void (*uninitialize)();
} MODULES[] = {
  { &Machine_initializeLogModule, &Machine_uninitializeLogModule },
  { &Machine_initializeJumpTargetModule, &Machine_uninitializeJumpTargetModule },
  { &Machine_initializeGcModule, &Machine_uninitializeGcModule },
  { &Machine_initializeStackModule, &Machine_uninitializeStackModule },
  { &Machine_initializeStaticVariablesModule, &Machine_uninitializeStaticVariablesModule },
};
static const size_t NUMBER_OF_MODULES = 4;

Machine_StatusValue Machine_startup() {
  for (size_t i = 0, n = NUMBER_OF_MODULES; i < n; ++i) {
    Machine_StatusValue status = MODULES[i].initialize();
    if (status) {
      while (i > 0) {
        MODULES[i - 1].uninitialize();
        i--;
      }
      return status;
    }
  }
  return Machine_Status_Success;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void visit(Machine_Tag* tag) {
  if (Machine_Tag_isGrey(tag) || Machine_Tag_isBlack(tag)) {
    return;
  }
  tag->gray = g_gray; g_gray = tag;
  Machine_Tag_setGrey(tag);
}

void Machine_Gc_run(size_t* live, size_t *dead) {
  (*live) = 0;
  (*dead) = 0;

  // Color all objects white. Add root objects or objects with a lock count greater than 0 to the gray list.
  for (Machine_Tag* object = g_objects; NULL != object; object = object->next) {
    Machine_Tag_setWhite(object);
    if (Machine_Tag_isRoot(object) || object->lockCount > 0) {
      object->gray = g_gray;
      g_gray = object;
      Machine_Tag_setGrey(object);
    }
  }
  // Pop objects from gray list, visit them, color them black.
  while (g_gray) {
    assert(g_gray != NULL);
    Machine_Tag* object = g_gray; g_gray = object->gray;
    assert(object != NULL);
    if (object->visit) {
      object->visit(Machine_t2o(object));
    }
    Machine_Tag_setBlack(object);
  }
  // Separate dead (white) and live (black) objects.
  Machine_Tag** previous = &g_objects, * current = g_objects;
  while (current) {
    if (Machine_Tag_isWhite(current)) {
      *previous = current->next;
      Machine_Tag* tag = current;
      current = current->next;
      if (tag->finalize) {
        tag->finalize(Machine_t2o(tag));
      }
      if ((tag->flags & Machine_Flag_Class) == Machine_Flag_Class) {
        Machine_ClassObjectTag* classObjectTag = t2cot(tag);
        Machine_Tag_uninitialize(tag);
        Machine_Eal_Memory_deallocate(classObjectTag);
      } else {
        Machine_Tag_uninitialize(tag);
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

void Machine_update() {
  size_t live, dead;
  Machine_Gc_run(&live, &dead);
}

void* Machine_allocateEx(size_t payloadSize, size_t tagPrefixSize, Machine_VisitCallback* visit, Machine_FinalizeCallback* finalize) {
  void* pt = Machine_Eal_Memory_allocate(tagPrefixSize + sizeof(Machine_Tag) + payloadSize);
  if (!pt) {
    return NULL;
  }
  g_objectCount++;
  memset(pt, 0, tagPrefixSize + sizeof(Machine_Tag) + payloadSize);
  Machine_Tag* t = (Machine_Tag *)(((char*)pt) + tagPrefixSize);
  Machine_Tag_initialize(t);
  t->size = payloadSize;
  t->visit = visit;
  t->finalize = finalize;
  t->next = g_objects; g_objects = t;
  return ((char *)(t)) + sizeof(Machine_Tag);
}

void* Machine_Gc_allocate(size_t size, Machine_VisitCallback* visit, Machine_FinalizeCallback* finalize) {
  return Machine_allocateEx(size, 0, visit, finalize);
}

void Machine_Gc_visit(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  if (Machine_Tag_isWhite(tag)) {
    tag->gray = g_gray; g_gray = tag;
    Machine_Tag_setGrey(tag);
  }
}

void Machine_shutdown() {
  size_t MAX_RUN = 8;
  size_t live = 0, dead = 0, run = 0;
  
  do {
    size_t newLive, newDead;
    Machine_Gc_run(&newLive, &newDead);
    if (newLive > 0 && newDead == 0) {
      fprintf(stderr, "gc not making progress\n");
      break;
    }
    dead = newDead;
    live = newLive;
    run++;
  } while (live > 0 && run < MAX_RUN);

  Machine_notifyStaticVariablesUninitialize();

  do {
    size_t newLive, newDead;
    Machine_Gc_run(&newLive, &newDead);
    if (newLive > 0 && newDead == 0) {
      fprintf(stderr, "gc not making progress\n");
      break;
    }
    dead = newDead;
    live = newLive;
    run++;
  } while (live > 0 && run < MAX_RUN);

  if (live > 0) {
    fprintf(stderr, "warning %zu live objects remaining\n", live);
  }

  for (size_t i = NUMBER_OF_MODULES; i > 0; --i) {
    MODULES[i-1].uninitialize();
  }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
