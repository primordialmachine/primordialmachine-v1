// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Boolean.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_BOOLEAN_H_INCLUDED)
#define RING2_OPERATIONS_BOOLEAN_H_INCLUDED

#include "Ring2/Types.h"
#include "Ring1/Intrinsic/CheckReturn.h"

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

/// @brief
/// Defined to @a 1 if <code>Boolean</code> can be compared by <code>isEqualTo</code>.
/// If <code>Boolean</code> supports <code>isEqualTo</code>, it also supports <code>isNotEqualTo</code>.
#define Ring2_Boolean_hasEqualTo (1)

/// @brief
/// Compute the hash value of a <code>Boolean</code> value.
/// @param x
/// The <code>Boolean</code> value.
/// @return
/// The hash value.
Ring1_CheckReturn() Ring2_Integer
Ring2_Boolean_getHashValue
  (
    Ring2_Boolean x
  );

/// @brief
/// Get if a <code>Boolean</code> value is in a "hash equal to" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in the "hash equal to" relation with the other <code>Boolean</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_getHashEqual
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  );

/// @brief
/// Compare two <code>Boolean</code> values for equality.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is equal to the second <code>Boolean</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isEqualTo
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  );

/// @brief
/// Compare two <code>Boolean</code> values for inequality.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is not equal to the second <code>Boolean</code> value,
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isNotEqualTo
  (
    Ring2_Boolean x,
    Ring2_Boolean y
  );

#endif // Ring2_Configuration_withBoolean

#endif // RING2_OPERATIONS_BOOLEAN_H_INCLUDED
