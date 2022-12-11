// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/ApIntTest.h
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING1_AP_TEST_APINTTESTS_H_INCLUDED)
#define RING1_AP_TEST_APINTTESTS_H_INCLUDED

#include "Ring1/Test.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_registerApIntTests
  (
    Ring1_Test_Context *ctx
  );

#endif // RING1_AP_TEST_APINTTESTS_H_INCLUDED
