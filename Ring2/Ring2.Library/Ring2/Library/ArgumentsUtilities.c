// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Library/ArgumentsUtilities.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

/// @brief Functionality to access argument lists.

#define RING2_LIBRARY_PRIVATE (1)
#include "Ring2/Library/ArgumentsUtilities.h"
#undef RING2_LIBRARY_PRIVATE


#include "Ring1/Status.h"


Ring1_CheckReturn() Ring2_Boolean
Machine_Extensions_getBooleanArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  )
{
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Ring2_Value_isBoolean(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Boolean v = Ring2_Value_getBoolean(arguments + i);
  return v;
}

Ring1_CheckReturn() Ring2_Integer
Machine_Extensions_getIntegerArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  )
{
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Ring2_Value_isInteger(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Integer v = Ring2_Value_getInteger(arguments + i);
  return v;
}

Ring1_CheckReturn() Ring2_Real32
Machine_Extensions_getReal32Argument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  )
{
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Ring2_Value_isReal32(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Real32 v = Ring2_Value_getReal32(arguments + i);
  return v;
}

Ring1_CheckReturn() Ring2_Real64
Machine_Extensions_getReal64Argument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  )
{
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Ring2_Value_isReal64(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Real64 v = Ring2_Value_getReal64(arguments + i);
  return v;
}

Ring1_CheckReturn() Ring2_String *
Machine_Extensions_getStringArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments,
    size_t i
  )
{
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Ring2_Value_isString(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_String* v = Ring2_Value_getString(arguments + i);
  return v;
}

Ring1_CheckReturn() Machine_Object *
Machine_Extensions_getObjectArgument
  (
    size_t numberOfArguments,
    Ring2_Value const* arguments, size_t i,
    Machine_ClassType* t
  )
{
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Ring2_Value_isObject(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Machine_Object* v = (Machine_Object *)Ring2_Value_getObject(arguments + i);
  if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(v), (Machine_Type*)t)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return v;
}
