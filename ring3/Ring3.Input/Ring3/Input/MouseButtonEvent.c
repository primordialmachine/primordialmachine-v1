/// @file Ring3/Input/MouseButtonEvent.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/MouseButtonEvent.h"

#include "Ring1/Intrinsic.h"

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_MouseButtonActions)

Ring1_CheckReturn() Ring2_String*
Machine_MouseButtonActions_toString
  (
    Machine_MouseButtonActions self
  )
{
  switch (self) {
    case Machine_MouseButtonActions_Press:
      return Ring2_String_fromC("press");
      break;
    case Machine_MouseButtonActions_Release:
      return Ring2_String_fromC("release");
      break;
    case Machine_MouseButtonActions_Undetermined:
    default:
      Ring2_unreachable();
  };
}

static void
Machine_MouseButtonEvent_visit
  (
    Machine_MouseButtonEvent* self
  )
{/*Intentionally empty.*/}

Ring1_CheckReturn() static Ring2_String*
Machine_MouseButtonEvent_toStringImpl
  (
    Ring2_Context *context,
    Machine_MouseButtonEvent const* self
  )
{
  Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create();

  Ring2_StringBuffer_appendBytes(stringBuffer, "{ ", crt_strlen("{ "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "type: 'mouse-button-event'",
                                    crt_strlen("type: 'mouse-button-event'"));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ", crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "action: '", crt_strlen("action: '"));
  Ring2_StringBuffer_appendString(stringBuffer,
                                  Machine_MouseButtonActions_toString(self->action));
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
Machine_MouseButtonEvent_constructClass
  (
    Machine_MouseButtonEvent_Class* self
  )
{
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Ring2_Context *, Machine_Object const*)) & Machine_MouseButtonEvent_toStringImpl;
}

static void
Machine_MouseButtonEvent_construct
  (
    Machine_MouseButtonEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->button = Ring2_Value_getInteger(&arguments[0]);
  self->action = Ring2_Value_getInteger(&arguments[1]);
  self->x = Ring2_Value_getReal32(&arguments[2]);
  self->y = Ring2_Value_getReal32(&arguments[3]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_MouseButtonEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_MouseButtonEvent,
                         Machine_Object,
                         &Machine_MouseButtonEvent_visit,
                         &Machine_MouseButtonEvent_construct,
                         NULL,
                         &Machine_MouseButtonEvent_constructClass,
                         NULL)

Ring1_CheckReturn() Machine_MouseButtonEvent*
Machine_MouseButtonEvent_create
  (
    int button,
    int action,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{
  Machine_ClassType* ty = Machine_MouseButtonEvent_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value ARGUMENTS[4]
      = { Ring2_Value_StaticInitializerVoid(), Ring2_Value_StaticInitializerVoid(),
          Ring2_Value_StaticInitializerVoid(), Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&ARGUMENTS[0], button);
  Ring2_Value_setInteger(&ARGUMENTS[1], action);
  Ring2_Value_setReal32(&ARGUMENTS[2], x);
  Ring2_Value_setReal32(&ARGUMENTS[3], y);
  Machine_MouseButtonEvent* self
      = (Machine_MouseButtonEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
