/// @file Collections/Collection.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/Collection.h"



MACHINE_DEFINE_CLASSTYPE(Machine_Collection, Machine_Object, NULL, &Machine_Collection_construct, NULL, NULL)

void Machine_Collection_construct(Machine_Collection* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Machine_Collection_getType());
}

void Machine_Collection_clear(Machine_Collection* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Collection, clear);
}

size_t Machine_Collection_getSize(const Machine_Collection* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Collection, getSize);
}
