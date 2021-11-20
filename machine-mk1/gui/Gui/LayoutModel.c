/// @file Gui/LayoutModel.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/LayoutModel.h"

static void Machine_Gui_LayoutModel_visit(Machine_Gui_LayoutModel* self) { /*Intentionally empty.*/
}

void Machine_Gui_LayoutModel_construct(Machine_Gui_LayoutModel* self, size_t numberOfArguments,
                                       Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->primaryDirection = Machine_Gui_Layout_Direction_Column;
  self->primaryJustification = Machine_Gui_Layout_Justification_Start;
  self->primaryInterChildSpacing = 0.f;
  Machine_setClassType((Machine_Object*)self, Machine_Gui_LayoutModel_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_LayoutModel, Machine_Object, &Machine_Gui_LayoutModel_visit,
                         &Machine_Gui_LayoutModel_construct, NULL, NULL)

Machine_Gui_LayoutModel* Machine_Gui_LayoutModel_create() {
  Machine_ClassType* ty = Machine_Gui_LayoutModel_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Gui_LayoutModel* self
      = (Machine_Gui_LayoutModel*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Gui_Layout_Direction Machine_Gui_LayoutModel_getPrimaryDirection(
    Machine_Gui_LayoutModel const* self) {
  return self->primaryDirection;
}

void Machine_Gui_LayoutModel_setPrimaryDirection(Machine_Gui_LayoutModel* self,
                                                 Machine_Gui_Layout_Direction primaryDirection) {
  self->primaryDirection = primaryDirection;
}

Machine_Gui_Layout_Justification Machine_Gui_LayoutModel_getPrimaryJustification(
    Machine_Gui_LayoutModel const* self) {
  return self->primaryJustification;
}

void Machine_Gui_LayoutModel_setPrimaryJustification(
    Machine_Gui_LayoutModel* self, Machine_Gui_Layout_Justification primaryJustifcation) {
  self->primaryJustification = primaryJustifcation;
}

Machine_Real Machine_Gui_LayoutModel_getPrimaryInterChildSpacing(
    Machine_Gui_LayoutModel const* self) {
  return self->primaryInterChildSpacing;
}

void Machine_Gui_LayoutModel_setPrimaryInterChildspacing(Machine_Gui_LayoutModel* self,
                                                         Machine_Real primaryInterChildSpacing) {
  self->primaryInterChildSpacing = primaryInterChildSpacing;
}
