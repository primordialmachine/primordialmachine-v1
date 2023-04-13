// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/IsPowerOfTwo.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/IsPowerOfTwo.h"

#include "Ring1/Intrinsic/_Include.h"
#include <inttypes.h>
#include "Ring1/Status.h"

#define Define(SUFFIX, VALUE, EXPECTED) \
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success); \
  r = Ring1_Intrinsic_isPowerOfTwo_##SUFFIX(&result, VALUE); \
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success); \
  RING1_TEST_ASSERT_EQ(ctx, result, EXPECTED);

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_s8
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(s8, 0, false);
  // Case of x = 1.
  Define(s8, 1, true);
  // Case of x = 2.
  Define(s8, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_u8
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(u8, 0, false);
  // Case of x = 1.
  Define(u8, 1, true);
  // Case of x = 2.
  Define(u8, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_s16
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(s16, 0, false);
  // Case of x = 1.
  Define(s16, 1, true);
  // Case of x = 2.
  Define(s16, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_u16
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(u16, 0, false);
  // Case of x = 1.
  Define(u16, 1, true);
  // Case of x = 2.
  Define(u16, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_s32
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(s32, 0, false);
  // Case of x = 1.
  Define(s32, 1, true);
  // Case of x = 2.
  Define(s32, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_u32
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(u32, 0, false);
  // Case of x = 1.
  Define(u32, 1, true);
  // Case of x = 2.
  Define(u32, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_s64
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(s64, 0, false);
  // Case of x = 1.
  Define(s64, 1, true);
  // Case of x = 2.
  Define(s64, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_u64
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(u64, 0, false);
  // Case of x = 1.
  Define(u64, 1, true);
  // Case of x = 2.
  Define(u64, 2, true);
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_isPowerOfTwo_sz
  (
    Ring1_Test_Context* ctx
  )
{
  bool result;
  Ring1_Result r;
  // Case of x = 0.
  Define(sz, 0, false);
  // Case of x = 1.
  Define(sz, 1, true);
  // Case of x = 2.
  Define(sz, 2, true);
  return Ring1_Result_Success;
}

#undef Define

Ring1_Result
Ring1_Intrinsic_Test_registerIsPowerOfTwoTests
  (
    Ring1_Test_Context* ctx
  )
{
  return
       Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[s8]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_s8)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[u8]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_u8)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[s16]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_s16)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[u16]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_u16)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[s32]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_s32)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[u32]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_u32)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[s64]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_s64)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[u64]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_u64) 
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.isPowerOfTwo[sz]",
                                  &Ring1_Intrinsic_Test_isPowerOfTwo_sz)
    ;
}
