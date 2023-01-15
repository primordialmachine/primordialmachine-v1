#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApNat.h"
#undef RING1_AP_PRIVATE


#define RING1_AP_PRIVATE (1)
#include "Ring1/Ap/ApNat.private.h"
#undef RING1_AP_PRIVATE
#include "Ring1/Status.h"
#include "Ring1/Crt/_Include.h"
#include "Ring1/Intrinsic/_Include.h"
#include <assert.h>
#include <stdio.h>


static Ring1_NoDiscardReturn() Ring1_Result
trim
  (
    Ring1_ApNat *self
  )
{
  for (size_t i = self->numberOfDigits; i > 0; --i) {
    if (self->digits[i - 1] != 0) {
      self->numberOfDigits = i;
      break;
    }
  }
  if (self->numberOfDigits == 0) {
    self->numberOfDigits = 1;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_print
  (
    Ring1_ApNat *self
  )
{
  size_t i = self->numberOfDigits;
  // Skip trailing zeroes.
  for (; i > 0; --i) {
    if (self->digits[i - 1] != 0) {
      break;
    }
  }
  for (; i > 0; --i) {
    uint8_t v = self->digits[i - 1];
    fprintf(stdout, "%"PRIu8, v);
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u8
  (
    Ring1_ApNat *self,
    uint8_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApNat_initialize_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u16
  (
    Ring1_ApNat *self,
    uint16_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApNat_initialize_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u32
  (
    Ring1_ApNat *self,
    uint32_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApNat_initialize_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u64
  (
    Ring1_ApNat *self,
    uint64_t value,
    int64_t numberOfDigits
  )
{
  size_t requiredNumberOfDigits = Ring1_countDecimalDigits_u64(value); 
  if (requiredNumberOfDigits > numberOfDigits) {
    numberOfDigits = requiredNumberOfDigits;
  }
  // Allocate array.
  self->digits = crt_malloc(sizeof(uint8_t) * numberOfDigits);
  if (!self->digits) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  // Initialize array with zeroes.
  crt_memset(self->digits, 0, sizeof(uint8_t)* numberOfDigits);
  self->numberOfDigits = numberOfDigits;

  size_t i = 0;
  uint64_t t0 = value;
  do {
    uint8_t t1 = t0 % 10;
    self->digits[i++] = t1;
    t0 /= 10;
  } while (t0);

  // Return success.
  return Ring1_Result_Success;
}

Ring1_Result
Ring1_ApNat_uninitialize
  (
    Ring1_ApNat *self
  )
{
  if (!self) {
    return Ring1_Result_Success;
  }
  crt_free(self->digits);
  self->digits = 0;
  self->numberOfDigits = 0;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u8
  (
    Ring1_ApNat* self,
    uint8_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApNat_set_u16(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u16
  (
    Ring1_ApNat* self,
    uint16_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApNat_set_u32(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u32
  (
    Ring1_ApNat* self,
    uint32_t value,
    int64_t numberOfDigits
  )
{ return Ring1_ApNat_set_u64(self, value, numberOfDigits); }

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u64
  (
    Ring1_ApNat* self,
    uint64_t value,
    int64_t numberOfDigits
  )
{
  size_t requiredNumberOfDigits = Ring1_countDecimalDigits_u64(value); 
  if (requiredNumberOfDigits > numberOfDigits) {
    numberOfDigits = requiredNumberOfDigits;
  }
  // Reallocate array.
  self->digits = crt_realloc(self->digits, sizeof(uint8_t) * numberOfDigits);
  if (!self->digits) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  if (self->numberOfDigits < numberOfDigits) {
    for (size_t i = self->numberOfDigits, n = numberOfDigits; i < n; ++i) {
      self->digits[i] = 0;
    }
  }
  self->numberOfDigits = numberOfDigits;
  size_t i = 0;
  uint64_t t0 = value;
  do {
    uint8_t t1 = t0 % 10;
    self->digits[i++] = t1;
    t0 /= 10;
  } while (t0);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_setZero
  (
    Ring1_ApNat* self,
    int64_t numberOfDigits
  )
{
  return Ring1_ApNat_set_u8(self, 0, numberOfDigits);
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_add
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  )
{
  // Compute the maximum of both number of digits.
  size_t numberOfDigits = self->numberOfDigits;
  if (numberOfDigits < other->numberOfDigits) {
    numberOfDigits = other->numberOfDigits;
  }
  // If the maximum is equal to SIZE_MAX,
  // then we pessimistically assume an overflow will occur.
  if (numberOfDigits == SIZE_MAX) {
    Ring1_Status_set(Ring1_Status_TooLong);
    return Ring1_Result_Failure;
  }
  // Ensure both summands have the same number of digits.
  if (grow(self, numberOfDigits + 1 - self->numberOfDigits)) {
    return Ring1_Result_Failure;
  }
  if (grow(other, numberOfDigits + 1 - other->numberOfDigits)) {
    return Ring1_Result_Failure;
  }

  uint16_t carry = 0;
  for (size_t i = 0, n = numberOfDigits; i < n; ++i) {
    uint16_t x = self->digits[i];
    uint16_t y = other->digits[i];
    uint16_t z = x + y + carry;
    if (z > 9) {
      carry = 1;
      z -= 10;
    } else {
      carry = 0;
    }
    self->digits[i] = z;
  }
  if (carry) {
    self->digits[numberOfDigits] = carry;
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_add2
  (
    Ring1_ApNat* self,
    Ring1_ApNat* first,
    Ring1_ApNat* second
  )
{
  Ring1_ApNat temporary;
  if (Ring1_ApNat_initialize_u8(&temporary, 0, 0)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_ApNat_assign(&temporary, first)) {
    Ring1_ApNat_uninitialize(&temporary);
    return Ring1_Result_Failure;
  }
  if (Ring1_ApNat_add(&temporary, second)) {
    Ring1_ApNat_uninitialize(&temporary);
    return Ring1_Result_Failure; 
  }
  if (Ring1_ApNat_assign(self, &temporary)) {
    Ring1_ApNat_uninitialize(&temporary);
    return Ring1_Result_Failure;
  }
  Ring1_ApNat_uninitialize(&temporary);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_subtract
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  )
{
  if (trim(self) || trim(other)) {
    return Ring1_Result_Failure;
  }
  // Compute the maximum of both number of digits.
  size_t numberOfDigits = self->numberOfDigits;
  if (numberOfDigits < other->numberOfDigits) {
    numberOfDigits = other->numberOfDigits;
  }
  if (self->numberOfDigits < other->numberOfDigits) {
    Ring1_Status_set(Ring1_Status_NumericOverflow);
    return Ring1_Result_Failure; 
  } else if (self->numberOfDigits > other->numberOfDigits) {
    // The number of digits in self is greater than the number of digits in other.
    // An underflow cannot occur.
    if (grow(other, numberOfDigits - other->numberOfDigits)) {
      return Ring1_Result_Failure;
    }
    uint16_t borrow = 0;
    for (size_t i = 0, n = numberOfDigits; i < n; ++i) {
      uint16_t x = self->digits[i];
      uint16_t y = other->digits[i];
      uint16_t z;
      // We gotta subtract more than we have.
      if (y > x) {
        x += 10;
        // The least value of x before adding 10 is 0, so x is at least 10.
        // As borrow is at max 1 and y is at max 9, we can safely subtract y and borrow.
        z = x - y - borrow;
        borrow = 1;
      } else if (y < x) {
        // As x is at least greater than y by 1, we can safely subtract y and borrow.
        z = x - y - borrow;  
        borrow = 0;
      } else {
        borrow = 0;
        z = 0;
      }
      self->digits[i] = z;
    }
    assert(borrow == 0);
  } else {
    // The number of digits in self is equal to the number of digits in other.
    // An underflow can occur.
    uint8_t *temporary = crt_malloc(sizeof(uint8_t) * numberOfDigits);
    if (!temporary) {
      Ring1_Status_set(Ring1_Status_AllocationFailed);
      return Ring1_Result_Failure;
    }
    uint16_t borrow = 0;
    for (size_t i = 0, n = numberOfDigits; i < n; ++i) {
      uint16_t x = self->digits[i];
      uint16_t y = other->digits[i];
      uint16_t z;
      // We gotta subtract more than we have.
      if (y + borrow > x) {
        x += 10;
        // The least value of x before adding 10 is 0, so x is at least 10.
        // As borrow is at max 1 and y is at max 9, we can safely subtract y and borrow.
        z = x - y - borrow;
        borrow = 1;
      } else if (y + borrow < x) {
        // As x is at least greater than y by 1, we can safely subtract y and borrow.
        z = x - y - borrow;  
        borrow = 0;
      } else {
        borrow = 0;
        z = 0;
      }
      temporary[i] = z;
    }
    if (borrow) {
      crt_free(temporary);
      Ring1_Status_set(Ring1_Status_NumericOverflow);
      return Ring1_Result_Failure;
    } else {
      crt_free(self->digits);
      self->digits = temporary;
    }
  }
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_subtract2
  (
    Ring1_ApNat* self,
    Ring1_ApNat* first,
    Ring1_ApNat* second
  )
{
  Ring1_ApNat temporary;
  if (Ring1_ApNat_initialize_u8(&temporary, 0, 0)) {
    return Ring1_Result_Failure;
  }
  if (Ring1_ApNat_assign(&temporary, first)) {
    Ring1_ApNat_uninitialize(&temporary);
    return Ring1_Result_Failure;
  }
  if (Ring1_ApNat_subtract(&temporary, second)) {
    Ring1_ApNat_uninitialize(&temporary);
    return Ring1_Result_Failure; 
  }
  if (Ring1_ApNat_assign(self, &temporary)) {
    Ring1_ApNat_uninitialize(&temporary);
    return Ring1_Result_Failure;
  }
  Ring1_ApNat_uninitialize(&temporary);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_multiply
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  )
{
  // if self has n digits and other has m digits,
  // then the product has at most n + m digits.
  uint8_t *temporary = crt_malloc(sizeof(uint8_t) * (self->numberOfDigits + other->numberOfDigits));
  if (!temporary) {
    Ring1_Status_set(Ring1_Status_AllocationFailed);
    return Ring1_Result_Failure;
  }
  for (size_t i = 0; i < self->numberOfDigits + other->numberOfDigits; ++i) {
    temporary[i] = 0;
  }

  size_t j = 0;
  for (size_t i = 0; i < other->numberOfDigits; ++i) {
    uint8_t carry = 0;
    uint8_t current = 0;
    j = i;
    for (; j < self->numberOfDigits + i; ++j) {
      current = temporary[j]
              + (other->digits[i] * self->digits[j - i])
              + carry;
      carry = current / 10;
      temporary[j] = current % 10;
    }
    if (carry > 0) {
      current = temporary[j] + carry;
      carry = current / 10;
      temporary[j] = current % 10;
    }
  }

  crt_free(self->digits);
  self->digits = temporary;
  self->numberOfDigits = j;

  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_assign
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (self == other) {
    return Ring1_Result_Success;
  }
  if (self->numberOfDigits < other->numberOfDigits) {
    if (grow(self, other->numberOfDigits - self->numberOfDigits)) {
      return Ring1_Result_Failure;
    }
  }
  crt_memcpy(self->digits, other->digits, other->numberOfDigits);
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_compare
  (
    int64_t* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  size_t i = self->numberOfDigits;
  size_t j = other->numberOfDigits;
  // Skip trailing zeroes.
  for (; i > 0; --i) {
    if (self->digits[i - 1] != 0) {
      break;
    }
  }
  for (; j > 0; --j) {
    if (other->digits[i - 1] != 0) {
      break;
    }
  }

  // Compare by number of digits.
  if (i < j) {
    *result = -1;
    return Ring1_Result_Success;
  } else if (i > j) {
    *result = +1;
    return Ring1_Result_Success;
  }

  //
  for (; i > 0; --i) {
    if (self->digits[i-1] < other->digits[i-1]) {
      *result = -1;
      return Ring1_Result_Success;
    } else if (self->digits[i-1] > other->digits[i-1]) {
      *result = +1;
      return Ring1_Result_Success;
    }
  }

  //
  *result = 0;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_toU64
  (
    uint64_t* result,
    Ring1_ApNat* self
  )
{
  uint64_t v = 0;
  size_t i = self->numberOfDigits;
  // Skip trailing zeroes.
  for (; i > 0; --i) {
    if (self->digits[i - 1] != 0) {
      break;
    }
  }
  for (; i > 0; --i) {
    uint8_t u = self->digits[i - 1];
    v *= 10;
    v += u;
  }
  *result = v;
  return Ring1_Result_Success;
}
