#include "./../GUI/WidgetList.h"

struct Machine_GUI_WidgetList {
  Machine_Object parent;
  Machine_PointerArray* backing;
};

static void Machine_GUI_WidgetList_visit(Machine_GUI_WidgetList* self) {
  if (self->backing) {
    Machine_visit(self->backing);
  }
}

static void Machine_GUI_WidgetList_constructClass(Machine_GUI_WidgetList* self)
{/*Intentionally empty.*/}

void Machine_GUI_WidgetList_construct(Machine_GUI_WidgetList* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->backing = Machine_PointerArray_create();
  Machine_GUI_WidgetList_constructClass(self);
  Machine_setClassType((Machine_Object *)self, Machine_GUI_WidgetList_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_WidgetList, Machine_Object, &Machine_GUI_WidgetList_visit, &Machine_GUI_WidgetList_construct, NULL)

Machine_GUI_WidgetList* Machine_GUI_WidgetList_create() {
  Machine_ClassType* ty = Machine_GUI_WidgetList_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_GUI_WidgetList* self = (Machine_GUI_WidgetList*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

size_t Machine_GUI_WidgetList_getSize(Machine_GUI_WidgetList* self) {
  return Machine_PointerArray_getSize(self->backing);
}

Machine_GUI_Widget* Machine_GUI_WidgetList_getAt(Machine_GUI_WidgetList* self, size_t index) {
  return (Machine_GUI_Widget *)Machine_PointerArray_getAt(self->backing, index);
}

void Machine_GUI_WidgetList_append(Machine_GUI_WidgetList* self, Machine_GUI_Widget* widget) {
  Machine_PointerArray_append(self->backing, widget);
}
