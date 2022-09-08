#define MACHINE_SIGNALS_PRIVATE (1)
#include "Signals/Connection.h"

static void Machine_Signals_Connection_visit(Machine_Signals_Connection* self);

MACHINE_DEFINE_CLASSTYPE(Machine_Signals_Connection, Machine_Object,
                         &Machine_Signals_Connection_visit, &Machine_Signals_Connection_construct,
                         NULL, NULL, NULL)

static void Machine_Signals_Connection_visit(Machine_Signals_Connection* self) {
  if (self->context) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->context);
  }
  if (self->name) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->name);
  }
}

void Machine_Signals_Connection_construct(Machine_Signals_Connection* self, size_t numberOfArguments, const Ring2_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Ring2_assert(numberOfArguments == 3, Ring1_Status_InvalidNumberOfArguments);
  self->name = (Ring2_String*)Ring2_Value_getString(&arguments[0]);
  self->context = (Machine_Object*)Ring2_Value_getObject(&arguments[1]);
  self->callback = (Ring2_ForeignProcedure*)Ring2_Value_getForeignProcedure(&arguments[2]);
  Machine_setClassType((Machine_Object*)self, Machine_Signals_Connection_getType());
}

Machine_Signals_Connection* Machine_Signals_Connection_create(Ring2_String* name, Machine_Object* context, Ring2_ForeignProcedure* callback) {
  Machine_ClassType* ty = Machine_Signals_Connection_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3];
  Ring2_Value_setString(&ARGUMENTS[0], name);
  Ring2_Value_setObject(&ARGUMENTS[1], context);
  Ring2_Value_setForeignProcedure(&ARGUMENTS[2], callback);
  Machine_Signals_Connection* self = (Machine_Signals_Connection*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
