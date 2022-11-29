/// @file Ring3/Input/KeyboardKeys.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/KeyboardKeys.h"

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_KeyboardKeys)

Ring1_CheckReturn() Ring2_String*
Machine_KeyboardKeys_toString
  (
    Machine_KeyboardKeys self
  )
{
#define DefineKeyboardKey(NAME, STRING)                                   \
  case Machine_KeyboardKeys_##NAME: {                                     \
    return Ring2_String_fromC(STRING);                                    \
  } break;

  switch (self) {
#include "Ring3/Input/KeyboardKeys.i"
    default:
      Ring2_unreachable();
  };

#undef DefineKeyboardKey
}
