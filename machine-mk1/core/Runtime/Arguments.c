/// @file Runtime/Arguments.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/Arguments.h"
#include "Runtime/JumpTargetModule.h"
#include "Runtime/Object/Object.h"
#include "Runtime/Status.h"

Machine_Integer Machine_Extensions_getBooleanArgument(size_t numberOfArguments,
                                                             Machine_Value const* arguments,
                                                             size_t i) {
  if (i >= numberOfArguments) {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
  if (!Machine_Value_isBoolean(arguments + i)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Boolean v = Machine_Value_getBoolean(arguments + i);
  return v;
}

Machine_Integer Machine_Extensions_getIntegerArgument(size_t numberOfArguments,
                                                             Machine_Value const* arguments,
                                                             size_t i) {
  if (i >= numberOfArguments) {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
  if (!Machine_Value_isInteger(arguments + i)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Integer v = Machine_Value_getInteger(arguments + i);
  return v;
}

Machine_String* Machine_Extensions_getStringArgument(size_t numberOfArguments,
                                                            Machine_Value const* arguments,
                                                            size_t i) {
  if (i >= numberOfArguments) {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
  if (!Machine_Value_isString(arguments + i)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_String* v = Machine_Value_getString(arguments + i);
  return v;
}

Machine_Object* Machine_Extensions_getObjectArgument(size_t numberOfArguments,
                                                            Machine_Value const* arguments,
                                                            size_t i, Machine_ClassType* t) {
  if (i >= numberOfArguments) {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
  if (!Machine_Value_isObject(arguments + i)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Object* v = Machine_Value_getObject(arguments + i);
  if (!Machine_Type_isSubTypeOf((Machine_Type*)Machine_getClassType(v), (Machine_Type*)t)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  return v;
}
