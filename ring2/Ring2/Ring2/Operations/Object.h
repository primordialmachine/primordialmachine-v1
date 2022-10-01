// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Object.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_OBJECT_H_INCLUDED)
#define RING2_OPERATIONS_OBJECT_H_INCLUDED

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

#include "Ring2/Context.h"
#include "Ring2/Types.h"
#include "Ring2/Types/Value.h"

/// @brief Get the hash value of this <code>Object</code> value.
/// @param context The context.
/// @param self This <code>Object</code> value.
/// @return The hash value.
Ring1_CheckReturn() Ring2_Integer
Machine_Object_getHashValue
  (
    Ring2_Context* context,
    Machine_Object const* self
  );

/// @brief Get if this <code>Object</code> is in a "equal to" relation with another value.
/// @param context The context.
/// @param self This <code>Object</code> value.
/// @param other The other value.
/// @return @a true if this <code>Object</code> value is in an "equal to" relation with the other value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Machine_Object_isEqualTo
  (
    Ring2_Context* context,
    Machine_Object const* self,
    Ring2_Value const* other
  );

/// @brief Get if this <code>Object</code> is in a "not equal to" relation with another value.
/// @param context The context.
/// @param self This <code>Object</code> value.
/// @param other The other value.
/// @return @a true if this <code>Object</code> is in a "not equal to" relation with the other value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Machine_Object_isNotEqualTo
  (
    Ring2_Context* context,
    Machine_Object const* self,
    Ring2_Value const* other
  );

/// @brief Get if this <code>Object</code> value is in a "hash equal to" relation with another value.
/// @param context The context.
/// @param self This <code>Object</code> value.
/// @param other The other value.
/// @return @a true if this <code>Object</code> value is in a "hash equal to" relation with the other value.
/// @a false otherwise.
/// @brief Convert this <code>Object</code> value to a <code>String</code> value.
/// @param context The context.
/// @param self This <code>Object</code> value.
/// @return The <code>String</code> value.
Ring1_CheckReturn() Ring2_String*
Machine_Object_toString
  (
    Ring2_Context* context,
    Machine_Object const* self
  );

#endif // Ring2_Configuration_withObject

#endif // RING2_OPERATIONS_OBJECT_H_INCLUDED
