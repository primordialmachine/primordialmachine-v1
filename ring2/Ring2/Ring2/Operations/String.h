// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Real64.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_STRING_H_INCLUDED)
#define RING2_OPERATIONS_STRING_H_INCLUDED

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

#endif // Ring2_Configuration_withString

#endif // RING2_OPERATIONS_STRING_H_INCLUDED
