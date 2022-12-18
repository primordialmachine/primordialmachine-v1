// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/Test/FloatingPointTypes.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/Test/FloatingPointTypes.h"

#include "Ring1/Intrinsic/_Include.h"
#include <inttypes.h>
#include "Ring1/Status.h"

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_countLeadingZeroes_u32.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_floatingPointTypes_f32
  (
    Ring1_Test_Context *ctx
  )
{
  bool sign;
  int32_t significant, exponent;
  Ring1_Fp_split_f32(-0.f, &sign, &significant, &exponent, true);
  return Ring1_Result_Success;
}

/// @brief Unit test function asserting correctness of Ring1_Intrinsic_countLeadingZeroes_u64.
/// @param ctx A pointer to the test context.
static Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_Test_floatingPointTypes_f64
  (
    Ring1_Test_Context* ctx
  )
{
  bool sign;
  int64_t significant, exponent;
  
  // plus/minus 0
  Ring1_Fp_split_f64(-0., &sign, &significant, &exponent, true);
  Ring1_Fp_split_f64(+0., &sign, &significant, &exponent, true);

  // plus/minus 1
  Ring1_Fp_split_f64(-1, &sign, &significant, &exponent, true);
  RING1_TEST_ASSERT_EQ(ctx, significant, 1);
  RING1_TEST_ASSERT_EQ(ctx, exponent, 0);
  Ring1_Fp_split_f64(+1, &sign, &significant, &exponent, true);
  RING1_TEST_ASSERT_EQ(ctx, significant, 1);
  RING1_TEST_ASSERT_EQ(ctx, exponent, 0);

  // plus/minus 2
  Ring1_Fp_split_f64(-2, &sign, &significant, &exponent, true);
  RING1_TEST_ASSERT_EQ(ctx, significant, 1);
  RING1_TEST_ASSERT_EQ(ctx, exponent, 1);
  Ring1_Fp_split_f64(+2, &sign, &significant, &exponent, true);
  RING1_TEST_ASSERT_EQ(ctx, significant, 1);
  RING1_TEST_ASSERT_EQ(ctx, exponent, 1);

  // plus/minus 256
  Ring1_Fp_split_f64(-256., &sign, &significant, &exponent, true);
  RING1_TEST_ASSERT_EQ(ctx, significant, 1);
  RING1_TEST_ASSERT_EQ(ctx, exponent, 8);
  Ring1_Fp_split_f64(+256., &sign, &significant, &exponent, true);
  RING1_TEST_ASSERT_EQ(ctx, significant, 1);
  RING1_TEST_ASSERT_EQ(ctx, exponent, 8);

  return Ring1_Result_Success;
}

Ring1_Result
Ring1_Intrinsic_Test_registerFloatingPointTypesTests
  (
    Ring1_Test_Context* ctx
  )
{
  return Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.floatingPointTypes[f32]",
                                    &Ring1_Intrinsic_Test_floatingPointTypes_f32)
      || Ring1_Test_Context_addTest(ctx,
                                    "Ring1.Intrinsic.Test.floatingPointTypes[f64]",
                                    &Ring1_Intrinsic_Test_floatingPointTypes_f64);
}
