// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Nat/Add.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/Nat/Add.h"

#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>

static Ring1_NoDiscardResult() Ring1_Result
doAddition
  (
    Ring1_Test_Context *ctx,
    uint64_t x,
    uint64_t y,
    uint64_t z
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
    uint64_t t;
    r = Ring1_ApNat_toU64(&t, &a);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApNat_uninitialize(&b);
      Ring1_ApNat_uninitialize(&a);
      return r;
    }
    RING1_TEST_ASSERT_EQ(ctx, t, x);
  }
  {
    uint64_t t;
    r = Ring1_ApNat_toU64(&t, &b);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApNat_uninitialize(&b);
      Ring1_ApNat_uninitialize(&a);
      return r;
    }
    RING1_TEST_ASSERT_EQ(ctx, t, y);
  }
  {
    r = Ring1_ApNat_add(&a, &b);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApNat_uninitialize(&b);
      Ring1_ApNat_uninitialize(&a);
      return r;
    }
    {
      uint64_t t;
      r = Ring1_ApNat_toU64(&t, &a);
      RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
      if (r) {
        Ring1_ApNat_uninitialize(&b);
        Ring1_ApNat_uninitialize(&a);
        return r;
      }
      RING1_TEST_ASSERT_EQ(ctx, t, z);
    }
    Ring1_ApNat_uninitialize(&b);
    Ring1_ApNat_uninitialize(&a);
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
addition
  (
    Ring1_Test_Context *ctx
  )
{
  for (uint64_t i = 0, n = 1024; i < n; ++i) {
    for (uint64_t j = 0, n = 1024; j < n; ++j) {
      if (doAddition(ctx, i, j, i + j)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardResult() Ring1_Result
Ring1_Ap_Test_Nat_registerAddTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.addition", &addition)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
