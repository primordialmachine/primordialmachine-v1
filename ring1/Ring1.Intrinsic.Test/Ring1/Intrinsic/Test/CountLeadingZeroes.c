// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/CountLeadingZeroes.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/CountLeadingZeroes.h"

#include "Ring1/Intrinsic/CountLeadingZeroes/countLeadingZeroes.h"
#include <inttypes.h>
#include "Ring1/Status.h"

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_countLeadingZeroes_u8.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_countLeadingZeroes_u8
  (
    Ring1_Test_Context *ctx
  )
{
  short n;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u8(&n, 0));
  RING1_TEST_ASSERT_EQ(ctx, 8, n);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u8(&n, 1));
  RING1_TEST_ASSERT_EQ(ctx, 7, n);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u8(&n, UINT8_MAX));
  RING1_TEST_ASSERT_EQ(ctx, 0, n);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_countLeadingZeroes_u16.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_countLeadingZeroes_u16
  (
    Ring1_Test_Context *ctx
  )
{
  short n;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u16(&n, 0));
  RING1_TEST_ASSERT_EQ(ctx, 16, n);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u16(&n, 1));
  RING1_TEST_ASSERT_EQ(ctx, 15, n);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u16(&n, UINT16_MAX));
  RING1_TEST_ASSERT_EQ(ctx, 0, n);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_countLeadingZeroes_u32.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_countLeadingZeroes_u32
  (
    Ring1_Test_Context *ctx
  )
{
  short n;
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u32(&n, 0));
  RING1_TEST_ASSERT_EQ(ctx, 32, n);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u32(&n, 1));
  RING1_TEST_ASSERT_EQ(ctx, 31, n);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u32(&n, UINT32_MAX));
  RING1_TEST_ASSERT_EQ(ctx, 0, n);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_countLeadingZeroes_u64.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardResult() Ring1_Result
Ring1_Intrinsic_Test_countLeadingZeroes_u64
  (
    Ring1_Test_Context* ctx
  )
{
  short n;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u64(&n, 0));
  RING1_TEST_ASSERT_EQ(ctx, 64, n);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u64(&n, 1));
  RING1_TEST_ASSERT_EQ(ctx, 63, n);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Result_Success, Ring1_Intrinsic_countLeadingZeroes_u64(&n, UINT64_MAX));
  RING1_TEST_ASSERT_EQ(ctx, 0, n);

  return Ring1_Result_Success;
}

Ring1_Result
Ring1_Intrinsic_Test_registerCountLeadingZeroesTests
  (
    Ring1_Test_Context* ctx
  )
{
  return Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.countLeadingZeroes[u8]",
                                    &Ring1_Intrinsic_Test_countLeadingZeroes_u8)
      || Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.countLeadingZeroes[u16]",
                                    &Ring1_Intrinsic_Test_countLeadingZeroes_u16)
      || Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.countLeadingZeroes[u32]",
                                    &Ring1_Intrinsic_Test_countLeadingZeroes_u32)
      || Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.countLeadingZeroes[u64]",
                                    &Ring1_Intrinsic_Test_countLeadingZeroes_u64);
}
