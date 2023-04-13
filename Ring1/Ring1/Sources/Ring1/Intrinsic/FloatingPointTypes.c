// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/FloatingPointTypes.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/FloatingPointTypes.h"

#include "Ring1/Status.h"

#if defined(Ring1_Intrinsic_WithFp32) && 1 == Ring1_Intrinsic_WithFp32

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_equalToWithTolerance_f32
  (
    bool* result,
    float x,
    float y,
    float a,
    float r
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = (fabs(x - y) <= a + r * fabs(y));
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_getRawBits_f32
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

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_getBits_f32
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
  if (Ring1_Fp_getRawBits_f32(&y, x)) {
    return Ring1_Result_Failure;
  }
  // Canonicalize no number values.
  if ((y & Ring1_Fp_ExponentMask_f32) == Ring1_Fp_ExponentMask_f32 &&
      (y & Ring1_Fp_SignificantMask_f32) != UINT32_C(0))
  {
    y = UINT32_C(0x7FC00000);
  }
  // Canonicalize negative zero values.
  if (y == Ring1_Fp_NegativeZero_f32)
  {
    y = Ring1_Fp_PositiveZero_f32;
  }
  *result = y;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_split_f32
  (
    float x,
    bool *sign,
    int32_t *significant,
    int32_t* exponent,
    bool normalize
  )
{
  uint32_t a;
  if (Ring1_Fp_getBits_f32(&a, x)) {
    return Ring1_Result_Failure;
  }
  // sign
  {
    uint32_t b = (a & Ring1_Fp_SignMask_f32) >> UINT64_C(31);
    *sign = b;
  }
  // exponent
  int64_t unbiasedExponent = 0;
  {
    uint32_t b = (a & Ring1_Fp_ExponentMask_f32) >> UINT64_C(23);
    unbiasedExponent = b;
    int32_t c = ((int32_t)a) - INT32_C(127) - INT32_C(23);
    // -23 because we actually have to divide the exponent bits by 2^23.
    *exponent = c;
  }
  // significant
  {
    uint32_t b = a & Ring1_Fp_SignificantMask_f32;
    if (unbiasedExponent == 0) {
      // subnormal if b != 0: sign x 2^(1 - 1075) x 0.fraction = 0
      // signed zero if b = 0: sign x 2^(1 - 1075) x 0.0 = 0
      b = b << 1;
    } else {
      // normal: sign x 1.fraction x 2^(-1075)
      b = b | (UINT64_C(1) << UINT64_C(52));
    }
    // b = b | (UINT32_C(1) << UINT32_C(23));
    int32_t c = (int32_t)b;
    *significant = c;
  }
  if ((*significant) != 0 && normalize) {
    // As long as the significant is divisble by 2,
    // divide significant by 2 and add 1 to the exponent.
    while ((*significant % 2) == 0) {
      (*significant) >>= 1;
      (*exponent)++;
    }
  }
  return Ring1_Result_Success;
}

#endif // Ring1_Intrinsic_WithFp32

#if defined(Ring1_Intrinsic_WithFp64) && 1 == Ring1_Intrinsic_WithFp64

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_equalToWithTolerance_f64
  (
    bool* result,
    double x,
    double y,
    double a,
    double r
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = (fabs(x - y) <= a + r * fabs(y));
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_getRawBits_f64
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

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_getBits_f64
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
  if (Ring1_Fp_getRawBits_f64(&y, x)) {
    return Ring1_Result_Failure;
  }
  // Canonicalize no number values.
  if ((y & Ring1_Fp_ExponentMask_f64) == Ring1_Fp_ExponentMask_f64 &&
      (y & Ring1_Fp_SignificantMask_f64) != UINT64_C(0))
  {
    y = UINT64_C(0x7FF8000000000000);
  }
  // Canonicalize negative zero values.
  if (y == Ring1_Fp_NegativeZero_f64)
  {
    y = Ring1_Fp_PositiveZero_f64;
  }
  *result = y;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Fp_split_f64
  (
    double x,
    bool *sign,
    int64_t *significant,
    int64_t* exponent,
    bool normalize
  )
{
  uint64_t a;
  if (Ring1_Fp_getBits_f64(&a, x)) {
    return Ring1_Result_Failure;
  }
  // sign
  {
    uint64_t b = (a & Ring1_Fp_SignMask_f64) >> UINT64_C(63);
    *sign = b;
  }
  // exponent
  int64_t unbiasedExponent = 0;
  {
    uint64_t b = (a & Ring1_Fp_ExponentMask_f64) >> UINT64_C(52);
    unbiasedExponent = b;
    int64_t c = ((int64_t)b) - INT64_C(1023) - INT64_C(52);
    // -52 because we actually have to divide the exponent bits by 2^52.
    *exponent = c;
  }
  // significant
  {
    uint64_t b = a & Ring1_Fp_SignificantMask_f64;
    if (unbiasedExponent == 0) {
      // subnormal if b != 0: sign x 2^(1 - 1075) x 0.fraction = 0
      // signed zero if b = 0: sign x 2^(1 - 1075) x 0.0 = 0
      b = b << 1;
    } else {
      // normal: sign x 1.fraction x 2^(-1075)
      b = b | (UINT64_C(1) << UINT64_C(52));
    }
    int64_t c = (int64_t)b;
    *significant = c;
  }
  if ((*significant) != 0 && normalize) {
    // As long as the significant is divisble by 2,
    // divide significant by 2 and add 1 to the exponent.
    while ((*significant % 2) == 0) {
      (*significant) >>= 1;
      (*exponent)++;
    }
  }
  return Ring1_Result_Success;
}

#endif // Ring1_Intrinsic_WithFp64
