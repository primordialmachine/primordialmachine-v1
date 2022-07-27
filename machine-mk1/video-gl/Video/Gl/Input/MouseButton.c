/// @file Video/Gl/Input/MouseButton.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/MouseButton.h"

#include "Ring1/Status.h"

static Ring1_Result mapButton(int source, Ring2_Integer* target) {
  switch (source) {
    case GLFW_MOUSE_BUTTON_1: {
      *target = 0;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_2: {
      *target = 1;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_3: {
      *target = 2;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_4: {
      *target = 3;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_5: {
      *target = 4;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_6: {
      *target = 5;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_7: {
      *target = 6;
      return Ring1_Result_Success;      
    } break;
    case GLFW_MOUSE_BUTTON_8: {
      *target = 7;
      return Ring1_Result_Success;      
    } break;
    default:
      Ring1_Status_set(Ring1_Status_NotYetImplemented);
      return Ring1_Result_Failure;
  };
}

static Ring1_Result mapButtonAction(int source, Machine_MouseButtonActions* target) {
  switch (source) {
    case GLFW_PRESS: {
      *target = Machine_MouseButtonActions_Press;
      return Ring1_Result_Success;    
    } break;
    case GLFW_RELEASE: {
      *target = Machine_MouseButtonActions_Release;
      return Ring1_Result_Success;    
    } break;
    default:
      Ring1_Status_set(Ring1_Status_NotYetImplemented);
      return Ring1_Result_Failure;
  };
}

Machine_MouseButtonEvent* Machine_Video_Gl_Input_mapMouseButtonEvent(GLFWwindow* window, int button,
                                                                     int action, int modifiers) {
  Ring2_Integer buttonInternal;
  Machine_MouseButtonActions actionInternal;
  if (mapButton(button, &buttonInternal) || mapButtonAction(action, &actionInternal)) {
    Ring2_jump();
  }
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Machine_MouseButtonEvent* event
      = Machine_MouseButtonEvent_create(buttonInternal, actionInternal, x, y);
  return event;
}
