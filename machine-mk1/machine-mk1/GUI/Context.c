#include "./../GUI/Context.h"



#include "./../Video.h"



static void Machine_GUI_Context_visit(Machine_GUI_Context* self) {
  if (self->gdlContext) {
    Machine_visit(self->gdlContext);
  }
  if (self->signalsContext) {
    Machine_visit(self->signalsContext);
  }
  if (self->rootGroup) {
    Machine_visit(self->rootGroup);
  }
  if (self->context2) {
    Machine_visit(self->context2);
  }
}

static void Machine_GUI_Context_construct(Machine_GUI_Context* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->gdlContext = Machine_GUI_GDL_Context_create((Machine_GDL_Context*)Machine_Value_getObject(&arguments[0]));
  self->signalsContext = Machine_GUI_Signals_Context_create();
  self->context2 = (Machine_Context2*)Machine_Value_getObject(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Machine_GUI_Context_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_GUI_Context, Machine_Object, &Machine_GUI_Context_visit, &Machine_GUI_Context_construct, NULL)

Machine_GUI_Context* Machine_GUI_Context_create(Machine_GDL_Context* gdlContext, Machine_Context2* context2) {
  Machine_ClassType* ty = Machine_GUI_Context_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setObject(&ARGUMENTS[0], (Machine_Object*)gdlContext);
  Machine_Value_setObject(&ARGUMENTS[1], (Machine_Object*)context2);
  Machine_GUI_Context* self = (Machine_GUI_Context*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_GUI_Context_onCanvasSizechanged(Machine_GUI_Context* self, Machine_CanvasSizeChangedEvent* event) {
  Machine_Context2_setTargetSize(self->context2, event->width, event->height);
}

void Machine_GUI_Context_setRootGroup(Machine_GUI_Context* self, Machine_GUI_Group* rootGroup) {
  self->rootGroup = rootGroup;
}

Machine_GUI_Group* Machine_GUI_Context_getRootGroup(const Machine_GUI_Context* self) {
  return self->rootGroup;
}
