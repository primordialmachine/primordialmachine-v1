/// @file Ring3/Gui/GroupNode.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(MACHINE_GUI_GROUPNODE_H_INCLUDED)
#define MACHINE_GUI_GROUPNODE_H_INCLUDED

#if !defined(RING3_GUI_PRIVATE)
#error("Do not include `Ring3/Gui/GroupNode.h` directly, include `Ring3/Gui/_Include.h` instead.")
#endif
#include "Ring3/Gui/header.h.i"
#include "Ring3/Gui/Widget.h"
#include "Ring3/Gui/ArrayWidgetList.h"

/// @brief A group node.
/// @extends Machine.Gui.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_GroupNode)

struct Machine_Gui_GroupNode_Class {
  Machine_Gui_Widget_Class __parent;
};

struct Machine_Gui_GroupNode {
  Machine_Gui_Widget __parent;
  Machine_Gui_LayoutModel* layoutModel;
  Machine_Gui_ArrayWidgetList* children;
};

/// @brief Create a group with default values.
/// @param context The context the group belongs to.
/// @return The group.
Ring1_NoDiscardReturn() Machine_Gui_GroupNode*
Machine_Gui_GroupNode_create
  (
    Machine_Gui_Context* context
  );

Ring1_NoDiscardReturn() Machine_Gui_LayoutModel const*
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

#endif // MACHINE_GUI_GROUPNODE_H_INCLUDED
