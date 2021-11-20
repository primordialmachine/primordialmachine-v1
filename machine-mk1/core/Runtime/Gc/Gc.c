/// @file Runtime/Gc/Gc.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Gc/Gc.h"



Machine_StatusValue Machine_initializeGcModule() {
  return Machine_Status_Success;
}

void Machine_uninitializeGcModule() {
}

void Machine_lock(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  Machine_Tag_lock(tag);
}

void Machine_unlock(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  Machine_Tag_unlock(tag);
}

void Machine_setRoot(void* object, bool isRoot) {
  Machine_Tag* tag = Machine_o2t(object);
  Machine_Tag_setRoot(tag, isRoot);
}

bool Machine_isRoot(void* object) {
  Machine_Tag* tag = Machine_o2t(object);
  return Machine_Tag_isRoot(tag);
}
