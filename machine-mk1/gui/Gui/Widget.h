/// @file Gui/Widget.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_WIDGET_H_INCLUDED)
#define MACHINE_GUI_WIDGET_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly, include `_Gui.h` instead.")
#endif
#include "_Collections.h"
#include "_Graphics2.h"
#include "_Math.h"
#include "_Signals.h"
typedef struct Machine_Gui_Context Machine_Gui_Context;

/// @brief Base of all widgets.
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Widget)

struct Machine_Gui_Widget_Class {
  Machine_Object_Class __parent;

  void (*render)(Machine_Gui_Widget* self, Machine_Context2* ctx2);

  Machine_Math_Rectangle2 const* (*getRectangle)(Machine_Gui_Widget const* self);
  void (*setRectangle)(Machine_Gui_Widget* self, Machine_Math_Rectangle2 const* rectangle);
  Machine_Math_Rectangle2 const* (*getCanvasRectangle)(Machine_Gui_Widget const* self);

  Machine_Math_Vector2 const* (*getPosition)(Machine_Gui_Widget const* self);
  void (*setPosition)(Machine_Gui_Widget* self, Machine_Math_Vector2 const* position);

  Machine_Math_Vector2 const* (*getSize)(Machine_Gui_Widget const* self);
  void (*setSize)(Machine_Gui_Widget* self, Machine_Math_Vector2 const* size);

  Machine_Math_Vector2 const* (*getPreferredSize)(Machine_Gui_Widget const* self);

  Machine_Math_Vector2 const* (*getAbsolutePosition)(Machine_Gui_Widget const* self);
  Machine_Math_Rectangle2 const* (*getAbsoluteRectangle)(Machine_Gui_Widget const* self);
  Machine_Math_Rectangle2 const* (*getAbsoluteCanvasRectangle)(Machine_Gui_Widget const* self);
};

struct Machine_Gui_Widget {
  Machine_Object __parent;

  /// @brief The context this widget belongs to.
  Machine_Gui_Context* context;
  /// @brief Rectangle in canvas coordinate sof the parent.
  Machine_Math_Rectangle2* rectangle;
  Machine_Gui_Widget* parent;

  Machine_Signals_Signal* signal;
};

/// @brief Construct this widget.
/// @param self This widget.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_Gui_Widget_construct(Machine_Gui_Widget* self, size_t numberOfArguments,
                                  Machine_Value const* arguments);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Render this widget.
/// @param self This widget.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
void Machine_Gui_Widget_render(Machine_Gui_Widget* self, Machine_Context2* ctx2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the position.
/// @param self This widget.
/// @param position The position.
void Machine_Gui_Widget_setPosition(Machine_Gui_Widget* self, Machine_Math_Vector2 const* position);

/// @brief Get the position.
/// @param self This widget.
/// @return The position.
Machine_Math_Vector2 const* Machine_Gui_Widget_getPosition(Machine_Gui_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the size.
/// @param self This widget.
/// @param size The size.
void Machine_Gui_Widget_setSize(Machine_Gui_Widget* self, Machine_Math_Vector2 const* size);

/// @brief Get the size.
/// @param self This widget.
/// @return The size.
Machine_Math_Vector2 const* Machine_Gui_Widget_getSize(Machine_Gui_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the rectangle.
/// @param self This widget.
/// @param rectangle The rectangle.
void Machine_Gui_Widget_setRectangle(Machine_Gui_Widget* self,
                                     Machine_Math_Rectangle2 const* rectangle);

/// @brief Get the rectangle.
/// @param self This widget.
/// @return The rectangle.
Machine_Math_Rectangle2 const* Machine_Gui_Widget_getRectangle(Machine_Gui_Widget const* self);

/// @brief Get the canvas rectangle.
/// @param self This widget.
/// @return The canvas rectangle.
Machine_Math_Rectangle2 const* Machine_Gui_Widget_getCanvasRectangle(
    Machine_Gui_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the preferred size.
/// @param self This widget.
/// @return The preferred size.
Machine_Math_Vector2 const* Machine_Gui_Widget_getPreferredSize(Machine_Gui_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the absolute position.
/// @param self This widget.
/// @return The absolute position.
Machine_Math_Vector2 const* Machine_Gui_Widget_getAbsolutePosition(Machine_Gui_Widget const* self);

/// @brief Get the absolute rectangle.
/// @param self This widget.
/// @return The absolute rectangle.
Machine_Math_Rectangle2 const* Machine_Gui_Widget_getAbsoluteRectangle(
    Machine_Gui_Widget const* self);

/// @brief Get the absolute canvas rectangle.
/// @param self This widget.
/// @return The absolute canvas rectangle.
Machine_Math_Rectangle2 const* Machine_Gui_Widget_getAbsoluteCanvasRectangle(
    Machine_Gui_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the name of this widget.
/// @param self This widget.
/// @return The name of this widget if any, null otherwise.
Machine_String* Machine_Gui_Widget_getName(Machine_Gui_Widget* self);

/// @brief Set the name of this widge.t
/// @param self This widget.
/// @param name The name of this widget if any, null otherwise.
void Machine_Gui_Widget_setName(Machine_Gui_Widget* self, Machine_String* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Subscribe to an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback.
void Machine_Gui_Widget_subscribe(Machine_Gui_Widget* self, Machine_String* name,
                                  Machine_Object* context, Machine_ForeignProcedure* callback);

/// @brief Unsubscribe from an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback. [context:Machine.Object,arguments:M
void Machine_Gui_Widget_unsubscribe(Machine_Gui_Widget* self, Machine_String* name,
                                    Machine_Object* context, Machine_ForeignProcedure* callback);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_Gui_Widget_emitSignal(Machine_Gui_Widget* self, Machine_String* name,
                                   size_t numberOfArguments, Machine_Value const* arguments);

void Machine_Gui_Widget_emitPositionChangedSignal(Machine_Gui_Widget* self);

void Machine_Gui_Widget_emitSizeChangedSignal(Machine_Gui_Widget* self);

#endif // MACHINE_GUI_WIDGET_H_INCLUDED
