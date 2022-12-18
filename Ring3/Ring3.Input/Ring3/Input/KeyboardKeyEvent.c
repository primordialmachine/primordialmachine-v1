/// @file Ring3/Input/KeyboardKeyEvent.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/KeyboardKeyEvent.h"

#include "Ring1/All/_Include.h"

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_KeyboardKeyActions)

Ring1_CheckReturn() Ring2_String*
Machine_KeyboardKeyActions_toString
  (
    Machine_KeyboardKeyActions self
  )
{
  switch (self) {
    case Machine_KeyboardKeyActions_Press:
      return Ring2_String_fromC("press");
      break;
    case Machine_KeyboardKeyActions_Release:
      return Ring2_String_fromC("release");
      break;
    case Machine_KeyboardKeyActions_Repeat:
      return Ring2_String_fromC("repeat");
      break;
    case Machine_KeyboardKeyActions_Undetermined:
    default:
      Ring2_unreachable();
  };
}

static void
Machine_KeyboardKeyEvent_visit
  (
    Machine_KeyboardKeyEvent* self
  )
{/*Intentionally empty.*/}

static Ring1_CheckReturn() Ring2_String*
Machine_KeyboardKeyEvent_toStringImpl
  (
    Ring2_Context *context,
    Machine_KeyboardKeyEvent const* self
  )
{
  Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create();

  Ring2_StringBuffer_appendBytes(stringBuffer, "{ ", crt_strlen("{ "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "type: 'keyboard-key-event'",
                                    crt_strlen("type: 'keyboard-key-event'"));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ", crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "keyAction: '", crt_strlen("keyAction: '"));
  Ring2_StringBuffer_appendString(stringBuffer,
                                  Machine_KeyboardKeyActions_toString(self->action));
  Ring2_StringBuffer_appendBytes(stringBuffer, "', ", crt_strlen("', "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "key: '", crt_strlen("key: '"));
  Ring2_StringBuffer_appendString(stringBuffer, Machine_KeyboardKeys_toString(self->key));
  Ring2_StringBuffer_appendBytes(stringBuffer, "'", crt_strlen("'"));

  Ring2_StringBuffer_appendBytes(stringBuffer, " }", crt_strlen(" }"));

  return Machine_Object_toString(Ring2_Context_get(), (Machine_Object*)stringBuffer);
}

static void
Machine_KeyboardKeyEvent_constructClass
  (
    Machine_KeyboardKeyEvent_Class* self
  )
{
  Ring1_cast(Machine_Object_Class*, self)->toString
      = (Ring2_String * (*)(Ring2_Context *, Machine_Object const*)) & Machine_KeyboardKeyEvent_toStringImpl;
}

static void
Machine_KeyboardKeyEvent_construct
  (
    Machine_KeyboardKeyEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->key = Ring2_Value_getInteger(&arguments[0]);
  self->action = Ring2_Value_getInteger(&arguments[1]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_KeyboardKeyEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_KeyboardKeyEvent,
                         Machine_Object,
                         &Machine_KeyboardKeyEvent_visit,
                         &Machine_KeyboardKeyEvent_construct,
                         NULL,
                         &Machine_KeyboardKeyEvent_constructClass,
                         NULL)

Ring1_CheckReturn() Machine_KeyboardKeyEvent*
Machine_KeyboardKeyEvent_create
  (
    Machine_KeyboardKeys key,
    Machine_KeyboardKeyActions keyAction
  )
{
  Machine_ClassType* ty = Machine_KeyboardKeyEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[2]
      = { Ring2_Value_StaticInitializerVoid(), Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&ARGUMENTS[0], key);
  Ring2_Value_setInteger(&ARGUMENTS[1], keyAction);
  Machine_KeyboardKeyEvent* self
      = (Machine_KeyboardKeyEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
