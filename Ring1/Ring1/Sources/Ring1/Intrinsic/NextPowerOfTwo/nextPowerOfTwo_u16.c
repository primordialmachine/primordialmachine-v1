// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo_u16.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"

#include "Ring1/Intrinsic/CountLeadingZeroes/countLeadingZeroes.h"
#include "Ring1/Status.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_u16
  (
    uint16_t *result,
    uint16_t x
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
  if (Ring1_Intrinsic_countLeadingZeroes_u16(&i, x - 1)) {
    return Ring1_Result_Failure;
  }
  uint16_t t = 1 << (16 - i);
  if (i == 0 && t != x) {
    return Ring1_Result_Failure;
  }
  *result = t;
  return Ring1_Result_Success;
}
