/// @file Ring3/Visuals/Gl/Input/MouseButton.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/Input/MouseButton.h"

#include "Ring3/Visuals/Gl/Canvas.package.h"
#undef RING3_VISUALS_GL_PRIVATE


static bool const g_verbose = false;


static Ring1_Result
mapAction
  (
    int source,
    Ring3_MouseButtonAction* target
  );

static Ring1_Result
mapButton
  (
    int source,
    Ring2_Integer* target
  );

static Ring3_MouseButtonEvent*
mapEvent
  (
    GLFWwindow* window,
    int button,
    int action,
    int modifiers
  );

static Ring1_Result
mapAction
  (
    int source,
    Ring3_MouseButtonAction* target
  )
{
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

static Ring1_Result
mapButton
  (
    int source,
    Ring2_Integer* target
  )
{
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

static Ring3_MouseButtonEvent*
mapEvent
  (
    GLFWwindow* window,
    int button,
    int action,
    int modifiers
  )
{
  Ring2_Integer buttonInternal;
  Ring3_MouseButtonAction actionInternal;
  if (mapButton(button, &buttonInternal) || mapAction(action, &actionInternal)) {
    Ring2_jump();
  }
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Ring3_MouseButtonEvent* event = Ring3_MouseButtonEvent_create(buttonInternal, actionInternal, x, y);
  return event;
}

void
Ring3_Visuals_Gl_Glfw_mouseButtonCallback
  (
    GLFWwindow* window,
    int button,
    int action,
    int modifiers
  )
{
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring3_MouseButtonEvent* event = mapEvent(window,
                                             button,
                                             action,
                                             modifiers);
    Ring3_Canvas_addMouseButtonEvent(Ring1_cast(Ring3_Canvas*, canvas), event);
    if (g_verbose) {
      Ring2_String* zeroTerminatorString = Ring2_String_create("", 1);
      Ring2_String* eventString = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object*, event));
      eventString = Ring2_String_concatenate(Ring2_Context_get(), eventString, zeroTerminatorString);
      Ring2_log(Ring2_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Ring2_String_getBytes(eventString));
    }
    Ring2_popJumpTarget();
  } else {
    if (Ring1_Status_get() == Ring1_Status_NotYetImplemented) {
      Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
                "failed to map mouse button event\n");
      Ring1_Status_set(Ring1_Status_Success);
    }
    Ring2_popJumpTarget();
  }
}
