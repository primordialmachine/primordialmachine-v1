/// @file Input/MouseButtonEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "Input/MouseButtonEvent.h"

#include <string.h>

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_MouseButtonActions)

Machine_String* Machine_MouseButtonActions_toString(Machine_MouseButtonActions self) {
  switch (self) {
    case Machine_MouseButtonActions_Press:
      return Machine_String_create("press", strlen("press"));
      break;
    case Machine_MouseButtonActions_Release:
      return Machine_String_create("release", strlen("release"));
      break;
    case Machine_MouseButtonActions_Undetermined:
    default:
      MACHINE_ASSERT_UNREACHABLE();
  };
}

static void Machine_MouseButtonEvent_visit(Machine_MouseButtonEvent* self) {
  /*Intentionally empty.*/
}

static Machine_String* Machine_MouseButtonEvent_toStringImpl(Machine_MouseButtonEvent const* self) {
  Machine_StringBuffer* stringBuffer = Machine_StringBuffer_create();

  Machine_StringBuffer_appendBytes(stringBuffer, "{ ", strlen("{ "));

  Machine_StringBuffer_appendBytes(stringBuffer, "type: 'mouse-button-event'",
                                   strlen("type: 'mouse-button-event'"));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "action: '", strlen("action: '"));
  Machine_StringBuffer_appendString(stringBuffer,
                                    Machine_MouseButtonActions_toString(self->action));
  Machine_StringBuffer_appendBytes(stringBuffer, "', ", strlen("', "));

  Machine_StringBuffer_appendBytes(stringBuffer, "button: ", strlen("button: "));
  Machine_StringBuffer_appendString(stringBuffer, Machine_Integer_toString(self->button));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "x: ", strlen("x: "));
  Machine_StringBuffer_appendString(stringBuffer, Machine_Real_toString(self->x));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "y: ", strlen("y: "));
  Machine_StringBuffer_appendString(stringBuffer, Machine_Real_toString(self->y));

  Machine_StringBuffer_appendBytes(stringBuffer, " }", strlen(" }"));

  return Machine_Object_toString((Machine_Object*)stringBuffer);
}

static void Machine_MouseButtonEvent_constructClass(Machine_MouseButtonEvent_Class* self) {
  ((Machine_Object_Class*)self)->toString
      = (Machine_String * (*)(Machine_Object const*)) & Machine_MouseButtonEvent_toStringImpl;
}

static void Machine_MouseButtonEvent_construct(Machine_MouseButtonEvent* self,
                                               size_t numberOfArguments,
                                               Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->button = Machine_Value_getInteger(&arguments[0]);
  self->action = Machine_Value_getInteger(&arguments[1]);
  self->x = Machine_Value_getReal(&arguments[2]);
  self->y = Machine_Value_getReal(&arguments[3]);
  Machine_setClassType((Machine_Object*)self, Machine_MouseButtonEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_MouseButtonEvent, Machine_Object, &Machine_MouseButtonEvent_visit,
                         &Machine_MouseButtonEvent_construct, NULL,
                         &Machine_MouseButtonEvent_constructClass, NULL)

Machine_MouseButtonEvent* Machine_MouseButtonEvent_create(int button, int action, Machine_Real x,
                                                          Machine_Real y) {
  Machine_ClassType* ty = Machine_MouseButtonEvent_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 4;
  Machine_Value ARGUMENTS[4]
      = { Machine_Value_StaticInitializerVoid(), Machine_Value_StaticInitializerVoid(),
          Machine_Value_StaticInitializerVoid(), Machine_Value_StaticInitializerVoid() };
  Machine_Value_setInteger(&ARGUMENTS[0], button);
  Machine_Value_setInteger(&ARGUMENTS[1], action);
  Machine_Value_setReal(&ARGUMENTS[2], x);
  Machine_Value_setReal(&ARGUMENTS[3], y);
  Machine_MouseButtonEvent* self
      = (Machine_MouseButtonEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
