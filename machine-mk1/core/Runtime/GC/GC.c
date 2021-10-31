/// @file Runtime/GC/GC.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/GC/GC.h"



Machine_StatusValue Machine_initializeGcModule() {
  return Machine_Status_Success;
}

void Machine_uninitializeGcModule() {
}

void Machine_lock(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  tag->lockCount++;
}

void Machine_unlock(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  tag->lockCount--;
}

void Machine_setRoot(void* object, bool isRoot) {
  Machine_Tag* tag = Machine_o2t(object);
  if (isRoot) {
    tag->flags |= Machine_Flag_Root;
  }
  else {
    tag->flags &= ~Machine_Flag_Root;
  }
}

bool Machine_isRoot(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  return Machine_Flag_Root == (tag->flags & Machine_Flag_Root);
}
