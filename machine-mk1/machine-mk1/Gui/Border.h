/// @file Gui/Border.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_BORDER_H_INCLUDED)
#define MACHINE_GUI_BORDER_H_INCLUDED



#include "Gui/Widget.h"



/// @brief A border around any widget.
/// The default color is <code>(0.1, 0.1, 0.1)</code>.
/// The default width is <code>1</code>.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Border)

/// @brief Create a border with default values.
/// @param context The GUI context the border belongs to.
/// @return The border.
Machine_Gui_Border* Machine_Gui_Border_create(Machine_Gui_Context* context);

/// @brief Get the child.
/// @param self This border.
/// @return A pointer to the child if any, a null pointer otherwise.
Machine_Gui_Widget* Machine_Gui_Widget_getChild(Machine_Gui_Border* self);

/// @brief Set the child.
/// @param self This border.
/// @param child A pointer to the child if any, a null pointer otherwise.
void Machine_Gui_Border_setChild(Machine_Gui_Border* self, Machine_Gui_Widget* child);

/// @brief Get the color of this border.
/// @param self This border.
/// @return The color.
Machine_Math_Vector4 const* Machine_Gui_Border_getBorderColor(Machine_Gui_Border const* self);

/// @brief Set the color of this border.
/// @param self This border.
/// @param color The color.
void Machine_Gui_Border_setBorderColor(Machine_Gui_Border* self, Machine_Math_Vector4 const* color);

/// @brief Get the border width.
/// @param self This border.
/// @return The border width.
Machine_Real Machine_Gui_Border_getBorderLeftWidth(Machine_Gui_Border const* self);
Machine_Real Machine_Gui_Border_getBorderRightWidth(Machine_Gui_Border const* self);
Machine_Real Machine_Gui_Border_getBorderTopWidth(Machine_Gui_Border const* self);
Machine_Real Machine_Gui_Border_getBorderBottomWidth(Machine_Gui_Border const* self);

/// @brief Set the border width.
/// @param self This border.
/// @param width The border width.
void Machine_Gui_Border_setBorderWidth(Machine_Gui_Border* self, Machine_Real width);
void Machine_Gui_Border_setLeftBorderWidth(Machine_Gui_Border* self, Machine_Real width);
void Machine_Gui_Border_setRightBorderWidth(Machine_Gui_Border* self, Machine_Real width);
void Machine_Gui_Border_setTopBorderWidth(Machine_Gui_Border* self, Machine_Real width);
void Machine_Gui_Border_setBottomBorderWidth(Machine_Gui_Border* self, Machine_Real width);


#endif // MACHINE_GUI_BORDER_H_INCLUDED
