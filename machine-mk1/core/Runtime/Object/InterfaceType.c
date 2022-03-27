/// @file Runtime/Object/InterfaceType.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Object/InterfaceType.h"

#include "Ring1/Status.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/Object/InterfaceType.module.h"
#include "Runtime/Type.module.h"

static void Machine_InterfaceType_finalize(Machine_InterfaceType* self) {
  if (self->extendsArrayInitialized) {
    for (size_t i = 0, n = self->extends.size; i < n; ++i) {
      Machine_InterfaceType* element = Machine_Eal_InlineArray_getAt(&self->extends, i);
      Machine_Gc_unlock(element);
    }
    Machine_Eal_InlineArray_uninitialize(&self->extends);
  }
  _Type_finalize((Machine_Type*)self);
}

static void Machine_InterfaceType_visit(Machine_InterfaceType* self) {
  _Type_visit((Machine_Type*)self);
}

Machine_InterfaceType* Machine_createInterfaceType(Machine_CreateInterfaceTypeArgs* args) {
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = 0,
    .suffixSize = sizeof(Machine_InterfaceType),
    .visit = (Machine_Gc_VisitCallback*)Machine_InterfaceType_visit,
    .finalize = (Machine_Gc_FinalizeCallback*)&Machine_InterfaceType_finalize,
  };
  Machine_InterfaceType* interfaceType = Machine_Gc_allocate(&allocationArguments);
  if (!interfaceType) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  ((Machine_Type*)interfaceType)->flags = Machine_TypeFlags_Interface;
  ((Machine_Type*)interfaceType)->typeRemoved = args->createTypeArgs.typeRemoved;
  ((Machine_Type*)interfaceType)->children.elements = NULL;
  if (Ring1_Memory_allocateArray((void **) & (((Machine_Type*)interfaceType)->children.elements), 0,
                                 sizeof(Machine_Type*))) {
    Ring1_Status_set(Ring1_Status_Success);
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  ((Machine_Type*)interfaceType)->children.size = 0;
  static const Machine_Eal_InlineArrayDispatch extendsConfiguration = {
    .elementSize = sizeof(Machine_Type*),
  };
  if (Machine_Eal_InlineArray_initialize(&interfaceType->extends, &extendsConfiguration)) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  interfaceType->extendsArrayInitialized = true;
  interfaceType->size = args->size;
  interfaceType->addPrerequisites = args->addPrerequisites;
  return interfaceType;
}

bool Machine_InterfaceType_extend(Machine_InterfaceType* self, Machine_Type* extended) {
  if (!self || !extended || !Machine_Type_isInterface(extended)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (_TypeFlag_isSet((Machine_Type*)self, Machine_TypeFlags_Initialized)) {
    Machine_setStatus(Machine_Status_InvalidOperation);
    Machine_jump();
  }
  // If EXTENDED is a super-type of THIS, return true.
  if (Machine_Type_isSuperTypeOf(extended, (Machine_Type*)self)) {
    return true;
  }
  // If EXTENDED is a sub-type of THIS, return false.
  if (Machine_Type_isSubTypeOf(extended, (Machine_Type*)self)) {
    return false;
  }
  if (Machine_Eal_InlineArray_append(&self->extends, extended)) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  Machine_Gc_lock(extended);
  return true;
}

void Machine_InterfaceType_ensureInitialized(Machine_InterfaceType* self) {
  if (_TypeFlag_isSet((Machine_Type*)self, Machine_TypeFlags_Initialized)) {
    return;
  }
  if (!Machine_InterfaceType_hasFlag(self, Machine_InterfaceTypeFlags_PrerequisitesAdded)) {
    if (self->addPrerequisites) {
      self->addPrerequisites(self);
    }
    Machine_InterfaceType_addFlag(self, Machine_InterfaceTypeFlags_PrerequisitesAdded);
  }
  if (!Machine_InterfaceType_hasFlag(self, Machine_InterfaceTypeFlags_PrerequisitesInitialized)) {
    for (size_t i = 0, n = self->extends.size; i < n; ++i) {
      Machine_InterfaceType* element = Machine_Eal_InlineArray_getAt(&self->extends, i);
      Machine_InterfaceType_ensureInitialized(element);
    }
    Machine_InterfaceType_addFlag(self, Machine_InterfaceTypeFlags_PrerequisitesInitialized);
  }
  _TypeFlag_set((Machine_Type*)self, Machine_TypeFlags_Initialized);
}
