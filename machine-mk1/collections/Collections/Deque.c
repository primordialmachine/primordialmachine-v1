/// @file Collection/Deque.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/Deque.h"

#include "Collections/Collection.h"

static void addPrerequisites(Machine_InterfaceType* self) {
  Machine_InterfaceType_extend(self, (Machine_Type*)Machine_Collection_getType());
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
