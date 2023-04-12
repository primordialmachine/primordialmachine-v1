/// @file Ring3/Input/KeyboardKeyAction.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/KeyboardKeyAction.h"
#undef RING3_INPUT_PRIVATE

MACHINE_DEFINE_ENUMERATIONTYPE(Ring3_KeyboardKeyAction)

Ring1_CheckReturn() Ring2_String*
Ring3_KeyboardKeyAction_toString
  (
    Ring3_KeyboardKeyAction self
  )
{
  switch (self) {
    case Ring3_KeyboardKeyAction_Press:
      return Ring2_String_fromC(false, "press");
      break;
    case Ring3_KeyboardKeyAction_Release:
      return Ring2_String_fromC(false, "release");
      break;
    case Ring3_KeyboardKeyAction_Repeat:
      return Ring2_String_fromC(false, "repeat");
      break;
    case Ring3_KeyboardKeyAction_Undetermined:
    default:
      Ring2_unreachable();
  };
}
