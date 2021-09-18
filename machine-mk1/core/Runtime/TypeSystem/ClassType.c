/// @file Runtime/TypeSystem/ClassType.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/TypeSystem/ClassType.h"



#include "Machine.h"



static void Machine_ClassType_visit(Machine_ClassType* self) {
  if (self->parent) {
    Machine_visit(self->parent);
  }
}

static void Machine_ClassType_finalize(Machine_ClassType* self) {
  if (self->parent) {
    Machine_unlock(self->parent);
  }
  if (self->typeRemoved) {
    self->typeRemoved();
  }
}

Machine_ClassType* Machine_createClassType(Machine_ClassType* parent, size_t size, Machine_ClassTypeRemovedCallback* typeRemoved, Machine_ClassObjectVisitCallback* visit, Machine_ClassObjectConstructCallback* construct, Machine_ClassObjectDestructCallback* destruct) {
  Machine_ClassType* classType = Machine_allocate(sizeof(Machine_ClassType), (Machine_VisitCallback*)&Machine_ClassType_visit, (Machine_FinalizeCallback*)&Machine_ClassType_finalize);
  if (!classType) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  classType->size = size;
  classType->typeRemoved = typeRemoved;
  classType->visit = visit;
  classType->construct = construct;
  classType->destruct = destruct;
  classType->parent = parent;
  if (parent) {
    Machine_lock(classType->parent);
  }
  return classType;
}
