/// @file GUI/Border.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GUI/Border.h"

struct Machine_GUI_Border {
  Machine_Math_Vector3* color;
  float width;
};

static void Machine_GUI_Border_visit(Machine_GUI_Border* self);

static void Machine_GUI_Border_construct(Machine_GUI_Border* self, size_t numberOfArguments, const Machine_Value* arguments);

MACHINE_DEFINE_CLASSTYPE(Machine_GUI_Border)

Machine_ClassType* Machine_GUI_Border_getClassType() {
  if (!g_Machine_GUI_Border_ClassType) {
    g_Machine_GUI_Border_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_GUI_Border),
          (Machine_ClassTypeRemovedCallback*)&Machine_GUI_Border_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)&Machine_GUI_Border_visit,
          (Machine_ClassObjectConstructCallback*)&Machine_GUI_Border_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_GUI_Border_ClassType;
}

static void Machine_GUI_Border_visit(Machine_GUI_Border* self) {
  if (self->color) {
    Machine_visit(self->color);
  }
}

static void Machine_GUI_Border_construct(Machine_GUI_Border* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->width = 1.f;
  self->color = Machine_Math_Vector3_create(0.1f, 0.1f, 0.1f);
}

Machine_GUI_Border* Machine_GUI_Border_create() {
  Machine_ClassType* ty = Machine_GUI_Border_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_GUI_Border* self = (Machine_GUI_Border*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

const Machine_Math_Vector3* Machine_GUI_Border_getBorderColor(Machine_GUI_Border* self) {
  return self->color;
}

void Machine_GUI_Border_setBorderColor(Machine_GUI_Border* self, Machine_Math_Vector3* color) {
  Machine_Math_Vector3_copy(self->color, color);
}

float Machine_GUI_Border_getBorderWidth(Machine_GUI_Border* self) {
  return self->width;
}

void Machine_GUI_Border_setBorderWidth(Machine_GUI_Border* self, float width) {
  self->width = width;
}
