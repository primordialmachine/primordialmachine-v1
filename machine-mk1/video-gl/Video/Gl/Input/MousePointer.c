/// @file Video/Gl/Input/MousePointer.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/MousePointer.h"

Ring3_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerEnterExitEvent(GLFWwindow* window,
                                                                                int entered) {
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Ring3_MousePointerEvent* event = Ring3_MousePointerEvent_create(
      entered ? Ring3_MousePointerAction_Enter : Ring3_MousePointerAction_Exit, x, y);
  return event;
}

Ring3_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerMoveEvent(GLFWwindow* window,
                                                                         double x, double y) {
  Ring3_MousePointerEvent* event
      = Ring3_MousePointerEvent_create(Ring3_MousePointerAction_Move, x, y);
  return event;
}
