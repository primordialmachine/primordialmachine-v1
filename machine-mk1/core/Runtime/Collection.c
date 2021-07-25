/// @file Runtime/Collection.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Collection.h"

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Collection, Machine_Object, NULL, &Machine_Collection_construct, NULL)

static void Machine_Collection_constructClass(Machine_Collection_Class *self)
{/*Intentionally empty.*/}

void Machine_Collection_construct(Machine_Collection* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_Collection_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_Collection_getClassType());
}

void Machine_Collection_clear(Machine_Collection* self) {
  MACHINE_ASSERT_NOTNULL(self);
  self->clear(self);
}

size_t Machine_Collection_getSize(const Machine_Collection* self) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->getSize(self);
}
