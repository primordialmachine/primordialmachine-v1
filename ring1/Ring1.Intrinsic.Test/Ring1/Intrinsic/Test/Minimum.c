// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Minium.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Minimum.h"

#include "Ring1/Intrinsic/Environment.h"
#include "Ring1/Intrinsic/FloatingPointTypes.h"
#include "Ring1/Intrinsic/minimum.h"
#include "Ring1/Status.h"

#define ExpectFailure(a, b, c, suffix)                                         \
  {                                                                            \
    Ring1_Result _result;                                                      \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    _result = Ring1_Intrinsic_minimum_##suffix(a, b, c);                       \
    RING1_TEST_ASSERT_EQ(ctx, _result, Ring1_Result_Failure);                  \
    RING1_TEST_ASSERT_EQ(                                                      \
      ctx, Ring1_Status_get(), Ring1_Status_InvalidArgument);                  \
    Ring1_Status_set(Ring1_Status_Success);                                    \
  }

static void
Ring1_Intrinsic_Test_minimum_f32
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0.f, 0.f, f32);
  float r;
  ExpectFailure(&r, 0.f, Ring1_Intrinsic_Fp_NoNumber_f32, f32);                             // maximum is no number.
  ExpectFailure(&r, Ring1_Intrinsic_Fp_NoNumber_f32, 0.f, f32);                             // minimum is no number.
  ExpectFailure(&r, Ring1_Intrinsic_Fp_NoNumber_f32, Ring1_Intrinsic_Fp_NoNumber_f32, f32); // both maximum and minimum is no number.
}

static void
Ring1_Intrinsic_Test_minimum_f64
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0., 0., f32);
  double r;
  ExpectFailure(&r, 0., Ring1_Intrinsic_Fp_NoNumber_f32, f64);                              // maximum is no number.
  ExpectFailure(&r, Ring1_Intrinsic_Fp_NoNumber_f64, 0., f64);                              // minimum is no number.
  ExpectFailure(&r, Ring1_Intrinsic_Fp_NoNumber_f64, Ring1_Intrinsic_Fp_NoNumber_f64, f64); // both maximum and minimum are no number.
}

#undef ExpectFailure

#define ExpectFailure(a, b, c, suffix)                                         \
  {                                                                            \
    Ring1_Result _result;                                                      \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    _result = Ring1_Intrinsic_minimum_##suffix(a, b, c);                       \
    RING1_TEST_ASSERT_EQ(ctx, _result, Ring1_Result_Failure);                  \
    RING1_TEST_ASSERT_EQ(                                                      \
      ctx, Ring1_Status_get(), Ring1_Status_InvalidArgument);                  \
    Ring1_Status_set(Ring1_Status_Success);                                    \
  }

#define ExpectSuccess(first, second, typeName, typeSuffix, expected)           \
  {                                                                            \
    Ring1_Result _result;                                                      \
    typeName _received;                                                        \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    _result = Ring1_Intrinsic_minimum_##typeSuffix(&_received, first, second); \
    RING1_TEST_ASSERT_EQ(ctx, _result, Ring1_Result_Success);                  \
    RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);       \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    RING1_TEST_ASSERT_EQ(ctx, _received, expected);                            \
  }

