/// @file Gui/BorderModel.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/BorderModel.h"


#include "Ring1/Intrinsic.h"


static void Machine_Gui_BorderModel_visit(Machine_Gui_BorderModel* self) {
  if (self->color) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->color);
  }
}

static void Machine_Gui_BorderModel_constructClass(
    Machine_Gui_BorderModel_Class* self) { /*Intentionally empty.*/
}

void Machine_Gui_BorderModel_construct(Machine_Gui_BorderModel* self, size_t numberOfArguments,
                                       Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->leftWidth = 1.f;
  self->rightWidth = 1.f;
  self->topWidth = 1.f;
  self->bottomWidth = 1.f;
  self->color = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(self->color, 0.1f, 0.1f, 0.1f, 1.f);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_BorderModel_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_BorderModel, Machine_Object, &Machine_Gui_BorderModel_visit,
                         &Machine_Gui_BorderModel_construct, NULL,
                         &Machine_Gui_BorderModel_constructClass, NULL)

Machine_Gui_BorderModel* Machine_Gui_BorderModel_create() {
  Machine_ClassType* ty = Machine_Gui_BorderModel_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
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

Ring2_Real32 Machine_Gui_BorderModel_getLeftWidth(Machine_Gui_BorderModel const* self) {
  return self->leftWidth;
}

void Machine_Gui_BorderModel_setLeftWidth(Machine_Gui_BorderModel* self, Ring2_Real32 width) {
  self->leftWidth = width;
}

Ring2_Real32 Machine_Gui_BorderModel_getRightWidth(Machine_Gui_BorderModel const* self) {
  return self->rightWidth;
}

void Machine_Gui_BorderModel_setRightWidth(Machine_Gui_BorderModel* self, Ring2_Real32 width) {
  self->rightWidth = width;
}

Ring2_Real32 Machine_Gui_BorderModel_getTopWidth(Machine_Gui_BorderModel const* self) {
  return self->topWidth;
}

void Machine_Gui_BorderModel_setTopWidth(Machine_Gui_BorderModel* self, Ring2_Real32 width) {
  self->topWidth = width;
}

Ring2_Real32 Machine_Gui_BorderModel_getBottomWidth(Machine_Gui_BorderModel const* self) {
  return self->bottomWidth;
}

void Machine_Gui_BorderModel_setBottomWidth(Machine_Gui_BorderModel* self, Ring2_Real32 width) {
  self->bottomWidth = width;
}

void Machine_Gui_BorderModel_setWidth(Machine_Gui_BorderModel* self, Ring2_Real32 width) {
  Machine_Gui_BorderModel_setLeftWidth(self, width);
  Machine_Gui_BorderModel_setRightWidth(self, width);
  Machine_Gui_BorderModel_setTopWidth(self, width);
  Machine_Gui_BorderModel_setBottomWidth(self, width);
}
