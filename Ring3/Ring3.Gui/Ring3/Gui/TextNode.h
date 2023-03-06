/// @file Ring3/Gui/TextNode.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_TEXTNODE_H_INCLUDED)
#define MACHINE_GUI_TEXTNODE_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/TextNode.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/header.h.i"
#include "Ring3/Gui/Widget.h"

/// @brief A text node.
/// @extends Machine.Gui.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_TextNode)

/// @brief Create a text node with default values.
/// @param context The GUI context the text node belongs to.
/// @return The text node.
Ring1_NoDiscardReturn() Machine_Gui_TextNode*
Machine_Gui_TextNode_create
  (
    Machine_Gui_Context* context
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the text.
/// @param self This text node.
/// @param text The text.
void
Machine_Gui_TextNode_setText
  (
    Machine_Gui_TextNode* self,
    Ring2_String* text
  );

/// @brief Get the text.
/// @param self This text node.
/// @return The text.
Ring1_NoDiscardReturn() Ring2_String*
Machine_Gui_TextNode_getText
  (
    Machine_Gui_TextNode const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the background color.
/// @param self This text node.
/// @param backgroundColor The background color.
void
Machine_Gui_TextNode_setBackgroundColor
  (
    Machine_Gui_TextNode* self,
    Ring3_Math_Vector4f32 const* backgroundColor
  );

/// @brief Get the background color.
/// @param self This text node.
/// @return The background color.
/// @remarks A copy of the stored object is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_TextNode_getBackgroundColor
  (
    Machine_Gui_TextNode const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Set the foreground color.
/// @param self This text node.
/// @param foregroundColor The foreground color.
void
Machine_Gui_TextNode_setForegroundColor
  (
    Machine_Gui_TextNode* self,
    Ring3_Math_Vector3f32 const* foregroundColor
  );

/// @brief Set the foreground color.
/// @param self This text node.
/// @return The foreground color.
Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Machine_Gui_TextNode_getForegroundColor
  (
    Machine_Gui_TextNode const* self
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_GUI_TEXTNODE_H_INCLUDED
