/// @file Runtime/Enumeration/EnumerationType.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Enumeration/EnumerationType.h"

#include "Runtime/Enumeration/EnumerationType.module.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/Type.module.h"

static void Machine_EnumerationType_finalize(Machine_EnumerationType* self) {
  _Type_finalize((Machine_Type*)self);
}

static void Machine_EnumerationType_visit(Machine_EnumerationType* self) {
  _Type_visit((Machine_Type*)self);
}

Machine_EnumerationType* Machine_createEnumerationType(Machine_CreateEnumerationTypeArgs* args) {
  Machine_Gc_AllocationArguments const allocationArguments = {
    .prefixSize = 0,
    .suffixSize = sizeof(Machine_EnumerationType),
    .visit = (Machine_Gc_VisitCallback*)Machine_EnumerationType_visit,
    .finalize = (Machine_Gc_FinalizeCallback*)&Machine_EnumerationType_finalize,
  };
  Machine_EnumerationType* enumerationType = Machine_Gc_allocate(&allocationArguments);
  if (!enumerationType) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  ((Machine_Type*)enumerationType)->flags = Machine_TypeFlags_Enumeration;
  ((Machine_Type*)enumerationType)->typeRemoved = args->createTypeArgs.typeRemoved;
  ((Machine_Type*)enumerationType)->children.elements
      = Machine_Eal_Memory_allocateArray(sizeof(Machine_Type*), 0);
  ((Machine_Type*)enumerationType)->children.size = 0;
  return enumerationType;
}

void Machine_EnumerationType_ensureInitialized(Machine_EnumerationType* self) {
  if (_TypeFlag_isSet((Machine_Type*)self, Machine_TypeFlags_Initialized)) {
    return;
  }
  _TypeFlag_set((Machine_Type*)self, Machine_TypeFlags_Initialized);
}
