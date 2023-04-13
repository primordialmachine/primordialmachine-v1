// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Hash.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Hash.h"

#include "Ring1/Status.h"

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_p
  (
    size_t *result,
    void const* value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = (size_t)(uintptr_t)value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_p
  (
    int64_t *result,
    void const* value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_WIN64)
  *result = (int64_t)(intptr_t)value;
#elif defined(_WIN32)
  *result = (int64_t)(intptr_t)value;
#else
  #error("environment not supported")
#endif
  return Ring1_Result_Success;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_b
  (
    size_t* result,
    bool value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // 1231 and 1237 are merely two positive and sufficiently big prime numbers.
  *result = value ? 1231 : 1237;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_b
  (
    int64_t* result,
    bool value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  // 1231 and 1237 are merely two positive and sufficiently big prime numbers.
  *result = value ? 1231 : 1237;
  return Ring1_Result_Success;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i64
  (
    int64_t* result,
    int64_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i64
  (
    size_t* result,
    int64_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_WIN64)
  *result = (size_t)value;
#elif defined(_WIN32)
  *result = (size_t)value;
#else
  #error("environment not supported")
#endif
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i32
  (
    int64_t* result,
    int32_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i32
  (
    size_t* result,
    int32_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i16
  (
    int64_t* result,
    int16_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i16
  (
    size_t* result,
    int16_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_i8
  (
    int64_t* result,
    int8_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_i8
  (
    size_t* result,
    int8_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u64
  (
    size_t* result,
    uint64_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u32
  (
    size_t* result,
    uint32_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u16
  (
    size_t* result,
    uint16_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_u8
  (
    size_t* result,
    uint8_t value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  *result = value;
  return Ring1_Result_Success;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

#include <float.h>
#include <math.h>

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_f32
  (
    size_t* result,
    float value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  switch (fpclassify(value)) {
    case FP_INFINITE: {
      *result = value > 0.0f ? 7 : 11;
      return Ring1_Result_Success;
    };
    case FP_NAN: {
      *result = 13;
      return Ring1_Result_Success;
    };
    case FP_ZERO: {
      *result = 17;
      return Ring1_Result_Success;
    };
    case FP_NORMAL:
    case FP_SUBNORMAL:
    default: // The default case handles the case when fpclassify may return an
             // implementation defined type gracefully.
    {
      if (value == 0.0f)
        value = +0.0f; // +0.0f == -0.0f. Hence, map both to +0.0f.
      typedef union Bits
      {
        int32_t i32;
        float f32;
      } Bits;
      Bits bits;
      bits.f32 = value;
      *result = bits.i32;
      return Ring1_Result_Success;
    };
  };
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_f32
  (
    int64_t* result,
    float value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  switch (fpclassify(value)) {
    case FP_INFINITE: {
      *result = value > 0.0f ? 7 : 11;
      return Ring1_Result_Success;
    };
    case FP_NAN: {
      *result = 13;
      return Ring1_Result_Success;
    };
    case FP_ZERO: {
      *result = 17;
      return Ring1_Result_Success;
    };
    case FP_NORMAL:
    case FP_SUBNORMAL:
    default: // The default case handles the case when fpclassify may return an
             // implementation defined type gracefully.
    {
      if (value == 0.0f)
        value = +0.0f; // +0.0f == -0.0f. Hence, map both to +0.0f.
      typedef union Bits
      {
        int32_t i32;
        float f32;
      } Bits;
      Bits bits;
      bits.f32 = value;
      *result = bits.i32;
      return Ring1_Result_Success;
    };
  };
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toSz_f64
  (
    size_t* result,
    double value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  switch (fpclassify(value)) {
    case FP_INFINITE: {
      *result = value > 0.0 ? 7 : 11;
      return Ring1_Result_Success;
    };
    case FP_NAN: {
      *result = 13;
      return Ring1_Result_Success;
    };
    case FP_ZERO: {
      *result = 17;
      return Ring1_Result_Success;
    };
    case FP_NORMAL:
    case FP_SUBNORMAL:
    default: // The default case handles the case when fpclassify may return an
             // implementation defined type gracefully.
    {
      if (value == 0.0)
        value = +0.0; // +0.0 == -0.0. Hence, map both to +0.0.
      typedef union Bits
      {
        uint64_t i64;
        double f64;
      } Bits;
      Bits bits;
      bits.f64 = value;
      return Ring1_Hash_toSz_u64(result, bits.i64);
      return Ring1_Result_Success;
    };
  };
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Hash_toI64_f64
  (
    int64_t* result,
    double value
  )
{
  if (Ring1_Unlikely(!result)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  switch (fpclassify(value)) {
    case FP_INFINITE: {
      *result = value > 0.0 ? 7 : 11;
      return Ring1_Result_Success;
    };
    case FP_NAN: {
      *result = 13;
      return Ring1_Result_Success;
    };
    case FP_ZERO: {
      *result = 17;
      return Ring1_Result_Success;
    };
    case FP_NORMAL:
    case FP_SUBNORMAL:
    default: // The default case handles the case when fpclassify may return an
             // implementation defined type gracefully.
    {
      if (value == 0.0)
        value = +0.0; // +0.0 == -0.0. Hence, map both to +0.0.
      typedef union Bits
      {
        int64_t i64;
        double f64;
      } Bits;
      Bits bits;
      bits.f64 = value;
      *result = bits.i64;
      return Ring1_Result_Success;
    };
  };
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
