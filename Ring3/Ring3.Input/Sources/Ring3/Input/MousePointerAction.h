/// @file Ring3/Input/MousePointerAction.h
/// @copyright Copyright (c) 2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_MOUSEPOINTERACTION_H_INCLUDED)
#define RING3_INPUT_MOUSEPOINTERACTION_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/MousePointerAction.h`directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Ring3_MousePointerAction)

enum Ring3_MousePointerAction {

  Ring3_MousePointerAction_Undetermined = (0),

  /// @brief A mouse pointer was moved.
  Ring3_MousePointerAction_Move = (1),

  /// @brief A mouse pointer entered an area.
  Ring3_MousePointerAction_Enter = (2),

  /// @brief A mouse pointer exited an area.
  Ring3_MousePointerAction_Exit = (3)

};

Ring1_CheckReturn() Ring2_String*
Ring3_MousePointerAction_toString
  (
    Ring3_MousePointerAction self
  );

#endif // RING3_INPUT_MOUSEPOINTERACTION_H_INCLUDED
