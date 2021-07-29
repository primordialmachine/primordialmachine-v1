#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "./../Graphics2/Shape2.h"



#include <string.h>



static void Machine_Shape2_visit(Machine_Shape2* self)
{/*Intentionally empty.*/}

static void Machine_Shape2_constructClass(Machine_Shape2_Class* self)
{/*Intentionally empty.*/}

void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_Shape2_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_Shape2_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Shape2, Machine_Object, &Machine_Shape2_visit, Machine_Shape2_construct, NULL)

void Machine_Shape2_render(Machine_Shape2* self, float width, float height) {
  if (!self || !self->render) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  self->render(self, width, height);
}
