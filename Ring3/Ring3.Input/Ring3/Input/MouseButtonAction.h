/// @file Ring3/Input/MouseButtonAction.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_MOUSEBUTTONACTION_H_INCLUDED)
#define RING3_INPUT_MOUSEBUTTONACTION_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/MouseButtonAction.h` directly, include `Ring/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_MouseButtonAction)

enum Ring3_MouseButtonAction {

  Ring3_MouseButtonAction_Undetermined = (0),

  /// @brief A mouse button was pressed.
  Ring3_MouseButtonAction_Press = (1),

  /// @brief A mouse button was released.
  Ring3_MouseButtonAction_Release = (2),

};

Ring1_CheckReturn() Ring2_String*
Ring3_MouseButtonAction_toString
  (
    Ring3_MouseButtonAction self
  );

#endif // RING3_INPUT_MOUSEBUTTONACTION_H_INCLUDED
