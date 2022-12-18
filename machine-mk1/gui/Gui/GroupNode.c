/// @file Gui/GroupNode.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/GroupNode.h"


#include "Ring1/All/_Include.h"
#include "Gui/Context.h"
#include "_Video.h"


static void Machine_Gui_GroupNode_visit(Machine_Gui_GroupNode* self) {
  if (self->layoutModel) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->layoutModel);
  }
  if (self->children) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->children);
  }
}

static Ring3_Math_Vector2 const* Machine_Gui_GroupNode_getPreferredSize(
    Machine_Gui_GroupNode const* self) {
  return Ring3_Math_Rectangle2_getSize(Machine_Gui_Widget_getRectangle((Machine_Gui_Widget*)self));
}

static void Machine_Gui_GroupNode_render(Machine_Gui_GroupNode* self, Machine_Context2* ctx2) {
  Machine_Gui_Context* ctx = Machine_Gui_Context_create(
      Machine_Gdl_Context_create(), Machine_Context2_create(ctx2->videoContext));
  Ring3_Math_Vector2 const* size = Machine_Gui_Widget_getSize((Machine_Gui_Widget*)self);
  Machine_Context2* tmp = Machine_Context2_create(ctx2->videoContext);
  Machine_Context2_setTargetSize(tmp, Ring3_Math_Vector2_getX(size),
                                      Ring3_Math_Vector2_getY(size));
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self->children); i < n; ++i) {
    Machine_Gui_Widget* widget = Machine_Gui_WidgetList_getAt(self->children, i);
    Machine_Gui_Widget_render(widget, tmp);
  }
}

static void Machine_Gui_GroupNode_constructClass(Machine_Gui_GroupNode_Class* self) {
  ((Machine_Gui_Widget_Class*)self)->render
      = (void (*)(Machine_Gui_Widget*, Machine_Context2*)) & Machine_Gui_GroupNode_render;
  ((Machine_Gui_Widget_Class*)self)->getPreferredSize
      = (Ring3_Math_Vector2 const* (*)(Machine_Gui_Widget const*))
        & Machine_Gui_GroupNode_getPreferredSize;
}

void Machine_Gui_GroupNode_construct(Machine_Gui_GroupNode* self, size_t numberOfArguments,
                                     Ring2_Value const* arguments) {
  Machine_Gui_Widget_construct((Machine_Gui_Widget*)self, numberOfArguments, arguments);
  self->layoutModel = Machine_Gui_LayoutModel_create();
  self->children = Machine_Gui_WidgetList_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_GroupNode_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_GroupNode, Machine_Gui_Widget, &Machine_Gui_GroupNode_visit,
                         &Machine_Gui_GroupNode_construct, NULL,
                         &Machine_Gui_GroupNode_constructClass, NULL)

Machine_Gui_GroupNode* Machine_Gui_GroupNode_create(Machine_Gui_Context* context) {
  Machine_ClassType* ty = Machine_Gui_GroupNode_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context);
  Machine_Gui_GroupNode* self
      = (Machine_Gui_GroupNode*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Gui_LayoutModel const* Machine_Gui_GroupNode_getLayoutModel(
    Machine_Gui_GroupNode const* self) {
  return self->layoutModel;
}

void Machine_Gui_GroupNode_setLayoutModel(Machine_Gui_GroupNode* self,
                                          Machine_Gui_LayoutModel* layoutModel) {
  self->layoutModel = layoutModel;
}

void Machine_Gui_GroupNode_relayout(Machine_Gui_GroupNode* self, Ring2_Real32 canvasWidth,
                                    Ring2_Real32 canvasHeight) {
  // Set the size of all children to the same value: That value is the component-wise maxima vector
  // of the preferred sizes of all children.
  Ring3_Math_Vector2* preferredSize = Ring3_Math_Vector2_clone(
      Machine_Gui_Widget_getPreferredSize(Machine_Gui_WidgetList_getAt(self->children, 0)));
  for (size_t i = 1, n = Machine_Gui_WidgetList_getSize(self->children); i < n; ++i) {
    Ring3_Math_Vector2_maxima(preferredSize, preferredSize,
                              Machine_Gui_Widget_getPreferredSize(Machine_Gui_WidgetList_getAt(self->children, i)));
  }
  for (size_t i = 0, n = Machine_Gui_WidgetList_getSize(self->children); i < n; ++i) {
    Machine_Gui_Widget_setSize(Machine_Gui_WidgetList_getAt(self->children, i), preferredSize);
  }
  // Layout the children.
  Ring3_Math_Vector2 const* size = Machine_Gui_Widget_getSize((Machine_Gui_Widget*)self);
  Machine_Gui_WidgetList_layout(self->children, Ring3_Math_Vector2_getX(size),
                                                Ring3_Math_Vector2_getY(size),
                                                canvasWidth, canvasHeight,
                                                self->layoutModel);
}
