/// @file Input/KeyboardKeyEvent.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_INPUT_KEYBOARDKEYEVENT_H_INCLUDED)
#define MACHINE_INPUT_KEYBOARDKEYEVENT_H_INCLUDED

#if !defined(MACHINE_INPUT_PRIVATE)
#error("Do not include this file directly, include `_Input.h` instead.")
#endif

#include "./../Input/KeyboardKeys.h"

typedef enum Machine_KeyboardKeyActions {

  Machine_KeyboardKeyActions_Undetermined = (0),

  /// @brief A keyboard key was pressed.
  Machine_KeyboardKeyActions_Press = (1),

  /// @brief A keyboard key was released.
  Machine_KeyboardKeyActions_Release  = (2),

  /// @brief A keyboard key was pressed until it repeated.
  Machine_KeyboardKeyActions_Repeat = (3)

} Machine_KeyboardKeyActions;

Machine_String* Machine_KeyboardKeyActions_toString(Machine_KeyboardKeyActions self);

/// @brief An event pertaining to a keyboard key.
/// @extends Machine.Object
/// @tood Shoud extend Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_KeyboardKeyEvent)

struct Machine_KeyboardKeyEvent {
  Machine_Object parent;
  Machine_KeyboardKeys key;
  Machine_KeyboardKeyActions keyAction;
};

/// @brief Create a keyboard key event.
/// @param key The keyboard key.
/// @param keyAction The action of the keyboard key.
/// #Machine_KeyboardKeyAction_Press if the keyboard key was pressed,
/// #Machine_KeyboardKeyAction_Release if the keyboard key was released.
/// @return The keyboard key event.
Machine_KeyboardKeyEvent* Machine_KeyboardKeyEvent_create(Machine_KeyboardKeys key, Machine_KeyboardKeyActions keyAction);

#endif // MACHINE_INPUT_KEYBOARDKEYEVENT_H_INCLUDED
