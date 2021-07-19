/// @file Runtime/ConvertPrimitiveTypes.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#if !defined(MACHINE_RUNTIME_CONVERTPRIMITIVETYPES_H_INCLUDED)
#define MACHINE_RUNTIME_CONVERTPRIMITIVETYPES_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "./../Runtime/PrimitiveTypes.h"
typedef struct Machine_String Machine_String;



/// @brief Convert a <code>Boolean</code> value to a <code>String</code> value.
/// The resulting string is <code>true</code> if the value is <code>true</code> and <code>false</code> if the value is <code>false</code>.
/// @param value The <code>Boolean</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Boolean_toString(Machine_Boolean value);

/// @brief Convert a <code>ForeignProcedure</code> value to a <code>String</code> value.
/// @param value The <code>ForeignProcedure</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_ForeignProcedure_toString(Machine_ForeignProcedure* value);

/// @brief Convert an <code>Integer</code> value to a <code>String</code> value.
/// @param value The <code>Integer</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Integer_toString(Machine_Integer value);

/// @brief Convert an <code>Real</code> value to a <code>String</code> value.
/// @param value The <code>Real</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Real_toString(Machine_Real value);

/// @brief Convert a <code>Void</code> value to a <code>String</code> value.
/// The resulting string is <code>void</code>.
/// @param value The <code>Void</code> value.
/// @return The <code>String</code> value.
Machine_String* Machine_Void_toString(Machine_Void value);



#endif // MACHINE_RUNTIME_CONVERTPRIMITIVETYPES_H_INCLUDED
