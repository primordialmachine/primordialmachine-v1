/// @file Ring3/Input/MousePointerEvent.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_INPUT_MOUSEPOINTEREVENT_H_INCLUDED)
#define RING3_INPUT_MOUSEPOINTEREVENT_H_INCLUDED

#if !defined(RING3_INPUT_PRIVATE)
#error("Do not include `Ring3/Input/MousePointerEvent.h`directly, include `Ring3/Input/_Include.h` instead.")
#endif
#include "Ring3/Input/MousePointerAction.h"

/// @brief An event pertaining to a mouse pointer.
/// @extends Machine.Object
/// @todo Should extend from Ring3.Input.Event.
MACHINE_DECLARE_CLASSTYPE(Ring3_MousePointerEvent)

struct Ring3_MousePointerEvent_Class {
  Machine_Object_Class parent;
};

struct Ring3_MousePointerEvent {
  Machine_Object parent;
  Ring3_MousePointerAction action;
  Ring2_Real32 x;
  Ring2_Real32 y;
};

/// @brief Create a mouse pointer event.
/// @param action The action.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse pointer event.
Ring1_CheckReturn() Ring3_MousePointerEvent*
Ring3_MousePointerEvent_create
  (
    Ring3_MousePointerAction action,
    Ring2_Real32 x,
    Ring2_Real32 y
  );

#endif // RING3_INPUT_MOUSEPOINTEREVENT_H_INCLUDED
