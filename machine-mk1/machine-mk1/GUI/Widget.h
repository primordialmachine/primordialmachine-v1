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
};

/// @brief Construct this widget.
/// @param self This widget.
/// @param numberOfArguments The number of arguments. 
/// @param arguments The arguments.
void Machine_GUI_Widget_construct(Machine_GUI_Widget* self, size_t numberOfArguments, const Machine_Value* arguments);

// @todo Add and use Machine.GUI.Widget.render.
void Machine_GUI_Widget_render(Machine_GUI_Widget* self, float width, float height);

#endif // MACHINE_GUI_WIDGET_H_INCLUDED
