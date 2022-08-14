// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/ForeignProcedure.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.

#if !defined(RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED)
#define RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED

#if !defined(RING2_INTERNAL)
#error("Do not include `Ring2/Types/ForeignProcedure.h` directly, include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withForeignFunction) && 1 == Ring2_Configuration_withForeignFunction

#include "Ring1/Intrinsic/CheckReturn.h"
#include <stdint.h>
#include <stdbool.h>
typedef struct Ring2_Context Ring2_Context; // Forward declaration.
typedef struct Ring2_String Ring2_String;   // Forward declaration.
typedef struct Machine_Value Machine_Value; // Forward declaration.

/// @brief The C-level representation of the <code>ForeignProcedure</code> type.
typedef void(Machine_ForeignProcedure)(Ring2_Context* context,
                                       Machine_Value *result,
                                       size_t numberOfArguments,
                                       Machine_Value const* arguments);

Ring1_CheckReturn() int64_t
Machine_ForeignProcedure_getHashValue
  (
    Ring2_Context* context,
    Machine_ForeignProcedure *x
  );

/// @brief
/// Compare two <code>ForeignProceduree</code> values for equality.
/// @param x
/// The first <code>ForeignProceduree</code> value.
/// @param y
/// The second <code>ForeignProceduree</code> value.
/// @return
/// @a true if
///   the first <code>ForeignProceduree</code> value
/// is equal to
///   the second <code>ForeignProceduree</code> value
/// . @a false otherwise.
Ring1_CheckReturn() bool
Machine_ForeignProcedure_isEqualTo
  (
    Ring2_Context *context,
    Machine_ForeignProcedure* x,
    Machine_ForeignProcedure* y
  );

/// @brief Convert a <code>ForeignProcedure</code> value to a <code>String</code> value.
/// @param x The <code>ForeignProcedure</code> value.
/// @return The <code>String</code> value.
Ring1_CheckReturn() Ring2_String *
Machine_ForeignProcedure_toString
  (
    Ring2_Context *context,
    Machine_ForeignProcedure *x
  );

#endif // Ring2_Configuration_withForeignFunction

#endif // RING2_TYPES_FOREIGNPROCEDURE_H_INCLUDED
