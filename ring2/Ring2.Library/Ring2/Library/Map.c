// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Map.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Map.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#undef RING2_LIBRARY_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Machine_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Machine_Map, &addPrerequisites)

void Machine_Map_set(Machine_Map* self, Ring2_Value key, Ring2_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Map, set, , self, key, value);
}

Ring2_Value Machine_Map_get(Machine_Map const* self, Ring2_Value key) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Map, get, return, self, key);
}

Machine_List* Machine_Map_toList(Machine_Map const* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Map, toList, return, self);
}
