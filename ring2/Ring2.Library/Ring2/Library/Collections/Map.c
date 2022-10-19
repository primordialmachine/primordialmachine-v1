// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Map.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Map.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collections_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring2_Collections_Map, &addPrerequisites)

Ring2_Value
Ring2_Collections_Map_get
  (
    Ring2_Collections_Map const* self,
    Ring2_Value key
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Map, get, return, self, key); }

void
Ring2_Collections_Map_remove
  (
    Ring2_Collections_Map* self,
    Ring2_Value key
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Map,remove, , self, key); }

void
Ring2_Collections_Map_set
  (
    Ring2_Collections_Map* self,
    Ring2_Value key,
    Ring2_Value value
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Map, set, , self, key, value); }

Ring2_Collections_List*
Ring2_Collections_Map_toList
  (
    Ring2_Collections_Map const* self
  )
{ MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Map, toList, return, self); }
