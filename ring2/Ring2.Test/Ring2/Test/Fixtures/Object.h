// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Fixtures/Object.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TEST_FIXTURES_OBJECT_H_INCLUDED)
#define RING2_TEST_FIXTURES_OBJECT_H_INCLUDED

#include "Ring2/_Include.h"

MACHINE_DECLARE_CLASSTYPE(Ring2_Test_Fixtures_A)

struct Ring2_Test_Fixtures_A_Class {
  Machine_Object_Class _parent;
};

struct Ring2_Test_Fixtures_A {
  Machine_Object _parent;
};

void
Ring2_Test_Fixtures_A_construct
  (
    Ring2_Test_Fixtures_A *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

Ring2_Test_Fixtures_A*
Ring2_Test_Fixtures_A_create
  (
  );

#endif // RING2_TEST_FIXTURES_OBJECT_H_INCLUDED
