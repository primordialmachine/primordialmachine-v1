/// @file Gui/BorderNode.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_BORDERNODE_H_INCLUDED)
#define MACHINE_GUI_BORDERNODE_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include this file directly. Include `_Gui.h` instead.")
#endif
#include "Gui/Widget.h"

/// @brief A border node.
/// Surrounds a widget with a border.
/// The default color is <code>(0.1, 0.1, 0.1)</code>.
/// The default width is <code>1</code>.
/// @extends Machine.Gui.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_BorderNode)

/// @brief Create a border node with default values.
/// @param context The GUI context the border node belongs to.
/// @return The border node.
Machine_Gui_BorderNode* Machine_Gui_BorderNode_create(Machine_Gui_Context* context);

/// @brief Get the child.
/// @param self This border node.
/// @return A pointer to the child if any, a null pointer otherwise.
Machine_Gui_Widget* Machine_Gui_BorderNode_getChild(Machine_Gui_BorderNode* self);

/// @brief Set the child.
/// @param self This border node.
/// @param child A pointer to the child if any, a null pointer otherwise.
void Machine_Gui_BorderNode_setChild(Machine_Gui_BorderNode* self, Machine_Gui_Widget* child);

/// @brief Get the color of this border.
/// @param self This border node.
/// @return The color.
Ring3_Math_Vector4 const* Machine_Gui_BorderNode_getBorderColor(Machine_Gui_BorderNode const* self);

/// @brief Set the color of this border.
/// @param self This border node.
/// @param color The color.
void Machine_Gui_BorderNode_setBorderColor(Machine_Gui_BorderNode* self,
                                           Ring3_Math_Vector4 const* color);

/// @brief Get the border width.
/// @param self This border node.
/// @return The border width.
Ring2_Real32 Machine_Gui_BorderNode_getBorderLeftWidth(Machine_Gui_BorderNode const* self);
Ring2_Real32 Machine_Gui_BorderNode_getBorderRightWidth(Machine_Gui_BorderNode const* self);
Ring2_Real32 Machine_Gui_BorderNode_getBorderTopWidth(Machine_Gui_BorderNode const* self);
Ring2_Real32 Machine_Gui_BorderNode_getBorderBottomWidth(Machine_Gui_BorderNode const* self);

/// @brief Set the border width.
/// @param self This border node.
/// @param width The border width.
void Machine_Gui_BorderNode_setBorderWidth(Machine_Gui_BorderNode* self, Ring2_Real32 width);
void Machine_Gui_BorderNode_setLeftBorderWidth(Machine_Gui_BorderNode* self, Ring2_Real32 width);
void Machine_Gui_BorderNode_setRightBorderWidth(Machine_Gui_BorderNode* self, Ring2_Real32 width);
void Machine_Gui_BorderNode_setTopBorderWidth(Machine_Gui_BorderNode* self, Ring2_Real32 width);
void Machine_Gui_BorderNode_setBottomBorderWidth(Machine_Gui_BorderNode* self, Ring2_Real32 width);

#endif // MACHINE_GUI_BORDERNODE_H_INCLUDED
