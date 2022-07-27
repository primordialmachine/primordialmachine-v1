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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Convert a <code>Boolean</code> value to a <code>String</code> value.
/// The resulting string is <code>true</code> if the value is <code>true</code> and
/// <code>false</code> if the value is <code>false</code>.
/// @param x The <code>Boolean</code> value.
/// @return The <code>String</code> value.
Ring2_String* Machine_Boolean_toString(Ring2_Boolean x);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of the <code>ForeignProcedure</code> type.
typedef Machine_Value(Machine_ForeignProcedure)(size_t numberOfArguments,
                                                Machine_Value const* arguments);

Ring2_Integer Machine_ForeignProcedure_getHashValue(Machine_ForeignProcedure* x);

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
Ring2_Boolean Machine_ForeignProcedure_isEqualTo(Machine_ForeignProcedure* x,
                                                 Machine_ForeignProcedure* y);

/// @brief Convert a <code>ForeignProcedure</code> value to a <code>String</code> value.
/// @param x The <code>ForeignProcedure</code> value.
/// @return The <code>String</code> value.
Ring2_String* Machine_ForeignProcedure_toString(Machine_ForeignProcedure* x);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Convert an <code>Integer</code> value to a <code>String</code> value.
/// @param x The <code>Integer</code> value.
/// @return The <code>String</code> value.
Ring2_String* Machine_Integer_toString(Ring2_Integer x);

/// @brief Compare two <code>Integer</code> values.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// A negative value if
///   the first <code>Integer</code> value
/// is smaller than
///   the second <code>Integer</code> value. 
/// A positive value if
///   the first <code>Integer</code> value
/// is greater than
///   the second <code>Integer</code> value.
/// Zero if both are equal.
Ring2_Integer Machine_Integer_compareTo(Ring2_Integer x, Ring2_Integer y);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Convert an <code>Real</code> value to a <code>String</code> value.
/// @param x The <code>Real</code> value.
/// @return The <code>String</code> value.
Ring2_String* Machine_Real_toString(Ring2_Real32 x);

/// @brief Compare two <code>Real</code> values.
/// @param x
/// The first <code>Real</code> value.
/// @param y
/// The second <code>Real</code> value.
/// @return
/// A negative value if
///   the first <code>Real</code> value
/// is smaller than
///   the second <code>Real</code> value.
/// A positive value if
///   the first <code>Real</code> value
/// is greater than
///   the second <code>Real</code> value.
/// Zero if both are equal.
/// @remarks
/// This function uses the following interpretations of "smaller than", "equal to", and "greater than".
/// - Smaller:
/// The first value is smaller than the second value according to IEEE754 specification.
/// The first value is NaN and the second value is not NaN.
/// - Equal:
/// Both values are equal according to IEEE754 specification.
/// Both values are NaN.
/// - Greater:
/// The second value is smaller than the first value according to IEEE754 specification.
/// The second value is NaN and the first value is not NaN.
Ring2_Integer Machine_Real_compareTo(Ring2_Real32 x, Ring2_Real32 y);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Convert a <code>Void</code> value to a <code>String</code> value.
/// The resulting string is <code>void</code>.
/// @param x The <code>Void</code> value.
/// @return The <code>String</code> value.
Ring2_String* Machine_Void_toString(Ring2_Void x);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_RUNTIME_PRIMITIVETYPES_H_INCLUDED
