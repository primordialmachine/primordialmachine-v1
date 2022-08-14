// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/InterfaceType.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/TypeSystem/InterfaceType.h"

#include "Ring2/Types/Object.h"
#include "Ring2/TypeSystem/ClassType.h"
#include "Ring2/TypeSystem/EnumerationType.h"
#include "Ring2/Gc.h"
#include "Ring2/JumpTarget.h"
#include "Ring1/Memory.h"
#include "Ring1/Status.h"

static void Machine_InterfaceType_finalize(void *gc, Machine_InterfaceType* self) {
  if (self->extendsArrayInitialized) {
    for (size_t i = 0, n = self->extends.size; i < n; ++i) {
      Machine_InterfaceType* element = Ring1_InlineArray_getAt(&self->extends, i);
      Ring2_Gc_unlock(element);
    }
    Ring1_InlineArray_uninitialize(&self->extends);
  }
  Ring2_Type_finalize((Machine_Type*)self);
}

static void Machine_InterfaceType_visit(void *gc, Machine_InterfaceType* self) {
  Ring2_Type_visit((Machine_Type*)self);
}

Machine_InterfaceType* Machine_createInterfaceType(Machine_CreateInterfaceTypeArgs* args) {
  static Ring2_Gc_Type const gcType = {
    .finalize = (Ring2_Gc_FinalizeCallback*)&Machine_InterfaceType_finalize,
    .visit = (Ring2_Gc_VisitCallback*)Machine_InterfaceType_visit,
  };
  Machine_InterfaceType* interfaceType = Ring2_ObjectModule_allocate(Ring2_Gc_get(), sizeof(Machine_InterfaceType), &gcType);
  if (!interfaceType) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    Ring2_jump();
  }
  ((Machine_Type*)interfaceType)->flags = Ring2_TypeFlags_Interface;
  ((Machine_Type*)interfaceType)->typeRemoved = args->createTypeArgs.typeRemoved;
  ((Machine_Type*)interfaceType)->children.elements = NULL;
  if (Ring1_Memory_allocateArray((void **) & (((Machine_Type*)interfaceType)->children.elements), 0,
                                 sizeof(Machine_Type*))) {
    Ring2_jump();
  }
  ((Machine_Type*)interfaceType)->children.size = 0;
  static const Ring1_InlineArrayDispatch extendsConfiguration = {
    .elementSize = sizeof(Machine_Type*),
  };
  if (Ring1_InlineArray_initialize(&interfaceType->extends, &extendsConfiguration)) {
    Ring2_jump();
  }
  interfaceType->extendsArrayInitialized = true;
  interfaceType->size = args->size;
  interfaceType->addPrerequisites = args->addPrerequisites;
  return interfaceType;
}

bool Machine_InterfaceType_extend(Machine_InterfaceType* self, Machine_Type* extended) {
  if (!self || !extended || !Machine_Type_isInterface(extended)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (Ring2_TypeFlag_isSet((Machine_Type*)self, Ring2_TypeFlags_Initialized)) {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  }
  // If EXTENDED is a super-type of THIS, return true.
  if (Machine_Type_isSuperTypeOf(extended, (Machine_Type*)self)) {
    return true;
  }
  // If EXTENDED is a sub-type of THIS, return false.
  if (Machine_Type_isSubTypeOf(extended, (Machine_Type*)self)) {
    return false;
  }
  if (Ring1_InlineArray_append(&self->extends, extended)) {
    Ring2_jump();
  }
  Ring2_Gc_lock(extended);
  return true;
}

void Machine_InterfaceType_ensureInitialized(Machine_InterfaceType* self) {
  if (Ring2_TypeFlag_isSet((Machine_Type*)self, Ring2_TypeFlags_Initialized)) {
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
      Machine_InterfaceType* element = Ring1_InlineArray_getAt(&self->extends, i);
      Machine_InterfaceType_ensureInitialized(element);
    }
    Machine_InterfaceType_addFlag(self, Machine_InterfaceTypeFlags_PrerequisitesInitialized);
  }
  Ring2_TypeFlag_set((Machine_Type*)self, Ring2_TypeFlags_Initialized);
}
