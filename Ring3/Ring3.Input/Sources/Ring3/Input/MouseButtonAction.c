/// @file Ring3/Input/MouseButtonAction.c
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/MouseButtonAction.h"
#undef RING3_INPUT_PRIVATE

MACHINE_DEFINE_ENUMERATIONTYPE(Ring3_MouseButtonAction)

Ring1_CheckReturn() Ring2_String*
Ring3_MouseButtonAction_toString
  (
    Ring3_MouseButtonAction self
  )
{
  switch (self) {
    case Ring3_MouseButtonAction_Press:
      return Ring2_String_fromC(false, "press");
      break;
    case Ring3_MouseButtonAction_Release:
      return Ring2_String_fromC(false, "release");
      break;
    case Ring3_MouseButtonAction_Undetermined:
    default:
      Ring2_unreachable();
  };
}
