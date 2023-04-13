// Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/Nat/Subtract.c
/// @copyright Copyright (c) 2022-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/Nat/Power.h"

#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>

static Ring1_Result checkIsEq(Ring1_Test_Context* ctx, Ring1_ApNat* a, uint64_t x) {
  uint64_t t;
  Ring1_Result r = Ring1_ApNat_toU64(&t, a);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  RING1_TEST_ASSERT_EQ(ctx, t, x);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
doSet
  (
    Ring1_Test_Context* ctx,
    uint64_t x
  )
{
  Ring1_Result r;
  Ring1_ApNat a, b;

  // Initialize a to x.
  r = Ring1_ApNat_initialize_u64(&a, x, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  {
    if (checkIsEq(ctx, &a, x)) {
      Ring1_ApNat_uninitialize(&a);
      return Ring1_Result_Failure;
    }
  }
  // Initialize b to 0.
  r = Ring1_ApNat_initialize_u64(&b, 0, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }
  {
    if (checkIsEq(ctx, &b, 0)) {
      Ring1_ApNat_uninitialize(&b);
      Ring1_ApNat_uninitialize(&a);
      return Ring1_Result_Failure;
    }
  }
  // Set b to x.
  if (Ring1_ApNat_set_u64(&b, x, b.numberOfDigits)) {
    Ring1_ApNat_uninitialize(&b);
    Ring1_ApNat_uninitialize(&a);
    return Ring1_Result_Failure;
  }
  if (checkIsEq(ctx, &b, x)) {
    Ring1_ApNat_uninitialize(&b);
    Ring1_ApNat_uninitialize(&a);
    return Ring1_Result_Failure;
  }
  Ring1_ApNat_uninitialize(&b);
  Ring1_ApNat_uninitialize(&a);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
set
  (
    Ring1_Test_Context* ctx
  )
{
  // 0
  if (doSet(ctx, 0)) {
    return Ring1_Result_Failure;
  }
  // 1
  if (doSet(ctx, 1)) {
    return Ring1_Result_Failure;
  }
  // UINT64_MAX
  if (doSet(ctx, UINT64_MAX)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_Nat_registerSetTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.set", &set)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
