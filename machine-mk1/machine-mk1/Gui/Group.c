/// @file Gui/Group.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/Group.h"



#include "Gui/Context.h"
#include "./../Video.h"



static void Machine_Gui_Group_visit(Machine_Gui_Group* self) {
  if (self->layoutModel) {
    Machine_Gc_visit(self->layoutModel);
  }
  if (self->children) {
    Machine_Gc_visit(self->children);
  }
}

static Machine_Math_Vector2 const* Machine_Gui_Group_getPreferredSize(Machine_Gui_Group const* self) {
  return Machine_Math_Rectangle2_getSize(Machine_GUI_Widget_getRectangle((Machine_GUI_Widget *)self));
}

static void Machine_Gui_Group_render(Machine_Gui_Group* self, Machine_Context2 *ctx2) {
  Machine_Gui_Context* ctx = Machine_Gui_Context_create(Machine_GDL_Context_create(), Machine_Context2_create(Machine_getVideoContext()));
  Machine_Math_Vector2 const* size = Machine_GUI_Widget_getSize((Machine_GUI_Widget *)self);
  Machine_Context2* tmp = Machine_Context2_create(Machine_getVideoContext());
  Machine_Context2_setTargetSize(tmp, Machine_Math_Vector2_getX(size), Machine_Math_Vector2_getY(size));
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self->children); i < n; ++i) {
    Machine_GUI_Widget* widget = Machine_Gui_WidgetList_getAt(self->children, i);
    Machine_GUI_Widget_render(widget, tmp);
  }
}

static void Machine_Gui_Group_constructClass(Machine_Gui_Group_Class* self) {
  ((Machine_GUI_Widget_Class*)self)->render = (void (*)(Machine_GUI_Widget*, Machine_Context2*)) & Machine_Gui_Group_render;
  ((Machine_GUI_Widget_Class*)self)->getPreferredSize = (Machine_Math_Vector2 const* (*)(Machine_GUI_Widget const*)) & Machine_Gui_Group_getPreferredSize;
}

void Machine_Gui_Group_construct(Machine_Gui_Group* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_GUI_Widget_construct((Machine_GUI_Widget*)self, numberOfArguments, arguments);
  self->layoutModel = Machine_GUI_LayoutModel_create();
  self->children = Machine_Gui_WidgetList_create();
  Machine_setClassType((Machine_Object*)self, Machine_Gui_Group_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Group, Machine_GUI_Widget, &Machine_Gui_Group_visit, &Machine_Gui_Group_construct, NULL, &Machine_Gui_Group_constructClass)

Machine_Gui_Group* Machine_Gui_Group_create(Machine_Gui_Context* context) {
  Machine_ClassType* ty = Machine_Gui_Group_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value ARGUMENTS[1];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context);
  Machine_Gui_Group* self = (Machine_Gui_Group*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_GUI_LayoutModel const* Machine_Gui_Group_getLayoutModel(Machine_Gui_Group const* self) {
  return self->layoutModel;
}

void Machine_Gui_Group_setLayoutModel(Machine_Gui_Group* self, Machine_GUI_LayoutModel* layoutModel) {
  self->layoutModel = layoutModel;
}

void Machine_Gui_Group_relayout(Machine_Gui_Group* self, Machine_Real canvasWidth, Machine_Real canvasHeight) {
  // Set the size of all children to the same value: That value is the component-wise maxima vector of the preferred sizes of all children.
  Machine_Math_Vector2* preferredSize = Machine_Math_Vector2_clone(Machine_GUI_Widget_getPreferredSize(Machine_Gui_WidgetList_getAt(self->children, 0)));
  for (size_t i = 1, n = Machine_Gui_WidgetList_getSize(self->children); i < n; ++i) {
    Machine_Math_Vector2_maxima(preferredSize, preferredSize, Machine_GUI_Widget_getPreferredSize(Machine_Gui_WidgetList_getAt(self->children, i)));
  }
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self->children); i < n; ++i) {
    Machine_GUI_Widget_setSize(Machine_Gui_WidgetList_getAt(self->children, i), preferredSize);
  }
  // Layout the children.
  Machine_Math_Vector2 const* size = Machine_GUI_Widget_getSize((Machine_GUI_Widget*)self);
  Machine_Gui_WidgetList_layout(self->children, Machine_Math_Vector2_getX(size), Machine_Math_Vector2_getY(size), canvasWidth, canvasHeight, self->layoutModel);
}
