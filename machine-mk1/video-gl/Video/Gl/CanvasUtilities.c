/// @file Video/Gl/CanvasUtilities.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/CanvasUtilities.h"

#include "Video/Gl/Input/Keyboard.h"
#include "Video/Gl/Input/MouseButton.h"
#include "Video/Gl/Input/MousePointer.h"
#include "Video/Gl/UtilitiesGl.h"
#include "_Collections.h"
#include "_Input.h"

#define VERBOSE (0)

static size_t g_referenceCount = 0;
static Machine_List* g_events = NULL;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_KeyboardKeyEvent* event
        = Machine_Video_Gl_Input_mapKeyboardKeyEvent(window, key, scancode, action, modifiers);
    Machine_Video_Canvas_addKeyboardKeyEvent((Machine_Video_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
    Machine_String* zeroTerminatorString = Ring2_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
#endif
    if (event->key == Machine_KeyboardKeys_Escape && action == Machine_KeyboardKeyActions_Press)
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

static void cursorPositionCallback(GLFWwindow* window, double x, double y) {
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MousePointerEvent* event
        = Machine_Video_Gl_Input_mapMousePointerMoveEvent(window, x, y);
    Machine_Video_Canvas_addMousePointerEvent((Machine_Video_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
    Machine_String* zeroTerminatorString = Ring2_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
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

static void cursorEnterCallback(GLFWwindow* window, int entered) {
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MousePointerEvent* event
        = Machine_Video_Gl_Input_mapMousePointerEnterExitEvent(window, entered);
    Machine_Video_Canvas_addMousePointerEvent((Machine_Video_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
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

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
  Machine_Video_Gl_Canvas* canvas = glfwGetWindowUserPointer(window);
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MouseButtonEvent* event
        = Machine_Video_Gl_Input_mapMouseButtonEvent(window, button, action, modifiers);
    Machine_Video_Canvas_addMouseButtonEvent((Machine_Video_Canvas*)canvas, event);
#if defined(VERBOSE) && 1 == VERBOSE
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
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

void Machine_Glfw_startupCanvasInput() {
  if (0 == g_referenceCount) {
    glfwSetKeyCallback(Machine_Glfw_getWindow(), keyCallback);
    glfwSetMouseButtonCallback(Machine_Glfw_getWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(Machine_Glfw_getWindow(), cursorPositionCallback);
    glfwSetCursorEnterCallback(Machine_Glfw_getWindow(), cursorEnterCallback);
    Ring2_JumpTarget jumpTarget;
    Ring2_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      g_events = (Machine_List*)Machine_ArrayList_create();
      Ring2_Gc_lock(g_events);
      Ring2_popJumpTarget();
    } else {
      Ring2_popJumpTarget();
      Ring2_jump();
    }
    g_referenceCount++;
  }
}

void Machine_Glfw_shutdownCanvasInput() {
  if (0 == --g_referenceCount) {
    Ring2_Gc_unlock(g_events);
    g_events = NULL;
  }
}

void Machine_Glfw_pollEvents() {
  glfwPollEvents();
  if (Ring1_Status_get() != Ring1_Status_Success) {
    Ring2_jump();
  }
}
