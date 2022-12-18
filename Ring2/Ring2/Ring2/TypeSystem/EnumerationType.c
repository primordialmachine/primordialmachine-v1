// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/TypeSystem/EnumerationType.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/TypeSystem/EnumerationType.h"
#undef RING2_PRIVATE


#include "Ring1/All/_Include.h"
#define RING2_PRIVATE (1)
#include "Ring2/JumpTarget.h"
#include "Ring2/TypeSystem.h"
#undef RING2_PRIVATE


static void Machine_EnumerationType_finalize(Ring2_Gc *gc, Machine_EnumerationType* self) {
  Ring2_Type_finalize((Machine_Type*)self);
}

static void Machine_EnumerationType_visit(Ring2_Gc *gc, Machine_EnumerationType* self) {
  Ring2_Type_visit((Machine_Type*)self);
}

Machine_EnumerationType* Machine_createEnumerationType(Machine_CreateEnumerationTypeArgs* args) {
  static const Ring2_Gc_Type TYPE = {
    .finalize = &Machine_EnumerationType_finalize,
    .visit = &Machine_EnumerationType_visit,
  };
  Machine_EnumerationType* enumerationType = (Machine_EnumerationType *)Ring2_Type_allocate(sizeof(Machine_EnumerationType), 
                                                                                            &TYPE);
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
