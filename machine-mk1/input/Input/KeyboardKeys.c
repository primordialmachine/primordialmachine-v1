/// @file Input/KeyboardKeys.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "Input/KeyboardKeys.h"

#include <string.h>

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_KeyboardKeys)

Ring2_String* Machine_KeyboardKeys_toString(Machine_KeyboardKeys self) {
#define DefineKeyboardKey(NAME, STRING)                                                            \
  case Machine_KeyboardKeys_##NAME: {                                                              \
    return Ring2_String_create(Ring2_Context_get(), STRING, strlen(STRING));                       \
  } break;

  switch (self) {
#include "Input/KeyboardKeys.i"
    default:
      Ring2_unreachable();
  };

#undef DefineKeyboardKey
}
