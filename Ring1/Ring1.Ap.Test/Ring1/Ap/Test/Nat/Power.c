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

/// Succeed
///  x^y == z
///  x^y overflows and overflow == true
/// Fail otherwise.
static Ring1_NoDiscardReturn() Ring1_Result
doPower
  (
    Ring1_Test_Context *ctx,
    uint64_t x,
    uint64_t y,
    uint64_t z, // ignored if overflow is true
    bool overflow
  )
{
  Ring1_Result r;
  Ring1_ApNat a;

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
  {
    r = Ring1_ApNat_power(&a, y);
    if (overflow) {
      RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
      RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
      Ring1_Status_set(Ring1_Status_Success);
    } else {
      if (r) {
        Ring1_ApNat_uninitialize(&a);
        return r;
      }
    }
    {
      if (checkIsEq(ctx, &a, z)) {
        Ring1_ApNat_uninitialize(&a);
        return Ring1_Result_Failure;
      }
    }
    Ring1_ApNat_uninitialize(&a);
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
power
  (
    Ring1_Test_Context *ctx
  )
{
  // x^0 = 1, x = 0
  if (doPower(ctx, 0, 0, 1, false)) {
    return Ring1_Result_Failure;
  }
  // x^0 = 1, x = 1
  if (doPower(ctx, 1, 0, 1, false)) {
    return Ring1_Result_Failure;
  }
  // x^0 = 1, x = UINT64_MAX
  if (doPower(ctx, UINT64_MAX, 0, 1, false)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Ap_Test_Nat_registerPowerTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.Nat.power", &power)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
