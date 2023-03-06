/// @file Ring3/Input/MouseButtonEvent.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_MOUSEBUTTONEVENT_H_INCLUDED)
#define RING3_INPUT_MOUSEBUTTONEVENT_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/MouseButtonEvent.h` directly, include `Ring/Input/_Include.h` instead.")
#endif
#include "Ring3/Input/MouseButtonAction.h"

/// @brief An event pertaining to a mouse button.
/// @extends Machine.Object
/// @todo Should extend from Ring3.Input.Event.
MACHINE_DECLARE_CLASSTYPE(Ring3_MouseButtonEvent)

struct Ring3_MouseButtonEvent_Class {
  Machine_Object_Class parent;
};

struct Ring3_MouseButtonEvent {
  Machine_Object parent;
  int button;
  Ring3_MouseButtonAction action;
  Ring2_Real32 x;
  Ring2_Real32 y;
};

/// @brief Create a mouse button event.
/// @param button The index of the mouse button.
/// @param action The action of the mouse button.
/// #Ring3_MouseButtonActions_Press if the button was pressed.
/// #Ring3_MouseButtonActions_Release if the button was released.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse button event.
Ring1_CheckReturn() Ring3_MouseButtonEvent*
Ring3_MouseButtonEvent_create
  (
    int button,
    Ring3_MouseButtonAction action,
    Ring2_Real32 x,
    Ring2_Real32 y
  );

#endif // RING3_INPUT_MOUSEBUTTONEVENT_H_INCLUDED
