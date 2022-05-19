// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real64.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_REAL64_H_INCLUDED)
#define RING2_OPERATIONS_REAL64_H_INCLUDED

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring2/Types.h"

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

/// @brief
/// Compute the hash value of an <code>Real64</code> value.
/// @param x
/// The <code>Real64</code> value.
/// @return
/// The hash value.
Ring1_CheckReturn() Ring2_Integer
Ring2_Real64_getHashValue
  (
    Ring2_Real64 x
  );

/// @brief
/// Get if a <code>Real64</code> value is in a "hash equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in the "hash equal to" relation with the other <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_getHashEqual
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in a "equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is equal to the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isEqualTo
  (
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
/// @a true if the first <code>Real64</code> value is not equal to the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isNotEqualTo
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if an <code>Real64</code> value is in the "lower than" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in the "lower than" relation with th eother <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThan
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if an <code>Real64</code> value is in the "lower than or equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in the "lower than or equal to" relation with the second <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isLowerThanOrEqualTo
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in the "greater than" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in the "greater than" relation with the other <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThan
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  );

/// @brief
/// Get if a <code>Real64</code> value is in the "greater than or equal to" relation with another <code>Real64</code> value.
/// @param x
/// The first <code>Real64</code> value.
/// @param y
/// The second <code>Real64</code> value.
/// @return
/// @a true if the first <code>Real64</code> value is in the "greater than or equal to" relation with the other <code>Real64</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Real64_isGreaterThanOrEqualTo
  (
    Ring2_Real64 x,
    Ring2_Real64 y
  );

#endif // Ring2_Configuration_withReal

#endif // RING2_OPERATIONS_REAL64_H_INCLUDE
