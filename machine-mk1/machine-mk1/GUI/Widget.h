/// @file GUI/Widget.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_WIDGET_H_INCLUDED)
#define MACHINE_GUI_WIDGET_H_INCLUDED

#include "_Math.h"

/// @brief Base of all widgets.
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_Widget)

struct Machine_GUI_Widget {
  void (*render)(Machine_GUI_Widget* self, float width, float height);
  
  const Machine_Math_Rectangle2* (*getRectangle)(Machine_GUI_Widget* self);
  void (*setRectangle)(Machine_GUI_Widget* self, const Machine_Math_Rectangle2* rectangle);
  
  const Machine_Math_Vector2* (*getPosition)(Machine_GUI_Widget* self);
  void (*setPosition)(Machine_GUI_Widget* self, const Machine_Math_Vector2* position);

  const Machine_Math_Vector2* (*getSize)(Machine_GUI_Widget* self);
  void (*setSize)(Machine_GUI_Widget* self, const Machine_Math_Vector2* size);

  const Machine_Math_Vector2* (*getPreferredSize)(Machine_GUI_Widget* self);
};

/// @brief Construct this widget.
/// @param self This widget.
/// @param numberOfArguments The number of arguments. 
/// @param arguments The arguments.
void Machine_GUI_Widget_construct(Machine_GUI_Widget* self, size_t numberOfArguments, const Machine_Value* arguments);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Render this widget.
/// @param self This widget.
/// @param width The width of the canvas.
/// @param height The height of the canvas.
void Machine_GUI_Widget_render(Machine_GUI_Widget* self, float width, float height);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the position.
/// @param self This widget.
/// @param position The position.
void Machine_GUI_Widget_setPosition(Machine_GUI_Widget* self, const Machine_Math_Vector2* position);

/// @brief Get the position.
/// @param self This widget.
/// @return The position.
const Machine_Math_Vector2* Machine_GUI_Widget_getPosition(Machine_GUI_Widget* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the size.
/// @param self This widget.
/// @param size The size.
void Machine_GUI_Widget_setSize(Machine_GUI_Widget* self, const Machine_Math_Vector2* size);

/// @brief Get the size.
/// @param self This widget.
/// @return The size.
const Machine_Math_Vector2* Machine_GUI_Widget_getSize(Machine_GUI_Widget* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the rectangle.
/// @param self This widget.
/// @param rectangle The rectangle.
void Machine_GUI_Widget_setRectangle(Machine_GUI_Widget* self, const Machine_Math_Rectangle2* rectangle);

/// @brief Get the rectangle.
/// @param self This widget.
/// @return The rectangle.
const Machine_Math_Rectangle2* Machine_GUI_Widget_getRectangle(Machine_GUI_Widget* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Get the preferred size.
/// @param self This widget.
/// @return The preferred size.
const Machine_Math_Vector2* Machine_GUI_Widget_getPreferredSize(Machine_GUI_Widget* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_GUI_WIDGET_H_INCLUDED
