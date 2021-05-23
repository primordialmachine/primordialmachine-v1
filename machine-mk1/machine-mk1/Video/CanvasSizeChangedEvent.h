/// @file Video/CanvasSizeChangedEvent.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_CANVASSIZECHANGEDEVENT_H_INCLUDED)
#define MACHINE_VIDEO_CANVASSIZECHANGEDEVENT_H_INCLUDED

#if !defined(MACHINE_VIDEO_PRIVATE)
#error("Do not include this file directly, include `_Video.h` instead.")
#endif

#include "_Runtime.h"

/// @brief An event pertaining to a canvas of which the size has changed.
/// @extends Machine.Object
/// @todo Should extend from Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Machine_CanvasSizeChangedEvent)

struct Machine_CanvasSizeChangedEvent {
  Machine_Object parent;
  float width;
  float height;
};

/// @brief Create a canvas size changed event.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
/// @return The mouse pointer event.
Machine_CanvasSizeChangedEvent* Machine_CanvasSizeChangedEvent_create(float width, float height);

#endif // MACHINE_VIDEO_CANVASSIZECHANGEDEVENT_H_INCLUDED
