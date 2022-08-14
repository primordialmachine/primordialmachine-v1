/// @file Input/MousePointerEvent.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_INPUT_PRIVATE (1)
#include "Input/MousePointerEvent.h"

#include <string.h>

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_MousePointerActions)

Ring2_String* Machine_MousePointerActions_toString(Machine_MousePointerActions self) {
  switch (self) {
    case Machine_MousePointerActions_Move:
      return Ring2_String_create(Ring2_Context_get(), "move", strlen("move"));
      break;
    case Machine_MousePointerActions_Enter:
      return Ring2_String_create(Ring2_Context_get(), "enter", strlen("enter"));
      break;
    case Machine_MousePointerActions_Exit:
      return Ring2_String_create(Ring2_Context_get(), "exit", strlen("exit"));
      break;
    case Machine_MousePointerActions_Undetermined:
    default:
      Ring2_unreachable();
  };
}

static void Machine_MousePointerEvent_visit(
    Machine_MousePointerEvent* self) { /*Intentionally empty.*/
}

static Ring2_String* Machine_MousePointerEvent_toStringImpl(
    Machine_MousePointerEvent const* self) {
  Machine_StringBuffer* stringBuffer = Machine_StringBuffer_create();

  Machine_StringBuffer_appendBytes(stringBuffer, "{ ", strlen("{ "));

  Machine_StringBuffer_appendBytes(stringBuffer, "type: 'mouse-pointer-event'",
                                   strlen("type: 'mouse-pointer-event'"));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "action: '", strlen("action: '"));
  Machine_StringBuffer_appendString(stringBuffer,
                                    Machine_MousePointerActions_toString(self->action));
  Machine_StringBuffer_appendBytes(stringBuffer, "', ", strlen("', "));

  Machine_StringBuffer_appendBytes(stringBuffer, "x: ", strlen("x: "));
  Machine_StringBuffer_appendString(stringBuffer, Ring2_Real32_toString(Ring2_Context_get(), self->x));
  Machine_StringBuffer_appendBytes(stringBuffer, ", ", strlen(", "));

  Machine_StringBuffer_appendBytes(stringBuffer, "y: ", strlen("y: "));
  Machine_StringBuffer_appendString(stringBuffer, Ring2_Real32_toString(Ring2_Context_get(), self->y));

  Machine_StringBuffer_appendBytes(stringBuffer, " }", strlen(" }"));

  return Machine_Object_toString(Ring2_Context_get(), (Machine_Object*)stringBuffer);
}

static void Machine_MousePointerEvent_constructClass(Machine_MousePointerEvent_Class* self) {
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Machine_Object const*)) & Machine_MousePointerEvent_toStringImpl;
}

static void Machine_MousePointerEvent_construct(Machine_MousePointerEvent* self,
                                                size_t numberOfArguments,
                                                Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->action = Machine_Value_getInteger(&arguments[0]);
  self->x = Machine_Value_getReal32(&arguments[1]);
  self->y = Machine_Value_getReal32(&arguments[2]);
  Machine_setClassType((Machine_Object*)self, Machine_MousePointerEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_MousePointerEvent, Machine_Object,
                         &Machine_MousePointerEvent_visit, &Machine_MousePointerEvent_construct,
                         NULL, &Machine_MousePointerEvent_constructClass, NULL)

Machine_MousePointerEvent* Machine_MousePointerEvent_create(Machine_MousePointerActions action,
                                                            Ring2_Real32 x, Ring2_Real32 y) {
  Machine_ClassType* ty = Machine_MousePointerEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Machine_Value ARGUMENTS[3]
      = { Machine_Value_StaticInitializerVoid(), Machine_Value_StaticInitializerVoid(),
          Machine_Value_StaticInitializerVoid() };
  Machine_Value_setInteger(&ARGUMENTS[0], action);
  Machine_Value_setReal32(&ARGUMENTS[1], x);
  Machine_Value_setReal32(&ARGUMENTS[2], y);
  Machine_MousePointerEvent* self
      = (Machine_MousePointerEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
