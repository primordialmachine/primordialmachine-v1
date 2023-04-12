/// @file Ring3/Input/MousePointerAction.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/MousePointerAction.h"
#undef RING3_INPUT_PRIVATE

MACHINE_DEFINE_ENUMERATIONTYPE(Ring3_MousePointerAction)

Ring1_CheckReturn() Ring2_String*
Ring3_MousePointerAction_toString
  (
    Ring3_MousePointerAction self
  )
{
  switch (self) {
    case Ring3_MousePointerAction_Move:
      return Ring2_String_fromC(false, "move");
      break;
    case Ring3_MousePointerAction_Enter:
      return Ring2_String_fromC(false, "enter");
      break;
    case Ring3_MousePointerAction_Exit:
      return Ring2_String_fromC(false, "exit");
      break;
    case Ring3_MousePointerAction_Undetermined:
    default:
      Ring2_unreachable();
  };
}
