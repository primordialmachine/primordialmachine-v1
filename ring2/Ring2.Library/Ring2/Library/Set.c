// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Set.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Set.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#undef RING2_LIBRARY_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring2_Set, &addPrerequisites)

void
Ring2_Set_add
  (
    Ring2_Set* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Set, add, , self, value); }

Ring2_Boolean
Ring2_Set_contains
  (
    Ring2_Set const* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Set, contains, return, self, value); }

void
Ring2_Set_remove
  (
    Ring2_Set* self,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Set, remove, , self, value); }

Ring2_List*
Ring2_Set_toList
  (
    Ring2_Set const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Set, toList, return, self); }
