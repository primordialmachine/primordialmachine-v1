// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/ApRealTests.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/ApRealTests.h"


#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>


static void
doTestConversion_u64
  (
    Ring1_Test_Context *ctx,
    uint64_t v
  )
{
  Ring1_Result r;
  Ring1_ApReal x;
  r = Ring1_ApReal_initialize_u64(&x, v, 0, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return;
  }
  Ring1_ApReal_uninitialize(&x);
}

static void
doTestConversion_s64
  (
    Ring1_Test_Context *ctx,
    int64_t v
  )
{
  Ring1_Result r;
  Ring1_ApReal x;
  r = Ring1_ApReal_initialize_s64(&x, v, 0, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return;
  }
  Ring1_ApReal_uninitialize(&x);
}

static Ring1_CheckReturn() Ring1_Result
ApRealTestConversionNatural
  (
    Ring1_Test_Context *ctx
  )
{
  for (uint64_t i = 0, n = 1024; i < n; ++i) {
    doTestConversion_u64(ctx, i);
  }
  for (uint64_t i = UINT64_MAX - 1024, n = UINT64_MAX; i < n; ++i) {
    doTestConversion_u64(ctx, i);
  }
  return Ring1_Result_Success;
}

static Ring1_CheckReturn() Ring1_Result
ApRealTestConversionInteger
  (
    Ring1_Test_Context *ctx
  )
{
  for (int64_t i = INT64_MAX - 1024, n = INT64_MAX; i < n; ++i) {
    doTestConversion_s64(ctx, i);
  }
  for (int64_t i = INT64_MIN + 1024, n = INT64_MIN; i > n; --i) {
    doTestConversion_s64(ctx, i);
  }
  return Ring1_Result_Success;
}

static Ring1_CheckReturn() Ring1_Result
ApRealTestConversionReal
  (
    Ring1_Test_Context *ctx
  )
{
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_registerApRealTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApRealTestConversion.Natural", &ApRealTestConversionNatural)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApRealTestConversion.Integer", &ApRealTestConversionInteger)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApRealTestConversion.Real", &ApRealTestConversionReal)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
