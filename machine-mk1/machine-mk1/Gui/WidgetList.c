/// @file Gui/WidgetList.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#include "Gui/WidgetList.h"

struct Machine_Gui_WidgetList_Class {
  Machine_Object_Class __parent;
};

struct Machine_Gui_WidgetList {
  Machine_Object __parent;

  Machine_PointerArray* backing;
};

static void Machine_Gui_WidgetList_visit(Machine_Gui_WidgetList* self) {
  if (self->backing) {
    Machine_Gc_visit(self->backing);
  }
}

static void Machine_Gui_WidgetList_constructClass(Machine_Gui_WidgetList_Class* self)
{/*Intentionally empty.*/}

void Machine_Gui_WidgetList_construct(Machine_Gui_WidgetList* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->backing = Machine_PointerArray_create();
  Machine_setClassType((Machine_Object *)self, Machine_Gui_WidgetList_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gui_WidgetList, Machine_Object, &Machine_Gui_WidgetList_visit, &Machine_Gui_WidgetList_construct, NULL, &Machine_Gui_WidgetList_constructClass)

Machine_Gui_WidgetList* Machine_Gui_WidgetList_create() {
  Machine_ClassType* ty = Machine_Gui_WidgetList_getClassType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Gui_WidgetList* self = (Machine_Gui_WidgetList*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

size_t Machine_Gui_WidgetList_getSize(Machine_Gui_WidgetList* self) {
  return Machine_PointerArray_getSize(self->backing);
}

Machine_GUI_Widget* Machine_Gui_WidgetList_getAt(Machine_Gui_WidgetList* self, size_t index) {
  return (Machine_GUI_Widget *)Machine_PointerArray_getAt(self->backing, index);
}

void Machine_Gui_WidgetList_append(Machine_Gui_WidgetList* self, Machine_GUI_Widget* widget) {
  Machine_PointerArray_append(self->backing, widget);
}
