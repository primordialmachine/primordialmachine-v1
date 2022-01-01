#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Canvas.h"

#include "_Input.h"

MACHINE_DEFINE_CLASSTYPE(Machine_Video_Canvas, Machine_Object, NULL,
                         &Machine_Video_Canvas_construct, NULL, NULL, NULL)

void Machine_Video_Canvas_construct(Machine_Video_Canvas* self, size_t numberOfArguments,
                                    Machine_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  self->signal = Machine_Signals_Signal_create();
  Machine_setClassType((Machine_Object*)self, Machine_Video_Canvas_getType());
}

void Machine_Video_Canvas_getFrameBuffersSize(Machine_Video_Canvas* self, Machine_Integer* width,
                                              Machine_Integer* height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Video_Canvas, getFrameBuffersSize, width, height);
}

void Machine_Video_Canvas_maximizeCanvas(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Video_Canvas, maximizeCanvas);
}

void Machine_Video_Canvas_swapFrameBuffers(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Video_Canvas, swapFrameBuffers);
}

void Machine_Video_Canvas_setCanvasIcons(Machine_Video_Canvas* self, Machine_List* images) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_Video_Canvas, setCanvasIcons, images);
}

void Machine_Video_Canvas_pollEvents(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Video_Canvas, pollEvents);
}

Machine_Boolean Machine_Video_Canvas_getQuitRequested(Machine_Video_Canvas* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_Video_Canvas, getQuitRequested);
}

void Machine_Video_Canvas_subscribeKeyboardKeyPressedEvent(Machine_Video_Canvas* self,
                                                           Machine_Object* context,
                                                           Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_KeyboardKeyPressed(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeKeyboardKeyReleasedEvent(Machine_Video_Canvas* self,
                                                            Machine_Object* context,
                                                            Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_KeyboardKeyReleased(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeMouseButtonPressedEvent(Machine_Video_Canvas* self,
                                                           Machine_Object* context,
                                                           Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MouseButtonPressed(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeMouseButtonReleasedEvent(Machine_Video_Canvas* self,
                                                            Machine_Object* context,
                                                            Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MouseButtonReleased(),
                                   context, callback);
}

void Machine_Video_Canvas_subscribeMousePointerMovedEvent(Machine_Video_Canvas* self,
                                                          Machine_Object* context,
                                                          Machine_ForeignProcedure* callback) {
  Machine_Signals_Signal_subscribe(self->signal, Machine_Input_SignalName_MousePointerMoved(),
                                   context, callback);
}
