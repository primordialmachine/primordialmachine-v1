// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/ArrayStack.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com).

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/ArrayStack.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/CollectionUtilities.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE
#include "Ring1/Intrinsic.h"
#include "Ring2/Library/_Include.h"


#include "Ring2/Library/Collections/ArrayStack.decls.i"

MACHINE_DEFINE_CLASSTYPE(Ring2_Collections_ArrayStack /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring2_Collections_ArrayStack_visit /*visit*/,
                         &Ring2_Collections_ArrayStack_construct /*construct*/,
                         &Ring2_Collections_ArrayStack_destruct /*destruct*/,
                         NULL /*constructClass*/,
                         &implementInterfaces /*implementInterfaces*/)

#include "Ring2/Library/Collections/ArrayStack.defns.i"

void
Ring2_Collections_ArrayStack_construct
  (
    Ring2_Collections_ArrayStack *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = MIN_CAPACITY;
  self->values = NULL;
  if (Ring1_Memory_allocateArray(&self->values, (size_t)self->capacity, sizeof(Ring2_Value))) {
    fprintf(stderr, "allocation failed");
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_Collections_ArrayStack_getType());
}

Ring2_Collections_ArrayStack*
Ring2_Collections_ArrayStack_create
  (
  )
{
  Machine_ClassType* ty = Ring2_Collections_ArrayStack_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Collections_ArrayStack* self = (Ring2_Collections_ArrayStack*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
