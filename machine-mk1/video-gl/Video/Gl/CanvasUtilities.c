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

static size_t g_referenceCount = 0;
static Machine_List* g_events = NULL;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_KeyboardKeyEvent* event
        = Machine_Video_Gl_Input_mapKeyboardKeyEvent(window, key, scancode, action, modifiers);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));

    if (event->key == Machine_KeyboardKeys_Escape && action == Machine_KeyboardKeyActions_Press)
      glfwSetWindowShouldClose(window, GLFW_TRUE);

    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
  }
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MousePointerEvent* event
        = Machine_Video_Gl_Input_mapMousePointerMoveEvent(window, x, y);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
  }
}

static void cursorEnterCallback(GLFWwindow* window, int entered) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MousePointerEvent* event
        = Machine_Video_Gl_Input_mapMousePointerEnterExitEvent(window, entered);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
  }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MouseButtonEvent* event
        = Machine_Video_Gl_Input_mapMouseButtonEvent(window, button, action, modifiers);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Machine_String_getBytes(eventString));
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
  }
}

void Machine_Glfw_startupCanvasInput() {
  if (0 == g_referenceCount) {
    glfwSetKeyCallback(Machine_Glfw_getWindow(), keyCallback);
    glfwSetMouseButtonCallback(Machine_Glfw_getWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(Machine_Glfw_getWindow(), cursorPositionCallback);
    glfwSetCursorEnterCallback(Machine_Glfw_getWindow(), cursorEnterCallback);
    Machine_JumpTarget jumpTarget;
    Machine_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      g_events = (Machine_List*)Machine_ArrayList_create();
      Machine_Gc_lock(g_events);
      Machine_popJumpTarget();
    } else {
      Machine_popJumpTarget();
      Machine_jump();
    }
    g_referenceCount++;
  }
}

void Machine_Glfw_shutdownCanvasInput() {
  if (0 == --g_referenceCount) {
    Machine_Gc_unlock(g_events);
    g_events = NULL;
  }
}

void Machine_Glfw_pollEvents() {
  glfwPollEvents();
  if (Machine_getStatus() != Machine_Status_Success) {
    Machine_jump();
  }
}
