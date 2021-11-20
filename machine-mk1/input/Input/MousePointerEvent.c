/// @file Input/MousePointerEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "./../Input/MousePointerEvent.h"



#include <string.h>



static void Machine_MousePointerEvent_visit(Machine_MousePointerEvent* self)
{/*Intentionally empty.*/}

static Machine_String* Machine_MousePointerEvent_toStringImpl(Machine_MousePointerEvent const* self) {
  Machine_StringBuffer* stringBuffer = Machine_StringBuffer_create();

  Machine_StringBuffer_appendBytes(stringBuffer, "{ ", strlen("{ "));

  Machine_StringBuffer_appendBytes(stringBuffer, "type: 'mouse-pointer-event'", strlen("type: 'mouse-pointer-event'"));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "x: ", strlen("x: "));
  Machine_StringBuffer_appendString(stringBuffer, Machine_Real_toString(self->x));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "y: ", strlen("y: "));
  Machine_StringBuffer_appendString(stringBuffer, Machine_Real_toString(self->y));

  Machine_StringBuffer_appendBytes(stringBuffer, " }", strlen(" }"));

  return Machine_Object_toString((Machine_Object *)stringBuffer);
}

static void Machine_MousePointerEvent_constructClass(Machine_MousePointerEvent_Class* self) {
  ((Machine_Object_Class*)self)->toString = (Machine_String * (*)(Machine_Object const*)) & Machine_MousePointerEvent_toStringImpl;
}

static void Machine_MousePointerEvent_construct(Machine_MousePointerEvent* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->x = Machine_Value_getReal(&arguments[0]);
  self->y = Machine_Value_getReal(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Machine_MousePointerEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_MousePointerEvent, Machine_Object, &Machine_MousePointerEvent_visit, &Machine_MousePointerEvent_construct, NULL, &Machine_MousePointerEvent_constructClass)

Machine_MousePointerEvent* Machine_MousePointerEvent_create(Machine_Real x, Machine_Real y) {
  Machine_ClassType* ty = Machine_MousePointerEvent_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2] = { Machine_Value_StaticInitializerVoid(), Machine_Value_StaticInitializerVoid() };
  Machine_Value_setReal(&ARGUMENTS[0], x);
  Machine_Value_setReal(&ARGUMENTS[1], y);
  Machine_MousePointerEvent* self = (Machine_MousePointerEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
