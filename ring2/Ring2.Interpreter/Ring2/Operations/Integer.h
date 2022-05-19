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

#endif // Ring2_Configuration_withInteger

#endif // RING2_OPERATIONS_INTEGER_H_INCLUDED
