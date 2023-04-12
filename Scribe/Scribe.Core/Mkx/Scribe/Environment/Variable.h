// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/Variable.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_ENVIRONMENT_VARIABLE_H_INCLUDED)
#define MKX_SCRIBE_ENVIRONMENT_VARIABLE_H_INCLUDED


#include "Mkx/Scribe/Common.h"


MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Variable)

void
Mkx_Scribe_Variable_construct
  (
    Mkx_Scribe_Variable *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a variable.
/// @param name The name.
/// @return The variable.
Mkx_Scribe_Variable *
Mkx_Scribe_Variable_create
  (
    Ring2_String* name
  );

/// @brief Get the name of a variable.
/// @param var the variable
/// @return the name of the variable
Ring2_String*
Mkx_Scribe_Variable_getName
  (
    Mkx_Scribe_Variable* var
  );

/// @brief Get the value of a variable.
/// @param self The variable.
/// @return the value of the variable.
Ring2_Integer
Mkx_Scribe_Variable_getIntegerValue
  (
    Mkx_Scribe_Variable* self
  );

/// @brief Set the value of a variable.
/// @param self The variable.
/// @param value the value of the variable.
void
Mkx_Scribe_Variable_setIntegerValue
  (
    Mkx_Scribe_Variable* self,
    Ring2_Integer value
  );

bool
Mkx_Scribe_Variable_isIntegerValue
  (
    Mkx_Scribe_Variable* self
  );

/// @brief Get the value of a variable.
/// @param self The variable.
/// @return the value of the variable.
Ring2_String*
Mkx_Scribe_Variable_getStringValue
  (
    Mkx_Scribe_Variable* self
  );

/// @brief Set the value of a variable.
/// @param self The variable.
/// @param value The value.
void
Mkx_Scribe_Variable_setStringValue
  (
    Mkx_Scribe_Variable* self,
    Ring2_String* value
  );

bool
Mkx_Scribe_Variable_isStringValue
  (
    Mkx_Scribe_Variable* self
  );

/// @brief Get the value of a variable.
/// @param self The variable.
/// @return the value of the variable.
Ring2_ForeignProcedure*
Mkx_Scribe_Variable_getForeignFunctionValue
  (
    Mkx_Scribe_Variable* self
  );

/// @brief Set the value of a variable.
/// @param self The variable.
/// @param value the value of the variable.
void
Mkx_Scribe_Variable_setForeignFunctionValue
  (
    Mkx_Scribe_Variable* self,
    Ring2_ForeignProcedure* value
  );

bool
Mkx_Scribe_Variable_isForeignFunctionValue
  (
    Mkx_Scribe_Variable* self
  );

Ring2_Value
Mkx_Scribe_Variable_get
  (
    Mkx_Scribe_Variable* self
  );

void
Mkx_Scribe_Variable_set
  (
    Mkx_Scribe_Variable* self,
    Ring2_Value value
  );

#endif // MKX_SCRIBE_ENVIRONMENT_VARIABLE_H_INCLUDED
