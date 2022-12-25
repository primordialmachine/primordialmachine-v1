// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Fixtures/Object.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Fixtures/Object.h"

#include "Ring1/All/_Include.h"
#include "Ring2/_Include.h"

MACHINE_DEFINE_CLASSTYPE(Ring2_Test_Fixtures_A /*type*/,
                         Machine_Object /*parentType*/,
                         NULL /*visit*/,
                         &Ring2_Test_Fixtures_A_construct /*construct*/,
                         NULL /*destruct*/,
                         NULL /*constructClass*/,
                         NULL /*implementInterfaces*/)

void
Ring2_Test_Fixtures_A_construct
  (
    Ring2_Test_Fixtures_A *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring2_Test_Fixtures_A_getType());
}

Ring2_Test_Fixtures_A*
Ring2_Test_Fixtures_A_create
  (
  )
{
  Machine_ClassType* ty = Ring2_Test_Fixtures_A_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  Ring2_Value ARGUMENTS[1] = { Ring2_Value_StaticInitializerVoid() };
  Ring2_Test_Fixtures_A* self = (Ring2_Test_Fixtures_A*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
