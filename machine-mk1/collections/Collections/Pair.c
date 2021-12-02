/// @file Collections/Pair.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_COLLECTIONS_PRIVATE (1)
#include "Collections/Pair.h"



MACHINE_DEFINE_CLASSTYPE(Machine_Pair, Machine_Object, NULL, &Machine_Pair_construct, NULL, NULL,
                         NULL)

void Machine_Pair_construct(Machine_Pair* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  MACHINE_ASSERT(numberOfArguments == 2, Machine_Status_InvalidNumberOfArguments);
  self->first = arguments[0];
  self->second = arguments[1];
  Machine_setClassType((Machine_Object*)self, Machine_Pair_getType());
}

Machine_Pair* Machine_Pair_create(Machine_Value first, Machine_Value second) {
  Machine_ClassType* ty = Machine_Pair_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[] = { first, second };
  Machine_Pair* self = (Machine_Pair*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Value Machine_Pair_get(Machine_Pair* self, Machine_Integer index) {
  MACHINE_ASSERT(index == 0 || index == 1, Machine_Status_IndexOutOfBounds);
  if (index == 0) {
    return self->first;
  } else {
    return self->second;
  }
}
