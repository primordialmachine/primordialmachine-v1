/// @file Video/Gl/Input/MousePointer.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/MousePointer.h"

Machine_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerEnterExitEvent(GLFWwindow* window,
                                                                                int entered) {
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Machine_MousePointerEvent* event = Machine_MousePointerEvent_create(
      entered ? Machine_MousePointerActions_Enter : Machine_MousePointerActions_Exit, x, y);
  return event;
}

Machine_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerMoveEvent(GLFWwindow* window, double x,
                                                                           double y) {
  Machine_MousePointerEvent * event = Machine_MousePointerEvent_create(Machine_MousePointerActions_Move, x, y);
  return event;
}
