// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/ForeignProcedure.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

#if !defined(RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED)
#define RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED


#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/ForeignProcedure.h` directly, include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

#include <stdint.h>
#include <stdbool.h>

/// @brief The C-level representation of the <code>ForeignProcedure</code> type.
typedef void(Ring2_ForeignProcedure)(Ring2_Context* context,
                                     Ring2_Value *result,
                                     size_t numberOfArguments,
                                     Ring2_Value const* arguments);

Ring1_CheckReturn() int64_t
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
Ring1_CheckReturn() bool
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
Ring1_CheckReturn() bool
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

#endif // RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED