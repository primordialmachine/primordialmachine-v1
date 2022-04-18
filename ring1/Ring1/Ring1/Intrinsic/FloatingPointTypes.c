// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/FloatingPointTypes.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/FloatingPointTypes.h"

#include "Ring1/Status.h"

#if defined(Ring1_Intrinsic_WithFp32) && 1 == Ring1_Intrinsic_WithFp32

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getRawBits_f32
  (
    uint32_t *result,
    float x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  union {
    float source;
    uint32_t target;
  } temporary = { .source = x };
  *result = temporary.target;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getBits_f32
  (
    uint32_t *result,
    float x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  uint32_t y;
  if (Ring1_Intrinsic_Fp_getRawBits_f32(&y, x)) {
    return Ring1_Result_Failure;
  }
  // Canonicalize no number values.
  if ((y & Ring1_Intrinsic_Fp_ExponentMask_f32) == Ring1_Intrinsic_Fp_ExponentMask_f32 &&
      (y & Ring1_Intrinsic_Fp_SignificantMask_f32) != UINT32_C(0))
  {
    y = UINT32_C(0x7FC00000);
  }
  // Canonicalize negative zero values.
  if (y == Ring1_Intrinsic_Fp_NegativeZero_f32)
  {
    y = Ring1_Intrinsic_Fp_PositiveZero_f32;
  }
  *result = y;
  return Ring1_Result_Success;
}

#endif // Ring1_Intrinsic_WithFp32

#if defined(Ring1_Intrinsic_WithFp64) && 1 == Ring1_Intrinsic_WithFp64

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getRawBits_f64
  (
    uint64_t *result,
    double x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  union {
    double source;
    uint64_t target;
  } temporary = { .source = x };
  *result = temporary.target;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_Fp_getBits_f64
  (
    uint64_t *result,
    double x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  uint64_t y;
  if (Ring1_Intrinsic_Fp_getRawBits_f64(&y, x)) {
    return Ring1_Result_Failure;
  }
  // Canonicalize no number values.
  if ((y & Ring1_Intrinsic_Fp_ExponentMask_f64) == Ring1_Intrinsic_Fp_ExponentMask_f64 &&
      (y & Ring1_Intrinsic_Fp_SignificantMask_f64) != UINT64_C(0))
  {
    y = UINT64_C(0x7FF8000000000000);
  }
  // Canonicalize negative zero values.
  if (y == Ring1_Intrinsic_Fp_NegativeZero_f64)
  {
    y = Ring1_Intrinsic_Fp_PositiveZero_f64;
  }
  *result = y;
  return Ring1_Result_Success;
}

#endif // Ring1_Intrinsic_WithFp64
