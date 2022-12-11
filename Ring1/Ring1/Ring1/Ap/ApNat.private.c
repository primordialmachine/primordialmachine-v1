#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApNat.private.h"
#undef RING1_AP_PRIVATE


#include "Ring1/Status.h"
#include "Ring1/Intrinsic.h"
#include <malloc.h>
#include <stdio.h>


Ring1_NoDiscardReturn() Ring1_Result
resize
  (
    Ring1_ApNat *x,
    size_t newNumberOfDigits
  )
{
  if (newNumberOfDigits  < 1) {
      Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  size_t oldNumberOfDigits = x->numberOfDigits;
  if (newNumberOfDigits > oldNumberOfDigits) {
    uint8_t *newDigits = realloc(x->digits, sizeof(uint8_t) * newNumberOfDigits);
    if (!newDigits) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    for (size_t i = oldNumberOfDigits; i < newNumberOfDigits; ++i) {
      newDigits[i] = 0;
    }
    x->digits = newDigits;
  } else {
    uint8_t *newDigits = realloc(x->digits, sizeof(uint8_t) * newNumberOfDigits);
    if (!newDigits) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    x->digits = newDigits;   
  }
  x->numberOfDigits = newNumberOfDigits;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
grow
  (
    Ring1_ApNat *x,
    size_t additionalNumberOfDigits
  )
{
  size_t oldNumberOfDigits = x->numberOfDigits;
  size_t availableNumberOfDigits = SIZE_MAX - oldNumberOfDigits;
  if (availableNumberOfDigits < additionalNumberOfDigits) {
    return Ring1_Result_Failure;
  }
  return resize(x, oldNumberOfDigits + additionalNumberOfDigits);
}
