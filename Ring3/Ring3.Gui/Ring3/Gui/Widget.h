/// @file Ring3/Gui/Widget.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_WIDGET_H_INCLUDED)
#define RING3_GUI_WIDGET_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Widget.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/header.h.i"
typedef struct Ring3_Gui_RenderContext Ring3_Gui_RenderContext;
typedef struct Machine_Gui_Context Machine_Gui_Context;

/// @brief Base of all widgets.
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Widget)

struct Machine_Gui_Widget_Class {
  Machine_Object_Class __parent;

  void (*render)(Machine_Gui_Widget* self, Ring3_Gui_RenderContext* renderContext);

  Ring3_Math_Rectangle2* (*getRectangle)(Machine_Gui_Widget const* self);
  void (*setRectangle)(Machine_Gui_Widget* self, Ring3_Math_Rectangle2 const* rectangle);
  Ring3_Math_Rectangle2* (*getCanvasRectangle)(Machine_Gui_Widget const* self);

  Ring3_Math_Vector2f32* (*getPosition)(Machine_Gui_Widget const* self);
  void (*setPosition)(Machine_Gui_Widget* self, Ring3_Math_Vector2f32 const* position);

  Ring3_Math_Vector2f32* (*getSize)(Machine_Gui_Widget const* self);
  void (*setSize)(Machine_Gui_Widget* self, Ring3_Math_Vector2f32 const* size);

  Ring3_Math_Vector2f32* (*getPreferredSize)(Machine_Gui_Widget const* self);

  Ring3_Math_Vector2f32* (*getAbsolutePosition)(Machine_Gui_Widget const* self);
  Ring3_Math_Rectangle2* (*getAbsoluteRectangle)(Machine_Gui_Widget const* self);
  Ring3_Math_Rectangle2* (*getAbsoluteCanvasRectangle)(Machine_Gui_Widget const* self);

  void (*layout)(Machine_Gui_Widget* self);
};

struct Machine_Gui_Widget {
  Machine_Object __parent;

  /// @brief Pointer to the name of the widget or the null pointer.
  Ring2_String* name;
  /// @brief The context this widget belongs to.
  Machine_Gui_Context* context;
  /// @brief Rectangle in canvas coordinate sof the parent.
  Ring3_Math_Rectangle2* rectangle;
  Machine_Gui_Widget* parent;

  Machine_Signals_Signal* signal;
};

/// @brief Construct this widget.
/// @param self This widget.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void
Machine_Gui_Widget_construct
  (
    Machine_Gui_Widget* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Render this widget.
/// @param self This widget.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
void
Machine_Gui_Widget_render
  (
    Machine_Gui_Widget* self,
    Ring3_Gui_RenderContext* renderContext
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the position.
/// @param self This widget.
/// @param position The position.
void
Machine_Gui_Widget_setPosition
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* position
  );

/// @brief Get the position.
/// @param self This widget.
/// @return The position.
Ring3_Math_Vector2f32*
Machine_Gui_Widget_getPosition
  (
    Machine_Gui_Widget const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the size.
/// @param self This widget.
/// @param size The size.
void
Machine_Gui_Widget_setSize
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* size
  );

/// @brief Get the size.
/// @param self This widget.
/// @return The size.
Ring3_Math_Vector2f32*
Machine_Gui_Widget_getSize
  (
    Machine_Gui_Widget const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the rectangle.
/// @param self This widget.
/// @param rectangle The rectangle.
void
Machine_Gui_Widget_setRectangle
  (
    Machine_Gui_Widget* self,
    Ring3_Math_Rectangle2 const* rectangle
  );

/// @brief Get the rectangle.
/// @param self This widget.
/// @return The rectangle.
Ring3_Math_Rectangle2*
Machine_Gui_Widget_getRectangle
  (
    Machine_Gui_Widget const* self
  );

/// @brief Get the canvas rectangle.
/// @param self This widget.
/// @return The canvas rectangle.
Ring3_Math_Rectangle2*
Machine_Gui_Widget_getCanvasRectangle
  (
    Machine_Gui_Widget const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the preferred size.
/// @param self This widget.
/// @return The preferred size.
Ring3_Math_Vector2f32*
Machine_Gui_Widget_getPreferredSize
  (
    Machine_Gui_Widget const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the absolute position.
/// @param self This widget.
/// @return The absolute position.
Ring3_Math_Vector2f32*
Machine_Gui_Widget_getAbsolutePosition
  (
    Machine_Gui_Widget const* self
  );

/// @brief Get the absolute rectangle.
/// @param self This widget.
/// @return The absolute rectangle.
Ring3_Math_Rectangle2*
Machine_Gui_Widget_getAbsoluteRectangle
  (
    Machine_Gui_Widget const* self
  );

/// @brief Get the absolute canvas rectangle.
/// @param self This widget.
/// @return The absolute canvas rectangle.
Ring3_Math_Rectangle2*
Machine_Gui_Widget_getAbsoluteCanvasRectangle
  (
    Machine_Gui_Widget const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the name of this widget.
/// @param self This widget.
/// @return The name of this widget if any, null otherwise.
Ring1_NoDiscardReturn() Ring2_String*
Machine_Gui_Widget_getName
  (
    Machine_Gui_Widget* self
  );

/// @brief Set the name of this widge.t
/// @param self This widget.
/// @param name The name of this widget if any, null otherwise.
void
Machine_Gui_Widget_setName
  (
    Machine_Gui_Widget* self,
    Ring2_String* name
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_layout
  (
    Machine_Gui_Widget* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Subscribe to an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback.
void
Machine_Gui_Widget_subscribe
  (
    Machine_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/// @brief Unsubscribe from an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback.
void
Machine_Gui_Widget_unsubscribe
  (
    Machine_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void
Machine_Gui_Widget_emitSignal
  (
    Machine_Gui_Widget* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

void
Machine_Gui_Widget_emitPositionChangedSignal
  (
    Machine_Gui_Widget* self
  );

void
Machine_Gui_Widget_emitSizeChangedSignal
  (
    Machine_Gui_Widget* self
  );

#endif // RING3_GUI_WIDGET_H_INCLUDED
