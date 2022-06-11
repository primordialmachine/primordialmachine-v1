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
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif
#include "_Eal.h" // Include for environment abstraction layer.
#include "Ring2/Types.h"
#include "Ring2/Operations.h"
typedef struct Machine_String Machine_String; // Forward declaration.
typedef struct Machine_Value Machine_Value; // Forward declaration.

/// @brief The proper way to compute the int64_t hash value of a pointer.
/// @param x The pointer.
/// @return The int64_t hash value.
int64_t Machine_hashPointer_i64(void const* x);

/// @defgroup c_level_declarations C-level declarations
/// @{

/// @brief The C-level representation of the <code>Boolean</code> type.
typedef Ring2_Boolean Machine_Boolean;

/// @brief The C-level representation of the <code>Integer</code> type.
typedef Ring2_Integer Machine_Integer;

/// @}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of the <code>true</code> value.
#define Machine_Boolean_True (Ring2_Boolean_True)

/// @brief The C-level representation of the <code>false</code> value.
#define Machine_Boolean_False (Ring2_Boolean_False)

Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Integer
Machine_Boolean_getHashValue
  (
    Machine_Boolean x
  )
{ return Ring2_Boolean_getHashValue(Ring2_Context_get(), x); }

/// @brief
/// Get if a <code>Boolean</code> value is in a "equal to" relation with another <code>Boolean</code> value.
/// @param x
/// The first <code>Boolean</code> value.
/// @param y
/// The second <code>Boolean</code> value.
/// @return
/// @a true if  the first <code>Boolean</code> value
/// is equal to
///   the second <code>Boolean</code> value
/// . @a false otherwise.
Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Boolean
Machine_Boolean_isEqualTo
  (
    Machine_Boolean x,
    Machine_Boolean y
  )
{ return Ring2_Boolean_isEqualTo(Ring2_Context_get(), x, y); }

/// @brief Convert a <code>Boolean</code> value to a <code>String</code> value.
/// The resulting string is <code>true</code> if the value is <code>true</code> and
/// <code>false</code> if the value is <code>false</code>.
/// @param x The <code>Boolean</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Boolean_toString(Machine_Boolean x);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of the <code>ForeignProcedure</code> type.
typedef Machine_Value(Machine_ForeignProcedure)(size_t numberOfArguments,
                                                Machine_Value const* arguments);

Machine_Integer Machine_ForeignProcedure_getHashValue(Machine_ForeignProcedure* x);

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
Machine_Boolean Machine_ForeignProcedure_isEqualTo(Machine_ForeignProcedure* x,
                                                   Machine_ForeignProcedure* y);

/// @brief Convert a <code>ForeignProcedure</code> value to a <code>String</code> value.
/// @param x The <code>ForeignProcedure</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_ForeignProcedure_toString(Machine_ForeignProcedure* x);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The greatest <code>Integer</code> value.
#define Machine_Integer_Greatest (Ring2_Integer_Greatest)

/// @brief The least <code>Integer</code> value.
#define Machine_Integer_Least (Ring2_Integer_Least)

Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Integer
Machine_Integer_getHashValue
  (
    Machine_Integer x
  )
{ return Ring2_Integer_getHashValue(Ring2_Context_get(), x); }

/// @brief
/// Get if an <code>Integer</code> value is in a "equal to" relation with another <code>Integer</code> value.
/// @param x
/// The first <code>Integer</code> value.
/// @param y
/// The second <code>Integer</code> value.
/// @return
/// @a true if the first <code>Integer</code> value is in a "equal to" relation with the second <code>Integer</code> value,
/// @a false otherwise.
Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Boolean
Machine_Integer_isEqualTo
  (
    Machine_Integer x,
    Machine_Integer y
  )
{ return Ring2_Integer_isEqualTo(Ring2_Context_get(), x, y); }

/// @brief Convert an <code>Integer</code> value to a <code>String</code> value.
/// @param x The <code>Integer</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Integer_toString(Machine_Integer x);

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
Machine_Integer Machine_Integer_compareTo(Machine_Integer x, Machine_Integer y);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of a <code>Real</code> value.
typedef Ring2_Real32 Machine_Real;

Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Integer
Machine_Real_getHashValue
  (
    Machine_Real x
  )
{ return Ring2_Real32_getHashValue(Ring2_Context_get(), x); }

/// @brief
/// Compare two <code>Real</code> values for equality.
/// @param x
/// The first <code>Real</code> value.
/// @param y
/// The second <code>Real</code> value.
/// @return
/// @a true if the first <code>Real</code> value is equal to the second <code>Real</code> value.
/// @a false otherwise.
/// @remarks
/// Comparison is performed in full accordance with the IEEE754 specification.
Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Boolean
Machine_Real_isEqualTo
  (
    Machine_Real x,
    Machine_Real y
  )
{ return Ring2_Real32_isEqualTo(Ring2_Context_get(), x, y); }

/// @brief Convert an <code>Real</code> value to a <code>String</code> value.
/// @param x The <code>Real</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Real_toString(Machine_Real x);

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
Machine_Integer Machine_Real_compareTo(Machine_Real x, Machine_Real y);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief The C-level representation of the <code>void</code> value.
#define Machine_Void_Void (Ring2_Void_Void)

/// @brief The C-level representation of the <code>Void</code> type.
typedef Ring2_Void Machine_Void;

Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Integer
Machine_Void_getHashValue
  (
    Machine_Void x
  )
{ return Ring2_Void_getHashValue(Ring2_Context_get(), x); }

/// @brief
/// Compare two <code>Void</code> values for equality.
/// @param x
/// The first <code>Void</code> value.
/// @param y
/// The second <code>Void</code> value.
/// @return
/// @a true if
///   the first <code>Void</code> value
/// is equal to
///   the second <code>Void</code> value
/// . @a false otherwise.
/// @remarks
/// There exists only one void value.
/// That value is equal to itself.
Ring1_Intrinsic_Inline() Ring1_CheckReturn() Machine_Boolean
Machine_Void_isEqualTo
  (
    Machine_Void x,
    Machine_Void y
  )
{ return Ring2_Void_isEqualTo(Ring2_Context_get(), x, y); }

/// @brief Convert a <code>Void</code> value to a <code>String</code> value.
/// The resulting string is <code>void</code>.
/// @param x The <code>Void</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Void_toString(Machine_Void x);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_RUNTIME_PRIMITIVETYPES_H_INCLUDED
