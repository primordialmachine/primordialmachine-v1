/// @file Input/KeyboardKeyEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved
#define MACHINE_INPUT_PRIVATE (1)
#include "Input/KeyboardKeyEvent.h"

#include <string.h>

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_KeyboardKeyActions)

Ring2_String* Machine_KeyboardKeyActions_toString(Machine_KeyboardKeyActions self) {
  switch (self) {
    case Machine_KeyboardKeyActions_Press:
      return Ring2_String_create(Ring2_Context_get(), "press", strlen("press"));
      break;
    case Machine_KeyboardKeyActions_Release:
      return Ring2_String_create(Ring2_Context_get(), "release", strlen("release"));
      break;
    case Machine_KeyboardKeyActions_Repeat:
      return Ring2_String_create(Ring2_Context_get(), "repeat", strlen("repeat"));
      break;
    case Machine_KeyboardKeyActions_Undetermined:
    default:
      Ring2_unreachable();
  };
}

static void Machine_KeyboardKeyEvent_visit(
    Machine_KeyboardKeyEvent* self) { /*Intentionally empty.*/
}

static Ring2_String* Machine_KeyboardKeyEvent_toStringImpl(Machine_KeyboardKeyEvent const* self) {
  Machine_StringBuffer* stringBuffer = Machine_StringBuffer_create();

  Machine_StringBuffer_appendBytes(stringBuffer, "{ ", strlen("{ "));

  Machine_StringBuffer_appendBytes(stringBuffer, "type: 'keyboard-key-event'",
                                   strlen("type: 'keyboard-key-event'"));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "keyAction: '", strlen("keyAction: '"));
  Machine_StringBuffer_appendString(stringBuffer,
                                    Machine_KeyboardKeyActions_toString(self->action));
  Machine_StringBuffer_appendBytes(stringBuffer, "', ", strlen("', "));

  Machine_StringBuffer_appendBytes(stringBuffer, "key: '", strlen("key: '"));
  Machine_StringBuffer_appendString(stringBuffer, Machine_KeyboardKeys_toString(self->key));
  Machine_StringBuffer_appendBytes(stringBuffer, "'", strlen("'"));

  Machine_StringBuffer_appendBytes(stringBuffer, " }", strlen(" }"));

  return Machine_Object_toString(Ring2_Context_get(), (Machine_Object*)stringBuffer);
}

static void Machine_KeyboardKeyEvent_constructClass(Machine_KeyboardKeyEvent_Class* self) {
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Machine_Object const*)) & Machine_KeyboardKeyEvent_toStringImpl;
}

static void Machine_KeyboardKeyEvent_construct(Machine_KeyboardKeyEvent* self,
                                               size_t numberOfArguments,
                                               Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->key = Machine_Value_getInteger(&arguments[0]);
  self->action = Machine_Value_getInteger(&arguments[1]);
  Machine_setClassType((Machine_Object*)self, Machine_KeyboardKeyEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_KeyboardKeyEvent, Machine_Object, &Machine_KeyboardKeyEvent_visit,
                         &Machine_KeyboardKeyEvent_construct, NULL,
                         &Machine_KeyboardKeyEvent_constructClass, NULL)

Machine_KeyboardKeyEvent* Machine_KeyboardKeyEvent_create(Machine_KeyboardKeys key,
                                                          Machine_KeyboardKeyActions keyAction) {
  Machine_ClassType* ty = Machine_KeyboardKeyEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2]
      = { Machine_Value_StaticInitializerVoid(), Machine_Value_StaticInitializerVoid() };
  Machine_Value_setInteger(&ARGUMENTS[0], key);
  Machine_Value_setInteger(&ARGUMENTS[1], keyAction);
  Machine_KeyboardKeyEvent* self
      = (Machine_KeyboardKeyEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
