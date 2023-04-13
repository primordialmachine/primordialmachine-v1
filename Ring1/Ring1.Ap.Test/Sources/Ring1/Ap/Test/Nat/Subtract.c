// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Nat/Subtract.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/Nat/Subtract.h"

#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>

static Ring1_NoDiscardReturn() Ring1_Result
doSubtraction
  (
    Ring1_Test_Context *ctx,
    uint64_t x,
    uint64_t y,
    uint64_t z, // ignored if overflow is true
    bool overflow
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
    r = Ring1_ApNat_subtract(&a, &b);
    if (overflow) {
      RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
      RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
      Ring1_Status_set(Ring1_Status_Success);
    } else {
      if (r) {
        Ring1_ApNat_uninitialize(&b);
        Ring1_ApNat_uninitialize(&a);
        return r;
      }
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

static Ring1_NoDiscardReturn() Ring1_Result
subtract
  (
    Ring1_Test_Context *ctx
  )
{
  uint64_t pivot = 20;
  for (uint64_t i = pivot + 5, n = pivot - 5; i > n; --i) {
     for (uint64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doSubtraction(ctx, i, j,  (i >= j) ? (i - j) : i, (i >= j) ? false : true)) {
        return Ring1_Result_Failure;
      }
    } 
  }
  for (uint64_t i = pivot - 5, n = pivot + 5; i < n; ++i) {
    for (uint64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doSubtraction(ctx, i, j,  (i >= j) ? (i - j) : i, (i >= j) ? false : true)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_Nat_registerSubtractTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.subtract", &subtract)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
