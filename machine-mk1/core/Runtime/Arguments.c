/// @file Runtime/Arguments.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Arguments.h"

#include "Ring2/_Include.h"
#include "Runtime/Object/Object.h"
#include "Ring1/Status.h"

Ring2_Integer Machine_Extensions_getBooleanArgument(size_t numberOfArguments,
                                                    Machine_Value const* arguments, size_t i) {
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Machine_Value_isBoolean(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Boolean v = Machine_Value_getBoolean(arguments + i);
  return v;
}

Ring2_Integer Machine_Extensions_getIntegerArgument(size_t numberOfArguments,
                                                    Machine_Value const* arguments, size_t i) {
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Machine_Value_isInteger(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Integer v = Machine_Value_getInteger(arguments + i);
  return v;
}

Ring2_String* Machine_Extensions_getStringArgument(size_t numberOfArguments,
                                                   Machine_Value const* arguments, size_t i) {
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Machine_Value_isString(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_String* v = Machine_Value_getString(arguments + i);
  return v;
}

Machine_Object* Machine_Extensions_getObjectArgument(size_t numberOfArguments,
                                                     Machine_Value const* arguments, size_t i,
                                                     Machine_ClassType* t) {
  if (i >= numberOfArguments) {
    Ring1_Status_set(Ring1_Status_InvalidNumberOfArguments);
    Ring2_jump();
  }
  if (!Machine_Value_isObject(arguments + i)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Machine_Object* v = Machine_Value_getObject(arguments + i);
  if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(v), (Machine_Type*)t)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return v;
}
