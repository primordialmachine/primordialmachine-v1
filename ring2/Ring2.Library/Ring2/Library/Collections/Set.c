// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Set.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Set.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collections_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring2_Collections_Set, &addPrerequisites)

void
Ring2_Collections_Set_add
  (
    Ring2_Collections_Set* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Set, add, , self, value); }

Ring2_Boolean
Ring2_Collections_Set_contains
  (
    Ring2_Collections_Set const* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Set, contains, return, self, value); }

void
Ring2_Collections_Set_remove
  (
    Ring2_Collections_Set* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Set, remove, , self, value); }

Ring2_Collections_List*
Ring2_Collections_Set_toList
  (
    Ring2_Collections_Set const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Set, toList, return, self); }
