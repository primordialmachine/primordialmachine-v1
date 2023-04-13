// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Multiply.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Multiply.h"

#include "Ring1/Intrinsic/Multiply/multiply.h"
#include <inttypes.h>
#include "Ring1/Status.h"

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_s8.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_s8
  (
    Ring1_Test_Context *ctx
  )
{
  int8_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s8(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s8(&z, INT8_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s8(&z, INT8_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, -2);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s8(&z, INT8_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s8(&z, INT8_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_u8.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_u8
  (
    Ring1_Test_Context *ctx
  )
{
  uint8_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u8(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u8(&z, UINT8_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT8_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u8(&z, UINT8_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT8_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_s16.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_s16
  (
    Ring1_Test_Context *ctx
  )
{
  int16_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s16(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s16(&z, INT16_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s16(&z, INT16_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, -2);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s16(&z, INT16_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s16(&z, INT16_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_u16.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_u16
  (
    Ring1_Test_Context *ctx
  )
{
  uint16_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u16(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u16(&z, UINT16_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT16_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u16(&z, UINT16_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT16_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_s32.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_s32
  (
    Ring1_Test_Context *ctx
  )
{
  int32_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s32(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s32(&z, INT32_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s32(&z, INT32_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, -2);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s32(&z, INT32_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s32(&z, INT32_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_u32.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_u32
  (
    Ring1_Test_Context *ctx
  )
{
  uint32_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u32(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);
  
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u32(&z, UINT32_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT32_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u32(&z, UINT32_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT32_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_s64.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_s64
  (
    Ring1_Test_Context* ctx
  )
{
  int64_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s64(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s64(&z, INT64_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s64(&z, INT64_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, -2);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s64(&z, INT64_MIN, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MIN);
  Ring1_Status_set(Ring1_Status_Success);

  // Reduction of results smaller than INTn_MIN.
  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_s64(&z, INT64_MIN, -2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 0);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_multiply_u64.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_multiply_u64
  (
    Ring1_Test_Context* ctx
  )
{
  uint64_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u64(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 12);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u64(&z, UINT64_MAX, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT64_MAX);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_multiply_u64(&z, UINT64_MAX, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT64_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_registerMultiplyTests
  (
    Ring1_Test_Context* ctx
  )
{
  return
    //
       Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s8]", &Ring1_Intrinsic_Test_multiply_s8)
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u8]", &Ring1_Intrinsic_Test_multiply_u8)
    //
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s16]", &Ring1_Intrinsic_Test_multiply_s16)
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u16]", &Ring1_Intrinsic_Test_multiply_u16)
    //
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s32]", &Ring1_Intrinsic_Test_multiply_s32)
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u32]", &Ring1_Intrinsic_Test_multiply_u32)
    //
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[s64]", &Ring1_Intrinsic_Test_multiply_s64)
    || Ring1_Test_Context_addTest(ctx, "Mkx.Intrinsic.Test.multiply[u64]", &Ring1_Intrinsic_Test_multiply_u64);
}
