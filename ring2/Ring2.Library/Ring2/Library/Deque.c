// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Deque.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Deque.h"
#undef RING2_LIBRARY_PRIVATE


#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Collection.h"
#undef RING2_LIBRARY_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Machine_Deque, &addPrerequisites)

Ring2_Value Machine_Deque_popFront(Machine_Deque* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Deque, popFront, return, self);
}

void Machine_Deque_pushFront(Machine_Deque* self, Ring2_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Deque, pushFront, , self, value);
}

Ring2_Value Machine_Deque_popBack(Machine_Deque* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Deque, popBack, return, self);
}

void Machine_Deque_pushBack(Machine_Deque* self, Ring2_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Deque, pushBack, , self, value);
}
