/// @file Ring3/Input/MouseButtonEvent.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/MouseButtonEvent.h"
#undef RING3_INPUT_PRIVATE

static void
Ring3_MouseButtonEvent_visit
  (
    Ring3_MouseButtonEvent* self
  )
{/*Intentionally empty.*/}

Ring1_CheckReturn() static Ring2_String*
Ring3_MouseButtonEvent_toStringImpl
  (
    Ring2_Context *context,
    Ring3_MouseButtonEvent const* self
  )
{
  Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create();

  Ring2_StringBuffer_appendBytes(stringBuffer, "{ ", crt_strlen("{ "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "type: 'mouse-button-event'",
                                    crt_strlen("type: 'mouse-button-event'"));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ", crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "action: '", crt_strlen("action: '"));
  Ring2_StringBuffer_appendString(stringBuffer,
                                  Ring3_MouseButtonAction_toString(self->action));
  Ring2_StringBuffer_appendBytes(stringBuffer, "', ", crt_strlen("', "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "button: ", crt_strlen("button: "));
  Ring2_StringBuffer_appendString(stringBuffer, Ring2_Integer_toString(Ring2_Context_get(), self->button));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ", crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "x: ", crt_strlen("x: "));
  Ring2_StringBuffer_appendString(stringBuffer, Ring2_Real32_toString(Ring2_Context_get(), self->x));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ", crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "y: ", crt_strlen("y: "));
  Ring2_StringBuffer_appendString(stringBuffer, Ring2_Real32_toString(Ring2_Context_get(), self->y));

  Ring2_StringBuffer_appendBytes(stringBuffer, " }", crt_strlen(" }"));

  return Machine_Object_toString(Ring2_Context_get(), (Machine_Object*)stringBuffer);
}

static void
Ring3_MouseButtonEvent_constructClass
  (
    Ring3_MouseButtonEvent_Class* self
  )
{
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Ring2_Context *, Machine_Object const*)) & Ring3_MouseButtonEvent_toStringImpl;
}

static void
Ring3_MouseButtonEvent_construct
  (
    Ring3_MouseButtonEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->button = Ring2_Value_getInteger(&arguments[0]);
  self->action = Ring2_Value_getInteger(&arguments[1]);
  self->x = Ring2_Value_getReal32(&arguments[2]);
  self->y = Ring2_Value_getReal32(&arguments[3]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_MouseButtonEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_MouseButtonEvent,
                         Machine_Object,
                         &Ring3_MouseButtonEvent_visit,
                         &Ring3_MouseButtonEvent_construct,
                         NULL,
                         &Ring3_MouseButtonEvent_constructClass,
                         NULL)

Ring1_CheckReturn() Ring3_MouseButtonEvent*
Ring3_MouseButtonEvent_create
  (
    int button,
    int action,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{
  Machine_Type* ty = Ring3_MouseButtonEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value arguments[] =
    {
      Ring2_Value_StaticInitializerVoid(),
      Ring2_Value_StaticInitializerVoid(),
      Ring2_Value_StaticInitializerVoid(),
      Ring2_Value_StaticInitializerVoid(),
    };
  Ring2_Value_setInteger(&arguments[0], button);
  Ring2_Value_setInteger(&arguments[1], action);
  Ring2_Value_setReal32(&arguments[2], x);
  Ring2_Value_setReal32(&arguments[3], y);
  Ring3_MouseButtonEvent* self = Ring1_cast(Ring3_MouseButtonEvent*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}
