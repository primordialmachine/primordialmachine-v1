// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Void.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_VOID_H_INCLUDED)
#define RING2_OPERATIONS_VOID_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Operations/Void.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

#include "Ring2/Context.h"
#include "Ring2/Types.h"

/// @brief
/// Compute the hash value of a <code>Void</code> value.
/// @param x
/// The <code>Void</code> value.
/// @return
/// The hash value.
Ring1_CheckReturn() Ring2_Integer
Ring2_Void_getHashValue
  (
    Ring2_Context* context,
    Ring2_Void x
  );

/// @brief
/// Get if a <code>Void</code> value is in a "hash equal to" relation with another <code>Void</code> value.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_getHashEqual
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );

/// @brief
/// Compare two <code>Void</code> values for equality.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if
///   the first <code>Void</code> value
/// is equal to
///   the second <code>Void</code> value
/// . @a false otherwise.
/// @remarks
/// There exists only one void value.
/// That value is equal to itself.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );

/// @brief
/// Compare two <code>Void</code> values for inequality.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if the first <code>Void</code> value is not equal to the second <code>Void</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );

/// @brief
/// Get if an <code>Void</code> value is in a "lower than" relation with another <code>Void</code> value.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if the first <code>Void</code> value is in a "lower than" relation with the second <code>Void</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );

/// @brief
/// Get if an <code>Void</code> value is in a "lower than or equal to" relation with another <code>Void</code> value.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if the first <code>Void</code> value is in a "lower than or equal to" relation with the second <code>Void</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );

/// @brief
/// Get if a <code>Void</code> value is in a "greater than" relation with another <code>Void</code> value.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if the first <code>Void</code> value is in a "greater than" relation with the second <code>Void</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );

/// @brief
/// Get if a <code>Void</code> value is in a "greater than or equal to" relation with another <code>Void</code> value.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if the first <code>Void</code> value is in a "greater than or equal to" relation with the second <code>Void</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Void_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Void x,
    Ring2_Void y
  );


#endif // Ring2_Configuration_witVoid

#endif // RING2_OPERATIONS_VOID_H_INCLUDED
