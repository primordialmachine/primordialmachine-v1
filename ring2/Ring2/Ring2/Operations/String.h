// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real64.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_STRING_H_INCLUDED)
#define RING2_OPERATIONS_STRING_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Operations/String.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

#include "Ring2/Context.h"
#include "Ring2/Types.h"

/// @brief Get if a <code>String</code> value is in an "equal to" relation with another <code>String</code> value.
/// @param x The first <code>String</code> values.
/// @param y The second <code>String</code> value value.
/// @return
/// @a true if the first <code>String</code> value is an "equal to" relation with the second <code>String</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isEqualTo
  (
    Ring2_Context *context,
    Ring2_String const *x,
    Ring2_String const *y
  );

/// @brief Get if a <code>String</code> value is a "not equal to" relation with another <code>String</code> value.
/// @param x The first <code>String</code> value.
/// @param y The second <code>String</code> value.
/// @return
/// @a true if the first <code>String</code> value is a "not equal to" relation with the second <code>String</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  );

/// @brief Get if a <code>String</code> value is a "lower than" relation with another <code>String</code> value.
/// @param x The first <code>String</code> value.
/// @param y The second <code>String</code> value.
/// @return
/// @a true if the first <code>String</code> value is a "lower than" relation with the second <code>String</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isLowerThan
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  );

/// @brief Get if a <code>String</code> value is a "lower than or equal to" relation with another <code>String</code> value.
/// @param x The first <code>String</code> value.
/// @param y The second <code>String</code> value.
/// @return
/// @a true if the first <code>String</code> value is a "lower than or equal to" relation with the second <code>String</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  );

/// @brief Get if a <code>String</code> value is a "greater than" relation with another <code>String</code> value.
/// @param x The first <code>String</code> value.
/// @param y The second <code>String</code> value.
/// @return
/// @a true if the first <code>String</code> value is a "greater than" relation with the second <code>String</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  );

/// @brief Get if a <code>String</code> value is a "greater than or equal to" relation with another <code>String</code> value.
/// @param x The first <code>String</code> value.
/// @param y The second <code>String</code> value.
/// @return
/// @a true if the first <code>String</code> value is a "greater than or equal to" relation with the second <code>String</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_String const *x,
    Ring2_String const *y
  );

/// @brief Get if a string is a prefix of another string.
/// @param x The first string.
/// @param y The second string.
/// @return @a true if the second string is a prefix of the first string.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_startWith
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  );

/// @brief Get if a string is a suffix of another string.
/// @param x The first string.
/// @param y The second string.
/// @return
/// @a true if the second string is a suffix of the first string.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_String_endsWith
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  );

/// @brief Get the first occurrence of a string in another string.
/// @param x The first string.
/// @param y The last string.
/// @return
/// @a -1 if the second string has no occurrence in the first string.
/// The index of the first occurrence of the second string in the first string. 
Ring1_CheckReturn() Ring2_Integer
Ring2_String_firstOccurrenceOf
  (
    Ring2_Context* context,
    Ring2_String const* x,
    Ring2_String const* y
  );

/// @brief Get a substring of a string.
/// @param x The string.
/// @param i The index of the first Byte of the substring.
/// @param n The length, in Bytes, of the substring.
/// @return The substring on success, null on failure.
/// @remark This function fails if
/// - <tt>i</tt> is negative,
/// - <tt>n</tt> is negative,
/// - <tt>i + n</tt> overflows,
/// - <tt>i + n</tt> is greater than
/// <tt>Mkx_Interpreter_String_getNumberOfBytes(w)</tt>.
Ring1_CheckReturn() Ring2_String*
Ring2_String_substring
  (
    Ring2_Context* context,
    Ring2_String const* x,
    int64_t i,
    int64_t n
  );

#endif // Ring2_Configuration_withString

#endif // RING2_OPERATIONS_STRING_H_INCLUDED
