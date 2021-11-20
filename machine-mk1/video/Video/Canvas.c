#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/Canvas.h"



MACHINE_DEFINE_CLASSTYPE(Machine_Video_Canvas, Machine_Object, NULL, &Machine_Video_Canvas_construct, NULL, NULL)

void Machine_Video_Canvas_construct(Machine_Video_Canvas* self, size_t numberOfArguments, Machine_Value const* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Object_construct((Machine_Object*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_setClassType((Machine_Object*)self, Machine_Video_Canvas_getType());
}

void Machine_Video_Canvas_getFrameBuffersSize(Machine_Video_Canvas* self, Machine_Integer* width, Machine_Integer* height) {
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
