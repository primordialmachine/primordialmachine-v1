/// @file Ring3/Video/Gl/Input/MousePointer.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/Input/MousePointer.h"

#include "Ring3/Visuals/Gl/Canvas.package.h"
#undef RING3_VISUALS_GL_PRIVATE


static bool const g_verbose = false;


static Ring3_MousePointerEvent*
mapEnterEvent
  (
    GLFWwindow* window,
    int entered
  );

static Ring3_MousePointerEvent*
mapMoveEvent
  (
    GLFWwindow* window,
    double x,
    double y
  );

static Ring3_MousePointerEvent*
mapEnterEvent
  (
    GLFWwindow* window,
    int entered
  )
{
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  Ring3_MousePointerAction actionInternal;
  actionInternal = entered ? Ring3_MousePointerAction_Enter : Ring3_MousePointerAction_Exit;
  Ring3_MousePointerEvent* event = Ring3_MousePointerEvent_create(actionInternal, x, y);
  return event;
}

static Ring3_MousePointerEvent*
mapMoveEvent
  (
    GLFWwindow* window,
    double x,
    double y
  )
{
  Ring3_MousePointerAction actionInternal;
  actionInternal = Ring3_MousePointerAction_Move;
  Ring3_MousePointerEvent* event = Ring3_MousePointerEvent_create(actionInternal, x, y);
  return event;
}

void
Ring3_Visuals_Gl_Glfw_cursorEnterCallback
  (
    GLFWwindow* window,
    int entered
  )
{
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring3_MousePointerEvent* event = mapEnterEvent(window,
                                                   entered);
    Ring3_Canvas_addMousePointerEvent(Ring1_cast(Ring3_Canvas*, canvas), event);
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
                "failed to map mouse pointer event\n");
      Ring1_Status_set(Ring1_Status_Success);
    }
    Ring2_popJumpTarget();
  }
}

void
Ring3_Visuals_Gl_Glfw_cursorPositionCallback
  (
    GLFWwindow* window,
    double x,
    double y
  )
{
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring3_MousePointerEvent* event = mapMoveEvent(window,
                                                  x,
                                                  y);
    Ring3_Canvas_addMousePointerEvent((Ring3_Canvas*)canvas, event);
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
                "failed to map mouse pointer event\n");
      Ring1_Status_set(Ring1_Status_Success);
    }
    Ring2_popJumpTarget();
  }
}
