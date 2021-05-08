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

#define MACHINE_ASSERT_NOTNULL(e) \
  if (!(e)) \
  { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "e == NULL\n"); \
  }

void Machine_GUI_Widget_render(Machine_GUI_Widget* self, float width, float height) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->render);
  self->render(self, width, height);
}
