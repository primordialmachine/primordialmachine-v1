/// @file Video/Gl/Input/MouseButton.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/MouseButton.h"
#undef MACHINE_VIDEO_GL_PRIVATE


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

static Ring1_Result mapButtonAction(int source, Ring3_MouseButtonAction* target) {
  switch (source) {
    case GLFW_PRESS: {
      *target = Ring3_MouseButtonAction_Press;
      return Ring1_Result_Success;    
    } break;
    case GLFW_RELEASE: {
      *target = Ring3_MouseButtonAction_Release;
      return Ring1_Result_Success;    
    } break;
    default:
      Ring1_Status_set(Ring1_Status_NotYetImplemented);
      return Ring1_Result_Failure;
  };
}

Ring3_MouseButtonEvent* Machine_Video_Gl_Input_mapMouseButtonEvent(GLFWwindow* window, int button,
                                                                   int action, int modifiers) {
  Ring2_Integer buttonInternal;
  Ring3_MouseButtonAction actionInternal;
  if (mapButton(button, &buttonInternal) || mapButtonAction(action, &actionInternal)) {
    Ring2_jump();
  }
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Ring3_MouseButtonEvent* event
      = Ring3_MouseButtonEvent_create(buttonInternal, actionInternal, x, y);
  return event;
}
