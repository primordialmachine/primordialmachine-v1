// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Add.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Add.h"

#include "Ring1/Intrinsic/Add/add.h"
#include <inttypes.h>
#include "Ring1/Status.h"

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_s8.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_s8
  (
    Ring1_Test_Context *ctx
  )
{
  int8_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s8(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s8(&z, INT8_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s8(&z, INT8_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MIN + 1);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s8(&z, INT8_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s8(&z, INT8_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_u8.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_u8
  (
    Ring1_Test_Context *ctx
  )
{
  uint8_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u8(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u8(&z, UINT8_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u8(&z, UINT8_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_s16.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_s16
  (
    Ring1_Test_Context *ctx
  )
{
  int16_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s16(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s16(&z, INT16_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s16(&z, INT16_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MIN + 1);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s16(&z, INT16_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s16(&z, INT16_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_u16.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_u16
  (
    Ring1_Test_Context *ctx
  )
{
  uint16_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u16(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u16(&z, UINT16_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);
 
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u16(&z, UINT16_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_s32.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_s32
  (
    Ring1_Test_Context *ctx
  )
{
  int32_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s32(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s32(&z, INT32_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s32(&z, INT32_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MIN + 1);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s32(&z, INT32_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s32(&z, INT32_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_u32.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_u32
  (
    Ring1_Test_Context *ctx
  )
{
  uint32_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u32(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u32(&z, UINT32_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u32(&z, UINT32_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_s64.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_s64
  (
    Ring1_Test_Context* ctx
  )
{
  int64_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s64(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s64(&z, INT64_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s64(&z, INT64_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MIN + 1);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s64(&z, INT64_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_s64(&z, INT64_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_u64.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_u64
  (
    Ring1_Test_Context *ctx
  )
{
  uint64_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u64(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u64(&z, UINT64_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_u64(&z, UINT64_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_add_sz.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_add_sz
  (
    Ring1_Test_Context *ctx
  )
{
  size_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_sz(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 7);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_sz(&z, SIZE_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_add_sz(&z, SIZE_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_NumericOverflow);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

Ring1_Result
Ring1_Intrinsic_Test_registerAddTests
  (
    Ring1_Test_Context* ctx
  )
{
  return
     Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[s8]",
                                &Ring1_Intrinsic_Test_add_s8)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[u8]",
                                &Ring1_Intrinsic_Test_add_u8)
  //
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[s16]",
                                &Ring1_Intrinsic_Test_add_s16)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[u16]",
                                &Ring1_Intrinsic_Test_add_u16)
  //
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[s32]",
                                &Ring1_Intrinsic_Test_add_s32)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[u32]",
                                &Ring1_Intrinsic_Test_add_u32)
  //
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[s64]",
                                &Ring1_Intrinsic_Test_add_s64)
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[u64]",
                                &Ring1_Intrinsic_Test_add_u64)
  //
  || Ring1_Test_Context_addTest(ctx,
                                "Ring1.Intrinsic.Test.add[sz]", 
                                &Ring1_Intrinsic_Test_add_sz)
  ;
}
