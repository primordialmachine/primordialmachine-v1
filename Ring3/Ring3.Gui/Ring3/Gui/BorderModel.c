/// @file Ring3/Gui/BorderModel.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GUI_PRIVATE (1)
#include "Ring3/Gui/BorderModel.h"
#undef RING3_GUI_PRIVATE


void
Machine_Gui_BorderModel_construct
  (
    Machine_Gui_BorderModel* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

static void
Machine_Gui_BorderModel_constructClass
  (
    Machine_Gui_BorderModel_Class* self
  );

static void
Machine_Gui_BorderModel_visit
  (
    Machine_Gui_BorderModel* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_BorderModel,
                         Machine_Object,
                         &Machine_Gui_BorderModel_visit,
                         &Machine_Gui_BorderModel_construct,
                         NULL,
                         &Machine_Gui_BorderModel_constructClass,
                         NULL)

void
Machine_Gui_BorderModel_construct
  (
    Machine_Gui_BorderModel* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->leftWidth = 1.f;
  self->rightWidth = 1.f;
  self->topWidth = 1.f;
  self->bottomWidth = 1.f;
  self->color = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(self->color, 0.1f, 0.1f, 0.1f, 1.f);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Machine_Gui_BorderModel_getType());
}

static void
Machine_Gui_BorderModel_constructClass
  (
    Machine_Gui_BorderModel_Class* self
  )
{/*Intentionally empty.*/}

static void
Machine_Gui_BorderModel_visit
  (
    Machine_Gui_BorderModel* self
  )
{
  if (self->color) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->color);
  }
}

Ring1_NoDiscardReturn() Machine_Gui_BorderModel*
Machine_Gui_BorderModel_create
  (
  )
{
  Machine_Type* ty = Machine_Gui_BorderModel_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gui_BorderModel* self = Ring1_cast(Machine_Gui_BorderModel*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Machine_Gui_BorderModel_getColor
  (
    Machine_Gui_BorderModel const* self
  )
{ return Ring3_Math_Vector4f32_clone(self->color); }

void
Machine_Gui_BorderModel_setColor
  (
    Machine_Gui_BorderModel* self,
    Ring3_Math_Vector4f32 const* color
  )
{
  Ring3_Math_Vector4f32_copy(self->color, color);
}

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getLeftWidth
  (
    Machine_Gui_BorderModel const* self
  )
{ return self->leftWidth; }

void
Machine_Gui_BorderModel_setLeftWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  )
{ self->leftWidth = width; }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getRightWidth
  (
    Machine_Gui_BorderModel const* self
  )
{ return self->rightWidth; }

void
Machine_Gui_BorderModel_setRightWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  )
{ self->rightWidth = width; }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getTopWidth
  (
    Machine_Gui_BorderModel const* self
  )
{ return self->topWidth; }

void
Machine_Gui_BorderModel_setTopWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  )
{ self->topWidth = width; }

Ring1_NoDiscardReturn() Ring2_Real32
Machine_Gui_BorderModel_getBottomWidth
  (
    Machine_Gui_BorderModel const* self
  )
{ return self->bottomWidth; }

void
Machine_Gui_BorderModel_setBottomWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  )
{ self->bottomWidth = width; }

void
Machine_Gui_BorderModel_setWidth
  (
    Machine_Gui_BorderModel* self,
    Ring2_Real32 width
  )
{
  Machine_Gui_BorderModel_setLeftWidth(self, width);
  Machine_Gui_BorderModel_setRightWidth(self, width);
  Machine_Gui_BorderModel_setTopWidth(self, width);
  Machine_Gui_BorderModel_setBottomWidth(self, width);
}
