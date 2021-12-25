/// @file Collection/List.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/List.h"

#include "Collections/Collection.h"

static void addPrerequisites(Machine_InterfaceType* self){
  Machine_InterfaceType_extend(self, (Machine_Type *)Machine_Collection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Machine_List, &addPrerequisites)

Machine_Value Machine_List_getAt(Machine_List const* self, size_t index) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, getAt, return, self, index);
}

void Machine_List_prepend(Machine_List* self, Machine_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, prepend, , self, value);
}

void Machine_List_append(Machine_List* self, Machine_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, append, , self, value);
}

void Machine_List_insertAt(Machine_List* self, size_t index, Machine_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, insertAt, , self, index, value);
}

void Machine_List_removeAt(Machine_List* self, size_t index) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, removeAt, , self, index);
}

void Machine_List_removeAtFast(Machine_List* self, size_t index) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, removeAtFast, , self, index);
}

#if defined(Machine_List_withReverse) && Machine_List_withReverse == 1

void Machine_List_reverse(Machine_List* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, reverse, , self);
}

#endif

#if defined(Machine_List_withSlice) && Machine_List_withSlice == 1

Machine_List* Machine_List_slice(Machine_List* self, size_t start, size_t length) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_List, slice, return, self, start, length);
}

#endif
