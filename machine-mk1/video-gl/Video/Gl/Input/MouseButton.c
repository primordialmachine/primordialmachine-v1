/// @file Video/Gl/Input/MouseButton.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/MousePointer.h"

static bool mapButton(int source, Machine_Integer* target) {
  switch (source) {
    case GLFW_MOUSE_BUTTON_1: {
      *target = 0;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_2: {
      *target = 1;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_3: {
      *target = 2;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_4: {
      *target = 3;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_5: {
      *target = 4;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_6: {
      *target = 5;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_7: {
      *target = 6;
      return true;
    } break;
    case GLFW_MOUSE_BUTTON_8: {
      *target = 7;
      return true;
    } break;
    default:
      return false;
  };
}

static bool mapButtonAction(int source, Machine_MouseButtonActions* target) {
  switch (source) {
    case GLFW_PRESS: {
      *target = Machine_MouseButtonActions_Press;
      return true;
    } break;
    case GLFW_RELEASE: {
      *target = Machine_MouseButtonActions_Release;
      return true;
    } break;
    default:
      return false;
  };
}

Machine_MouseButtonEvent* Machine_Video_Gl_Input_mapMouseButtonEvent(GLFWwindow* window, int button,
                                                                     int action, int modifiers) {
  Machine_Integer buttonInternal;
  Machine_MouseButtonActions actionInternal;
  if (!mapButton(button, &buttonInternal) || !mapButtonAction(action, &actionInternal)) {
    Machine_setStatus(Machine_Status_InternalError);
    Ring2_jump();
  }
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Machine_MouseButtonEvent* event
      = Machine_MouseButtonEvent_create(buttonInternal, actionInternal, x, y);
  return event;
}
