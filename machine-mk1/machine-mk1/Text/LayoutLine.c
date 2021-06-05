#include "./../Text/LayoutLine.h"

void Machine_Text_LayoutLine_construct(Machine_Text_LayoutLine* self, size_t numberOfArguments, const Machine_Value* arguments);

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Text_LayoutLine, Machine_Object, NULL, &Machine_Text_LayoutLine_construct, NULL)

void Machine_Text_LayoutLine_construct(Machine_Text_LayoutLine* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->start = Machine_Value_getInteger(&arguments[0]);
  self->length = Machine_Value_getInteger(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Machine_Text_LayoutLine_getClassType());
}

Machine_Text_LayoutLine* Machine_Text_LayoutLine_create(int start, int length) {
  if (start < 0 || length < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  Machine_Value arguments[2];
  Machine_Value_setInteger(&arguments[0], start);
  Machine_Value_setInteger(&arguments[1], length);
  Machine_ClassType* ty = Machine_Text_LayoutLine_getClassType();
  Machine_Text_LayoutLine* self = (Machine_Text_LayoutLine *)Machine_allocateClassObject(ty, 2, arguments);
  return self;
}
