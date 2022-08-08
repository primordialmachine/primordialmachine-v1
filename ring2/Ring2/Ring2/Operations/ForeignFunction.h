// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/ForeignFunction.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_OPERATIONS_FOREIGNFUNCTION_H_INCLUDED)
#define RING2_OPERATIONS_FOREIGNFUNCTION_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Operations/ForeignFunction.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withForeignFunction) && 1 == Ring2_Configuration_withForeignFunction

#include "Ring2/Context.h"
#include "Ring2/Types.h"

/// @brief
/// Get if a <code>Ring2_ForeignFunction</code> value is in an "equal to" relation with another <code>Ring2_ForeignFunction</code> value.
/// @param x
/// The (reference to the) first <code>Ring2_ForeignFunction</code> values.
/// @param y
/// The (reference to the) first <code>Ring2_ForeignFunction</code> values.
/// @return
/// @a true if the first <code>Ring2_ForeignFunction</code> value is in an "equal to" relation with the second <code>Ring2_ForeignFunction</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignFunction_isEqualTo
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x,
    Ring2_ForeignFunction* y
  );

/// @brief
/// Get if a <code>Ring2_ForeignFunction</code> value is in a "not equal to" relation with another <code>Ring2_ForeignFunction</code> value.
/// @param x
/// The (reference to the) first <code>Ring2_ForeignFunction</code> values.
/// @param y
/// The (reference to the) first <code>Ring2_ForeignFunction</code> values.
/// @return
/// @a true if the first <code>Ring2_ForeignFunction</code> value is in a "not equal to" relation with the second <code>Ring2_ForeignFunction</code> value.
/// @a false otherwise.
Ring1_CheckReturn() Ring2_Boolean
Ring2_ForeignFunction_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x,
    Ring2_ForeignFunction* y
  );

Ring1_CheckReturn() Ring2_Integer
Ring2_ForeignFunction_getHashValue
  (
    Ring2_Context* context,
    Ring2_ForeignFunction *x
  );

Ring1_CheckReturn() Ring2_String*
Ring2_ForeignProcedure_toString
  (
    Ring2_Context* context,
    Ring2_ForeignFunction* x
  );

#endif // Ring2_Configuration_withForeignFunction

#endif // RING2_OPERATIONS_FOREIGNFUNCTION_H_INCLUDED
