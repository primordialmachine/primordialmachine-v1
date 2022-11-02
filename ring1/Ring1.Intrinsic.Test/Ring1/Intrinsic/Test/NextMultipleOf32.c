// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/NextMultipleOf32.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/NextMultipleOf32.h"

#include "Ring1/Intrinsic/NextMultipleOf32/nextMultipleOf32.h"
#include <inttypes.h>
#include "Ring1/Status.h"

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf32_u8
  (
    Ring1_Test_Context* ctx
  )
{
  uint8_t y;
  Ring1_Result r;

  r = Ring1_Intrinsic_nextMultipleOf32_u8(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  r = Ring1_Intrinsic_nextMultipleOf32_u8(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u8(&y, 31);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u8(&y, 32);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf32_u16
  (
    Ring1_Test_Context* ctx
  )
{
  uint16_t y;
  Ring1_Result r;

  r = Ring1_Intrinsic_nextMultipleOf32_u16(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  r = Ring1_Intrinsic_nextMultipleOf32_u16(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u16(&y, 31);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u16(&y, 32);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf32_u32
  (
    Ring1_Test_Context* ctx
  )
{
  uint32_t y;
  Ring1_Result r;

  r = Ring1_Intrinsic_nextMultipleOf32_u32(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  r = Ring1_Intrinsic_nextMultipleOf32_u32(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u32(&y, 31);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u32(&y, 32);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf32_u64
  (
    Ring1_Test_Context* ctx
  )
{
  uint64_t y;
  Ring1_Result r;

  r = Ring1_Intrinsic_nextMultipleOf32_u64(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  r = Ring1_Intrinsic_nextMultipleOf32_u64(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u64(&y, 31);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_u64(&y, 32);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf32_sz
  (
    Ring1_Test_Context* ctx
  )
{
  size_t y;
  Ring1_Result r;

  r = Ring1_Intrinsic_nextMultipleOf32_sz(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  r = Ring1_Intrinsic_nextMultipleOf32_sz(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_sz(&y, 31);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  r = Ring1_Intrinsic_nextMultipleOf32_sz(&y, 32);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 32);

  return Ring1_Result_Success;
}

Ring1_Result
Ring1_Intrinsic_Test_registerNextMultipleOf32Tests
  (
    Ring1_Test_Context* ctx
  )
{
  return
       Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf32[u8]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf32_u8)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf32[u16]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf32_u16)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf32[u32]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf32_u32)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf32[u64]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf32_u64)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf32[sz]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf32_sz);
}
