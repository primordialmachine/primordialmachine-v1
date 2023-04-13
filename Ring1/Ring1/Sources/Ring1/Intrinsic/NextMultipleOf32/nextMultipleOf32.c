// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextMultipleOf32/nextMultipleOf32.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/NextMultipleOf32/nextMultipleOf32.h"

#include "Ring1/Status.h"

#define Implementation_u(maximum) \
  if (!result) { \
    Ring1_Status_set(Ring1_Status_InvalidArgument); \
    return Ring1_Result_Failure; \
  } \
  if (x > (maximum) - 31) { \
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange); \
    return Ring1_Result_Failure; \
  } \
  *result = (x + 31) & (~31); \
  return Ring1_Result_Success;
  

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u8
  (
    uint8_t *result,
    uint8_t x
  )
{
  Implementation_u(UINT8_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u16
  (
    uint16_t *result,
    uint16_t x
  )
{
  Implementation_u(UINT16_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u32
  (
    uint32_t *result,
    uint32_t x
  )
{
  Implementation_u(UINT32_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_u64
  (
    uint64_t *result,
    uint64_t x
  )
{
  Implementation_u(UINT64_MAX);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextMultipleOf32_sz
  (
    size_t *result,
    size_t x
  )
{
  Implementation_u(SIZE_MAX);
}

#undef Implementation_u
