// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/Pair.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/Pair.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#include "Ring1/All/_Include.h"


MACHINE_DEFINE_CLASSTYPE(Ring2_Collections_Pair /*type*/,
                         Machine_Object /*parentType*/,
                         NULL /*visit*/,
                         &Ring2_Collections_Pair_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClasses*/,
                         NULL /*implementInterfaces*/)

void
Ring2_Collections_Pair_construct
  (
    Ring2_Collections_Pair* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Ring2_assert(numberOfArguments == 2, Ring1_Status_InvalidNumberOfArguments);
  self->first = arguments[0];
  self->second = arguments[1];
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring2_Collections_Pair_getType());
}

Ring2_Collections_Pair* Ring2_Collections_Pair_create(Ring2_Value first, Ring2_Value second) {
  Machine_Type* ty = Ring2_Collections_Pair_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[] = { first, second };
  Ring2_Collections_Pair* self = Ring1_cast(Ring2_Collections_Pair*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring2_Value Ring2_Collections_Pair_get(Ring2_Collections_Pair* self, Ring2_Integer index) {
  Ring2_assert(index == 0 || index == 1, Ring1_Status_IndexOutOfBounds);
  if (index == 0) {
    return self->first;
  } else {
    return self->second;
  }
}
