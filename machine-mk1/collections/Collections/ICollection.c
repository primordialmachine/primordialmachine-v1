/// @file Collection/ICollection.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/ICollection.h"

MACHINE_DEFINE_INTERFACETYPE(Machine_ICollection, NULL)

void Machine_ICollection_clear(Machine_ICollection* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_ICollection, clear, , self);
}

size_t Machine_ICollection_getSize(Machine_ICollection const* self) {
  MACHINE_VIRTUALIFACECALL_IMPL(Machine_ICollection, getSize, return, self);
}
