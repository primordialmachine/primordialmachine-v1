/// @file Gui/Widget.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_WIDGET_H_INCLUDED)
#define MACHINE_GUI_WIDGET_H_INCLUDED



#include "_Collections.h"
#include "_Math.h"
#include "_Signals.h"
#include "_Graphics2.h"
typedef struct Machine_GUI_Context Machine_GUI_Context;



/// @brief Base of all widgets.
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_Widget)

struct Machine_GUI_Widget_Class {
  Machine_Object_Class __parent;

  void (*render)(Machine_GUI_Widget* self, Machine_Context2* ctx2);

  Machine_Math_Rectangle2 const* (*getRectangle)(Machine_GUI_Widget const* self);
  void (*setRectangle)(Machine_GUI_Widget* self, Machine_Math_Rectangle2 const* rectangle);
  Machine_Math_Rectangle2 const* (*getCanvasRectangle)(Machine_GUI_Widget const* self);

  Machine_Math_Vector2 const* (*getPosition)(Machine_GUI_Widget const* self);
  void (*setPosition)(Machine_GUI_Widget* self, Machine_Math_Vector2 const* position);

  Machine_Math_Vector2 const* (*getSize)(Machine_GUI_Widget const* self);
  void (*setSize)(Machine_GUI_Widget* self, Machine_Math_Vector2 const* size);

  Machine_Math_Vector2 const* (*getPreferredSize)(Machine_GUI_Widget const* self);

  Machine_Math_Vector2 const* (*getAbsolutePosition)(Machine_GUI_Widget const* self);
  Machine_Math_Rectangle2 const* (*getAbsoluteRectangle)(Machine_GUI_Widget const* self);
  Machine_Math_Rectangle2 const* (*getAbsoluteCanvasRectangle)(Machine_GUI_Widget const* self);
};

struct Machine_GUI_Widget {
  Machine_Object __parent;

  /// @brief The context this widget belongs to.
  Machine_GUI_Context* context;
  /// @brief Rectangle in canvas coordinate sof the parent.
  Machine_Math_Rectangle2* rectangle;
  Machine_GUI_Widget* parent;

  Machine_Signals_Signal* signal;
};

/// @brief Construct this widget.
/// @param self This widget.
/// @param numberOfArguments The number of arguments. 
/// @param arguments The arguments.
void Machine_GUI_Widget_construct(Machine_GUI_Widget* self, size_t numberOfArguments, Machine_Value const* arguments);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Render this widget.
/// @param self This widget.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
void Machine_GUI_Widget_render(Machine_GUI_Widget* self, Machine_Context2* ctx2);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the position.
/// @param self This widget.
/// @param position The position.
void Machine_GUI_Widget_setPosition(Machine_GUI_Widget* self, Machine_Math_Vector2 const* position);

/// @brief Get the position.
/// @param self This widget.
/// @return The position.
Machine_Math_Vector2 const* Machine_GUI_Widget_getPosition(Machine_GUI_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the size.
/// @param self This widget.
/// @param size The size.
void Machine_GUI_Widget_setSize(Machine_GUI_Widget* self, Machine_Math_Vector2 const* size);

/// @brief Get the size.
/// @param self This widget.
/// @return The size.
Machine_Math_Vector2 const* Machine_GUI_Widget_getSize(Machine_GUI_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the rectangle.
/// @param self This widget.
/// @param rectangle The rectangle.
void Machine_GUI_Widget_setRectangle(Machine_GUI_Widget* self, Machine_Math_Rectangle2 const* rectangle);

/// @brief Get the rectangle.
/// @param self This widget.
/// @return The rectangle.
Machine_Math_Rectangle2 const* Machine_GUI_Widget_getRectangle(Machine_GUI_Widget const* self);

/// @brief Get the canvas rectangle.
/// @param self This widget.
/// @return The canvas rectangle.
Machine_Math_Rectangle2 const* Machine_GUI_Widget_getCanvasRectangle(Machine_GUI_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the preferred size.
/// @param self This widget.
/// @return The preferred size.
Machine_Math_Vector2 const* Machine_GUI_Widget_getPreferredSize(Machine_GUI_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the absolute position.
/// @param self This widget.
/// @return The absolute position.
Machine_Math_Vector2 const* Machine_GUI_Widget_getAbsolutePosition(Machine_GUI_Widget const* self);

/// @brief Get the absolute rectangle.
/// @param self This widget.
/// @return The absolute rectangle.
Machine_Math_Rectangle2 const* Machine_GUI_Widget_getAbsoluteRectangle(Machine_GUI_Widget const* self);

/// @brief Get the absolute canvas rectangle.
/// @param self This widget.
/// @return The absolute canvas rectangle.
Machine_Math_Rectangle2 const* Machine_GUI_Widget_getAbsoluteCanvasRectangle(Machine_GUI_Widget const* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the name of this widget.
/// @param self This widget.
/// @return The name of this widget if any, null otherwise.
Machine_String* Machine_GUI_Widget_getName(Machine_GUI_Widget* self);

/// @brief Set the name of this widge.t
/// @param self This widget.
/// @param name The name of this widget if any, null otherwise.
void Machine_GUI_Widget_setName(Machine_GUI_Widget* self, Machine_String* name);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Subscribe to an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback.
void Machine_GUI_Widget_subscribe(Machine_GUI_Widget* self, Machine_String *name, Machine_Object* context, Machine_ForeignProcedure* callback);

/// @brief Unsubscribe from an event.
/// @param self This widget.
/// @param name The name of the event.
/// @param context The context.
/// @param callback The callback. [context:Machine.Object,arguments:M
void Machine_GUI_Widget_unsubscribe(Machine_GUI_Widget* self, Machine_String *name, Machine_Object *context, Machine_ForeignProcedure* callback);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_emitSignal(Machine_GUI_Widget* self, Machine_String* name, size_t numberOfArguments, Machine_Value const* arguments);

void Machine_GUI_Widget_emitPositionChangedSignal(Machine_GUI_Widget* self);

void Machine_GUI_Widget_emitSizeChangedSignal(Machine_GUI_Widget* self);



#endif // MACHINE_GUI_WIDGET_H_INCLUDED
