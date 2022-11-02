// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Ap/Test/ApIntTests.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Ap/Test/ApIntTests.h"


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
  Ring1_ApInt x;
  r = Ring1_ApInt_initialize_u64(&x, v, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return;
  }
  Ring1_ApInt_uninitialize(&x);
}

static Ring1_CheckReturn() Ring1_Result
ApIntTestConversion
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

static Ring1_NoDiscardResult() Ring1_Result
doTestAddition
  (
    Ring1_Test_Context *ctx,
    int64_t x,
    int64_t y,
    int64_t z, // ignored if underflow is true
    bool overflow
  )
{
  Ring1_Result r;
  Ring1_ApInt a, b;

  r = Ring1_ApInt_initialize_s64(&a, x, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    return r;
  }

  r = Ring1_ApInt_initialize_s64(&b, y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  if (r) {
    Ring1_ApInt_uninitialize(&a);
    return r;
  }

  {
    int64_t t;
    r = Ring1_ApInt_toS64(&t, &a);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApInt_uninitialize(&b);
      Ring1_ApInt_uninitialize(&a);
      return r;
    }
    RING1_TEST_ASSERT_EQ(ctx, t, x);
  }
  {
    int64_t t;
    r = Ring1_ApInt_toS64(&t, &b);
    RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
    if (r) {
      Ring1_ApInt_uninitialize(&b);
      Ring1_ApInt_uninitialize(&a);
      return r;
    }
    RING1_TEST_ASSERT_EQ(ctx, t, y);
  }
  {
    r = Ring1_ApInt_add(&a, &b);
    if (overflow) {
      RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
      RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
      Ring1_Status_set(Ring1_Status_Success);
    } else {
      if (r) {
        Ring1_ApInt_uninitialize(&b);
        Ring1_ApInt_uninitialize(&a);
        return r;
      }
    }
    {
      uint64_t t;
      r = Ring1_ApInt_toS64(&t, &a);
      RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
      if (r) {
        Ring1_ApInt_uninitialize(&b);
        Ring1_ApInt_uninitialize(&a);
        return r;
      }
      RING1_TEST_ASSERT_EQ(ctx, t, z);
    }
    Ring1_ApInt_uninitialize(&b);
    Ring1_ApInt_uninitialize(&a);
  }
  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
ApIntTestAddition1
  (
    Ring1_Test_Context *ctx
  )
{
  int64_t pivot;
 
  //
  pivot = +20;
  for (int64_t i = pivot + 5, n = pivot - 5; i > n; --i) {
     for (int64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestAddition(ctx, i, j,  i + j, false)) {
        return Ring1_Result_Failure;
      }
    } 
  }
  for (int64_t i = pivot - 5, n = pivot + 5; i < n; ++i) {
    for (int64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestAddition(ctx, i, j,  i + j, false)) {
        return Ring1_Result_Failure;
      }
    }
  }

  //
  pivot = -20;
  for (int64_t i = pivot + 5, n = pivot - 5; i > n; --i) {
     for (int64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestAddition(ctx, i, j,  i + j, false)) {
        return Ring1_Result_Failure;
      }
    } 
  }
  for (int64_t i = pivot - 5, n = pivot + 5; i < n; ++i) {
    for (int64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestAddition(ctx, i, j,  i + j, false)) {
        return Ring1_Result_Failure;
      }
    }
  }

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
ApIntTestAddition2
  (
    Ring1_Test_Context *ctx
  )
{
  int64_t pivot;

  //
  pivot = 0;
  for (int64_t i = pivot + 5, n = pivot - 5; i > n; --i) {
     for (int64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestAddition(ctx, i, j,  i + j, false)) {
        return Ring1_Result_Failure;
      }
    } 
  }
  for (int64_t i = pivot - 5, n = pivot + 5; i < n; ++i) {
    for (int64_t j = pivot - 5, n = pivot + 5; j < n; ++j) {
      if (doTestAddition(ctx, i, j,  i + j, false)) {
        return Ring1_Result_Failure;
      }
    }
  }

  return Ring1_Result_Success;
}

Ring1_NoDiscardResult() Ring1_Result
Ring1_Ap_Test_registerApIntTests
  (
    Ring1_Test_Context* ctx
  )
{
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApIntTestConversion", &ApIntTestConversion)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApIntTestAddition1", &ApIntTestAddition1)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_Test_Context_addTest(ctx, "Ring1.Ap.Test.ApIntTestAddition2", &ApIntTestAddition2)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}
