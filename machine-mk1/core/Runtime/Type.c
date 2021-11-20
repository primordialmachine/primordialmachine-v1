/// @file Runtime/Type.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Type.h"

#include "Runtime/Object/ClassType.h"

void Machine_Type_ensureInitialized(Machine_Type* self) {
  if (Machine_Type_isClass(self)) {
    Machine_ClassType_ensureInitialized((Machine_ClassType*)self);
  } else if (Machine_Type_isInterface(self)) {
  }
}

bool Machine_Type_isClass(Machine_Type const* self) {
  return Machine_TypeFlags_Class == (self->flags & Machine_TypeFlags_Class);
}

bool Machine_Type_isInterface(Machine_Type const* self) {
  return Machine_TypeFlags_Interface == (self->flags & Machine_TypeFlags_Interface);
}
