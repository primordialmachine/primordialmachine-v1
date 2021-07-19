/// @file Runtime/ConvertPrimitiveTypes.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_RUNTIME_PRIVATE (1)
#include "Runtime/ConvertPrimitiveTypes.h"
#include "Runtime/String.h"

#include <inttypes.h>
#include <string.h>
#include <stdio.h>

Machine_String* Machine_Boolean_toString(Machine_Boolean value) {
  return value ? Machine_String_create("true", strlen("true")) : Machine_String_create("false", strlen("false"));
}

Machine_String* Machine_ForeignProcedure_toString(Machine_ForeignProcedure* value) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%p", value);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Machine_String* Machine_Integer_toString(Machine_Integer value) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%"PRIu64, value);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Machine_String* Machine_Real_toString(Machine_Real value) {
  char buffer[1024 + 1];
  int n = snprintf(buffer, 1024 + 1, "%g", value);
  if (n < 0 || n > 1024 + 1) {
    Machine_setStatus(Machine_Status_ConversionFailed);
    Machine_jump();
  }
  return Machine_String_create(buffer, (size_t)n);
}

Machine_String* Machine_Void_toString(Machine_Void value) {
  return Machine_String_create("void", strlen("void"));
}
