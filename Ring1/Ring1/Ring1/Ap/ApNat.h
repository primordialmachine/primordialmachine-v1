#if !defined(RING1_AP_APNAT_H_INCLUDED)
#define RING1_AP_APNAT_H_INCLUDED


#if !defined(RING1_AP_PRIVATE) || 1 != RING1_AP_PRIVATE
#error("Do not include `Ring1/Ap/ApNat.h` directly. Include `Ring1/_Include.h` instead.")
#endif


#include "Ring1/Annotations/_Include.h"
#include "Ring1/Result.h"
#include <inttypes.h>
#include <stdbool.h>


/// An array of n digits x[0], x[1], ..., x[n-1] each with a value between 0 and 9.
/// The digits represent a number
/// x[0] * 10^0 + x[1] * 10^1 + x[2] * 10^2 + ... + x[n-1] * 10^(n-1)
typedef struct Ring1_ApNat {
  size_t numberOfDigits;   ///< length of the array pointed to by @a a.
  uint8_t *digits; ///< array of decimal digits.
} Ring1_ApNat;

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_print
  (
    Ring1_ApNat* self
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u8
  (
    Ring1_ApNat* self,
    uint8_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u16
  (
    Ring1_ApNat* self,
    uint16_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u32
  (
    Ring1_ApNat* self,
    uint32_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_initialize_u64
  (
    Ring1_ApNat* self,
    uint64_t value,
    int64_t leastNumberOfDigits
  );

Ring1_Result
Ring1_ApNat_uninitialize
  (
    Ring1_ApNat* self
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u8
  (
    Ring1_ApNat* self,
    uint8_t value,
    int64_t numberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u16
  (
    Ring1_ApNat* self,
    uint16_t value,
    int64_t numberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u32
  (
    Ring1_ApNat* self,
    uint32_t value,
    int64_t numberOfDigits
  );

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_set_u64
  (
    Ring1_ApNat* self,
    uint64_t value,
    int64_t numberOfDigits
  );

/// @brief Assign this ApNat the value zero.
/// @param self A pointer to this ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_setZero
  (
    Ring1_ApNat* self,
    int64_t numberOfDigits
  );

/// @brief Compute the sum of this ApNat object and another ApNat object and assign the values of the sum to this ApNat object.
/// @param self A pointer to this ApNat object.
/// @param other A pointer to the other ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_add
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  );

/// @brief Compute the sum of one ApNat object and another ApNat object and assign the values of the sum to this ApNat object.
/// @param self A pointer to this ApNat object.
/// @param first A pointer to the 1st ApNat object.
/// @param second A pointer to the 2nd ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_add2
  (
    Ring1_ApNat* self,
    Ring1_ApNat* first,
    Ring1_ApNat* second
  );

/// @brief Compute the difference of this ApNat object and another ApNat object and assign the values of the difference to this ApNat object.
/// @param self A pointer to this ApNat object.
/// @param other A pointer to the other ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
/// @remarks
/// The values of this ApNat object are not modified if an error occurs.
/// @error #Ring1_Status_NumericOverflow the first ApNat object is smaller than the other ApNat object
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_subtract
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  );

/// @brief Compute the difference of one ApNat object and another ApNat object and assign the values of the difference to this ApNat object.
/// @param self A pointer to this ApNat object.
/// @param first A pointer to the first ApNat object.
/// @param second A pointer to the second ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
/// @remarks
/// The values of this ApNat object are not modified if an error occurs.
/// @error #Ring1_Status_NumericOverflow the first ApNat object is smaller than the other ApNat object
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_subtract2
  (
    Ring1_ApNat* self,
    Ring1_ApNat* first,
    Ring1_ApNat* second
  );

/// @brief Compute the product of one ApNat object and another ApNat object and assign the values of the product to this ApNat object.
/// @param self A pointer to this ApNat object.
/// @param first A pointer to the first ApNat object.
/// @param second A pointer to the second ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
/// @remarks
/// The values of this ApNat object are not modified if an error occurs.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_multiply
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  );

/// @brief
/// Assign the values of another ApNat object to this ApNat object.
/// @param self
/// A pointer to this ApNat object.
/// @param other
/// A pointer to the other ApNat object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_assign
  (
    Ring1_ApNat* self,
    Ring1_ApNat* other
  );

/// @brief
/// Compare two @a ApNat object.
/// @param result
/// A pointer to a <code>int64_t</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
/// @post
/// <code>*result</code> is assigned
/// - @a -1 (@a +1) if this @a ApNat object is smaller (greater) than the other @a ApNat object.
/// - @a 0 if both @a ApNat objects are equal. 
Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_compare
  (
    int64_t* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  );

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_isLowerThan
  (
    bool* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  int64_t relation;
  if (Ring1_ApNat_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation < 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_isLowerThanOrEqualTo
  (
    bool* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  int64_t relation;
  if (Ring1_ApNat_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation <= 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_isGreaterThan
  (
    bool* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  int64_t relation;
  if (Ring1_ApNat_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation > 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_isGreaterThanOrEqualTo
  (
    bool* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  int64_t relation;
  if (Ring1_ApNat_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation >= 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_isEqualTo
  (
    bool* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  int64_t relation;
  if (Ring1_ApNat_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation == 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApNat object.
/// @param other
/// A pointer to this @a ApNat object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_isNotEqualTo
  (
    bool* result,
    Ring1_ApNat const* self,
    Ring1_ApNat const* other
  )
{
  int64_t relation;
  if (Ring1_ApNat_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation != 0;
  return Ring1_Result_Success;
}

Ring1_NoDiscardReturn() Ring1_Result
Ring1_ApNat_toU64
  (
    uint64_t* result,
    Ring1_ApNat* self
  );


#endif // RING1_AP_APNAT_H_INCLUDED
