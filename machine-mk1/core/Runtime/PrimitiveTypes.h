/// @file Runtime/PrimitiveTypes.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief
/// C-level representations of primitive types and operations.
/// @details
/// C-level representations of primitive types and operations.
/// The following types are defined here.
/// <code>Boolean</code>,
/// <code>ForeignProcedure</code>,
/// <code>Integer</code>, <code>Real</code>, and
/// <code>Void</code> types.
/// Along with the types, the standard operations <code>hash</code>,
/// <code>equalTo</code> and <code>toString</code> are defined here.
#if !defined(MACHINE_RUNTIME_PRIMITIVETYPES_H_INCLUDED)
#define MACHINE_RUNTIME_PRIMITIVETYPES_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/PrimitiveTypes.h` directly, include `_Runtime.h` instead.")
#endif
#include "Ring1/Ring1.h"
#include "Ring2/_Include.h"
typedef struct Ring2_String Ring2_String;   // Forward declaration.
typedef struct Machine_Value Machine_Value; // Forward declaration.

/// @brief The C-level representation of the <code>ForeignProcedure</code> type.
typedef void(Machine_ForeignProcedure)(Ring2_Context* context,
                                       Machine_Value *result,
                                       size_t numberOfArguments,
                                       Machine_Value const* arguments);

Ring1_CheckReturn() Ring2_Integer
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
Ring1_CheckReturn() Ring2_Boolean
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

#endif // MACHINE_RUNTIME_PRIMITIVETYPES_H_INCLUDED
