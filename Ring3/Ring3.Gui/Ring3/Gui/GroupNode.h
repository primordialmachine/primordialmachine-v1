/// @file Ring3/Gui/GroupNode.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_GROUPNODE_H_INCLUDED)
#define MACHINE_GUI_GROUPNODE_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/GroupNode.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/WidgetBase.h"
#include "Ring3/Gui/WidgetList.h"
#include "Ring3/Math/_Include.h"
#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Gui/LayoutModel.h"

/// @brief A group node.
/// @extends Machine.Gui.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_GroupNode)

struct Machine_Gui_GroupNode_Class {
  Ring3_Gui_WidgetBase_Class __parent;
};

struct Machine_Gui_GroupNode {
  Ring3_Gui_WidgetBase __parent;
  /// @brief The shape for rendering the background.
  Ring3_Graphics2_Rectangle* background;
  Machine_Gui_LayoutModel* layoutModel;
  Ring3_Gui_WidgetList* children;
};

/// @brief Create a group with default values.
/// @param context The context the group belongs to.
/// @return The group.
Ring1_NoDiscardReturn() Machine_Gui_GroupNode*
Machine_Gui_GroupNode_create
  (
    Machine_Gui_Context* context
  );

/// @brief Get the layout model.
/// @param self A pointer to this group node.
/// @return The layout model of this group node.
/// @todo A group should subscribe to events of its layout model to detect changes to that model.
/// @todo A layout model should support events indicating changes to the model.
Ring1_NoDiscardReturn() Machine_Gui_LayoutModel*
Machine_Gui_GroupNode_getLayoutModel
  (
    Machine_Gui_GroupNode const* self
  );

void
Machine_Gui_GroupNode_setLayoutModel
  (
    Machine_Gui_GroupNode* self,
    Machine_Gui_LayoutModel* layoutModel
  );

/// @brief Get the background color of this group.
/// @param self This group node.
/// @return The background color.
/// @remarks A copy of the stored object is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_GroupNode_getBackgroundColor
  (
    Machine_Gui_GroupNode const* self
  );

/// @brief Set the background color of this group.
/// @param self This group node.
/// @param backgroundColor The background color.
void
Machine_Gui_GroupNode_setBackgroundColor
  (
    Machine_Gui_GroupNode* self,
    Ring3_Math_Vector4f32 const* backgroundColor
  );

#endif // MACHINE_GUI_GROUPNODE_H_INCLUDED
