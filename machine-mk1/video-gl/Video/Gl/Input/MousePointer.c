/// @file Video/Gl/Input/MousePointer.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/MousePointer.h"

Machine_MousePointerEvent* Machine_Video_Gl_Input_mapMousePointerEvent(GLFWwindow* window, double x,
                                                                       double y) {
  Machine_MousePointerEvent * event = Machine_MousePointerEvent_create(x, y);
  return event;
}
