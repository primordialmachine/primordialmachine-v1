// Copyright (c) 2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Nat/Subtract.c
/// @copyright Copyright (c) 2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/Nat/Subtract.h"

#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>

static Ring1_NoDiscardResult() Ring1_Result
doMultiply
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
    r = Ring1_ApNat_multiply(&a, &b);
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
      if (t != z) {
        fprintf(stdout, "%"PRIu64"!=%"PRIu64"\n", t, z);
      }
      RING1_TEST_ASSERT_EQ(ctx, t, z);
    }
    Ring1_ApNat_uninitialize(&b);
    Ring1_ApNat_uninitialize(&a);
  }
  return Ring1_Result_Success;
}

#include "Ring1/Intrinsic/_Include.h"

static Ring1_NoDiscardResult() Ring1_Result
multiply
  (
    Ring1_Test_Context *ctx
  )
{
  uint64_t pivot = 20;
  for (uint64_t i = pivot + 5, n = pivot - 5; i > n; --i) {
     for (uint64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      uint64_t k;
      if (Ring1_Intrinsic_multiply_u64(&k, i, j)) {
        return Ring1_Result_Failure;
      }
      if (doMultiply(ctx, i, j,  k)) {
        return Ring1_Result_Failure;
      }
    } 
  }
  for (uint64_t i = pivot - 5, n = pivot + 5; i < n; ++i) {
    for (uint64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      uint64_t k;
      if (Ring1_Intrinsic_multiply_u64(&k, i, j)) {
        return Ring1_Result_Failure;
      }
      if (doMultiply(ctx, i, j, k)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardResult() Ring1_Result
Ring1_Ap_Test_Nat_registerMultiplyTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.multiply", &multiply)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
