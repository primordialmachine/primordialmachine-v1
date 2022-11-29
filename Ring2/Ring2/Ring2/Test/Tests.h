// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Tests.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TESTS_H_INCLUDED)
#define RING2_TESTS_H_INCLUDED

#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Test/Tests.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/TypeSystem/ClassType.h"
#include "Ring2/Types/Value.h"

MACHINE_DECLARE_CLASSTYPE(Ring2_Tests)

struct Ring2_Tests_Class {
  Machine_Object_Class _parent;
};

typedef struct Ring2_Test Ring2_Test;

struct Ring2_Tests {
  Machine_Object _parent;
  Ring2_Test** elements;
  size_t size, capacity;
};

void
Ring2_Tests_construct
  (
    Ring2_Tests *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );
  
Ring2_Tests *
Ring2_Tests_create
  (
  );
  
void
Ring2_Tests_addTest
  (
    Ring2_Tests *self,
    Ring2_String *name,
    Ring2_ForeignProcedure *procedure
  );

void
Ring2_Tests_run
  (
    Ring2_Tests *self
  );

#endif // RING2_TESTS_INCLUDED
