// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/ApNatTests.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/ApNatTests.h"


#include "Ring1/Ap/_Include.h"
#include "Ring1/Status.h"
#include <stdio.h>


static Ring1_NoDiscardResult() Ring1_Result
doTestConversion
  (
    Ring1_Test_Context *ctx,
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

static Ring1_NoDiscardResult() Ring1_Result
ApNatTestConversion
  (
    Ring1_Test_Context *ctx
  )
{
  for (uint64_t i = 0, n = 1024; i < n; ++i) {
    if (doTestConversion(ctx, i)) {
      return Ring1_Result_Failure;
    }
  }
  for(uint64_t i = UINT64_MAX - 1024, n = UINT64_MAX; i < n; ++i) {
    if (doTestConversion(ctx, i)) {
      return Ring1_Result_Failure;
    }
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
doTestAddition
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
ApNatTestAddition
  (
    Ring1_Test_Context *ctx
  )
{
  for (uint64_t i = 0, n = 1024; i < n; ++i) {
    for (uint64_t j = 0, n = 1024; j < n; ++j) {
      if (doTestAddition(ctx, i, j, i + j)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
doTestCompare
  (
    Ring1_Test_Context *ctx,
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

static Ring1_NoDiscardResult() Ring1_Result
ApNatTestCompare
  (
    Ring1_Test_Context *ctx
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
      } else if (i > j) {
        expected = +1;
      }
      if (doTestCompare(ctx, i, j, expected)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
doTestSubtraction
  (
    Ring1_Test_Context *ctx,
    uint64_t x,
    uint64_t y,
    uint64_t z, // ignored if underflow is true
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

static Ring1_NoDiscardResult() Ring1_Result
ApNatTestSubtraction
  (
    Ring1_Test_Context *ctx
  )
{
  uint64_t pivot = 20;
  for (uint64_t i = pivot + 5, n = pivot - 5; i > n; --i) {
     for (uint64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestSubtraction(ctx, i, j,  (i >= j) ? (i - j) : i, (i >= j) ? false : true)) {
        return Ring1_Result_Failure;
      }
    } 
  }
  for (uint64_t i = pivot - 5, n = pivot + 5; i < n; ++i) {
    for (uint64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestSubtraction(ctx, i, j,  (i >= j) ? (i - j) : i, (i >= j) ? false : true)) {
        return Ring1_Result_Failure;
      }
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardResult() Ring1_Result
Ring1_Ap_Test_registerApNatTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApNatTestConversion", &ApNatTestConversion)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApNatTestAddition", &ApNatTestAddition)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApNatTestCompare", &ApNatTestCompare)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApNatTestSubtraction", &ApNatTestSubtraction)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
