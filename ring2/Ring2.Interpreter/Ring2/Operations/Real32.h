// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real32.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_REAL32_H_INCLUDED)
#define RING2_OPERATIONS_REAL32_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring2/Types.h"

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

/// @brief
/// Compute the hash value of an <code>Real32</code> value.
/// @param x
/// The <code>Real32</code> value.
/// @return
/// The hash value.
Ring1_CheckReturn() Ring2_Integer
Ring2_Real32_getHashValue
  (
    Ring2_Real32 x
  );

/// @brief
/// Get if a <code>Real32</code> value is in a "hash equal to" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is in the "hash equal to" relation with the other <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_getHashEqual
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief
/// Get if a <code>Real32</code> value is in a "equal to" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is equal to the second <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isEqualTo
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief
/// Get if a <code>Real32</code> value is in a "not equal to" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is not equal to the second <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isNotEqualTo
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief
/// Get if an <code>Real32</code> value is in the "lower than" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is in the "lower than" relation with th eother <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isLowerThan
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief
/// Get if an <code>Real32</code> value is in the "lower than or equal to" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is in the "lower than or equal to" relation with the second <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isLowerThanOrEqualTo
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief
/// Get if a <code>Real32</code> value is in the "greater than" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is in the "greater than" relation with the other <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isGreaterThan
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief
/// Get if a <code>Real32</code> value is in the "greater than or equal to" relation with another <code>Real32</code> value.
/// @param x
/// The first <code>Real32</code> value.
/// @param y
/// The second <code>Real32</code> value.
/// @return
/// @a true if the first <code>Real32</code> value is in the "greater than or equal to" relation with the other <code>Real32</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real32_isGreaterThanOrEqualTo
  (
    Ring2_Real32 x,
    Ring2_Real32 y
  );

#endif // Ring2_Configuration_withReal

#endif // RING2_OPERATIONS_REAL32_H_INCLUDE
