/// @file Ring3/Input/KeyboardKeyEvent.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_KEYBOARDKEYEVENT_H_INCLUDED)
#define RING3_INPUT_KEYBOARDKEYEVENT_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/KeyboardKeyEvent.h` directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring3/Input/KeyboardKey.h"
#include "Ring3/Input/KeyboardKeyAction.h"

/// @brief An event pertaining to a keyboard key.
/// @extends Machine.Object
/// @todo Should extend from Ring3.Input.Event.
MACHINE_DECLARE_CLASSTYPE(Ring3_KeyboardKeyEvent)

struct Ring3_KeyboardKeyEvent_Class {
  Machine_Object_Class parent;
};

struct Ring3_KeyboardKeyEvent {
  Machine_Object parent;
  Ring3_KeyboardKey key;
  Ring3_KeyboardKeyAction action;
};

/// @brief Create a keyboard key event.
/// @param key The keyboard key.
/// @param keyAction The action of the keyboard key.
/// #Ring3_KeyboardKeyAction_Press if the keyboard key was pressed,
/// #Ring3_KeyboardKeyAction_Release if the keyboard key was released.
/// @return The keyboard key event.
Ring1_CheckReturn() Ring3_KeyboardKeyEvent*
Ring3_KeyboardKeyEvent_create
  (
    Ring3_KeyboardKey key,
    Ring3_KeyboardKeyAction keyAction
  );

#endif // RING3_INPUT_KEYBOARDKEYEVENT_H_INCLUDED
