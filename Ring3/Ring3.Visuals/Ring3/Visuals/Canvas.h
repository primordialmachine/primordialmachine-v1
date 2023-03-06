/// @file Ring3/Visuals/Canvas.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_CANVAS_H_INCLUDED)
#define RING3_CANVAS_H_INCLUDED

#if !defined(RING3_VISUALS_PRIVATE)
#error("Do not include `Ring3/Visuals/Canvas.h` directly. Include `Ring3/Visuals/_Include.h` instead.")
#endif

#include "Ring3/Signals/_Include.h"
#include "Ring3/Input/_Include.h"

/// @brief Abstract base of all canvas.
/// This engine only supports one main canvas.
MACHINE_DECLARE_CLASSTYPE(Ring3_Canvas);

struct Ring3_Canvas_Class {
  Machine_Object_Class parent__;
  
  void
  (*getFrameBuffersSize)
    (
      Ring3_Canvas* self,
      Ring2_Integer* width,
      Ring2_Integer* height
    );
  
  void
  (*maximizeCanvas)
    (
      Ring3_Canvas* self
    );
  
  void
  (*swapFrameBuffers)
    (
      Ring3_Canvas* self
    );
  
  void
  (*setCanvasIcons)
    (
      Ring3_Canvas* self,
      Ring2_Collections_List* images
    );
  
  void
  (*pollEvents)
    (
      Ring3_Canvas* self
    );
  
  Ring2_Boolean
  (*getQuitRequested)
    (
      Ring3_Canvas* self
    );
};

struct Ring3_Canvas {
  Machine_Object parent;
  Machine_Signals_Signal* signal;
  Ring2_Collections_Deque* events;
};

void
Ring3_Canvas_construct
  (
    Ring3_Canvas* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Get the size, in pixels, of the frame buffers.
/// @param self This canvas.
/// @param width A pointer to a Machine_Integer variable.
/// @param height A pointer to a Machine_Integer variable.
/// @success
/// - The width was assigned to *width.
/// - The height was assigned to *height.
void
Ring3_Canvas_getFrameBuffersSize
  (
    Ring3_Canvas* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  );

/// @brief Maximize this canvas.
/// @param self This canvas.
void
Ring3_Canvas_maximizeCanvas
  (
    Ring3_Canvas* self
  );

/// @brief Swap the frame buffers of this canvas..
/// @param self This canvas.
void
Ring3_Canvas_swapFrameBuffers
  (
    Ring3_Canvas* self
  );

/// @brief Set the icons of this canvas.
/// @param self This canvas.
/// @param images The icons.
void
Ring3_Canvas_setCanvasIcons
  (
    Ring3_Canvas* self,
    Ring2_Collections_List* images
  );

/// @brief Poll the events of this canvas.
/// @param self This canvas.
void
Ring3_Canvas_pollEvents
  (
    Ring3_Canvas* self
  );

/// @brief Get if the application was requested to quit.
/// @param self This canvas.
/// @return @a true if quit was requested, @a false otherwise.
Ring2_Boolean
Ring3_Canvas_getQuitRequested
  (
    Ring3_Canvas* self
  );

/// @brief Subscribe to keyboard key pressed events.
/// @param self This canvas.
void
Ring3_Canvas_subscribeKeyboardKeyPressedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/// @brief Subscribe to keyboard key released events.
/// @param self This canvas.
void
Ring3_Canvas_subscribeKeyboardKeyReleasedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/// @brief Subscribe to the mouse button pressed events.
/// @param self This canvas.
void
Ring3_Canvas_subscribeMouseButtonPressedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/// @brief Subscribe to the mouse button released events.
/// @param self This canvas.
void
Ring3_Canvas_subscribeMouseButtonReleasedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/// @brief Subscribe to the mouse pointer moved event signals.
/// @param self This canvas.
void
Ring3_Canvas_subscribeMousePointerMovedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

void
Ring3_Canvas_addKeyboardKeyEvent
  (
    Ring3_Canvas* self,
    Ring3_KeyboardKeyEvent* event
  );

void
Ring3_Canvas_addMouseButtonEvent
  (
    Ring3_Canvas* self,
    Ring3_MouseButtonEvent* event
  );

void
Ring3_Canvas_addMousePointerEvent
  (
    Ring3_Canvas* self,
    Ring3_MousePointerEvent* event
  );

void
Ring3_Canvas_pumpEvents
  (
    Ring3_Canvas* self
  );

#endif // RING3_CANVAS_H_INCLUDED
