// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Integer.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_INTEGER_H_INCLUDED)
#define RING2_OPERATIONS_INTEGER_H_INCLUDED

#include "Ring2/Types.h"
#include "Ring1/Intrinsic/CheckReturn.h"

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

/// @brief
/// Compute the hash value of an <code>Integer</code> value.
/// @param x
/// The <code>Integer</code> value.
/// @return
/// The hash value.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_getHashValue
  (
    Ring2_Integer x
  );

/// @brief
/// Get if a <code>Integer</code> value is in a "hash equal to" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is in the "hash equal to" relation with the other <code>Integer</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_getHashEqual
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Compare two <code>Integer</code> values for equality.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if
///   the first <code>Integer</code> value
/// is equal to
///   the second <code>Integer</code> value
/// . @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isEqualTo
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Get if a <code>Integer</code> value is in a "not equal to" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is not equal to the second <code>Integer</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isNotEqualTo
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Get if an <code>Integer</code> value is in the "lower than" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is in the "lower than" relation with th eother <code>Integer</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isLowerThan
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Get if an <code>Integer</code> value is in the "lower than or equal to" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is in the "lower than or equal to" relation with the second <code>Integer</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isLowerThanOrEqualTo
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Get if a <code>Integer</code> value is in the "greater than" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is in the "greater than" relation with the other <code>Integer</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isGreaterThan
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Get if a <code>Integer</code> value is in the "greater than or equal to" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is in the "greater than or equal to" relation with the other <code>Integer</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Integer_isGreaterThanOrEqualTo
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Compute the sum of a <code>Integer</code> value and another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value, the augend.
/// @param y
/// The second <code>Integer</code> value, the augend.
/// @return
/// The sum <c>x + y</c> of the addend <c>x</c> and the augend <c>y</c>.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_add
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Compute the difference of a <code>Integer</code> value and another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value, the minuend.
/// @param y
/// The second <code>Integer</code> value, the subtrahend.
/// @return
/// The difference <c>x - y</c> of the minuend <c>x</c> and the subtrahend <c>y</c>.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_subtract
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Compute the product of a <code>Integer</code> value and another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value, the multiplier.
/// @param y
/// The second <code>Integer</code> value, the multiplicand.
/// @return
/// The product <c>x * y</c> of the multiplier <c>x</c> and the multiplicand <c>y</c>.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_multiply
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Compute the quotient of a <code>Integer</code> value and another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value, the dividend.
/// @param y
/// The second <code>Integer</code> value, the divisor.
/// @return
/// The quotient <c>x / y</c> of the dividend <c>x</c> and the divisor <c>y</c>.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_divide
  (
    Ring2_Integer x,
    Ring2_Integer y
  );

/// @brief
/// Compute the affirmation of an <code>Integer</code> value.
/// @param x
/// The <code>Integer</code> value.
/// @return
/// The affirmation <c>+x</c>.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_affirmate
  (
    Ring2_Integer x
  );

/// @brief
/// Compute the negation of an <code>Integer</code> value.
/// @param x
/// The <code>Integer</code> value.
/// @return
/// The negation <c>-x</c>.
Ring1_CheckReturn() Ring2_Integer
Ring2_Integer_negate
  (
    Ring2_Integer x
  );
  
#endif // Ring2_Configuration_withInteger

#endif // RING2_OPERATIONS_INTEGER_H_INCLUDED
