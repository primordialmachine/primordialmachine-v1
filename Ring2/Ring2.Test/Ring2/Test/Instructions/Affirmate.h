// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Test/Instructions/Affirmate.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TEST_INSTRUCTIONS_AFFIRMATE_H_INCLUDED)
#define RING2_TEST_INSTRUCTIONS_AFFIRMATE_H_INCLUDED

#include "Ring2/Test/Common.h"

void
Ring2_Test_Instructions_registerAffirmateTests
  (
    Ring2_Tests* tests
  );

void
Ring2_Test_Instructions_Affirmate_runAll
  (
    Ring2_Context* context
  );

#endif // RING2_TEST_INSTRUCTIONS_AFFIRMATE_H_INCLUDED
