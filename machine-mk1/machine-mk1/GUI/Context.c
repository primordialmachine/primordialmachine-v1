#include "./../GUI/Context.h"


static void Machine_GUI_Context_visit(Machine_GUI_Context* self) {
  if (self->gdlContext) {
    Machine_visit(self->gdlContext);
  }
  if (self->signalsContext) {
    Machine_visit(self->signalsContext);
  }
}

static void Machine_GUI_Context_construct(Machine_GUI_Context* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->gdlContext = Machine_GUI_GDL_Context_create((Machine_GDL_Context*)Machine_Value_getObject(&arguments[0]));
  self->signalsContext = Machine_GUI_Signals_Context_create();
  Machine_setClassType((Machine_Object*)self, Machine_GUI_Context_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_Context, Machine_Object, &Machine_GUI_Context_visit, &Machine_GUI_Context_construct, NULL)

Machine_GUI_Context* Machine_GUI_Context_create(Machine_GDL_Context* context) {
  Machine_ClassType* ty = Machine_GUI_Context_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Machine_Value ARGUMENTS[1];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)context);
  Machine_GUI_Context* self = (Machine_GUI_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
