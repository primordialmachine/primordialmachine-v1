#include "./../GUI/WidgetList.h"

struct Machine_GUI_WidgetList {
  Machine_PointerArray* backing;
};

static void Machine_GUI_WidgetList_visit(Machine_GUI_WidgetList* self) {
  if (self->backing) {
    Machine_visit(self->backing);
  }
}

void Machine_GUI_WidgetList_construct(Machine_GUI_WidgetList* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->backing = Machine_PointerArray_create();
  Machine_setClassType(self, Machine_GUI_WidgetList_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_GUI_WidgetList)

Machine_ClassType* Machine_GUI_WidgetList_getClassType() {
  if (!g_Machine_GUI_WidgetList_ClassType) {
    g_Machine_GUI_WidgetList_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_GUI_WidgetList),
          (Machine_ClassTypeRemovedCallback*)&Machine_GUI_WidgetList_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)&Machine_GUI_WidgetList_visit,
          (Machine_ClassObjectConstructCallback*)&Machine_GUI_WidgetList_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_GUI_WidgetList_ClassType;
}

Machine_GUI_WidgetList* Machine_GUI_WidgetList_create() {
  Machine_ClassType* ty = Machine_GUI_WidgetList_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
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
