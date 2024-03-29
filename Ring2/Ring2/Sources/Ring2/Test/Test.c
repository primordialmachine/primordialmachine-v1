// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Test.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_PRIVATE (1)
#include "Ring2/Test/Test.h"
#undef RING2_PRIVATE


#include "Ring1/All/_Include.h"


static void
Ring2_Test_destruct
  (
    Ring2_Test* self
  );

static void
Ring2_Test_visit
  (
    Ring2_Test* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring2_Test,
                         Machine_Object,
                         &Ring2_Test_visit,
                         &Ring2_Test_construct,
                         &Ring2_Test_destruct,
                         NULL,
                         NULL)

static void
Ring2_Test_destruct
  (
    Ring2_Test* self
  )
{}

static void
Ring2_Test_visit
  (
    Ring2_Test* self
  )
{
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
}

void
Ring2_Test_construct
  (
    Ring2_Test *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->name = Ring2_Value_getString(&arguments[0]);
  self->procedure = Ring2_Value_getForeignProcedure(&arguments[1]);
  self->flags = RING2_TEST_FLAG_ISNOTEVALUATED;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring2_Test_getType());
}
  
Ring2_Test *
Ring2_Test_create
  (
    Ring2_String *name,
    Ring2_ForeignProcedure *procedure
  )
{
  Machine_Type* ty = Ring2_Test_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setString(&arguments[0], name);
  Ring2_Value_setForeignProcedure(&arguments[1], procedure);
  Ring2_Test* self = Ring1_cast(Ring2_Test*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
