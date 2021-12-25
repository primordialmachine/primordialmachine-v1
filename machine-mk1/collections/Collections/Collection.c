/// @file Collection/Collection.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/Collection.h"

MACHINE_DEFINE_INTERFACETYPE(Machine_Collection, NULL)

void Machine_Collection_clear(Machine_Collection* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Collection, clear, , self);
}

size_t Machine_Collection_getSize(Machine_Collection const* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_Collection, getSize, return, self);
}
