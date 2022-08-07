#define MACHINE_SIGNALS_PRIVATE (1)
#include "Signals/Signal.h"



#include "Ring1/Status.h"
#include "Signals/Connection.h"



static void Machine_Signals_Signal_visit(Machine_Signals_Signal* self);

MACHINE_DEFINE_CLASSTYPE(Machine_Signals_Signal, Machine_Object, &Machine_Signals_Signal_visit,
                         &Machine_Signals_Signal_construct, NULL, NULL, NULL)

static void Machine_Signals_Signal_visit(Machine_Signals_Signal* self) {
  if (self->connections) {
    Machine_Gc_visit(self->connections);
  }
}

void Machine_Signals_Signal_construct(Machine_Signals_Signal* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  MACHINE_ASSERT(numberOfArguments == 0, Ring1_Status_InvalidNumberOfArguments);
  self->connections = (Machine_List *)Machine_ArrayList_create();
  Machine_setClassType((Machine_Object*)self, Machine_Signals_Signal_getType());
}

Machine_Signals_Signal* Machine_Signals_Signal_create() {
  Machine_ClassType* ty = Machine_Signals_Signal_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Signals_Signal* self = (Machine_Signals_Signal*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Signals_Signal_subscribe(Machine_Signals_Signal* self, Ring2_String* name, Machine_Object* context, Machine_ForeignProcedure* callback) {
  Machine_Signals_Connection* connection = Machine_Signals_Connection_create(name, context, callback);
  Machine_Value value;
  Machine_Value_setObject(&value, (Machine_Object*)connection);
  Machine_List_append(self->connections, value);
}

void Machine_Signals_Signal_unsubscribe(Machine_Signals_Signal* self, Ring2_String* name, Machine_Object* context, Machine_ForeignProcedure* callback) {
    for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)(self->connections)); i < n; ++i) {
      Machine_Value temporary = Machine_List_getAt(self->connections, i);
      Machine_Signals_Connection* c = (Machine_Signals_Connection*)Machine_Value_getObject(&temporary);
      if (Ring2_String_isEqualTo(Ring2_Context_get(), c->name, name) &&
          Machine_Object_isEqualTo(c->context, context) &&
          Machine_ForeignProcedure_isEqualTo(c->callback, callback)) {
        Machine_List_removeAtFast(self->connections, i);
        break;
      }
    }
}

void Machine_Signals_Signal_emit(Machine_Signals_Signal* self, Ring2_String* name, size_t numberOfArguments, Machine_Value const* arguments) {
  if (self->connections) {
    size_t numberOfArguments1
        = numberOfArguments + 1;
    Machine_Value* arguments1 = NULL;
    if (Ring1_Memory_allocateArray(&arguments1, numberOfArguments1, sizeof(Machine_Value))) {
      Ring2_jump();
    }
    for (size_t i = 0, n = numberOfArguments; i < n; ++i) {
      arguments1[i + 1] = arguments[i + 0];
    }
    Ring2_JumpTarget jt;
    Ring2_pushJumpTarget(&jt);
    if (!setjmp(jt.environment)) {
      for (size_t i = 0, n = Machine_Collection_getSize((Machine_Collection*)self->connections);
           i < n; ++i) {
        Machine_Value temporary = Machine_List_getAt(self->connections, i);
        Machine_Signals_Connection* c
            = (Machine_Signals_Connection*)Machine_Value_getObject(&temporary);
        if (Ring2_String_isEqualTo(Ring2_Context_get(), c->name, name)) {
          MACHINE_ASSERT_NOTNULL(c->callback);
          Machine_Value_setObject(&(arguments1[0]), c->context);
          c->callback(numberOfArguments1, arguments1);
        }
      }
      Ring2_popJumpTarget();
      Ring1_Memory_deallocate(arguments1);
    } else {
      Ring2_popJumpTarget();
      Ring1_Memory_deallocate(arguments1);
      Ring2_jump();
    }
  }
}
