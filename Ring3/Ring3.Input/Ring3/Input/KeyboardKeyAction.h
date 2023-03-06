/// @file Ring3/Input/KeyboardKeyAction.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_KEYBOARDKEYACTION_H_INCLUDED)
#define RING3_INPUT_KEYBOARDKEYACTION_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/KeyboardKeyAction.h` directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_KeyboardKeyAction)

enum Ring3_KeyboardKeyAction {

  Ring3_KeyboardKeyAction_Undetermined = (0),

  /// @brief A keyboard key was pressed.
  Ring3_KeyboardKeyAction_Press = (1),

  /// @brief A keyboard key was released.
  Ring3_KeyboardKeyAction_Release = (2),

  /// @brief A keyboard key was pressed until it repeated.
  Ring3_KeyboardKeyAction_Repeat = (3)

};

Ring1_CheckReturn() Ring2_String*
Ring3_KeyboardKeyAction_toString
  (
    Ring3_KeyboardKeyAction self
  );

#endif // RING3_INPUT_KEYBOARDKEYACTION_H_INCLUDED
