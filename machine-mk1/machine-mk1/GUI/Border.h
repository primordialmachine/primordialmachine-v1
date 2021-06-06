/// @file GUI/Border.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_BORDER_H_INCLUDED)
#define MACHINE_GUI_BORDER_H_INCLUDED

#include "./../GUI/Widget.h"

/// @brief A border around any widget.
/// The default color is <code>(0.1, 0.1, 0.1)</code>.
/// The default width is <code>1</code>.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_GUI_Border)

/// @brief Create a label with default values.
/// @return The label.
Machine_GUI_Border* Machine_GUI_Border_create();

/// @brief Get the child.
/// @param self This border.
/// @return A pointer to the child if any, a null pointer otherwise.
Machine_GUI_Widget* Machine_GUI_Widget_getChild(Machine_GUI_Border* self);

/// @brief Set the child.
/// @param self This border.
/// @param child A pointer to the child if any, a null pointer otherwise.
void Machine_GUI_Border_setChild(Machine_GUI_Border* self, Machine_GUI_Widget* child);

/// @brief Get the color of this border.
/// @param self This border.
/// @return The color.
const Machine_Math_Vector3* Machine_GUI_Border_getBorderColor(const Machine_GUI_Border* self);

/// @brief Set the color of this border.
/// @param self This border.
/// @param color The color.
void Machine_GUI_Border_setBorderColor(Machine_GUI_Border *self, Machine_Math_Vector3 *color);

/// @brief Get the border width.
/// @param self This border.
/// @return The border width.
float Machine_GUI_Border_getBorderWidth(const Machine_GUI_Border* self);

/// @brief Set the border width.
/// @param self This border.
/// @param width The border width.
void Machine_GUI_Border_setBorderWidth(Machine_GUI_Border* self, float width);

#endif // MACHINE_GUI_BORDER_H_INCLUDED
