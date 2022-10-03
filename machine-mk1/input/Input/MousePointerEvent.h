/// @file Input/MousePointerEvent.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_INPUT_MOUSEPOINTEREVENT_H_INCLUDED)
#define MACHINE_INPUT_MOUSEPOINTEREVENT_H_INCLUDED

#if !defined(MACHINE_INPUT_PRIVATE)
#error("Do not include this file directly, include `_Input.h` instead.")
#endif
#include "Ring2/Library/_Include.h"

MACHINE_DECLARE_ENUMERATIONTYPE(Machine_MousePointerActions)

enum Machine_MousePointerActions {

  Machine_MousePointerActions_Undetermined = (0),

  /// @brief A mouse pointer was moved.
  Machine_MousePointerActions_Move = (1),

  /// @brief A mouse pointer entered an area.
  Machine_MousePointerActions_Enter = (2),

  /// @brief A mouse pointer exited an area.
  Machine_MousePointerActions_Exit = (3)

};

Ring2_String* Machine_MousePointerActions_toString(Machine_MousePointerActions self);

/// @brief An event pertaining to a mouse pointer.
/// @extends Machine.Object
/// @todo Should extend from Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_MousePointerEvent)

struct Machine_MousePointerEvent_Class {
  Machine_Object_Class parent;
};

struct Machine_MousePointerEvent {
  Machine_Object parent;
  Machine_MousePointerActions action;
  Ring2_Real32 x;
  Ring2_Real32 y;
};

/// @brief Create a mouse pointer event.
/// @param action The action.
/// @param x The position of the mouse pointer along the x-axis.
/// @param y The position of the mouse pointer along the y-axis.
/// @return The mouse pointer event.
Machine_MousePointerEvent* Machine_MousePointerEvent_create(Machine_MousePointerActions action,
                                                            Ring2_Real32 x, Ring2_Real32 y);

#endif // MACHINE_MOUSEPOINTEREVENT_H_INCLUDED
