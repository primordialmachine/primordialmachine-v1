/// @file Collection/IList.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/IList.h"

static void addPrerequisites(Machine_InterfaceType* self){
  Machine_InterfaceType_extend(self, (Machine_Type *)Machine_ICollection_getType());
}

MACHINE_DEFINE_INTERFACETYPE(Machine_IList, &addPrerequisites)

Machine_Value Machine_IList_getAt(Machine_IList const* self, size_t index) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, getAt, return, self, index);
}

void Machine_IList_prepend(Machine_IList* self, Machine_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, prepend, , self, value);
}

void Machine_IList_append(Machine_IList* self, Machine_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, append, , self, value);
}

void Machine_IList_insertAt(Machine_IList* self, size_t index, Machine_Value value) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, insertAt, , self, index, value);
}

void Machine_IList_removeAt(Machine_IList* self, size_t index) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, removeAt, , self, index);
}

void Machine_IList_removeAtFast(Machine_IList* self, size_t index) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, removeAtFast, , self, index);
}

#if defined(Machine_IList_withReverse) && Machine_IList_withReverse == 1

void Machine_IList_reverse(Machine_IList* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, reverse, , self);
}

#endif

#if defined(Machine_IList_withSlice) && Machine_IList_withSlice == 1

Machine_IList* Machine_IList_slice(Machine_IList* self, size_t start, size_t length) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_IList, slice, return, self, start, length);
}

#endif
