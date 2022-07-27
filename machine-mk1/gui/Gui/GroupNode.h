/// @file Gui/GroupNode.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_GROUPNODE_H_INCLUDED)
#define MACHINE_GUI_GROUPNODE_H_INCLUDED

#if !defined(MACHINE_GUI_PRIVATE)
#error("Do not include `Gui/GroupNode.h` directly, include `_Gui.h` instead.")
#endif
#include "Gui/Widget.h"
#include "Gui/WidgetList.h"

/// @brief A group node.
/// @extends Machine.Gui.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_GroupNode)

struct Machine_Gui_GroupNode_Class {
  Machine_Gui_Widget_Class __parent;
};

struct Machine_Gui_GroupNode {
  Machine_Gui_Widget __parent;
  Machine_Gui_LayoutModel* layoutModel;
  Machine_Gui_WidgetList* children;
};

/// @brief Create a group with default values.
/// @param context The context the group belongs to.
/// @return The group.
Machine_Gui_GroupNode* Machine_Gui_GroupNode_create(Machine_Gui_Context* context);

Machine_Gui_LayoutModel const* Machine_Gui_GroupNode_getLayoutModel(
    Machine_Gui_GroupNode const* self);

void Machine_Gui_GroupNode_setLayoutModel(Machine_Gui_GroupNode* self,
                                          Machine_Gui_LayoutModel* layoutModel);

void Machine_Gui_GroupNode_relayout(Machine_Gui_GroupNode* self, Ring2_Real32 canvasWidth,
                                    Ring2_Real32 canvasHeight);

#endif // MACHINE_GUI_GROUPNODE_H_INCLUDED