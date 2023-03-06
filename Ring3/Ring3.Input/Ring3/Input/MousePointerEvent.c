/// @file Ring3/Input/MousePointerEvent.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_INPUT_PRIVATE (1)
#include "Ring3/Input/MousePointerEvent.h"
#undef RING3_INPUT_PRIVATE

static void
Ring3_MousePointerEvent_visit
  (
    Ring3_MousePointerEvent* self
  )
{/*Intentionally empty.*/}

Ring1_CheckReturn() static Ring2_String*
Ring3_MousePointerEvent_toStringImpl
  (
    Ring2_Context* context,
    Ring3_MousePointerEvent const* self
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
                                  Ring3_MousePointerAction_toString(self->action));
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
Ring3_MousePointerEvent_constructClass
  (
    Ring3_MousePointerEvent_Class* self
  )
{
  ((Machine_Object_Class*)self)->toString
      = (Ring2_String * (*)(Ring2_Context *context, Machine_Object const*)) & Ring3_MousePointerEvent_toStringImpl;
}

static void
Ring3_MousePointerEvent_construct
  (
    Ring3_MousePointerEvent* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->action = Ring2_Value_getInteger(&arguments[0]);
  self->x = Ring2_Value_getReal32(&arguments[1]);
  self->y = Ring2_Value_getReal32(&arguments[2]);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_MousePointerEvent_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_MousePointerEvent,
                         Machine_Object,
                         &Ring3_MousePointerEvent_visit,
                         &Ring3_MousePointerEvent_construct,
                         NULL,
                         &Ring3_MousePointerEvent_constructClass,
                         NULL)

Ring1_CheckReturn() Ring3_MousePointerEvent*
Ring3_MousePointerEvent_create
  (
    Ring3_MousePointerAction action,
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{
  Machine_ClassType* ty = Ring3_MousePointerEvent_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3]
      = { Ring2_Value_StaticInitializerVoid(),
          Ring2_Value_StaticInitializerVoid(),
          Ring2_Value_StaticInitializerVoid() };
  Ring2_Value_setInteger(&ARGUMENTS[0], action);
  Ring2_Value_setReal32(&ARGUMENTS[1], x);
  Ring2_Value_setReal32(&ARGUMENTS[2], y);
  Ring3_MousePointerEvent* self
      = (Ring3_MousePointerEvent*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
