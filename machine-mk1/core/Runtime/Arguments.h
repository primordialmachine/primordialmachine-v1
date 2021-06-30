/// @file Runtime/Arguments.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @brief Functionality to access argument lists.
#if !defined(MACHINE_RUNTIME_ARGUMENTS_H_INCLUDED)
#define MACHINE_RUNTIME_ARGUMENTS_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif



#include "Machine.h"
#include "Runtime/Status.h"
#include "Runtime/Value.h"



INLINE Machine_Integer Machine_Extensions_getBooleanArgument(size_t numberOfArguments, Machine_Value const* arguments, size_t i) {
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

INLINE Machine_Integer Machine_Extensions_getIntegerArgument(size_t numberOfArguments, Machine_Value const* arguments, size_t i) {
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

INLINE Machine_String* Machine_Extensions_getStringArgument(size_t numberOfArguments, Machine_Value const* arguments, size_t i) {
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

INLINE Machine_Object* Machine_Extensions_getObjectArgument(size_t numberOfArguments, Machine_Value const* arguments, size_t i, Machine_ClassType* t) {
  if (i >= numberOfArguments) {
    Machine_setStatus(Machine_Status_InvalidNumberOfArguments);
    Machine_jump();
  }
  if (!Machine_Value_isObject(arguments + i)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Object* v = Machine_Value_getObject(arguments + i);
  if (!Machine_isSubTypeOf(Machine_getClassType(v), t)) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  return v;
}



#endif // MACHINE_RUNTIME_ARGUMENTS_H_INCLUDED