static void
Ring1_Intrinsic_Test_minimum_s8
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, s8);
  ExpectSuccess(0, 0, int8_t, s8, 0);
  ExpectSuccess(0, 1, int8_t, s8, 0);
  ExpectSuccess(1, 0, int8_t, s8, 0);
  ExpectSuccess(1, 1, int8_t, s8, 1);
  ExpectSuccess(INT8_MIN, INT8_MIN, int8_t, s8, INT8_MIN);
  ExpectSuccess(INT8_MIN, INT8_MAX, int8_t, s8, INT8_MIN);
  ExpectSuccess(INT8_MAX, INT8_MIN, int8_t, s8, INT8_MIN);
  ExpectSuccess(INT8_MAX, INT8_MAX, int8_t, s8, INT8_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_u8
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, u8);
  ExpectSuccess(0, 0, uint8_t, u8, 0);
  ExpectSuccess(0, 1, uint8_t, u8, 0);
  ExpectSuccess(1, 0, uint8_t, u8, 0);
  ExpectSuccess(1, 1, uint8_t, u8, 1);
  ExpectSuccess(UINT8_MIN, UINT8_MIN, uint8_t, u8, UINT8_MIN);
  ExpectSuccess(UINT8_MIN, UINT8_MAX, uint8_t, u8, UINT8_MIN);
  ExpectSuccess(UINT8_MAX, UINT8_MIN, uint8_t, u8, UINT8_MIN);
  ExpectSuccess(UINT8_MAX, UINT8_MAX, uint8_t, u8, UINT8_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_s16
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, s16);
  ExpectSuccess(0, 0, int16_t, s16, 0);
  ExpectSuccess(0, 1, int16_t, s16, 0);
  ExpectSuccess(1, 0, int16_t, s16, 0);
  ExpectSuccess(1, 1, int16_t, s16, 1);
  ExpectSuccess(INT16_MIN, INT16_MIN, int16_t, s16, INT16_MIN);
  ExpectSuccess(INT16_MIN, INT16_MAX, int16_t, s16, INT16_MIN);
  ExpectSuccess(INT16_MAX, INT16_MIN, int16_t, s16, INT16_MIN);
  ExpectSuccess(INT16_MAX, INT16_MAX, int16_t, s16, INT16_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_u16
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, u16);
  ExpectSuccess(0, 0, uint16_t, u16, 0);
  ExpectSuccess(0, 1, uint16_t, u16, 0);
  ExpectSuccess(1, 0, uint16_t, u16, 0);
  ExpectSuccess(1, 1, uint16_t, u16, 1);
  ExpectSuccess(UINT16_MIN, UINT16_MIN, uint16_t, u16, UINT16_MIN);
  ExpectSuccess(UINT16_MIN, UINT16_MAX, uint16_t, u16, UINT16_MIN);
  ExpectSuccess(UINT16_MAX, UINT16_MIN, uint16_t, u16, UINT16_MIN);
  ExpectSuccess(UINT16_MAX, UINT16_MAX, uint16_t, u16, UINT16_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_s32
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, s32);
  ExpectSuccess(0, 0, int32_t, s32, 0);
  ExpectSuccess(0, 1, int32_t, s32, 0);
  ExpectSuccess(1, 0, int32_t, s32, 0);
  ExpectSuccess(1, 1, int32_t, s32, 1);
  ExpectSuccess(INT32_MIN, INT32_MIN, int32_t, s32, INT32_MIN);
  ExpectSuccess(INT32_MIN, INT32_MAX, int32_t, s32, INT32_MIN);
  ExpectSuccess(INT32_MAX, INT32_MIN, int32_t, s32, INT32_MIN);
  ExpectSuccess(INT32_MAX, INT32_MAX, int32_t, s32, INT32_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_u32
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, u32);
  ExpectSuccess(0, 0, uint32_t, u32, 0);
  ExpectSuccess(0, 1, uint32_t, u32, 0);
  ExpectSuccess(1, 0, uint32_t, u32, 0);
  ExpectSuccess(1, 1, uint32_t, u32, 1);
  ExpectSuccess(UINT32_MIN, UINT32_MIN, uint32_t, u32, UINT32_MIN);
  ExpectSuccess(UINT32_MIN, UINT32_MAX, uint32_t, u32, UINT32_MIN);
  ExpectSuccess(UINT32_MAX, UINT32_MIN, uint32_t, u32, UINT32_MIN);
  ExpectSuccess(UINT32_MAX, UINT32_MAX, uint32_t, u32, UINT32_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_s64
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, s64);
  ExpectSuccess(0, 0, int64_t, s64, 0);
  ExpectSuccess(0, 1, int64_t, s64, 0);
  ExpectSuccess(1, 0, int64_t, s64, 0);
  ExpectSuccess(1, 1, int64_t, s64, 1);
  ExpectSuccess(INT64_MIN, INT64_MIN, int64_t, s64, INT64_MIN);
  ExpectSuccess(INT64_MIN, INT64_MAX, int64_t, s64, INT64_MIN);
  ExpectSuccess(INT64_MAX, INT64_MIN, int64_t, s64, INT64_MIN);
  ExpectSuccess(INT64_MAX, INT64_MAX, int64_t, s64, INT64_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_u64
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, u64);
  ExpectSuccess(0, 0, uint64_t, u64, 0);
  ExpectSuccess(0, 1, uint64_t, u64, 0);
  ExpectSuccess(1, 0, uint64_t, u64, 0);
  ExpectSuccess(1, 1, uint64_t, u64, 1);
  ExpectSuccess(UINT64_MIN, UINT64_MIN, uint64_t, u64, UINT64_MIN);
  ExpectSuccess(UINT64_MIN, UINT64_MAX, uint64_t, u64, UINT64_MIN);
  ExpectSuccess(UINT64_MAX, UINT64_MIN, uint64_t, u64, UINT64_MIN);
  ExpectSuccess(UINT64_MAX, UINT64_MAX, uint64_t, u64, UINT64_MAX);
}

static void
Ring1_Intrinsic_Test_minimum_sz
  (
    Ring1_Test_Context* ctx
  )
{
  ExpectFailure(NULL, 0, 0, sz);
  ExpectSuccess(0, 0, size_t, sz, 0);
  ExpectSuccess(0, 1, size_t, sz, 0);
  ExpectSuccess(1, 0, size_t, sz, 0);
  ExpectSuccess(1, 1, size_t, sz, 1);
  ExpectSuccess(SIZE_MIN, SIZE_MIN, size_t, sz, SIZE_MIN);
  ExpectSuccess(SIZE_MIN, SIZE_MAX, size_t, sz, SIZE_MIN);
  ExpectSuccess(SIZE_MAX, SIZE_MIN, size_t, sz, SIZE_MIN);
  ExpectSuccess(SIZE_MAX, SIZE_MAX, size_t, sz, SIZE_MAX);
}

#undef ExpectSuccess
#undef ExpectFailure

Ring1_Result
Ring1_Intrinsic_Test_registerMinimumTests
  (
  Ring1_Test_Context* ctx
  )
{
  return Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[f32]",
                                    &Ring1_Intrinsic_Test_minimum_f32) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[f64]",
                                    &Ring1_Intrinsic_Test_minimum_f64) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[s8]",
                                    &Ring1_Intrinsic_Test_minimum_s8) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[u8]",
                                    &Ring1_Intrinsic_Test_minimum_u8) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[s16]",
                                    &Ring1_Intrinsic_Test_minimum_s16) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[u16]",
                                    &Ring1_Intrinsic_Test_minimum_u16) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[s32]",
                                    &Ring1_Intrinsic_Test_minimum_s32) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[u32]",
                                    &Ring1_Intrinsic_Test_minimum_u32) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[s64]",
                                    &Ring1_Intrinsic_Test_minimum_s64) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[u64]",
                                    &Ring1_Intrinsic_Test_minimum_u64) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.minimum[sz]",
                                    &Ring1_Intrinsic_Test_minimum_sz);
}
