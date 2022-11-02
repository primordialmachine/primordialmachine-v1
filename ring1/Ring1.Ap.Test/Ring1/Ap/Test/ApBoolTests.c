// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/ApBoolTests.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/ApBoolTests.h"


#include "Ring1/Ap/_Include.h"
#include <stdio.h>


static Ring1_NoDiscardResult() Ring1_Result
ApBoolTest1
  (
    Ring1_Test_Context *ctx
  )
{
  Ring1_Result r;
  Ring1_ApBool x;

  //
  r = Ring1_ApBool_initialize_bool(&x, false);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return Ring1_Result_Failure;
  }
  Ring1_ApBool_uninitialize(&x);

  //
  r = Ring1_ApBool_initialize_bool(&x, true);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return Ring1_Result_Failure;
  }
  Ring1_ApBool_uninitialize(&x);
  return Ring1_Result_Success;
}

Ring1_NoDiscardResult() Ring1_Result
Ring1_Ap_Test_registerApBoolTests
  (
    Ring1_Test_Context* ctx
  )
{ return Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApBoolTest1", &ApBoolTest1); }
