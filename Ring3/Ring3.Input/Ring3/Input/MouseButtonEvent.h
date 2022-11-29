/// @file Ring3/Input/MouseButtonEvent.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_MOUSEBUTTONEVENT_H_INCLUDED)
#define RING3_INPUT_MOUSEBUTTONEVENT_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/MouseButtonEvent.h` directly, include `Ring/Input/_Include.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_MouseButtonActions)

enum Machine_MouseButtonActions {

  Machine_MouseButtonActions_Undetermined = (0),

  /// @brief A mouse button was pressed.
  Machine_MouseButtonActions_Press = (1),

  /// @brief A mouse button was released.
  Machine_MouseButtonActions_Release = (2),

};

Ring1_CheckReturn() Ring2_String*
Machine_MouseButtonActions_toString
  (
    Machine_MouseButtonActions self
  );

/// @brief An event pertaining to a mouse button.
/// @extends Machine.Object
/// @tood Shoud extend Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_MouseButtonEvent)

struct Machine_MouseButtonEvent_Class {
  Machine_Object_Class parent;
};

struct Machine_MouseButtonEvent {
  Machine_Object parent;
  int button;
  Machine_MouseButtonActions action;
  Ring2_Real32 x;
  Ring2_Real32 y;
};

/// @brief Create a mouse button event.
/// @param button The index of the mouse button.
/// @param action The action of the mouse button.
/// #Machine_MouseButtonActions_Press if the button was pressed, #Machine_MouseButtonActions_Release
/// if the button was released.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse button event.
Ring1_CheckReturn() Machine_MouseButtonEvent*
Machine_MouseButtonEvent_create
  (
    int button,
    Machine_MouseButtonActions action,
    Ring2_Real32 x,
    Ring2_Real32 y
  );

#endif // RING3_INPUT_MOUSEBUTTONEVENT_H_INCLUDED
