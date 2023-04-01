/// @file Ring3/Signals/Connection.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_SIGNALS_PRIVATE (1)
#include "Ring3/Signals/Signal.h"

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include "Ring3/Signals/Connection.h"

static void
Machine_Signals_Signal_visit
  (
    Machine_Signals_Signal* self
  );

MACHINE_DEFINE_CLASSTYPE(Machine_Signals_Signal,
                         Machine_Object,
                         &Machine_Signals_Signal_visit,
                         &Machine_Signals_Signal_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Machine_Signals_Signal_visit
  (
    Machine_Signals_Signal* self
  )
{
  if (self->connections) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->connections);
  }
}

void
Machine_Signals_Signal_construct
  (
    Machine_Signals_Signal* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  Ring2_assert(numberOfArguments == 0, Ring1_Status_InvalidNumberOfArguments);
  self->connections = (Ring2_Collections_List *)Ring2_Collections_ArrayList_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Signals_Signal_getType());
}

Ring1_CheckReturn() Machine_Signals_Signal*
Machine_Signals_Signal_create
  (
  )
{
  Machine_Type* ty = Machine_Signals_Signal_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Signals_Signal* self = (Machine_Signals_Signal*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void
Machine_Signals_Signal_subscribe
  (
    Machine_Signals_Signal* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Machine_Signals_Connection* connection = Machine_Signals_Connection_create(name, context, callback);
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)connection);
  Ring2_Collections_List_append(self->connections, value);
}

void
Machine_Signals_Signal_unsubscribe
  (
    Machine_Signals_Signal* self,
    Ring2_String* name,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Ring2_Value contextValue;
  Ring2_Value_setObject(&contextValue, (Machine_Object *)context);
  for (int64_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)(self->connections)); i < n; ++i) {
    Ring2_Value temporary = Ring2_Collections_List_getAt(self->connections, i);
    Machine_Signals_Connection* c = (Machine_Signals_Connection*)Ring2_Value_getObject(&temporary);
    if (Ring2_String_isEqualTo(Ring2_Context_get(), c->name, name) &&
        Machine_Object_isEqualTo(Ring2_Context_get(), c->context, &contextValue) &&
        Ring2_ForeignProcedure_isEqualTo(Ring2_Context_get(), c->callback, callback)) {
      Ring2_Collections_List_removeAtFast(self->connections, i);
      break;
    }
  }
}

void
Machine_Signals_Signal_emit
  (
    Machine_Signals_Signal* self,
    Ring2_String* name,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  if (self->connections) {
    size_t numberOfArguments1
        = numberOfArguments + 1;
    Ring2_Value* arguments1 = NULL;
    if (Ring1_Memory_allocateArray(&arguments1, numberOfArguments1, sizeof(Ring2_Value))) {
      Ring2_jump();
    }
    for (size_t i = 0, n = numberOfArguments; i < n; ++i) {
      arguments1[i + 1] = arguments[i + 0];
    }
    Ring2_JumpTarget jt;
    Ring2_pushJumpTarget(&jt);
    if (!setjmp(jt.environment)) {
      for (size_t i = 0, n = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->connections);
           i < n; ++i) {
        Ring2_Value temporary = Ring2_Collections_List_getAt(self->connections, i);
        Machine_Signals_Connection* c
            = (Machine_Signals_Connection*)Ring2_Value_getObject(&temporary);
        if (Ring2_String_isEqualTo(Ring2_Context_get(), c->name, name)) {
          Ring2_assertNotNull(c->callback);
          Ring2_Value_setObject(&(arguments1[0]), (Machine_Object *)c->context);
          Ring2_Value result = { Ring2_Value_Tag_Void, Ring2_Void_Void };
          c->callback(Ring2_Context_get(), &result, numberOfArguments1, arguments1);
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
