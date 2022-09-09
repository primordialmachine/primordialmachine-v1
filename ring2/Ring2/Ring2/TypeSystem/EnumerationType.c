// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/EnumerationType.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/TypeSystem/EnumerationType.h"

#include "Ring2/Gc.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Types/Object.h"
#include "Ring1/Status.h"

static void Machine_EnumerationType_finalize(Ring2_Gc *gc, Machine_EnumerationType* self) {
  Ring2_Type_finalize((Machine_Type*)self);
}

static void Machine_EnumerationType_visit(Ring2_Gc *gc, Machine_EnumerationType* self) {
  Ring2_Type_visit((Machine_Type*)self);
}

Machine_EnumerationType* Machine_createEnumerationType(Machine_CreateEnumerationTypeArgs* args) {
  static Ring2_Gc_Type const gcType = {
    .finalize = (Ring2_Gc_FinalizeCallback*)&Machine_EnumerationType_finalize,
    .visit = (Ring2_Gc_VisitCallback*)Machine_EnumerationType_visit,
  };
  Machine_EnumerationType* enumerationType = Ring2_ObjectModule_allocate(Ring2_Gc_get(), sizeof(Machine_EnumerationType), &gcType);
  if (!enumerationType) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    Ring2_jump();
  }
  ((Machine_Type*)enumerationType)->flags = Ring2_TypeFlags_Enumeration;
  ((Machine_Type*)enumerationType)->typeRemoved = args->createTypeArgs.typeRemoved;
  ((Machine_Type*)enumerationType)->children.elements = NULL;
  if (Ring1_Memory_allocateArray((void **)&(((Machine_Type*)enumerationType)->children.elements), 0,
                                 sizeof(Machine_Type*))) {
    Ring2_jump(); 
  }
  ((Machine_Type*)enumerationType)->children.size = 0;
  return enumerationType;
}

void Machine_EnumerationType_ensureInitialized(Machine_EnumerationType* self) {
  if (Ring2_TypeFlag_isSet((Machine_Type*)self, Ring2_TypeFlags_Initialized)) {
    return;
  }
  Ring2_TypeFlag_set((Machine_Type*)self, Ring2_TypeFlags_Initialized);
}
