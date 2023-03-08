/// @file Ring3/Gui/Widget.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GUI_WIDGET_H_INCLUDED)
#define RING3_GUI_WIDGET_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/Widget.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Math/_Include.h"
typedef struct Ring3_Gui_RenderContext Ring3_Gui_RenderContext;
typedef struct Ring3_Gui_Selector Ring3_Gui_Selector;
typedef struct Ring3_Gui_WidgetList Ring3_Gui_WidgetList;

MACHINE_DECLARE_INTERFACETYPE(Ring3_Gui_Widget)

struct Ring3_Gui_Widget_Dispatch {
  Machine_InterfaceDispatch parent;
  
  void (*render)(Ring3_Gui_Widget* self, Ring3_Gui_RenderContext* renderContext);

  Ring1_NoDiscardReturn() Ring3_Math_Vector2f32* (*getPosition)(Ring3_Gui_Widget const* self);
  void (*setPosition)(Ring3_Gui_Widget* self, Ring3_Math_Vector2f32 const* position);

  Ring1_NoDiscardReturn() Ring3_Math_Vector2f32* (*getSize)(Ring3_Gui_Widget const* self);
  void (*setSize)(Ring3_Gui_Widget* self, Ring3_Math_Vector2f32 const* size);

  Ring1_NoDiscardReturn() Ring3_Math_Rectangle2* (*getRectangle)(Ring3_Gui_Widget const* self);
  void (*setRectangle)(Ring3_Gui_Widget* self, Ring3_Math_Rectangle2 const* rectangle);

  void (*layout)(Ring3_Gui_Widget* self);

  Ring1_NoDiscardReturn() Ring3_Math_Vector2f32* (*getPreferredSize)(Ring3_Gui_Widget const* self);

  void (*translate)(Ring3_Gui_Widget* self, Ring3_Math_Vector2f32 const* t);

  void (*emit)(Ring3_Gui_Widget* self, Ring2_String* name, size_t numberOfArguments, Ring2_Value const* arguments);
  void (*subscribe)(Ring3_Gui_Widget* self, Ring2_String* name, Machine_Object* context, Ring2_ForeignProcedure* callback );
  void (*unsubscribe)(Ring3_Gui_Widget* self, Ring2_String* name, Machine_Object* context, Ring2_ForeignProcedure* callback);

  Ring1_NoDiscardReturn() Ring3_Math_Vector2f32* (*getAbsolutePosition)(Ring3_Gui_Widget const* self);
  Ring1_NoDiscardReturn() Ring3_Math_Vector2f32* (*getAbsoluteSize)(Ring3_Gui_Widget const* self);
  Ring1_NoDiscardReturn() Ring3_Math_Rectangle2* (*getAbsoluteRectangle)(Ring3_Gui_Widget const* self);

  void (*setName)(Ring3_Gui_Widget* self, Ring2_String* name);
  Ring1_NoDiscardReturn() Ring2_String* (*getName)(Ring3_Gui_Widget const* self);

  Ring1_NoDiscardReturn() Ring2_Collections_List* (*getChildren)(Ring3_Gui_Widget const* self);

  void (*select)(Ring3_Gui_Widget const* self, Ring3_Gui_Selector const* selector, Ring3_Gui_WidgetList* results);
};

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Render this widget.
/// @param self This widget.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
void
Ring3_Gui_Widget_render
  (
    Ring3_Gui_Widget* self,
    Ring3_Gui_RenderContext* renderContext
  );

/// @brief Set the position.
/// @param self This widget.
/// @param position The position.
void
Ring3_Gui_Widget_setPosition
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* position
  );

/// @brief Get the position.
/// @param self This widget.
/// @return The position.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getPosition
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Set the size.
/// @param self This widget.
/// @param size The size.
void
Ring3_Gui_Widget_setSize
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* size
  );

/// @brief Get the size.
/// @param self This widget.
/// @return The size.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getSize
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Set the rectangle.
/// @param self This widget.
/// @param rectangle The rectangle.
void
Ring3_Gui_Widget_setRectangle
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Rectangle2 const* rectangle
  );

/// @brief Get the rectangle.
/// @param self This widget.
/// @return The rectangle.
Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_Widget_getRectangle
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Layout the children of this widget.
/// @param self This widget.
void
Ring3_Gui_Widget_layout
  (
    Ring3_Gui_Widget* self
  );

/// @brief Get the preferred size.
/// @param self This widget.
/// @return The preferred size.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getPreferredSize
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Translate this widget.
/// @param self This widget.
/// @param t The translation.
void
Ring3_Gui_Widget_translate
  (
    Ring3_Gui_Widget* self,
    Ring3_Math_Vector2f32 const* t
  );

/// @brief Emit an event.
/// @param name The name of the event.
/// @param numberOfArguments, arguments The event arguments.
void
Ring3_Gui_Widget_emit
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Subscribe to an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback.
void
Ring3_Gui_Widget_subscribe
  (
    Ring3_Gui_Widget* self,
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
Ring3_Gui_Widget_unsubscribe
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  );

/// @brief Get the absolute position.
/// @param self This widget.
/// @return The absolute position.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getAbsolutePosition
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Get the absolute size.
/// @param self This widget.
/// @return The absolute size.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Gui_Widget_getAbsoluteSize
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Get the absolute rectangle.
/// @param self This widget.
/// @return The absolute rectangle.
Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Gui_Widget_getAbsoluteRectangle
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Get the name of this widget.
/// @param self This widget.
/// @return The name of this widget if any, null otherwise.
Ring1_NoDiscardReturn() Ring2_String*
Ring3_Gui_Widget_getName
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Set the name of this widge.t
/// @param self This widget.
/// @param name The name of this widget if any, null otherwise.
void
Ring3_Gui_Widget_setName
  (
    Ring3_Gui_Widget* self,
    Ring2_String* name
  );

/// @brief Get the children of this widget.
/// @param self This widget.
/// @return A list containing the child widgets of this widget.
/// @remarks Modifying this list will not modify the list of children of this widget.
Ring1_NoDiscardReturn() Ring2_Collections_List*
Ring3_Gui_Widget_getChildren
  (
    Ring3_Gui_Widget const* self
  );

/// @brief Select the widgets.
/// This widget is considered as the "root"
/// @param self A pointer to this widget.
/// @param selector A pointer to the selector.
/// @param results List to append the results to.
void
Ring3_Gui_Widget_select
  (
    Ring3_Gui_Widget const* self,
    Ring3_Gui_Selector const* selector,
    Ring3_Gui_WidgetList *results
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // RING3_GUI_WIDGET_H_INCLUDED
