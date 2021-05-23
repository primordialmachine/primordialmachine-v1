/// @file Input/MouseButtonEvent.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_INPUT_MOUSEBUTTONEVENT_H_INCLUDED)
#define MACHINE_INPUT_MOUSEBUTTONEVENT_H_INCLUDED

#if !defined(MACHINE_INPUT_PRIVATE)
#error("Do not include this file directly, include `_Input.h` instead.")
#endif

#include "_Runtime.h"

/// @brief An event pertaining to a mouse button.
/// @extends Machine.Object
/// @tood Shoud extend Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_MouseButtonEvent)

struct Machine_MouseButtonEvent {
  Machine_Object parent;
  int button;
  int action;
  float x;
  float y;
};

/// @brief A button or was pressed.
#define Machine_ButtonAction_Press (1)

/// @brief A button or was released.
#define Machine_ButtonAction_Release (2)

/// @brief Create a mouse button event.
/// @param button The index of the mouse button.
/// @param action The action of the mouse button.
/// #Machine_ButtonAction_Press if the button was pressed, #Machine_ButtonAction_Release if the button was released.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse button event.
Machine_MouseButtonEvent* Machine_MouseButtonEvent_create(int button, int action, float x, float y);

#endif // MACHINE_INPUT_MOUSEBUTTONEVENT_H_INCLUDED
