/// @file Runtime/Object/ClassType.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/ClassType.h"



#include "Machine.h"
#include <malloc.h>
#include <string.h>



static void Machine_ClassType_visit(Machine_ClassType* self) {
  if (self->parent) {
    Machine_Gc_visit(self->parent);
  }
}

static void Machine_ClassType_finalize(Machine_ClassType* self) {
  if (self->parent) {
    Machine_unlock(self->parent);
  }
  if (self->data) {
    free(self->data);
    self->data = NULL;
  }
  if (((Machine_Type *)self)->typeRemoved) {
    ((Machine_Type*)self)->typeRemoved();
  }
}

Machine_ClassType* Machine_createClassType(Machine_CreateClassTypeArgs* args) {
  Machine_ClassType* classType = Machine_Gc_allocate(sizeof(Machine_ClassType),
                                                     (Machine_VisitCallback*)&Machine_ClassType_visit,
                                                     (Machine_FinalizeCallback*)&Machine_ClassType_finalize);
  if (!classType) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  if (args->parent) {
    if (args->parent->size > args->size) {
      Machine_setStatus(Machine_Status_InvalidArgument);
      Machine_jump();
    }
  }
  if (args->parent) {
    if (args->parent->classSize > args->classSize) {
      Machine_setStatus(Machine_Status_InvalidArgument);
      Machine_jump();
    }
  }

  ((Machine_Type*)classType)->typeRemoved = args->createTypeArgs.typeRemoved;
  classType->size = args->size;
  classType->visit = args->visit;
  classType->construct = args->construct;
  classType->destruct = args->destruct;
  classType->parent = args->parent;
  classType->classSize = args->classSize;
  classType->constructClass = args->constructClass;

  classType->data = malloc(classType->classSize > 0 ? classType->classSize : 1);
  if (!classType->data) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  memset(classType->data, 0, classType->classSize);
  if (args->parent) {
    memcpy(classType->data, args->parent->data, args->parent->classSize);
  }
  if (args->constructClass) {
    args->constructClass(classType->data);
  }
  if (args->parent) {
    Machine_lock(classType->parent);
  }
  return classType;
}

bool Machine_isSubTypeOf(Machine_ClassType const* subType, Machine_ClassType const* superType) {
  Machine_ClassType const* currentType = subType;
  while (currentType != NULL) {
    if (currentType == superType) {
      return true;
    }
    currentType = currentType->parent;
  }
  return false;
}