// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Pair.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/Pair.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/Intrinsic.h"


MACHINE_DEFINE_CLASSTYPE(Machine_Pair, Machine_Object, NULL, &Machine_Pair_construct, NULL, NULL,
                         NULL)

void Machine_Pair_construct(Machine_Pair* self, size_t numberOfArguments,
                            Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Ring2_assert(numberOfArguments == 2, Ring1_Status_InvalidNumberOfArguments);
  self->first = arguments[0];
  self->second = arguments[1];
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Pair_getType());
}

Machine_Pair* Machine_Pair_create(Ring2_Value first, Ring2_Value second) {
  Machine_ClassType* ty = Machine_Pair_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[] = { first, second };
  Machine_Pair* self
      = (Machine_Pair*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring2_Value Machine_Pair_get(Machine_Pair* self, Ring2_Integer index) {
  Ring2_assert(index == 0 || index == 1, Ring1_Status_IndexOutOfBounds);
  if (index == 0) {
    return self->first;
  } else {
    return self->second;
  }
}
