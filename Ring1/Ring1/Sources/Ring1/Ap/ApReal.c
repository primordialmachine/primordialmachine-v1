#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApReal.h"
#undef RING1_AP_PRIVATE


#include "Ring1/Status.h"
#include "Ring1/Intrinsic/_Include.h"
#include <malloc.h>
#include <stdio.h>


Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u8
  (
    Ring1_ApReal *self,
    int64_t exponent,
    uint8_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApReal_initialize_u64(self, exponent, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u16
  (
    Ring1_ApReal *self,
    int64_t exponent,
    uint16_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApReal_initialize_u64(self, exponent, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u32
  (
    Ring1_ApReal *self,
    int64_t exponent,
    uint32_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApReal_initialize_u64(self, exponent, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_u64
  (
    Ring1_ApReal *self,
    int64_t exponent,
    uint64_t value,
    int64_t numberOfDigits
  )
{
  self->exponent = exponent;
  return Ring1_ApInt_initialize_u64(&self->integer, value, numberOfDigits);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s8
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int8_t value,
    int64_t leastNumberOfDigits
  )
{ return Ring1_ApReal_initialize_s64(self, exponent, value, leastNumberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s16
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int16_t value,
    int64_t leastNumberOfDigits
  )
{ return Ring1_ApReal_initialize_s64(self, exponent, value, leastNumberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s32
  (
    Ring1_ApReal* self,
    int64_t exponent,
    int32_t value,
    int64_t leastNumberOfDigits
  )
{ return Ring1_ApReal_initialize_s64(self, exponent, value, leastNumberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_s64
  (
    Ring1_ApReal *self,
    int64_t exponent,
    int64_t value,
    int64_t numberOfDigits
  )
{
  self->exponent = exponent;
  return Ring1_ApInt_initialize_s64(&self->integer, value, numberOfDigits);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_f32
  (
    Ring1_ApReal* self,
    float value
  )
{
  bool sign;
  int32_t exponent, significant;
  if (Ring1_Fp_split_f32(value, &sign, &significant, &exponent, true)) {
    return Ring1_Result_Failure;
  }
  // As |INTx_MIN|+1=|INTx_MAX|, hence overflow is not possible.
  if (Ring1_ApInt_initialize_s32(&self->integer, sign ? significant : -significant, 0)) {
    return Ring1_Result_Failure;
  }
  self->exponent = exponent;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_initialize_f64
  (
    Ring1_ApReal* self,
    double value
  )
{
  bool sign;
  int64_t exponent, significant;
  if (Ring1_Fp_split_f64(value, &sign, &significant, &exponent, true)) {
    return Ring1_Result_Failure;
  }

  // Ring1_Fp_split_f64 returns the following number
  // sign * sig * 2^e
  // 
  // However, the ApReal representation is
  // sign * sig' * 10^e'

  // We compute a significant sig' and an exponent e' such that
  // sign * sig' * 10^e' = sign * sig * 2^e
  // holds.

  // If the exponent e is 0 or positive,
  // then we let sig':= sig * pow(two, e) and e' := 0.
  // 
  // However, if the exponent is negative, then we compute v  such that
  // sign * sig' * v * 10^e' = sign * sig * 2^e with sig' := sig and e' := e.
  // Let us compute v.
  // sign * sig' * v * 10^e' = sign * sig * 2^e | sig' := sig and e' := e
  // v * 10^e = 2^e                             | x * a = b <=> a = b / x
  // v = 2^e / 10^e                             | (a^n) / (b^n) <=> (a/b)^n
  // v = (2/10)^e                               | 
  // v = (1/5)^e                                |
  // v = (1^e / 5^e)                            | e < 0
  // v = (1^-|e| / 5^-|e|)                      |
  // v = (5^|e| / 1^|e|)                        |
  // v = 5^|e|                                  |

  if (exponent < 0) {
    Ring1_ApInt temporary;
    if (Ring1_ApInt_initialize_u8(&temporary, 5, 0)) {
      return Ring1_Result_Failure;
    }
    // Negation cannot overflow (see range of exponent as specified by Ring1_Fp_split_f64).
    if (Ring1_ApInt_power(&temporary, -exponent)) {
      Ring1_ApInt_uninitialize(&temporary);
      return Ring1_Result_Failure;
    }
    // As |INTx_MIN|+1=|INTx_MAX|, hence overflow is not possible.
    if (Ring1_ApInt_initialize_u64(&self->integer, sign ? significant : -significant, 0)) {
      Ring1_ApInt_uninitialize(&temporary);
      return Ring1_Result_Failure;
    }
    if (Ring1_ApInt_multiply(&self->integer, &temporary)) {
      Ring1_ApInt_uninitialize(&temporary);
      return Ring1_Result_Failure;
    }
    Ring1_ApInt_uninitialize(&temporary);
    self->exponent = -exponent;
    return Ring1_Result_Success;
  } else {
    Ring1_ApInt temporary;
    if (Ring1_ApInt_initialize_u8(&temporary, 2, 0)) {
      return Ring1_Result_Failure;
    }
    if (Ring1_ApInt_power(&temporary, exponent)) {
      Ring1_ApInt_uninitialize(&temporary);
      return Ring1_Result_Failure;
    }
    self->exponent = 0;
    return Ring1_Result_Success;
  }
}

Ring1_Result
Ring1_ApReal_uninitialize
  (
    Ring1_ApReal *self
  )
{
  if (!self) {
    return Ring1_Result_Success;
  }
  return Ring1_ApInt_uninitialize(&self->integer);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApReal_set
  (
    Ring1_ApReal* self,
    Ring1_ApInt* integer,
    int64_t exponent
  )
{
  if (Ring1_ApInt_assign(&self->integer, integer)) {
    return Ring1_Result_Failure;
  }
  self->exponent = exponent;
  return Ring1_Result_Success;
}
