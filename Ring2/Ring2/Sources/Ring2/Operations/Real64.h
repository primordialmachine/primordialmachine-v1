// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real64.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_REAL64_H_INCLUDED)
#define RING2_OPERATIONS_REAL64_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Operations/Real64.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

#include "Ring2/Types.h"

/// @brief
/// Compute the hash value of an <code>Real64</code> value.
/// @param x
/// The <code>Real64</code> value.
/// @return
/// The hash value.
Ring1_CheckReturn() Ring2_Integer
Ring2_Real64_getHashValue
  (
    Ring2_Context* context,
    Ring2_Real64 x
  );

/// @brief
/// Get if a <code>Real64</code> value is in a "hash equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in a "hash equal to" relation with the second <code>Real64</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_getHashEqual
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in an "equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in an "equal to" relation with the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in a "not equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in a "not equal to" relation with the second <code>Real64</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if an <code>Real64</code> value is in a "lower than" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in a "lower than" relation with the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if an <code>Real64</code> value is in a "lower than or equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in a "lower than or equal to" relation with the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in a "greater than" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in a "greater than" relation with the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in a "greater than or equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in a "greater than or equal to" relation with the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Compute the sum of a <code>Real64</code> value and another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value, the augend.
/// @param y
/// The second <code>Real64</code> value, the augend.
/// @return
/// The sum <c>x + y</c> of the addend <c>x</c> and the augend <c>y</c>.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_add
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Compute the difference of a <code>Real64</code> value and another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value, the minuend.
/// @param y
/// The second <code>Real64</code> value, the subtrahend.
/// @return
/// The difference <c>x - y</c> of the minuend <c>x</c> and the subtrahend <c>y</c>.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_subtract
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Compute the product of a <code>Real64</code> value and another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value, the multiplier.
/// @param y
/// The second <code>Real64</code> value, the multiplicand.
/// @return
/// The product <c>x * y</c> of the multiplier <c>x</c> and the multiplicand <c>y</c>.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_multiply
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Compute the quotient of a <code>Real64</code> value and another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value, the dividend.
/// @param y
/// The second <code>Real64</code> value, the divisor.
/// @return
/// The quotient <c>x / y</c> of the dividend <c>x</c> and the divisor <c>y</c>.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_divide
  (
    Ring2_Context* context,
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Compute the affirmation of an <code>Real64</code> value.
/// @param x
/// The <code>Real64</code> value.
/// @return
/// The affirmation <c>+x</c>.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_affirmate
  (
    Ring2_Context* context,
    Ring2_Real64 x
  );

/// @brief
/// Compute the negation of an <code>Real64</code> value.
/// @param x
/// The <code>Real64</code> value.
/// @return
/// The negation <c>-x</c>.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_negate
  (
    Ring2_Context* context,
    Ring2_Real64 x
  );
  
/// @brief Convert an <code>Real64</code> value to a <code>String</code> value.
/// @param x The <code>Real64</code> value.
/// @return The <code>String</code> value.
Ring1_CheckReturn() Ring2_String *
Ring2_Real64_toString
  (
    Ring2_Context* context,
    Ring2_Real64 x
  );

/// @brief Convert a <code>String</code> value to a <code>Real64</code> value.
/// @param x The <code>String</code> value.
/// @return The <code>Real64</code> value.
/// @error Ring1_Status_ConversionFailed
/// The <code>String</code> value cannot be converetd to a <code>Real64</code> value.
/// @error Ring1_Status_AllocationFailed
/// An allocation failed.
Ring1_CheckReturn() Ring2_Real64
Ring2_Real64_fromString
  (
    Ring2_Context* context,
    Ring2_String *x
  );

#endif // Ring2_Configuration_withReal

#endif // RING2_OPERATIONS_REAL64_H_INCLUDE
