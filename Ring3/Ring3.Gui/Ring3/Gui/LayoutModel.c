/// @file Ring3/Gui/LayoutModel.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/LayoutModel.h"
#undef RING3_GUI_PRIVATE


MACHINE_DEFINE_ENUMERATIONTYPE(Machine_Gui_Layout_Justification)

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_Gui_Layout_Direction)

static void
Machine_Gui_LayoutModel_visit
  (
    Machine_Gui_LayoutModel* self
  )
{/*Intentionally empty.*/}

void
Machine_Gui_LayoutModel_construct
  (
    Machine_Gui_LayoutModel* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->primaryDirection = Machine_Gui_Layout_Direction_Column;
  self->primaryJustification = Machine_Gui_Layout_Justification_Start;
  self->primaryInterChildSpacing = 0.f;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gui_LayoutModel_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_LayoutModel,
                         Machine_Object,
                         &Machine_Gui_LayoutModel_visit,
                         &Machine_Gui_LayoutModel_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Machine_Gui_LayoutModel*
Machine_Gui_LayoutModel_create
  (
  )
{
  Machine_ClassType* ty = Machine_Gui_LayoutModel_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Gui_LayoutModel* self = (Machine_Gui_LayoutModel*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_NoDiscardReturn() Machine_Gui_Layout_Direction
Machine_Gui_LayoutModel_getPrimaryDirection
  (
    Machine_Gui_LayoutModel const* self
  )
{ return self->primaryDirection; }

void
Machine_Gui_LayoutModel_setPrimaryDirection
  (
    Machine_Gui_LayoutModel* self,
    Machine_Gui_Layout_Direction primaryDirection
  )
{ self->primaryDirection = primaryDirection; }

Ring1_NoDiscardReturn() Machine_Gui_Layout_Justification
Machine_Gui_LayoutModel_getPrimaryJustification
  (
    Machine_Gui_LayoutModel const* self
  )
{ return self->primaryJustification; }

void
Machine_Gui_LayoutModel_setPrimaryJustification
  (
    Machine_Gui_LayoutModel* self,
    Machine_Gui_Layout_Justification primaryJustifcation
  )
{ self->primaryJustification = primaryJustifcation; }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_LayoutModel_getPrimaryInterChildSpacing
  (
    Machine_Gui_LayoutModel const* self
  )
{ return self->primaryInterChildSpacing; }

void
Machine_Gui_LayoutModel_setPrimaryInterChildspacing
  (
    Machine_Gui_LayoutModel* self,
    Ring2_Real32 primaryInterChildSpacing
  )
{ self->primaryInterChildSpacing = primaryInterChildSpacing; }
