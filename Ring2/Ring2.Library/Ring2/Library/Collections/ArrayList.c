// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/Collections/ArrayList.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/ArrayList.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE


#define RING2_LIBRARY_COLLECTIONS_PRIVATE (1)
#include "Ring2/Library/Collections/CollectionUtilities.h"
#undef RING2_LIBRARY_COLLECTIONS_PRIVATE
#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"


#include "Ring2/Library/Collections/ArrayList.decls.i"

MACHINE_DEFINE_CLASSTYPE(Ring2_Collections_ArrayList /*type*/,
                         Machine_Object /*parentType*/,
                         &Ring2_Collections_ArrayList_visit /*visit*/,
                         &Ring2_Collections_ArrayList_construct /*construct*/,
                         &Ring2_Collections_ArrayList_destruct /*destruct*/,
                         NULL /*constructClasses*/,
                         &implementInterfaces /*implementInterfaces*/)

#include "Ring2/Library/Collections/ArrayList.defns.i"

void
Ring2_Collections_ArrayList_construct
  (
    Ring2_Collections_ArrayList *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->size = 0;
  self->capacity = MIN_CAPACITY;
  self->values = NULL;
  if (Ring1_Memory_allocateArray(&self->values, (size_t)self->capacity, sizeof(Ring2_Value))) {
    fprintf(stderr, "allocation failed");
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring2_Collections_ArrayList_getType());
}

Ring2_Collections_ArrayList*
Ring2_Collections_ArrayList_create
  (
  )
{
  Machine_ClassType* ty = Ring2_Collections_ArrayList_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Collections_ArrayList* self = (Ring2_Collections_ArrayList*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
