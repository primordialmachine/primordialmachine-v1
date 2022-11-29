/// @file Ring3/Input/MousePointerEvent.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/MousePointerEvent.h"

#include "Ring1/Intrinsic.h"

MACHINE_DEFINE_ENUMERATIONTYPE(Machine_MousePointerActions)

Ring1_CheckReturn() Ring2_String*
Machine_MousePointerActions_toString
  (
    Machine_MousePointerActions self
  )
{
  switch (self) {
    case Machine_MousePointerActions_Move:
      return Ring2_String_fromC("move");
      break;
    case Machine_MousePointerActions_Enter:
      return Ring2_String_fromC("enter");
      break;
    case Machine_MousePointerActions_Exit:
      return Ring2_String_fromC("exit");
      break;
    case Machine_MousePointerActions_Undetermined:
    default:
      Ring2_unreachable();
  };
}

static void
Machine_MousePointerEvent_visit
  (
    Machine_MousePointerEvent* self
  )
{/*Intentionally empty.*/}

Ring1_CheckReturn() static Ring2_String*
Machine_MousePointerEvent_toStringImpl
  (
    Ring2_Context* context,
    Machine_MousePointerEvent const* self
  )
{
  Ring2_StringBuffer* stringBuffer = Ring2_StringBuffer_create();

  Ring2_StringBuffer_appendBytes(stringBuffer, "{ ",
                                    crt_strlen("{ "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "type: 'mouse-pointer-event'",
                                    crt_strlen("type: 'mouse-pointer-event'"));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ",
                                    crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "action: '",
                                    crt_strlen("action: '"));
  Ring2_StringBuffer_appendString(stringBuffer,
                                  Machine_MousePointerActions_toString(self->action));
  Ring2_StringBuffer_appendBytes(stringBuffer, "', ",
                                    crt_strlen("', "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "x: ",
                                    crt_strlen("x: "));
  Ring2_StringBuffer_appendString(stringBuffer, Ring2_Real32_toString(Ring2_Context_get(), self->x));
  Ring2_StringBuffer_appendBytes(stringBuffer, ", ",
                                    crt_strlen(", "));

  Ring2_StringBuffer_appendBytes(stringBuffer, "y: ",
                                    crt_strlen("y: "));
  Ring2_StringBuffer_appendString(stringBuffer, Ring2_Real32_toString(Ring2_Context_get(), self->y));

  Ring2_StringBuffer_appendBytes(stringBuffer, " }",
                                    crt_strlen(" }"));

  return Machine_Object_toString(Ring2_Context_get(), (Machine_Object*)stringBuffer);
}

static void
Machine_MousePointerEvent_constructClass
  (
    Machine_MousePointerEvent_Class* self
  )
{
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Ring2_Context *context, Machine_Object const*)) & Machine_MousePointerEvent_toStringImpl;
}

static void
Machine_MousePointerEvent_construct
  (
    Machine_MousePointerEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->action = Ring2_Value_getInteger(&arguments[0]);
  self->x = Ring2_Value_getReal32(&arguments[1]);
  self->y = Ring2_Value_getReal32(&arguments[2]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_MousePointerEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_MousePointerEvent,
                         Machine_Object,
                         &Machine_MousePointerEvent_visit,
                         &Machine_MousePointerEvent_construct,
                         NULL,
                         &Machine_MousePointerEvent_constructClass,
                         NULL)

Ring1_CheckReturn() Machine_MousePointerEvent*
Machine_MousePointerEvent_create
  (
    Machine_MousePointerActions action,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{
  Machine_ClassType* ty = Machine_MousePointerEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3]
      = { Ring2_Value_StaticInitializerVoid(),
          Ring2_Value_StaticInitializerVoid(),
          Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&ARGUMENTS[0], action);
  Ring2_Value_setReal32(&ARGUMENTS[1], x);
  Ring2_Value_setReal32(&ARGUMENTS[2], y);
  Machine_MousePointerEvent* self
      = (Machine_MousePointerEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
