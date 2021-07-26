/// @file GUI/BorderModel.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GUI/BorderModel.h"

static void Machine_GUI_BorderModel_visit(Machine_GUI_BorderModel* self) {
  if (self->color) {
    Machine_visit(self->color);
  }
}

static void Machine_GUI_BorderModel_constructClass(Machine_GUI_BorderModel_Class *self)
{/*Intentionally empty.*/}

void Machine_GUI_BorderModel_construct(Machine_GUI_BorderModel* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object *)self, numberOfArguments, arguments);
  self->leftWidth = 1.f;
  self->rightWidth = 1.f;
  self->topWidth = 1.f;
  self->bottomWidth = 1.f;
  self->color = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(self->color, 0.1f, 0.1f, 0.1f, 1.f);
  Machine_GUI_BorderModel_constructClass(self);
  Machine_setClassType((Machine_Object *)self, Machine_GUI_BorderModel_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_BorderModel, Machine_Object, &Machine_GUI_BorderModel_visit, &Machine_GUI_BorderModel_construct, NULL)

Machine_GUI_BorderModel* Machine_GUI_BorderModel_create() {
  Machine_ClassType* ty = Machine_GUI_BorderModel_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GUI_BorderModel* self = (Machine_GUI_BorderModel*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

const Machine_Math_Vector4* Machine_GUI_BorderModel_getColor(const Machine_GUI_BorderModel* self) {
  return self->color;
}

void Machine_GUI_BorderModel_setColor(Machine_GUI_BorderModel* self, const Machine_Math_Vector4* color) {
  Machine_Math_Vector4_copy(self->color, color);
}

Machine_Real Machine_GUI_BorderModel_getLeftWidth(const Machine_GUI_BorderModel* self) {
  return self->leftWidth;
}

void Machine_GUI_BorderModel_setLeftWidth(Machine_GUI_BorderModel* self, Machine_Real width) {
  self->leftWidth = width;
}

Machine_Real Machine_GUI_BorderModel_getRightWidth(const Machine_GUI_BorderModel* self) {
  return self->rightWidth;
}

void Machine_GUI_BorderModel_setRightWidth(Machine_GUI_BorderModel* self, Machine_Real width) {
  self->rightWidth = width;
}

Machine_Real Machine_GUI_BorderModel_getTopWidth(const Machine_GUI_BorderModel* self) {
  return self->topWidth;
}

void Machine_GUI_BorderModel_setTopWidth(Machine_GUI_BorderModel* self, Machine_Real width) {
  self->topWidth = width;
}

Machine_Real Machine_GUI_BorderModel_getBottomWidth(const Machine_GUI_BorderModel* self) {
  return self->bottomWidth;
}

void Machine_GUI_BorderModel_setBottomWidth(Machine_GUI_BorderModel* self, Machine_Real width) {
  self->bottomWidth = width;
}

void Machine_GUI_BorderModel_setWidth(Machine_GUI_BorderModel* self, Machine_Real width) {
  Machine_GUI_BorderModel_setLeftWidth(self, width);
  Machine_GUI_BorderModel_setRightWidth(self, width);
  Machine_GUI_BorderModel_setTopWidth(self, width);
  Machine_GUI_BorderModel_setBottomWidth(self, width);
}
