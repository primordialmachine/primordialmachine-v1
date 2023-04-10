/// @file Video/Gl/CanvasUtilities.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/CanvasUtilities.h"

#include "Video/Gl/Input/Keyboard.h"
#include "Video/Gl/Input/MouseButton.h"
#include "Video/Gl/Input/MousePointer.h"
#include "Video/Gl/UtilitiesGl.h"
#undef MACHINE_VIDEO_GL_PRIVATE


#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include <stdio.h>
#include "Ring3/Input/_Include.h"


#define VERBOSE (0)

static size_t g_referenceCount = 0;
static Ring2_Collections_List* g_events = NULL;

static void
keyCallback
  (
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int modifiers
  )
{
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring3_KeyboardKeyEvent* event = Machine_Video_Gl_Input_mapKeyboardKeyEvent(window,
                                                                               key,
                                                                               scancode,
                                                                               action,
                                                                               modifiers);
    Ring3_Canvas_addKeyboardKeyEvent((Ring3_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
      Ring2_String* zeroTerminatorString = Ring2_String_create("", 1);
      Ring2_String* eventString = Machine_Object_toString((Machine_Object*)event);
      eventString = Ring2_String_concatenate(eventString, zeroTerminatorString);
      Ring2_log(Ring2_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Ring2_String_getBytes(eventString));
#endif
    if (event->key == Ring3_KeyboardKey_Escape && action == Ring3_KeyboardKeyAction_Press)
      glfwSetWindowShouldClose(window, GLFW_TRUE);

    Ring2_popJumpTarget();
  } else {
    if (Ring1_Status_get() == Ring1_Status_NotYetImplemented) {
      Ring2_log(Ring2_LogFlags_ToErrors, __FILE__, __LINE__,
                "failed to map keyboard key event\n");
      Ring1_Status_set(Ring1_Status_Success);
    }
    Ring2_popJumpTarget();
  }
}

static void
cursorPositionCallback
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
    Ring3_MousePointerEvent* event = Machine_Video_Gl_Input_mapMousePointerMoveEvent(window,
                                                                                     x,
                                                                                     y);
    Ring3_Canvas_addMousePointerEvent((Ring3_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
      Ring2_String* zeroTerminatorString = Ring2_String_create("", 1);
      Ring2_String* eventString = Machine_Object_toString((Machine_Object*)event);
      eventString = Ring2_String_concatenate(eventString, zeroTerminatorString);
      Ring2_log(Ring2_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Ring2_String_getBytes(eventString));
#endif
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

static void 
cursorEnterCallback
  (
    GLFWwindow* window,
    int entered
  )
{
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Ring3_MousePointerEvent* event = Machine_Video_Gl_Input_mapMousePointerEnterExitEvent(window,
                                                                                          entered);
    Ring3_Canvas_addMousePointerEvent((Ring3_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
      Ring2_String* zeroTerminatorString = Ring2_String_create("", 1);
      Ring2_String* eventString = Machine_Object_toString((Machine_Object*)event);
      eventString = Ring2_String_concatenate(eventString, zeroTerminatorString);
      Ring2_log(Ring2_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Ring2_String_getBytes(eventString));
#endif
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

static void
mouseButtonCallback
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
    Ring3_MouseButtonEvent* event = Machine_Video_Gl_Input_mapMouseButtonEvent(window,
                                                                               button,
                                                                               action,
                                                                               modifiers);
    Ring3_Canvas_addMouseButtonEvent((Ring3_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
      Ring2_String* zeroTerminatorString = Ring2_String_create("", 1);
      Ring2_String* eventString = Machine_Object_toString((Machine_Object*)event);
      eventString = Ring2_String_concatenate(eventString, zeroTerminatorString);
      Ring2_log(Ring2_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Ring2_String_getBytes(eventString));
#endif
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

void
Machine_Glfw_startupCanvasInput
  (
  )
{
  if (0 == g_referenceCount) {
    glfwSetKeyCallback(Machine_Glfw_getWindow(), keyCallback);
    glfwSetMouseButtonCallback(Machine_Glfw_getWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(Machine_Glfw_getWindow(), cursorPositionCallback);
    glfwSetCursorEnterCallback(Machine_Glfw_getWindow(), cursorEnterCallback);
    Ring2_JumpTarget jumpTarget;
    Ring2_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      g_events = (Ring2_Collections_List*)Ring2_Collections_ArrayList_create();
      Ring2_Gc_lock(g_events);
      Ring2_popJumpTarget();
    } else {
      Ring2_popJumpTarget();
      Ring2_jump();
    }
    g_referenceCount++;
  }
}

void
Machine_Glfw_shutdownCanvasInput
  (
  )
{
  if (0 == --g_referenceCount) {
    Ring2_Gc_unlock(g_events);
    g_events = NULL;
  }
}

void
Machine_Glfw_pollEvents
  (
  )
{
  glfwPollEvents();
  if (Ring1_Status_get() != Ring1_Status_Success) {
    Ring2_jump();
  }
}
