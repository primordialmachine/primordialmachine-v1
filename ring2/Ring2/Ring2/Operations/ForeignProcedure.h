// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/ForeignProcedure.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_FOREIGNPROCEDURE_H_INCLUDED)
#define RING2_OPERATIONS_FOREIGNPROCEDURE_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Operations/ForeignProcedure.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

#include "Ring2/Context.h"
#include "Ring2/Types.h"

/// @brief Get the hash value of a foreign procedure.
/// @param context A pointer to the context.
/// @param x A pointer to a foreign procedur object.
/// @return The hash value of the foreign function object.
/// @undefined @a context does not point to a Ring2_Context object.
/// @undefined @a x does not point to a foreign procedure object.
Ring1_CheckReturn() Ring2_Integer
Ring2_ForeignProcedure_getHashValue
  (
    Ring2_Context* context,
    Ring2_ForeignProcedure *x
  );

/// @brief
/// Get if a <code>Ring2_ForeignProcedure</code> value is in an "equal to" relation with another <code>Ring2_ForeignProcedure</code> value.
/// @param x
/// The (reference to the) first <code>Ring2_ForeignProcedure</code> values.
/// @param y
/// The (reference to the) first <code>Ring2_ForeignProcedure</code> values.
/// @return
/// @a true if the first <code>Ring2_ForeignProcedure</code> value is in an "equal to" relation with the second <code>Ring2_ForeignProcedure</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignProcedure_isEqualTo
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure* x,
    Ring2_ForeignProcedure* y
  );

/// @brief
/// Get if a <code>Ring2_ForeignProcedure</code> value is in a "not equal to" relation with another <code>Ring2_ForeignProcedure</code> value.
/// @param x
/// The (reference to the) first <code>Ring2_ForeignProcedure</code> values.
/// @param y
/// The (reference to the) first <code>Ring2_ForeignProcedure</code> values.
/// @return
/// @a true if the first <code>Ring2_ForeignProcedure</code> value is in a "not equal to" relation with the second <code>Ring2_ForeignProcedure</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignProcedure_isNotEqualTo
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure* x,
    Ring2_ForeignProcedure* y
  );

/// @brief Convert a <code>ForeignProcedure</code> value to a <code>String</code> value.
/// @param x The <code>ForeignProcedure</code> value.
/// @return The <code>String</code> value.
Ring1_CheckReturn() Ring2_String *
Ring2_ForeignProcedure_toString
  (
    Ring2_Context *context,
    Ring2_ForeignProcedure *x
  );


#endif // Ring2_Configuration_withForeignProcedure

#endif // RING2_OPERATIONS_FOREIGNFUNCTION_H_INCLUDED
