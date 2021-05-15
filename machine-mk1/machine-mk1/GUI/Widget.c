/// @file GUI/Widget.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "./../GUI/Widget.h"




MACHINE_DEFINE_CLASSTYPE(Machine_GUI_Widget)

static void Machine_GUI_Widget_visit(Machine_GUI_Widget *self) {}

Machine_ClassType* Machine_GUI_Widget_getClassType() {
  if (!g_Machine_GUI_Widget_ClassType) {
    g_Machine_GUI_Widget_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_GUI_Widget),
          (Machine_ClassTypeRemovedCallback*)&Machine_GUI_Widget_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)&Machine_GUI_Widget_visit,
          (Machine_ClassObjectConstructCallback*)&Machine_GUI_Widget_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_GUI_Widget_ClassType;
}

void Machine_GUI_Widget_construct(Machine_GUI_Widget* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_setClassType(self, Machine_GUI_Widget_getClassType());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_render(Machine_GUI_Widget* self, float width, float height) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->render);
  self->render(self, width, height);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setPosition(Machine_GUI_Widget* self, const Machine_Math_Vector2* position) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->setPosition);
  MACHINE_ASSERT_NOTNULL(position);
  self->setPosition(self, position);
}

const Machine_Math_Vector2* Machine_GUI_Widget_getPosition(Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->getPosition);
  return self->getPosition(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setSize(Machine_GUI_Widget* self, const Machine_Math_Vector2* size) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->setSize);
  MACHINE_ASSERT_NOTNULL(size);
  self->setSize(self, size);
}

const Machine_Math_Vector2* Machine_GUI_Widget_getSize(Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  return self->getSize(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void Machine_GUI_Widget_setRectangle(Machine_GUI_Widget* self, const Machine_Math_Rectangle2* rectangle) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->setRectangle);
  MACHINE_ASSERT_NOTNULL(rectangle);
  self->setRectangle(self, rectangle);
}

const Machine_Math_Rectangle2* Machine_GUI_Widget_getRectangle(Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->getRectangle);
  return self->getRectangle(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

const Machine_Math_Vector2* Machine_GUI_Widget_getPreferredSize(Machine_GUI_Widget* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->getPreferredSize);
  return self->getPreferredSize(self);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/