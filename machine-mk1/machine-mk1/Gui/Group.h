/// @file Gui/Group.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GUI_GROUP_H_INCLUDED)
#define MACHINE_GUI_GROUP_H_INCLUDED



#include "Gui/Widget.h"
#include "Gui/WidgetList.h"



/// @brief A group.
/// @extends Machine.GUI.Widget
MACHINE_DECLARE_CLASSTYPE(Machine_Gui_Group)

struct Machine_Gui_Group_Class {
  Machine_GUI_Widget_Class __parent;
};

struct Machine_Gui_Group {
  Machine_GUI_Widget __parent;
  Machine_Gui_LayoutModel* layoutModel;
  Machine_Gui_WidgetList* children;
};

/// @brief Create a group with default values.
/// @param context The context the group belongs to.
/// @return The group.
Machine_Gui_Group* Machine_Gui_Group_create(Machine_Gui_Context* context);

Machine_Gui_LayoutModel const* Machine_Gui_Group_getLayoutModel(Machine_Gui_Group const* self);

void Machine_Gui_Group_setLayoutModel(Machine_Gui_Group* self, Machine_Gui_LayoutModel* layoutModel);

void Machine_Gui_Group_relayout(Machine_Gui_Group* self, Machine_Real canvasWidth, Machine_Real canvasHeight);

#endif // MACHINE_GUI_GROUP_H_INCLUDED