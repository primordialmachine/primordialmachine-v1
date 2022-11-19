/// @file Ring3/Input/KeyboardKeyEvent.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_KEYBOARDKEYEVENT_H_INCLUDED)
#define RING3_INPUT_KEYBOARDKEYEVENT_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/KeyboardKeyEvent.h` directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring3/Input/KeyboardKeys.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_KeyboardKeyActions)

enum Machine_KeyboardKeyActions {

  Machine_KeyboardKeyActions_Undetermined = (0),

  /// @brief A keyboard key was pressed.
  Machine_KeyboardKeyActions_Press = (1),

  /// @brief A keyboard key was released.
  Machine_KeyboardKeyActions_Release = (2),

  /// @brief A keyboard key was pressed until it repeated.
  Machine_KeyboardKeyActions_Repeat = (3)

};

Ring1_CheckReturn() Ring2_String*
Machine_KeyboardKeyActions_toString
  (
    Machine_KeyboardKeyActions self
  );

/// @brief An event pertaining to a keyboard key.
/// @extends Machine.Object
/// @tood Shoud extend Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_KeyboardKeyEvent)

struct Machine_KeyboardKeyEvent_Class {
  Machine_Object_Class parent;
};

struct Machine_KeyboardKeyEvent {
  Machine_Object parent;
  Machine_KeyboardKeys key;
  Machine_KeyboardKeyActions action;
};

/// @brief Create a keyboard key event.
/// @param key The keyboard key.
/// @param keyAction The action of the keyboard key.
/// #Machine_KeyboardKeyAction_Press if the keyboard key was pressed,
/// #Machine_KeyboardKeyAction_Release if the keyboard key was released.
/// @return The keyboard key event.
Ring1_CheckReturn() Machine_KeyboardKeyEvent*
Machine_KeyboardKeyEvent_create
  (
    Machine_KeyboardKeys key,
    Machine_KeyboardKeyActions keyAction
  );

#endif // RING3_INPUT_KEYBOARDKEYEVENT_H_INCLUDED
