// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Fixtures/ForeignProcedure.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TEST_FIXTURES_FOREIGNPROCEDURE_H_INCLUDED)
#define RING2_TEST_FIXTURES_FOREIGNPROCEDURE_H_INCLUDED

#include "Ring2/_Include.h"

void
Ring2_Test_Fixtures_a
  (
    Ring2_Context* ctx,
    Ring2_Value* result,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

#endif // RING2_TEST_FIXTURES_FOREIGNPROCEDURE_H_INCLUDED
