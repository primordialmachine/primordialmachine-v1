// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Nat/Compare.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/Nat/Compare.h"

#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>

static Ring1_NoDiscardReturn() Ring1_Result
doCompare
  (
    Ring1_Test_Context* ctx,
    uint64_t x,
    uint64_t y,
    int64_t expected
  )
{
  Ring1_Result r;
  Ring1_ApNat a, b;

  r = Ring1_ApNat_initialize_u64(&a, x, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }

  r = Ring1_ApNat_initialize_u64(&b, y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    Ring1_ApNat_uninitialize(&a);
    return r;
  }

  {
    int64_t received;
    r = Ring1_ApNat_compare(&received, &a, &b);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApNat_uninitialize(&b);
      Ring1_ApNat_uninitialize(&a);
      return r;
    }
    RING1_TEST_ASSERT_EQ(ctx, received, expected);
  }

  Ring1_ApNat_uninitialize(&b);
  Ring1_ApNat_uninitialize(&a);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
compare
  (
    Ring1_Test_Context* ctx
  )
{
  // Overlapping intervals
  // [N-64, N + 1024]
  // [N-1024, N + 64]
  for (uint64_t i = (UINT64_MAX / 2) - 64, n = (UINT64_MAX / 2) + 1024; i < n; ++i) {
    for (uint64_t j = (UINT64_MAX / 2) - 1024, m = (UINT64_MAX / 2) + 64; j < m; ++j) {
      int64_t expected = 0;
      if (i < j) {
        expected = -1;
      }
      else if (i > j) {
        expected = +1;
      }
      if (doCompare(ctx, i, j, expected)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_Nat_registerCompareTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.compare", &compare)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
