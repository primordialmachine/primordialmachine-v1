// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo_u32.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"

#include "Ring1/Intrinsic/CountLeadingZeroes/countLeadingZeroes.h"
#include "Ring1/Status.h"

Ring1_CheckReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_u32
  (
    uint32_t *result,
    uint32_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (x < 2) {
    *result = 1;
    return Ring1_Result_Success;
  }
  short i;
  if (Ring1_Intrinsic_countLeadingZeroes_u32(&i, x - 1)) {
    return Ring1_Result_Failure;
  }
  uint32_t t = (uint32_t)1 << (32 - i);
  if (i == 0 && t != x) {
    Ring1_Status_set(Ring1_Status_ArgumentOutOfRange);
    return Ring1_Result_Failure;
  }
  *result = t;
  return Ring1_Result_Success;
}
