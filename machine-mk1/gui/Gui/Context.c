/// @file Gui/Context.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/Context.h"

static void Machine_Gui_Context_visit(Machine_Gui_Context* self) {
  if (self->gdlContext) {
    Machine_Gc_visit(self->gdlContext);
  }
  if (self->signalsContext) {
    Machine_Gc_visit(self->signalsContext);
  }
  if (self->rootGroup) {
    Machine_Gc_visit(self->rootGroup);
  }
  if (self->context2) {
    Machine_Gc_visit(self->context2);
  }
}

static void Machine_Gui_Context_construct(Machine_Gui_Context* self, size_t numberOfArguments,
                                          Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->gdlContext = Machine_Gui_Gdl_Context_create(
      (Machine_GDL_Context*)Machine_Value_getObject(&arguments[0]));
  self->signalsContext = Machine_Gui_Signals_Context_create();
  self->context2 = (Machine_Context2*)Machine_Value_getObject(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Machine_Gui_Context_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_Context, Machine_Object, &Machine_Gui_Context_visit,
                         &Machine_Gui_Context_construct, NULL, NULL)

Machine_Gui_Context* Machine_Gui_Context_create(Machine_GDL_Context* gdlContext,
                                                Machine_Context2* context2) {
  Machine_ClassType* ty = Machine_Gui_Context_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)gdlContext);
  Machine_Value_setObject(&ARGUMENTS[1], (Machine_Object*)context2);
  Machine_Gui_Context* self
      = (Machine_Gui_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Gui_Context_onCanvasSizechanged(Machine_Gui_Context* self,
                                             Machine_CanvasSizeChangedEvent* event) {
  Machine_Context2_setTargetSize(self->context2, event->width, event->height);
}

Machine_Real Machine_Gui_Context_getCanvasWidth(Machine_Gui_Context* self) {
  return Machine_Context2_getTargetWidth(self->context2);
}

Machine_Real Machine_Gui_Context_getCanvasHeight(Machine_Gui_Context* self) {
  return Machine_Context2_getTargetHeight(self->context2);
}

void Machine_Gui_Context_setRootGroup(Machine_Gui_Context* self, Machine_Gui_GroupNode* rootGroup) {
  self->rootGroup = rootGroup;
}

Machine_Gui_GroupNode* Machine_Gui_Context_getRootGroup(Machine_Gui_Context const* self) {
  return self->rootGroup;
}

void Machine_Gui_Context_onRender(Machine_Gui_Context* self) {
  Machine_Real targetWidth = Machine_Context2_getTargetWidth(self->context2),
               targetHeight = Machine_Context2_getTargetHeight(self->context2);
  if (targetWidth > 0.f && targetHeight > 0.f && self->rootGroup) {
    Machine_Math_Vector2* canvasSize = Machine_Math_Vector2_create();
    Machine_Math_Vector2_set(canvasSize, targetWidth, targetHeight);
    Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->rootGroup, canvasSize);
    Machine_Gui_GroupNode_relayout(self->rootGroup, targetWidth, targetHeight);
  }
}
