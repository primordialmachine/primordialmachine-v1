/// @file Input/KeyboardKeyEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved
#define MACHINE_INPUT_PRIVATE (1)
#include "./../Input/KeyboardKeyEvent.h"

#include <string.h>

Machine_String* Machine_KeyboardKeyActions_toString(Machine_KeyboardKeyActions self) {
  switch (self) {
  case Machine_KeyboardKeyActions_Press:
    return Machine_String_create("press", strlen("press"));
    break;
  case Machine_KeyboardKeyActions_Release:
    return Machine_String_create("release", strlen("release"));
    break;
  case Machine_KeyboardKeyActions_Repeat:
    return Machine_String_create("repeat", strlen("repeat"));
    break;
  case Machine_KeyboardKeyActions_Undetermined:
  default:
    MACHINE_ASSERT_UNREACHABLE();
  };
}

static void Machine_KeyboardKeyEvent_visit(Machine_KeyboardKeyEvent* self) {
  /*Intentionally empty.*/
}

static Machine_String* Machine_KeyboardKeyEvent_toStringImpl(Machine_KeyboardKeyEvent const* self) {
  Machine_StringBuffer* stringBuffer = Machine_StringBuffer_create();

  Machine_StringBuffer_appendBytes(stringBuffer, "{ ", strlen("{ "));

  Machine_StringBuffer_appendBytes(stringBuffer, "type: 'keyboard-key-event'", strlen("type: 'keyboard-key-event'"));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "keyAction: '", strlen("keyAction: '"));
  Machine_StringBuffer_appendString(stringBuffer, Machine_KeyboardKeyActions_toString(self->keyAction));
  Machine_StringBuffer_appendBytes(stringBuffer, "', ", strlen("', "));

  Machine_StringBuffer_appendBytes(stringBuffer, "key: '", strlen("key: '"));
  Machine_StringBuffer_appendString(stringBuffer, Machine_KeyboardKeys_toString(self->key));
  Machine_StringBuffer_appendBytes(stringBuffer, "'", strlen("'"));

  Machine_StringBuffer_appendBytes(stringBuffer, " }", strlen(" }"));

  return Machine_Object_toString((Machine_Object *)stringBuffer);
}

static void Machine_KeyboardKeyEvent_construct(Machine_KeyboardKeyEvent* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->key = Machine_Value_getInteger(&arguments[0]);
  self->keyAction = Machine_Value_getInteger(&arguments[1]);
  ((Machine_Object*)self)->toString = (Machine_String * (*)(Machine_Object const*)) & Machine_KeyboardKeyEvent_toStringImpl;
  Machine_setClassType((Machine_Object*)self, Machine_KeyboardKeyEvent_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_KeyboardKeyEvent, Machine_Object, &Machine_KeyboardKeyEvent_visit, &Machine_KeyboardKeyEvent_construct, NULL)

Machine_KeyboardKeyEvent* Machine_KeyboardKeyEvent_create(Machine_KeyboardKeys key, Machine_KeyboardKeyActions keyAction) {
  Machine_ClassType* ty = Machine_KeyboardKeyEvent_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Machine_Value ARGUMENTS[2];
  Machine_Value_setInteger(&ARGUMENTS[0], key);
  Machine_Value_setInteger(&ARGUMENTS[1], keyAction);
  Machine_KeyboardKeyEvent* self = (Machine_KeyboardKeyEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}