// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo_sz.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring1/Intrinsic/NextPowerOfTwo/nextPowerOfTwo.h"

#include "Ring1/Status.h"

Ring1_NoDiscardReturn() Ring1_Result
Ring1_Intrinsic_nextPowerOfTwo_sz
  (
    size_t *result,
    size_t x
  )
{
  if (!result) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
#if defined(_MSC_VER) && defined(_WIN32) && !defined(_WIN64)
  static_assert(SIZE_MAX == UINT32_MAX, "SIZE_MAX must be equal to UINT32_MAX");
  uint32_t t;
  if (Ring1_Intrinsic_nextPowerOfTwo_u32(&t, x)) {
    return Ring1_Result_Failure;
  }
  *result = t;
  return Ring1_Result_Success;
#elif defined(_MSC_VER) && defined(_WIN32) && defined(_WIN64)
  static_assert(SIZE_MAX == UINT64_MAX, "SIZE_MAX must be equal to UINT64_MAX");
  uint64_t t;
  if (Ring1_Intrinsic_nextPowerOfTwo_u64(&t, x)) {
    return Ring1_Result_Failure;
  }
  *result = t;
  return Ring1_Result_Success;
#endif
}
