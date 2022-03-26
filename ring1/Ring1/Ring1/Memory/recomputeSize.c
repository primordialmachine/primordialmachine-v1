// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Memory/recomputeSize.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Memory/recomputeSize.h"

#include "Ring1/Status.h"
#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_u8
  (
    uint8_t min,
    uint8_t max,
    uint8_t old,
    uint8_t additional,
    uint8_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (UINT8_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  uint8_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_u8(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_s8
  (
    int8_t min,
    int8_t max,
    int8_t old,
    int8_t additional,
    int8_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max)
  {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (INT8_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  int8_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_s8(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_u16
  (
    uint16_t min,
    uint16_t max,
    uint16_t old,
    uint16_t additional,
    uint16_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (UINT16_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  uint16_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_u16(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_s16
  (
    int16_t min,
    int16_t max,
    int16_t old,
    int16_t additional,
    int16_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (INT16_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  int16_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_s16(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_u32
  (
    uint32_t min,
    uint32_t max,
    uint32_t old,
    uint32_t additional,
    uint32_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (UINT32_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  uint32_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_u32(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_s32
  (
    int32_t min,
    int32_t max,
    int32_t old,
    int32_t additional,
    int32_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (INT32_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  int32_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_s32(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_u64
  (
    uint64_t min,
    uint64_t max,
    uint64_t old,
    uint64_t additional,
    uint64_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (UINT64_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  uint64_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_u64(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_s64
  (
    int64_t min,
    int64_t max,
    int64_t old,
    int64_t additional,
    int64_t *new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (INT64_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  int64_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_s64(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new =  temporary;
  return Ring1_Result_Success;
}

Ring1_CheckReturn() Ring1_Result
Ring1_Memory_recomputeSize_sz
  (
    size_t min,
    size_t max,
    size_t old,
    size_t additional,
    size_t* new,
    bool saturate
  )
{
  if (!new || min < 0 || min > max || old < min || old > max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (SIZE_MAX - old < additional) {
    Ring1_Status_set(Ring1_Status_NotExists);
    return Ring1_Result_Failure;
  }
  // \f$old + additional \leq x\f$.
  size_t temporary = old + additional;
  // \f$x\f$ is a power of two.
  if (Ring1_Intrinsic_nextPowerOfTwo_sz(&temporary, temporary)) {
    return Ring1_Result_Failure;
  }
  // \f$x \leq max\f$.
  if (temporary > max) {
    if (!saturate) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
    temporary = max;
    if (temporary < old + additional) {
      Ring1_Status_set(Ring1_Status_NotExists);
      return Ring1_Result_Failure;
    }
  }
  *new = temporary;
  return Ring1_Result_Success;
}
