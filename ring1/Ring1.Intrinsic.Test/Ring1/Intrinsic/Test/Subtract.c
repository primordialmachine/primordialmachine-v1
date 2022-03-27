// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Subtract.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Subtract.h"

#include "Ring1/Intrinsic/Subtract/subtract.h"
#include <inttypes.h>
#include "Ring1/Status.h"

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_s8.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_s8
  (
    Ring1_Test_Context *ctx
  )
{
  int8_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s8(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, -1);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s8(&z, INT8_MIN, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s8(&z, INT8_MIN, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT8_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s8(&z, -3, -4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_u8.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_u8
  (
    Ring1_Test_Context *ctx
  )
{
  uint8_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u8(&z, 4, 3);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u8(&z, 0, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT8_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u8(&z, 0, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT8_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u8(&z, 0, UINT8_MAX);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_s16.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_s16
  (
    Ring1_Test_Context *ctx
  )
{
  int16_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s16(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, -1);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s16(&z, INT16_MIN, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s16(&z, INT16_MIN, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT16_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s16(&z, -3, -4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_u16.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_u16
  (
    Ring1_Test_Context *ctx
  )
{
  uint16_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u16(&z, 4, 3);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u16(&z, 0, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT16_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u16(&z, 0, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT16_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u16(&z, 0, UINT16_MAX);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_s32.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_s32
  (
    Ring1_Test_Context *ctx
  )
{
  int32_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s32(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, z, -1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s32(&z, INT32_MIN, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s32(&z, INT32_MIN, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT32_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s32(&z, -3, -4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_u32.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_u32
  (
    Ring1_Test_Context *ctx
  )
{
  uint32_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u32(&z, 4, 3);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u32(&z, 0, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT32_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u32(&z, 0, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT32_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u32(&z, 0, UINT32_MAX);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_s64.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_s64
  (
    Ring1_Test_Context *ctx
  )
{
  int64_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s64(&z, 3, 4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, -1);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s64(&z, INT64_MIN, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s64(&z, INT64_MIN, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, INT64_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_s64(&z, -3, -4);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_u64.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_u64
  (
    Ring1_Test_Context *ctx
  )
{
  uint64_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u64(&z, 4, 3);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u64(&z, 0, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT64_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u64(&z, 0, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, UINT64_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_u64(&z, 0, UINT64_MAX);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);
}

/// @brief Unit test function asserting correctness of Mkx_Intrinsic_subtract_sz.
/// @param ctx A pointer to the test context.
static void
Ring1_Intrinsic_Test_subtract_sz
  (
    Ring1_Test_Context *ctx
  )
{
  size_t z;
  Ring1_Result r;

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_sz(&z, 4, 3);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Success);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_sz(&z, 0, 1);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, SIZE_MAX);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_sz(&z, 0, 2);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, SIZE_MAX - 1);
  Ring1_Status_set(Ring1_Status_Success);

  RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);
  r = Ring1_Intrinsic_subtract_sz(&z, 0, SIZE_MAX);
  RING1_TEST_ASSERT_EQ(ctx, r, Ring1_Result_Failure);
  RING1_TEST_ASSERT_EQ(ctx, z, 1);
  Ring1_Status_set(Ring1_Status_Success);
}

Ring1_Result
Ring1_Intrinsic_Test_registerSubtractTests
  (
    Ring1_Test_Context* ctx
  )
{
  return
       Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[s8]",
                                  &Ring1_Intrinsic_Test_subtract_s8)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[u8]",
                                  &Ring1_Intrinsic_Test_subtract_u8)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[s16]",
                                  &Ring1_Intrinsic_Test_subtract_s16)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[u16]",
                                  &Ring1_Intrinsic_Test_subtract_u16)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[s32]",
                                  &Ring1_Intrinsic_Test_subtract_s32)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[u32]",
                                  &Ring1_Intrinsic_Test_subtract_u32)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[s64]",
                                  &Ring1_Intrinsic_Test_subtract_s64)
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[u64]",
                                  &Ring1_Intrinsic_Test_subtract_u64)
    //
    || Ring1_Test_Context_addTest(ctx,
                                  "Ring1.Intrinsic.Test.subtract[sz]",
                                  &Ring1_Intrinsic_Test_subtract_sz)
    ;
}

