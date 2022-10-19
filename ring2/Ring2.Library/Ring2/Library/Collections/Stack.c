// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Stack.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Stack.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collections_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring2_Collections_Stack, &addPrerequisites)

Ring2_Value
Ring2_Collections_Stack_pop
  (
    Ring2_Collections_Stack* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Stack, pop, return, self); }

void
Ring2_Collections_Stack_push
  (
    Ring2_Collections_Stack* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Stack, push, , self, value); }
