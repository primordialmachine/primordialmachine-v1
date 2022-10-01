/// @file Gui/WidgetList.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GUI_PRIVATE (1)
#include "Gui/WidgetList.h"

struct Machine_Gui_WidgetList_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gui_WidgetList {
  Machine_Object __parent;

  Machine_ArrayList* backing;
};

static void Machine_Gui_WidgetList_visit(Machine_Gui_WidgetList* self) {
  if (self->backing) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->backing);
  }
}

static void Machine_Gui_WidgetList_constructClass(
    Machine_Gui_WidgetList_Class* self) { /*Intentionally empty.*/
}

void Machine_Gui_WidgetList_construct(Machine_Gui_WidgetList* self, size_t numberOfArguments,
                                      Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->backing = Machine_ArrayList_create();
  Machine_setClassType((Machine_Object*)self, Machine_Gui_WidgetList_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_WidgetList, Machine_Object, &Machine_Gui_WidgetList_visit,
                         &Machine_Gui_WidgetList_construct, NULL,
                         &Machine_Gui_WidgetList_constructClass, NULL)

Machine_Gui_WidgetList* Machine_Gui_WidgetList_create() {
  Machine_ClassType* ty = Machine_Gui_WidgetList_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gui_WidgetList* self
      = (Machine_Gui_WidgetList*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

size_t Machine_Gui_WidgetList_getSize(Machine_Gui_WidgetList* self) {
  return Machine_Collection_getSize(Ring1_cast(Machine_Collection *, self->backing));
}

Machine_Gui_Widget* Machine_Gui_WidgetList_getAt(Machine_Gui_WidgetList* self, size_t index) {
  Ring2_Value t;
  t = Machine_List_getAt(Ring1_cast(Machine_List*, self->backing), index);
  return Ring1_cast(Machine_Gui_Widget *, Ring2_Value_getObject(&t));
}

void Machine_Gui_WidgetList_append(Machine_Gui_WidgetList* self, Machine_Gui_Widget* widget) {
  Ring2_Value t;
  Ring2_Value_setObject(&t, Ring1_cast(Machine_Object *, widget));
  Machine_List_append(Ring1_cast(Machine_List *, self->backing), t);
}
