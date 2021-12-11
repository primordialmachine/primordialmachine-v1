/// @file Runtime/Type.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Type.h"

#include "Runtime/JumpTargetModule.h"
#include "Runtime/Object/ClassType.module.h"
#include "Runtime/Object/InterfaceType.module.h"
#include "Runtime/Status.h"
#include "Runtime/Type.module.h"

void Machine_Type_ensureInitialized(Machine_Type* self) {
  if (Machine_Type_isClass(self)) {
    Machine_ClassType_ensureInitialized((Machine_ClassType*)self);
  } else if (Machine_Type_isInterface(self)) {
    Machine_InterfaceType_ensureInitialized((Machine_InterfaceType*)self);
  }
}

bool Machine_Type_isClass(Machine_Type const* self) {
  return Machine_TypeFlags_Class == (self->flags & Machine_TypeFlags_Class);
}

bool Machine_Type_isInterface(Machine_Type const* self) {
  return Machine_TypeFlags_Interface == (self->flags & Machine_TypeFlags_Interface);
}

bool Machine_Type_isSubTypeOf(Machine_Type const* self, Machine_Type const* other) {
  if (!self || !other) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (!_TypeFlag_isSet(self, Machine_TypeFlags_Class)
      || !_TypeFlag_isSet(other, Machine_TypeFlags_Class)) {
    Machine_setStatus(Machine_Status_NotYetImplemented);
    Machine_jump();
  }
  return Machine_ClassType_isSubTypeOf((Machine_ClassType const*)self, (Machine_ClassType const*)other);
}

bool Machine_Type_isTrueSubTypeOf(Machine_Type const* self, Machine_Type const* other) {
  if (!self || !other) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (!_TypeFlag_isSet(self, Machine_TypeFlags_Class)
      || !_TypeFlag_isSet(other, Machine_TypeFlags_Class)) {
    Machine_setStatus(Machine_Status_NotYetImplemented);
    Machine_jump();
  }
  return Machine_ClassType_isTrueSubTypeOf((Machine_ClassType const*)self, (Machine_ClassType const*)other);
}

bool Machine_Type_isSuperTypeOf(Machine_Type const* self, Machine_Type const* other) {
  return Machine_Type_isSubTypeOf(other, self);
}

bool Machine_Type_isTrueSuperTypeOf(Machine_Type const* self, Machine_Type const* other) {
  return Machine_Type_isTrueSubTypeOf(other, self);
}
