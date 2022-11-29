// Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Deque.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Deque.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Collection.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Ring2_Collections_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Ring2_Collections_Deque, &addPrerequisites)

Ring2_Value Ring2_Collections_Deque_popFront(Ring2_Collections_Deque* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Deque, popFront, return, self);
}

void Ring2_Collections_Deque_pushFront(Ring2_Collections_Deque* self, Ring2_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Deque, pushFront, , self, value);
}

Ring2_Value Ring2_Collections_Deque_popBack(Ring2_Collections_Deque* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Deque, popBack, return, self);
}

void Ring2_Collections_Deque_pushBack(Ring2_Collections_Deque* self, Ring2_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Ring2_Collections_Deque, pushBack, , self, value);
}
