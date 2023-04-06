#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApInt.h"
#undef RING1_AP_PRIVATE


#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApNat.private.h"
#undef RING1_AP_PRIVATE
#include "Ring1/Status.h"
#include "Ring1/Intrinsic/_Include.h"
#include <malloc.h>
#include <stdio.h>


Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_print
  (
    Ring1_ApInt *self
  )
{
  if (!self->sign) {
    fprintf(stdout, "-");   
  }
  return Ring1_ApNat_print(&self->magnitude);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_u8
  (
    Ring1_ApInt *self,
    uint8_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApInt_initialize_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_u16
  (
    Ring1_ApInt *self,
    uint16_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApInt_initialize_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_u32
  (
    Ring1_ApInt *self,
    uint32_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApInt_initialize_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_u64
  (
    Ring1_ApInt *self,
    uint64_t value,
    int64_t numberOfDigits
  )
{
  self->sign = true;
  return Ring1_ApNat_initialize_u64(&self->magnitude, value, numberOfDigits);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_s8
  (
    Ring1_ApInt* self,
    int8_t value,
    int64_t leastNumberOfDigits
  )
{ return Ring1_ApInt_initialize_s64(self, value, leastNumberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_s16
  (
    Ring1_ApInt* self,
    int16_t value,
    int64_t leastNumberOfDigits
  )
{ return Ring1_ApInt_initialize_s64(self, value, leastNumberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_s32
  (
    Ring1_ApInt* self,
    int32_t value,
    int64_t leastNumberOfDigits
  )
{ return Ring1_ApInt_initialize_s64(self, value, leastNumberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_initialize_s64
  (
    Ring1_ApInt *self,
    int64_t value,
    int64_t numberOfDigits
  )
{
  uint64_t temporary;
  if (value < 0) {
    self->sign = false;
    if (value == INT64_MIN) {
      // As |INT64_MIN| > |INT64_MAX| we cannot simply do value = -value.
      // Rather, we cast INT64_MAX into uint64_t and then add +1.
      temporary = ((uint64_t)INT64_MAX) + 1;
    } else {
      value = -value;
      temporary = value;
    }
  } else {
    self->sign = true;
    temporary = (int64_t)value;
  }
  return Ring1_ApNat_initialize_u64(&self->magnitude, temporary, numberOfDigits);
}

Ring1_Result
Ring1_ApInt_uninitialize
  (
    Ring1_ApInt *self
  )
{
  if (!self) {
    return Ring1_Result_Success;
  }
  return Ring1_ApNat_uninitialize(&self->magnitude);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_setZero
  (
    Ring1_ApInt* self,
    int64_t numberOfDigits
  )
{
  if (Ring1_ApNat_setZero(&self->magnitude, numberOfDigits)) {
    return Ring1_Result_Failure;
  }
  self->sign = true;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_negate
  (
    Ring1_ApInt* self
  )
{
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  self->sign = !self->sign;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_power
  (
    Ring1_ApInt* self,
    int64_t n
  )
{
  if (!self) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (Ring1_ApNat_power(&self->magnitude, n)) {
    return Ring1_Result_Failure;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_add
  (
    Ring1_ApInt* self,
    Ring1_ApInt* other
  )
{
  if (self->sign != other->sign) {
    if (!self->sign) {
      // self is negative, other is positive
      int64_t relation;
      Ring1_ApNat_compare(&relation, &self->magnitude, &other->magnitude);
      // |self| < |other| => +(|other|-|self|)
      if (relation < 0) {
        self->sign = true;
        Ring1_ApNat_subtract2(&self->magnitude, &other->magnitude, &self->magnitude);
      }
      // |self| > |other| => -(|self|-|other|)
      else if (relation > 0) {
        self->sign = false;
        Ring1_ApNat_subtract2(&self->magnitude, &self->magnitude, &other->magnitude);
      }
      // |self| = |other| => +0
      else {
        self->sign = true;
        Ring1_ApNat_set_u64(&self->magnitude, 0, 0);
      }
    } else {
      // other is negative, self is positive
      int64_t relation;
      Ring1_ApNat_compare(&relation, &self->magnitude, &other->magnitude);
      // |self| < |other| => -(|other|-|self|)
      if (relation < 0) {
        self->sign = false;
        Ring1_ApNat_subtract2(&self->magnitude, &other->magnitude, &self->magnitude);
      }
      // |self| > |other| => +(|self|-|other|)
      else if (relation > 0) {
        self->sign = true;
        Ring1_ApNat_subtract2(&self->magnitude, &self->magnitude, &other->magnitude);
      }
      // |self| = |other| => +0
      else {
        self->sign = true;
        Ring1_ApNat_set_u64(&self->magnitude, 0, 0);
      }  
    }
  } else {
    Ring1_ApNat_add2(&self->magnitude, &self->magnitude, &other->magnitude);
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_multiply
  (
    Ring1_ApInt* self,
    Ring1_ApInt* other
  )
{
  bool sign = self->sign != other->sign;
  if (Ring1_ApNat_multiply(&self->magnitude, &other->magnitude)) {
    return Ring1_Result_Failure;
  }
  self->sign = sign;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_assign
  (
    Ring1_ApInt* self,
    Ring1_ApInt* other
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (self == other) {
    return Ring1_Result_Success;
  }
  if (Ring1_ApNat_assign(&self->magnitude, &other->magnitude)) {
    return Ring1_Result_Failure;
  }
  self->sign = other->sign;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_compare
  (
    int64_t* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t temporary;
  Ring1_ApNat_compare(&temporary, &self->magnitude, &other->magnitude);
  if (0 == temporary) {
    *result = temporary;
    return Ring1_Result_Success;
  }
  if (self->sign == other->sign) {
    if (self->sign == false) {
      // both negative. The ApInt with the lesser magnitude is the lesser ApInt.
      *result = -temporary;
      return Ring1_Result_Success;
    } else {
      // both positive. The ApInt with the greater magnitude is the greater ApInt.
      *result = +temporary;
      return Ring1_Result_Success;
    }
  } else {
    if (self->sign == false) {
      // This ApInt is negative,
      // hence it is the smaller value.
      *result = -1;
      return Ring1_Result_Success;
    } else {
      // This ApInt is positive,
      // hece it is the greater value.
      *result = +1;
      return Ring1_Result_Success;
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_toS64
  (
    int64_t* result,
    Ring1_ApInt* self
  )
{
  uint64_t temporary;
  if (Ring1_ApNat_toU64(&temporary, &self->magnitude)) {
    return Ring1_Result_Failure;
  }
  // Basically, same check as temporary > (INT64_MAX + 1).
  if (temporary > 0 && (temporary - 1 > INT64_MAX)) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  if (!self->sign) {
    *result = -((int64_t)temporary);
    return Ring1_Result_Success;
  } else {
    *result = (int64_t)temporary;
    return Ring1_Result_Success;  
  }
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApInt_toU64
  (
    uint64_t* result,
    Ring1_ApInt* self
  )
{
  if (!self->sign) {
    Ring1_Status_set(Ring1_Status_ConversionFailed);
    return Ring1_Result_Failure;
  }
  uint64_t temporary;
  if (Ring1_ApNat_toU64(&temporary, &self->magnitude)) {
    return Ring1_Result_Failure;
  }
  *result = temporary;
  return Ring1_Result_Success;
}
