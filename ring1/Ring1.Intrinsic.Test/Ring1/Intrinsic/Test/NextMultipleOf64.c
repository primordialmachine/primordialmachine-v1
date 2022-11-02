// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/NextMultipleOf64.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/NextMultipleOf64.h"

#include "Ring1/Intrinsic/NextMultipleOf64/nextMultipleOf64.h"
#include <inttypes.h>
#include "Ring1/Status.h"

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf64_u8
  (
    Ring1_Test_Context* ctx
  )
{
  uint8_t y;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u8(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u8(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u8(&y, 63);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u8(&y, 64);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf64_u16
  (
    Ring1_Test_Context* ctx
  )
{
  uint16_t y;
  char r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u16(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u16(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u16(&y, 63);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u16(&y, 64);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf64_u32
  (
    Ring1_Test_Context* ctx
  )
{
  uint32_t y;
  char r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u32(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u32(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u32(&y, 63);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u32(&y, 64);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf64_u64
  (
    Ring1_Test_Context* ctx
  )
{
  uint64_t y;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u64(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u64(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u64(&y, 63);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_u64(&y, 64);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  return Ring1_Result_Success;
}

static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_nextMultipleOf64_sz
  (
    Ring1_Test_Context* ctx
  )
{
  size_t y;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_sz(&y, 0);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 0);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_sz(&y, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_sz(&y, 63);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_nextMultipleOf64_sz(&y, 64);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, y, 64);

  return Ring1_Result_Success;
}

Ring1_Result
Ring1_Intrinsic_Test_registerNextMultipleOf64Tests
  (
    Ring1_Test_Context* ctx
  )
{
  return
       Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf64[u8]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf64_u8)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf64[u16]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf64_u16)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf64[u32]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf64_u32)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf64[u64]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf64_u64)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.nextMultipleOf64[sz]",
                                  &Ring1_Intrinsic_Test_nextMultipleOf64_sz);
}
