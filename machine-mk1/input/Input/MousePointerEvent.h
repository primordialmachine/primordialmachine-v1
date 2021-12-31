/// @file Input/MousePointerEvent.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_INPUT_MOUSEPOINTEREVENT_H_INCLUDED)
#define MACHINE_INPUT_MOUSEPOINTEREVENT_H_INCLUDED

#if !defined(MACHINE_INPUT_PRIVATE)
#error("Do not include this file directly, include `_Input.h` instead.")
#endif
#include "_Runtime.h"

/// @brief An event pertaining to a mouse pointer.
/// @extends Machine.Object
/// @todo Should extend from Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_MousePointerEvent)

struct Machine_MousePointerEvent_Class {
  Machine_Object_Class parent;
};

struct Machine_MousePointerEvent {
  Machine_Object parent;
  Machine_Real x;
  Machine_Real y;
};

/// @brief Create a mouse pointer event.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse pointer event.
Machine_MousePointerEvent* Machine_MousePointerEvent_create(Machine_Real x, Machine_Real y);

#endif // MACHINE_MOUSEPOINTEREVENT_H_INCLUDED
