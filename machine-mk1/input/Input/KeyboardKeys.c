/// @file Input/KeyboardKeys.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "Input/KeyboardKeys.h"

#include <string.h>

Machine_String* Machine_KeyboardKeys_toString(Machine_KeyboardKeys self) {
#define DEFINE(NAME, STRING) \
  case Machine_KeyboardKeys_##NAME: { \
    return Machine_String_create(STRING, strlen(STRING)); \
  } break;

  switch (self) {
  #include "Input/KeyboardKeys.i"
  default:
    MACHINE_ASSERT_UNREACHABLE();
  };

#undef DEFINE
}
