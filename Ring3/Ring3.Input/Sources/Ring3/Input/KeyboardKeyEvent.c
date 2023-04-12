/// @file Ring3/Input/KeyboardKeyEvent.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/KeyboardKeyEvent.h"
#undef RING3_INPUT_PRIVATE

static void
Ring3_KeyboardKeyEvent_visit
  (
    Ring3_KeyboardKeyEvent* self
  )
{/*Intentionally empty.*/}

static Ring1_CheckReturn() Ring2_String*
Ring3_KeyboardKeyEvent_toStringImpl
  (
    Ring2_Context *context,
    Ring3_KeyboardKeyEvent const* self
  )
{
  Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create();

  Ring2_StringBuffer_appendBytes(stringBuffer, "{ ", crt_strlen("{ "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "type: 'keyboard-key-event'",
                                    crt_strlen("type: 'keyboard-key-event'"));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ", crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "keyAction: '", crt_strlen("keyAction: '"));
  Ring2_StringBuffer_appendString(stringBuffer,
                                  Ring3_KeyboardKeyAction_toString(self->action));
  Ring2_StringBuffer_appendBytes(stringBuffer, "', ", crt_strlen("', "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "key: '", crt_strlen("key: '"));
  Ring2_StringBuffer_appendString(stringBuffer, Ring3_KeyboardKey_toString(self->key));
  Ring2_StringBuffer_appendBytes(stringBuffer, "'", crt_strlen("'"));

  Ring2_StringBuffer_appendBytes(stringBuffer, " }", crt_strlen(" }"));

  return Machine_Object_toString(Ring2_Context_get(), (Machine_Object*)stringBuffer);
}

static void
Ring3_KeyboardKeyEvent_constructClass
  (
    Ring3_KeyboardKeyEvent_Class* self
  )
{
  Ring1_cast(Machine_Object_Class*, self)->toString
      = (Ring2_String * (*)(Ring2_Context *, Machine_Object const*)) & Ring3_KeyboardKeyEvent_toStringImpl;
}

static void
Ring3_KeyboardKeyEvent_construct
  (
    Ring3_KeyboardKeyEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->key = Ring2_Value_getInteger(&arguments[0]);
  self->action = Ring2_Value_getInteger(&arguments[1]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_KeyboardKeyEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_KeyboardKeyEvent,
                         Machine_Object,
                         &Ring3_KeyboardKeyEvent_visit,
                         &Ring3_KeyboardKeyEvent_construct,
                         NULL,
                         &Ring3_KeyboardKeyEvent_constructClass,
                         NULL)

Ring1_CheckReturn() Ring3_KeyboardKeyEvent*
Ring3_KeyboardKeyEvent_create
  (
    Ring3_KeyboardKey key,
    Ring3_KeyboardKeyAction keyAction
  )
{
  Machine_Type* ty = Ring3_KeyboardKeyEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value ARGUMENTS[2]
      = { Ring2_Value_StaticInitializerVoid(), Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&ARGUMENTS[0], key);
  Ring2_Value_setInteger(&ARGUMENTS[1], keyAction);
  Ring3_KeyboardKeyEvent* self
      = (Ring3_KeyboardKeyEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
