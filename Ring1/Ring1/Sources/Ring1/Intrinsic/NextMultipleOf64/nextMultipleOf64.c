// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextMultipleOf64/nextMultipleOf64.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/NextMultipleOf64/nextMultipleOf64.h"

#include "Ring1/Status.h"

#define Implementation_u(maximum) \
  if (!result) { \
    Ring1_Status_set(Ring1_Status_InvalidArgument); \
    return Ring1_Result_Failure; \
  } \
  if (x > (maximum) - 63) { \
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange); \
    return Ring1_Result_Failure; \
  } \
  *result = (x + 63) & (~63); \
  return Ring1_Result_Success;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u8
  (
    uint8_t *result,
    uint8_t x
  )
{
  Implementation_u(UINT8_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u16
  (
    uint16_t *result,
    uint16_t x
  )
{
  Implementation_u(UINT16_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u32
  (
    uint32_t *result,
    uint32_t x
  )
{
  Implementation_u(UINT32_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_u64
  (
    uint64_t *result,
    uint64_t x
  )
{
  Implementation_u(UINT64_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf64_sz
  (
    size_t *result,
    size_t x
  )
{
  Implementation_u(SIZE_MAX);
}

#undef Implementation_u
