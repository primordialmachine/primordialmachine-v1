/// @file Ring3/Input/KeyboardKey.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/KeyboardKey.h"
#undef RING3_INPUT_PRIVATE

MACHINE_DEFINE_ENUMERATIONTYPE(Ring3_KeyboardKey)

Ring1_CheckReturn() Ring2_String*
Ring3_KeyboardKey_toString
  (
    Ring3_KeyboardKey self
  )
{
#define DefineKeyboardKey(NAME, STRING)       \
  case Ring3_KeyboardKey_##NAME: {            \
    return Ring2_String_fromC(false, STRING); \
  } break;

  switch (self) {
#include "Ring3/Input/KeyboardKey.i"
    default:
      Ring2_unreachable();
  };

#undef DefineKeyboardKey
}
