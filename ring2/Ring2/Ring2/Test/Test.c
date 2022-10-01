// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Test.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Test/Test.h"
#undef RING2_INTERNAL

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
  Machine_ClassType* ty = Ring2_Test_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[2] = { Ring2_Value_StaticInitializerVoid(),
                               Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setString(&ARGUMENTS[0], name);
  Ring2_Value_setForeignProcedure(&ARGUMENTS[1], procedure);
  Ring2_Test* self = (Ring2_Test *)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
