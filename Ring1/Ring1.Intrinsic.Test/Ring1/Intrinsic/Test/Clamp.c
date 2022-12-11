// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/Clamp.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/Clamp.h"

#include "Ring1/Intrinsic/Environment.h"
#include "Ring1/Intrinsic/FloatingPointTypes.h"
#include "Ring1/Intrinsic/clamp.h"
#include "Ring1/Status.h"

#define ExpectFailure(a, b, c, d, suffix)                                      \
  {                                                                            \
    Ring1_Result r_;                                                           \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    r_ = Ring1_Intrinsic_clamp_##suffix(a, b, c, d);                           \
    RING1_TEST_ASSERT_EQ(ctx, r_, Ring1_Result_Failure);                       \
    RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(),                              \
                         Ring1_Status_InvalidArgument);                        \
    Ring1_Status_set(Ring1_Status_Success);                                    \
  }

#define ExpectSuccess(                                                         \
  value, minimum, maximum, typeName, typeMin, typeMax, typeSuffix, expected)   \
  {                                                                            \
    Ring1_Result _result;                                                      \
    typeName _received;                                                        \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    _result =                                                                  \
      Ring1_Intrinsic_clamp_##typeSuffix(&_received, value, minimum, maximum); \
    RING1_TEST_ASSERT_EQ(ctx, _received, expected);                            \
    RING1_TEST_ASSERT_EQ(ctx, _result, Ring1_Result_Success);                  \
    RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);       \
    Ring1_Status_set(Ring1_Status_Success);                                    \
  }

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_f32
  (
    Ring1_Test_Context* ctx
  )
{ 
  float r;
  ExpectFailure(NULL, 0, 0, 0, f32);
  ExpectFailure(&r, Ring1_Fp_NoNumber_f32, 0, 0, f32);
  ExpectFailure(&r, 0, Ring1_Fp_NoNumber_f32, 0, f32);
  ExpectFailure(&r, 0, 0, Ring1_Fp_NoNumber_f32, f32);
  ExpectFailure(&r, 0, +Ring1_Fp_Infinity_f32, -Ring1_Fp_Infinity_f32, f32);
  ExpectSuccess(0.f, -Ring1_Fp_Infinity_f32, +Ring1_Fp_Infinity_f32, float, -Ring1_Intrinsic_Fp_Infinity_f32, +Ring1_Intrinsic_Fp_Infinity_f32, f32, 0.f);
  ExpectSuccess(0, -7, +3, float, -Ring1_Fp_Infinity_f32, +Ring1_Intrinsic_Fp_Infinity_f32, f32, 0);   /* case of within bounds */
  ExpectSuccess(-9, -7, +3, float, -Ring1_Fp_Infinity_f32, +Ring1_Intrinsic_Fp_Infinity_f32, f32, -7); /* case of outside lower bound */
  ExpectSuccess(+5, -7, +3, float, -Ring1_Fp_Infinity_f32, +Ring1_Intrinsic_Fp_Infinity_f32, f32, +3); /* case of outside upper bound */
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_f64
  (
    Ring1_Test_Context* ctx
  )
{
  double r;
  ExpectFailure(NULL, 0, 0, 0, f64);
  ExpectFailure(&r, Ring1_Fp_NoNumber_f64, 0, 0, f64);
  ExpectFailure(&r, 0, Ring1_Fp_NoNumber_f64, 0, f64);
  ExpectFailure(&r, 0, 0, Ring1_Fp_NoNumber_f64, f64);
  ExpectFailure(&r, 0, +Ring1_Fp_Infinity_f64, -Ring1_Fp_Infinity_f64, f64);
  return Ring1_Result_Success;
}

#undef ExpectSuccess
#undef ExpectFailure

#define ExpectFailure(a, b, c, d, suffix)                                      \
  {                                                                            \
    Ring1_Result r_;                                                           \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    r_ = Ring1_Intrinsic_clamp_##suffix(a, b, c, d);                           \
    RING1_TEST_ASSERT_EQ(ctx, r_, Ring1_Result_Failure);                       \
    RING1_TEST_ASSERT_EQ(                                                      \
      ctx, Ring1_Status_get(), Ring1_Status_InvalidArgument);                  \
    Ring1_Status_set(Ring1_Status_Success);                                    \
  }

#define ExpectSuccess(value, minimum, maximum, type, suffix, expected)         \
  {                                                                            \
    Ring1_Result _result;                                                      \
    type _received;                                                            \
    Ring1_Status_set(Ring1_Status_Success);                                    \
    _result =                                                                  \
      Ring1_Intrinsic_clamp_##suffix(&_received, value, minimum, maximum);     \
    RING1_TEST_ASSERT_EQ(ctx, _received, expected);                            \
    RING1_TEST_ASSERT_EQ(ctx, _result, Ring1_Result_Success);                  \
    RING1_TEST_ASSERT_EQ(ctx, Ring1_Status_get(), Ring1_Status_Success);       \
    Ring1_Status_set(Ring1_Status_Success);                                    \
  }

#define OnUnsigned(typeName, typeSuffix, typeMin, typeMax) \
  typeName r; \
  ExpectFailure(NULL, 0, 0, 0, typeSuffix); \
  ExpectFailure(&r, 0, typeMax, typeMin, typeSuffix); \
  ExpectSuccess(+5, +3, +7, typeName, typeSuffix, +5); /* case of within bounds */ \
  ExpectSuccess(+1, +3, +7, typeName, typeSuffix, +3); /* case of outside lower bound */ \
  ExpectSuccess(+9, +3, +7, typeName, typeSuffix, +7); /* case of outside upper bound */ \
  return Ring1_Result_Success;

#define OnSigned(typeName, typeSuffix, typeMin, typeMax) \
  typeName r; \
  ExpectFailure(NULL, 0, 0, 0, typeSuffix); \
  ExpectFailure(&r, 0, typeMax, typeMin, typeSuffix); \
  ExpectSuccess(0, -7, +3, typeName, typeSuffix, 0);   /* case of within bounds */ \
  ExpectSuccess(-9, -7, +3, typeName, typeSuffix, -7); /* case of outside lower bound */ \
  ExpectSuccess(+5, -7, +3, typeName, typeSuffix, +3); /* case of outside upper bound */ \
  return Ring1_Result_Success;

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_s8
  (
    Ring1_Test_Context* ctx
  )
{
  int8_t r;
  ExpectFailure(NULL, 0, 0, 0, s8);
  ExpectFailure(&r, 0, INT8_MAX, INT8_MIN, s8);
  ExpectSuccess(0, -7, +3, int8_t, s8, 0);   // case of within bounds
  ExpectSuccess(-9, -7, +3, int8_t, s8, -7); // case of outside lower bound
  ExpectSuccess(+5, -7, +3, int8_t, s8, +3); // case of outside upper bound
  return Ring1_Result_Success;
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_u8
  (
    Ring1_Test_Context* ctx
  )
{
  OnUnsigned(uint8_t, u8, UINT8_MIN, UINT8_MAX)
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_s16
  (
    Ring1_Test_Context* ctx
  )
{
  OnSigned(int16_t, s16, INT16_MIN, INT16_MAX);
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_u16
  (
    Ring1_Test_Context* ctx
  )
{
  OnUnsigned(uint16_t, u16, UINT16_MIN, UINT16_MAX)
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_s32
  (
    Ring1_Test_Context* ctx
  )
{
  OnSigned(int32_t, s32, INT32_MIN, INT32_MAX);
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_u32
  (
    Ring1_Test_Context* ctx
  )
{
  OnUnsigned(uint32_t, u32, UINT32_MIN, UINT32_MAX)
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_s64
  (
    Ring1_Test_Context* ctx
  )
{
  OnSigned(int64_t, s64, INT64_MIN, INT64_MAX);
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_u64
  (
    Ring1_Test_Context* ctx
  )
{
  OnUnsigned(uint64_t, u64, UINT64_MIN, UINT64_MAX)
}

static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_clamp_sz
  (
    Ring1_Test_Context* ctx
  )
{
  OnUnsigned(size_t, sz, SIZE_MIN, SIZE_MAX)
}

#undef OnSigned
#undef OnUnsigned
#undef ExpectFailure
#undef ExpectSuccess

Ring1_Result
Ring1_Intrinsic_Test_registerClampTests
  (
    Ring1_Test_Context* ctx
  )
{
  return Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[f32]",
                                    &Ring1_Intrinsic_Test_clamp_f32) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[f64]",
                                    &Ring1_Intrinsic_Test_clamp_f64) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[s8]",
                                    &Ring1_Intrinsic_Test_clamp_s8) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[u8]",
                                    &Ring1_Intrinsic_Test_clamp_u8) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[s16]",
                                    &Ring1_Intrinsic_Test_clamp_s16) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[u16]",
                                    &Ring1_Intrinsic_Test_clamp_u16) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[s32]",
                                    &Ring1_Intrinsic_Test_clamp_s32) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[u32]",
                                    &Ring1_Intrinsic_Test_clamp_u32) ||
         //
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[s64]",
                                    &Ring1_Intrinsic_Test_clamp_s64) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[u64]",
                                    &Ring1_Intrinsic_Test_clamp_u64) ||
         Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.clamp[sz]",
                                    &Ring1_Intrinsic_Test_clamp_sz);
}
