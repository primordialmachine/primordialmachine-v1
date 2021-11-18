/// @file Gui/BorderModel.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/BorderModel.h"

static void Machine_Gui_BorderModel_visit(Machine_Gui_BorderModel* self) {
  if (self->color) {
    Machine_Gc_visit(self->color);
  }
}

static void Machine_Gui_BorderModel_constructClass(
    Machine_Gui_BorderModel_Class* self) { /*Intentionally empty.*/
}

void Machine_Gui_BorderModel_construct(Machine_Gui_BorderModel* self, size_t numberOfArguments,
                                       Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->leftWidth = 1.f;
  self->rightWidth = 1.f;
  self->topWidth = 1.f;
  self->bottomWidth = 1.f;
  self->color = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(self->color, 0.1f, 0.1f, 0.1f, 1.f);
  Machine_setClassType((Machine_Object*)self, Machine_Gui_BorderModel_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_BorderModel, Machine_Object, &Machine_Gui_BorderModel_visit,
                         &Machine_Gui_BorderModel_construct, NULL,
                         &Machine_Gui_BorderModel_constructClass)

Machine_Gui_BorderModel* Machine_Gui_BorderModel_create() {
  Machine_ClassType* ty = Machine_Gui_BorderModel_getClassType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Gui_BorderModel* self
      = (Machine_Gui_BorderModel*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Vector4 const* Machine_Gui_BorderModel_getColor(Machine_Gui_BorderModel const* self) {
  return self->color;
}

void Machine_Gui_BorderModel_setColor(Machine_Gui_BorderModel* self,
                                      Machine_Math_Vector4 const* color) {
  Machine_Math_Vector4_copy(self->color, color);
}

Machine_Real Machine_Gui_BorderModel_getLeftWidth(Machine_Gui_BorderModel const* self) {
  return self->leftWidth;
}

void Machine_Gui_BorderModel_setLeftWidth(Machine_Gui_BorderModel* self, Machine_Real width) {
  self->leftWidth = width;
}

Machine_Real Machine_Gui_BorderModel_getRightWidth(Machine_Gui_BorderModel const* self) {
  return self->rightWidth;
}

void Machine_Gui_BorderModel_setRightWidth(Machine_Gui_BorderModel* self, Machine_Real width) {
  self->rightWidth = width;
}

Machine_Real Machine_Gui_BorderModel_getTopWidth(Machine_Gui_BorderModel const* self) {
  return self->topWidth;
}

void Machine_Gui_BorderModel_setTopWidth(Machine_Gui_BorderModel* self, Machine_Real width) {
  self->topWidth = width;
}

Machine_Real Machine_Gui_BorderModel_getBottomWidth(Machine_Gui_BorderModel const* self) {
  return self->bottomWidth;
}

void Machine_Gui_BorderModel_setBottomWidth(Machine_Gui_BorderModel* self, Machine_Real width) {
  self->bottomWidth = width;
}

void Machine_Gui_BorderModel_setWidth(Machine_Gui_BorderModel* self, Machine_Real width) {
  Machine_Gui_BorderModel_setLeftWidth(self, width);
  Machine_Gui_BorderModel_setRightWidth(self, width);
  Machine_Gui_BorderModel_setTopWidth(self, width);
  Machine_Gui_BorderModel_setBottomWidth(self, width);
}
