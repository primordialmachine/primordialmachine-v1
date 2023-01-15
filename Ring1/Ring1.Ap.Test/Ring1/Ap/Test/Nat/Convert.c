// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Nat/Convert.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/Nat/Convert.h"

#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>


static Ring1_NoDiscardReturn() Ring1_Result
doConversion
  (
    Ring1_Test_Context* ctx,
    uint64_t v
  )
{
  Ring1_Result r;

  Ring1_ApNat x;
  r = Ring1_ApNat_initialize_u64(&x, UINT64_MAX, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  uint64_t MAX = x.numberOfDigits;
  Ring1_ApNat_uninitialize(&x);

  for (int64_t i = 0, n = 256; i < n; ++i) {
    Ring1_ApNat x;
    r = Ring1_ApNat_initialize_u64(&x, v, MAX);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      return r;
    }
    uint64_t u;
    r = Ring1_ApNat_toU64(&u, &x);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApNat_uninitialize(&x);
      return r;
    }
    Ring1_ApNat_uninitialize(&x);
    RING1_TEST_ASSERT_EQ(ctx, u, v);
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
convert
  (
    Ring1_Test_Context* ctx
  )
{
  for (uint64_t i = 0, n = 1024; i < n; ++i) {
    if (doConversion(ctx, i)) {
      return Ring1_Result_Failure;
    }
  }
  for (uint64_t i = UINT64_MAX - 1024, n = UINT64_MAX; i < n; ++i) {
    if (doConversion(ctx, i)) {
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_Nat_registerConvertTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.convert", &convert)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
