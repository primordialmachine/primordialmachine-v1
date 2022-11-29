#if !defined(RING1_AP_APINT_H_INCLUDED)
#define RING1_AP_APINT_H_INCLUDED


#if !defined(RING1_AP_PRIVATE) || 1 != RING1_AP_PRIVATE
#error("Do not include `Ring1/Ap/ApInt.h` directly. Include `Ring1/_Include.h` instead.")
#endif


#include "Ring1/Ap/ApNat.h"


/// An ApNat represents the magnitude and a boolean value denotes the sign.
typedef struct Ring1_ApInt {
  Ring1_ApNat magnitude;
  bool sign; ///< @brief The number is positive or positive zero if @a true, the number is negative or negative zero if @a false.
} Ring1_ApInt;

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_print
  (
    Ring1_ApInt* self
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_u8
  (
    Ring1_ApInt* self,
    uint8_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_u16
  (
    Ring1_ApInt* self,
    uint16_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_u32
  (
    Ring1_ApInt* self,
    uint32_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_u64
  (
    Ring1_ApInt* self,
    uint64_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_s8
  (
    Ring1_ApInt* self,
    int8_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_s16
  (
    Ring1_ApInt* self,
    int16_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_s32
  (
    Ring1_ApInt* self,
    int32_t value,
    int64_t leastNumberOfDigits
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_initialize_s64
  (
    Ring1_ApInt* self,
    int64_t value,
    int64_t leastNumberOfDigits
  );

Ring1_Result
Ring1_ApInt_uninitialize
  (
    Ring1_ApInt* self
  );

/// @brief Compute the sum of this ApInt object and another ApInt object and assign the values of the sum to this ApInt object.
/// @param self A pointer to this ApInt object.
/// @param other A pointer to the other ApInt object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_add
  (
    Ring1_ApInt* self,
    Ring1_ApInt* other
  );

/// @brief Assign the values of another ApInt object to this ApInt object.
/// @param self A pointer to this ApInt object.
/// @param other A pointer to the other ApInt object.
/// @return
/// #Ring_Result_Success on success.
/// #Ring_Result_Failure on failure.
Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_assign
  (
    Ring1_ApInt* self,
    Ring1_ApInt* other
  );

/// @brief
/// Compare two @a ApInt objects.
/// @param result
/// A pointer to a <code>int64_t</code> variable.
/// @param self
/// A pointer to this @a ApInt object.
/// @param other
/// A pointer to this @a ApInt object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
/// @post
/// <code>*result</code> is assigned
/// - @a -1 (@a +1) if this @a ApInt object is smaller (greater) than the other @a ApInt object.
/// - @a 0 if both @a ApInt objects are equal. 
Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_compare
  (
    int64_t* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  );

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApInt object.
/// @param other
/// A pointer to this @a ApInt object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_isLowerThan
  (
    bool* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t relation;
  if (Ring1_ApInt_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation < 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApInt object.
/// @param other
/// A pointer to this @a ApInt object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_isLowerThanOrEqualTo
  (
    bool* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t relation;
  if (Ring1_ApInt_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation <= 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApInt object.
/// @param other
/// A pointer to this @a ApInt object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_isGreaterThan
  (
    bool* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t relation;
  if (Ring1_ApInt_compare(&relation, self, other)) {
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
Ring1_Inline() Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_isGreaterThanOrEqualTo
  (
    bool* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t relation;
  if (Ring1_ApInt_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation >= 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApInt object.
/// @param other
/// A pointer to this @a ApInt object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_isEqualTo
  (
    bool* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t relation;
  if (Ring1_ApInt_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation == 0;
  return Ring1_Result_Success;
}

/// @param result
/// A pointer to a <code>bool</code> variable.
/// @param self
/// A pointer to this @a ApInt object.
/// @param other
/// A pointer to this @a ApInt object.
/// @return
/// #Ring1_Result_Success on success.
/// #Ring1_Result_Failure on failure.
Ring1_Inline() Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_isNotEqualTo
  (
    bool* result,
    Ring1_ApInt const* self,
    Ring1_ApInt const* other
  )
{
  int64_t relation;
  if (Ring1_ApInt_compare(&relation, self, other)) {
    return Ring1_Result_Failure;
  }
  *result = relation != 0;
  return Ring1_Result_Success;
}

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_toS64
  (
    int64_t* result,
    Ring1_ApInt* self
  );

Ring1_NoDiscardResult() Ring1_Result
Ring1_ApInt_toU64
  (
    uint64_t* result,
    Ring1_ApInt* self
  );


#endif // RING1_AP_APINT_H_INCLUDED
