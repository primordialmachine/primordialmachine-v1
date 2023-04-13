// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Boolean.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_BOOLEAN_H_INCLUDED)
#define RING2_OPERATIONS_BOOLEAN_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Operations/Boolean.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

#include "Ring2/Types.h"

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
    Ring2_Context *context,
    Ring2_Boolean x
  );

/// @brief
/// Get if a <code>Boolean</code> value is in a "hash equal to" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in a "hash equal to" relation with the second <code>Boolean</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_getHashEqual
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  );

/// @brief
/// Get if a <code>Boolean</code> value is in an "equal to" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in an "equal to" relation with the second <code>Boolean</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isEqualTo
  (
    Ring2_Context *context,
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
/// @a true if the first <code>Boolean</code> value is not equal to the second <code>Boolean</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_isNotEqualTo
  (
    Ring2_Context *context,
    Ring2_Boolean x,
    Ring2_Boolean y
  );

/// @brief
/// Get if an <code>Boolean</code> value is in a "lower than" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in a "lower than" relation with the second <code>Boolean</code> value.
/// @a false otherwise.
void
Ring2_Boolean_isLowerThan
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  );

/// @brief
/// Get if an <code>Boolean</code> value is in a "lower than or equal to" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in a "lower than or equal to" relation with the second <code>Boolean</code> value.
/// @a false otherwise.
void
Ring2_Boolean_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );

/// @brief
/// Get if a <code>Boolean</code> value is in a "greater than" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in a "greater than" relation with the second <code>Boolean</code> value.
/// @a false otherwise.
void
Ring2_Boolean_isGreaterThan
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );

/// @brief
/// Get if a <code>Boolean</code> value is in a "greater than or equal to" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if the first <code>Boolean</code> value is in a "greater than or equal to" relation with the second <code>Boolean</code> value.
/// @a false otherwise.
void
Ring2_Boolean_isGreaterThanOrEqualTo
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );
  
/// @brief
/// Compute the logical and of a <code>Boolean</code> value and another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// The logical and <c>and(x, y)</c> of <c>x</c> and <c>y</c>.
void
Ring2_Boolean_and
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );

/// @brief
/// Compute the logical or of a <code>Boolean</code> value and another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// The logical or <c>or(x, y)</c> of <c>x</c> and <c>y</c>.
void
Ring2_Boolean_or
  (
    Ring2_Context *context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  );

/// @brief
/// Compute the affirmation of a <code>Boolean</code> value.
/// @param x
/// The <code>Boolean</code> value.
/// @return
/// The affirmation <c>id x</c>.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_affirmate
  (
    Ring2_Context *context,
    Ring2_Boolean x
  );

/// @brief
/// Compute the negation of a <code>Boolean</code> value.
/// @param x
/// The <code>Boolean</code> value.
/// @return
/// The negation <c>neg x</c>.
Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_negate
  (
    Ring2_Context *context,
    Ring2_Boolean x
  );

/// @brief Convert a <code>Boolean</code> value to a <code>String</code> value.
/// The resulting string is <code>true</code> if the value is <code>true</code> and
/// <code>false</code> if the value is <code>false</code>.
/// @param x The <code>Boolean</code> value.
/// @return The <code>String</code> value.
Ring1_CheckReturn() Ring2_String *
Ring2_Boolean_toString
  (
    Ring2_Context* context,
    Ring2_Boolean x
  );

Ring1_CheckReturn() Ring2_Boolean
Ring2_Boolean_fromString
  (
    Ring2_Context* context,
    Ring2_String* w
  );

#endif // Ring2_Configuration_withBoolean

#endif // RING2_OPERATIONS_BOOLEAN_H_INCLUDED
