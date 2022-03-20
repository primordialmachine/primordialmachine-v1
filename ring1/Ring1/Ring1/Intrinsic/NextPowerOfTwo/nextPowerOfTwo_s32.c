// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo_s32.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"

#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_s32
  (
    int32_t *result,
    int32_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (x <= 0) {
    *result = 1;
    return Ring1_Result_Success;
  }
  uint32_t z;
  if (Ring1_Intrinsic_nextPowerOfTwo_u32(&z, (uint32_t)x)) {
    return Ring1_Result_Failure;
  }
  if (z > INT32_MAX) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  *result = (int32_t)z;
  return Ring1_Result_Success;
}
