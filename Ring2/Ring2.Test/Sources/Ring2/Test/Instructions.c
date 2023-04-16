// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Instructions.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring2/Test/Instructions.h"

#include "Ring2/Test/Instructions/Relational.h"
#include "Ring2/Test/Instructions/Arithmetic.h"
#include "Ring2/Test/Instructions/Logical.h"
#include "Ring2/Test/Common.h"

void
Ring2_Test_registerInstructionTests
  (
    Ring2_Tests* tests
  )
{
  Ring2_Test_Instructions_registerLogicalTests(tests);
  Ring2_Test_Instructions_registerArithmeticTests(tests);
  Ring2_Test_Instructions_registerRelationalTests(tests);
}
