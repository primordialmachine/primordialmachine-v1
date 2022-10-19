#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Canvas.h"


#include "Ring1/Intrinsic.h"
#include "Ring2/Library/_Include.h"
#include "_Input.h"


static void visit(Machine_Video_Canvas* self);

MACHINE_DEFINE_CLASSTYPE(Machine_Video_Canvas, Machine_Object, &visit,
                         &Machine_Video_Canvas_construct, NULL, NULL, NULL)

static void visit(Machine_Video_Canvas* self) {
  if (self->events) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->events);
  }
  if (self->signal) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->signal);
  }
}

void Machine_Video_Canvas_construct(Machine_Video_Canvas* self, size_t numberOfArguments,
                                    Ring2_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  self->events = (Ring2_Collections_Deque*)Ring2_Collections_ArrayDeque_create();
  self->signal = Machine_Signals_Signal_create();
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Video_Canvas_getType());
}

void Machine_Video_Canvas_getFrameBuffersSize(Machine_Video_Canvas* self, Ring2_Integer* width,
                                              Ring2_Integer* height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Video_Canvas, getFrameBuffersSize, width, height);
}

void Machine_Video_Canvas_maximizeCanvas(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Video_Canvas, maximizeCanvas);
}

void Machine_Video_Canvas_swapFrameBuffers(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Video_Canvas, swapFrameBuffers);
}

void Machine_Video_Canvas_setCanvasIcons(Machine_Video_Canvas* self, Ring2_Collections_List* images) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Video_Canvas, setCanvasIcons, images);
}

void Machine_Video_Canvas_pollEvents(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Video_Canvas, pollEvents);
}

Ring2_Boolean Machine_Video_Canvas_getQuitRequested(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Video_Canvas, getQuitRequested);
}

void Machine_Video_Canvas_pumpEvents(Machine_Video_Canvas* self) {
  while (Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)self->events) > 0) {
    Ring2_Value value = Ring2_Collections_Deque_popFront((Ring2_Collections_Deque*)self->events);
    Machine_Object* object = Ring2_Value_getObject(&value);
    Machine_Type* type = (Machine_Type*)Machine_getClassType(object);
    if (Machine_Type_isSubTypeOf(type, (Machine_Type*)Machine_MouseButtonEvent_getType())) {
      Machine_MouseButtonEvent* mouseButtonEvent = (Machine_MouseButtonEvent*)object;
      switch (mouseButtonEvent->action) {
        case Machine_MouseButtonActions_Press: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_MouseButtonPressed(),
                                      numberOfArguments, arguments);
        } break;
        case Machine_MouseButtonActions_Release: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_MouseButtonReleased(),
                                      numberOfArguments, arguments);
        } break;
      };
    } else if (Machine_Type_isSubTypeOf(type, (Machine_Type*)Machine_MousePointerEvent_getType())) {
      size_t numberOfArguments = 1;
      Ring2_Value arguments[1];
      Ring2_Value_setObject(&arguments[0], object);
      Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_MousePointerMoved(),
                                  numberOfArguments, arguments);
    } else if (Machine_Type_isSubTypeOf(type, (Machine_Type*)Machine_KeyboardKeyEvent_getType())) {
      Machine_KeyboardKeyEvent* keyboardKeyEvent = (Machine_KeyboardKeyEvent*)object;
      switch (keyboardKeyEvent->action) {
        case Machine_KeyboardKeyActions_Press: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_KeyboardKeyPressed(),
                                      numberOfArguments, arguments);
        } break;
        case Machine_KeyboardKeyActions_Release: {
          size_t numberOfArguments = 1;
          Ring2_Value arguments[1];
          Ring2_Value_setObject(&arguments[0], object);
          Machine_Signals_Signal_emit(self->signal, Machine_Input_SignalName_KeyboardKeyReleased(),
                                      numberOfArguments, arguments);
        } break;
        case Machine_KeyboardKeyActions_Repeat: {
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

void Machine_Video_Canvas_subscribeKeyboardKeyPressedEvent(Machine_Video_Canvas* self,
                                                           Machine_Object* context,
                                                           Ring2_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_KeyboardKeyPressed(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeKeyboardKeyReleasedEvent(Machine_Video_Canvas* self,
                                                            Machine_Object* context,
                                                            Ring2_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_KeyboardKeyReleased(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeMouseButtonPressedEvent(Machine_Video_Canvas* self,
                                                           Machine_Object* context,
                                                           Ring2_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MouseButtonPressed(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeMouseButtonReleasedEvent(Machine_Video_Canvas* self,
                                                            Machine_Object* context,
                                                            Ring2_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MouseButtonReleased(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeMousePointerMovedEvent(Machine_Video_Canvas* self,
                                                          Machine_Object* context,
                                                          Ring2_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MousePointerMoved(),
                                   context, callback);
}

void Machine_Video_Canvas_addKeyboardKeyEvent(Machine_Video_Canvas* self,
                                              Machine_KeyboardKeyEvent* event) {
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)event);
  Ring2_Collections_Deque_pushBack((Ring2_Collections_Deque*)self->events, value);
}

void Machine_Video_Canvas_addMouseButtonEvent(Machine_Video_Canvas* self,
                                              Machine_MouseButtonEvent* event) {
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)event);
  Ring2_Collections_Deque_pushBack((Ring2_Collections_Deque*)self->events, value);
}

void Machine_Video_Canvas_addMousePointerEvent(Machine_Video_Canvas* self,
                                               Machine_MousePointerEvent* event) {
  Ring2_Value value;
  Ring2_Value_setObject(&value, (Machine_Object*)event);
  Ring2_Collections_Deque_pushBack((Ring2_Collections_Deque*)self->events, value);
}
