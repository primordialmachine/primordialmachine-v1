#define MACHINE_TEXT_PRIVATE (1)
#include "Text/LayoutLine.h"


#include "Ring1/Intrinsic.h"


void Machine_Text_LayoutLine_construct(Machine_Text_LayoutLine* self, size_t numberOfArguments, const Ring2_Value* arguments);

MACHINE_DEFINE_CLASSTYPE(Machine_Text_LayoutLine, Machine_Object, NULL,
                         &Machine_Text_LayoutLine_construct, NULL, NULL, NULL)

void Machine_Text_LayoutLine_construct(Machine_Text_LayoutLine* self, size_t numberOfArguments, const Ring2_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->start = Ring2_Value_getInteger(&arguments[0]);
  self->length = Ring2_Value_getInteger(&arguments[1]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Text_LayoutLine_getType());
}

Machine_Text_LayoutLine* Machine_Text_LayoutLine_create(Ring2_Integer start, Ring2_Integer length) {
  if (start < 0 || length < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring2_Value arguments[2] = { Ring2_Value_StaticInitializerVoid(), Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&arguments[0], start);
  Ring2_Value_setInteger(&arguments[1], length);
  Machine_ClassType* ty = Machine_Text_LayoutLine_getType();
  Machine_Text_LayoutLine* self = (Machine_Text_LayoutLine *)Machine_allocateClassObject(ty, 2, arguments);
  return self;
}
