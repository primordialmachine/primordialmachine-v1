/// @file Ring3/Visuals/Canvas.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/Canvas.h"
#undef RING3_VISUALS_PRIVATE

static void
visit
  (
    Ring3_Canvas* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_Canvas,
                         Machine_Object,
                         &visit,
                         &Ring3_Canvas_construct,
                         NULL,
                         NULL,
                         NULL)

static void
visit
  (
    Ring3_Canvas* self
  )
{
  if (self->events) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->events);
  }
  if (self->signal) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->signal);
  }
}

void
Ring3_Canvas_construct
  (
    Ring3_Canvas* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  self->events = (Ring2_Collections_Deque*)Ring2_Collections_ArrayDeque_create();
  self->signal = Machine_Signals_Signal_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Canvas_getType());
}

void
Ring3_Canvas_getFrameBuffersSize
  (
    Ring3_Canvas* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Canvas, getFrameBuffersSize, width, height); }

void
Ring3_Canvas_maximizeCanvas
  (
    Ring3_Canvas* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Ring3_Canvas, maximizeCanvas); }

void
Ring3_Canvas_swapFrameBuffers
  (
    Ring3_Canvas* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Ring3_Canvas, swapFrameBuffers); }

void
Ring3_Canvas_setCanvasIcons
  (
    Ring3_Canvas* self,
    Ring2_Collections_List* images
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_Canvas, setCanvasIcons, images); }

void
Ring3_Canvas_pollEvents
  (
    Ring3_Canvas* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Ring3_Canvas, pollEvents); }

Ring2_Boolean
Ring3_Canvas_getQuitRequested
  (
    Ring3_Canvas* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_Canvas, getQuitRequested); }

void
Ring3_Canvas_pumpEvents
  (
    Ring3_Canvas* self
  )
{
  while (Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->events) > 0) {
    Ring2_Value value = Ring2_Collections_Deque_popFront((Ring2_Collections_Deque*)self->events);
    Machine_Object* object = Ring2_Value_getObject(&value);
    Machine_Type* type = (Machine_Type*)Machine_getClassType(object);
    if (Machine_Type_isSubTypeOf(type, (Machine_Type*)Ring3_MouseButtonEvent_getType())) {
      Ring3_MouseButtonEvent* mouseButtonEvent = (Ring3_MouseButtonEvent*)object;
      switch (mouseButtonEvent->action) {
        case Ring3_MouseButtonAction_Press: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_MouseButtonPressed(),
                                      numberOfArguments, arguments);
        } break;
        case Ring3_MouseButtonAction_Release: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_MouseButtonReleased(),
                                      numberOfArguments, arguments);
        } break;
      };
    } else if (Machine_Type_isSubTypeOf(type, (Machine_Type*)Ring3_MousePointerEvent_getType())) {
      size_t numberOfArguments = 1;
      Ring2_Value arguments[1];
      Ring2_Value_setObject(&arguments[0], object);
      Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_MousePointerMoved(),
                                  numberOfArguments, arguments);
    } else if (Machine_Type_isSubTypeOf(type, (Machine_Type*)Ring3_KeyboardKeyEvent_getType())) {
      Ring3_KeyboardKeyEvent* keyboardKeyEvent = (Ring3_KeyboardKeyEvent*)object;
      switch (keyboardKeyEvent->action) {
        case Ring3_KeyboardKeyAction_Press: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_KeyboardKeyPressed(),
                                      numberOfArguments, arguments);
        } break;
        case Ring3_KeyboardKeyAction_Release: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_KeyboardKeyReleased(),
                                      numberOfArguments, arguments);
        } break;
        case Ring3_KeyboardKeyAction_Repeat: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_KeyboardKeyRepeated(),
                                      numberOfArguments, arguments);
        } break;
      };
    }
  };
}

void
Ring3_Canvas_subscribeKeyboardKeyPressedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_KeyboardKeyPressed(),
                                   context, callback);
}

void
Ring3_Canvas_subscribeKeyboardKeyReleasedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_KeyboardKeyReleased(),
                                   context, callback);
}

void
Ring3_Canvas_subscribeMouseButtonPressedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MouseButtonPressed(),
                                   context, callback);
}

void
Ring3_Canvas_subscribeMouseButtonReleasedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MouseButtonReleased(),
                                   context, callback);
}

void
Ring3_Canvas_subscribeMousePointerMovedEvent
  (
    Ring3_Canvas* self,
    Machine_Object* context,
    Ring2_ForeignProcedure* callback
  )
{
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MousePointerMoved(),
                                   context, callback);
}

void
Ring3_Canvas_addKeyboardKeyEvent
  (
    Ring3_Canvas* self,
    Ring3_KeyboardKeyEvent* event
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)event);
  Ring2_Collections_Deque_pushBack((Ring2_Collections_Deque*)self->events, value);
}

void
Ring3_Canvas_addMouseButtonEvent
  (
    Ring3_Canvas* self,
    Ring3_MouseButtonEvent* event
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)event);
  Ring2_Collections_Deque_pushBack((Ring2_Collections_Deque*)self->events, value);
}

void
Ring3_Canvas_addMousePointerEvent
  (
    Ring3_Canvas* self,
    Ring3_MousePointerEvent* event
  )
{
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)event);
  Ring2_Collections_Deque_pushBack((Ring2_Collections_Deque*)self->events, value);
}
