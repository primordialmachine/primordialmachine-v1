/// @file Ring3/Visuals/CanvasSizeChangedEvent.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_CANVASSIZECHANGEDEVENT_H_INCLUDED)
#define RING3_VISUALS_CANVASSIZECHANGEDEVENT_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/CanvasSizeChangedEvent.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring2/_Include.h"


/// @brief An event pertaining to a canvas of which the size has changed.
/// @extends Machine.Object
/// @todo Should extend from Machine.Event.
MACHINE_DECLARE_CLASSTYPE(Ring3_CanvasSizeChangedEvent)

struct Ring3_CanvasSizeChangedEvent_Class {
  Machine_Object_Class parent;
};

struct Ring3_CanvasSizeChangedEvent {
  Machine_Object parent;
  float width;
  float height;
};

/// @brief Create a canvas size changed event.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
/// @return The mouse pointer event.
Ring1_CheckReturn() Ring3_CanvasSizeChangedEvent*
Ring3_CanvasSizeChangedEvent_create
  (
    float width,
    float height
  );

#endif // RING3_VISUALS_CANVASSIZECHANGEDEVENT_H_INCLUDED
