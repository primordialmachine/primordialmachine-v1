// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Mkx/Scribe/Environment/Environment.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MKX_SCRIBE_ENVIRONMENT_ENVIRONMENT_H_INCLUDED)
#define MKX_SCRIBE_ENVIRONMENT_ENVIRONMENT_H_INCLUDED


#include "Mkx/Scribe/Common.h"
typedef struct Mkx_Scribe_Variable Mkx_Scribe_Variable; // Forward declaration.


/// @brief An environment.
MACHINE_DECLARE_CLASSTYPE(Mkx_Scribe_Environment)

void
Mkx_Scribe_Environment_construct
  (
    Mkx_Scribe_Environment* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an environment.
/// @return The environment.
/// @remark The environment is empty.
Mkx_Scribe_Environment *
Mkx_Scribe_Environment_create
  (
  );

/// @brief Get a variable in this environment.
/// @param self This environment.
/// @param name The name of the variable.
/// @return The variable or null.
Mkx_Scribe_Variable *
Mkx_Scribe_Environment_get
  (
    Mkx_Scribe_Environment* self,
    Ring2_String* name
  );

Mkx_Scribe_Variable*
Mkx_Scribe_Environment_getRecursive
  (
    Mkx_Scribe_Environment* self,
    Ring2_String* name
  );

/// @brief Add a variable to this environment.
/// @param self This environment.
/// @param var The variable.
/// @detail An existing variable is replaced by an incoming variable if they are equivalent.
void
Mkx_Scribe_Environment_set
  (
    Mkx_Scribe_Environment* self,
    Mkx_Scribe_Variable* var
  );

/// @brief Add all variables from an other environment to this environment.
/// @param self This environment.
/// @param source The other environment.
/// @detail An existing variable is replaced by an incoming variable if they are equivalent.
void
Mkx_Scribe_Environment_setAll
  (
    Mkx_Scribe_Environment* self,
    Mkx_Scribe_Environment* other
  );

Mkx_Scribe_Environment*
Mkx_Scribe_Environment_getEnclosing
  (
    Mkx_Scribe_Environment* self
  );

void
Mkx_Scribe_Environment_setEnclosing
  (
    Mkx_Scribe_Environment* self,
    Mkx_Scribe_Environment* enclosing
  );

#endif // MKX_SCRIBE_ENVIRONMENT_ENVIRONMENT_H_INCLUDED
