// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Add.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_INTRINSIC_TEST_ADD_H_INCLUDED)
#define RING1_INTRINSIC_TEST_ADD_H_INCLUDED

#include "Ring1/Test.h"

Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_registerAddTests
  (
    Ring1_Test_Context* ctx
  );

#endif // RING1_INTRINSIC_TEST_ADD_H_INCLUDED
