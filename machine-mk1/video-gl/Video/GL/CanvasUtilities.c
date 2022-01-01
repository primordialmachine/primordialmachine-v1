/// @file Video/Gl/CanvasUtilities.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/CanvasUtilities.h"



#include "_Collections.h"
#include "_Input.h"
#include "Video/Gl/UtilitiesGl.h"
#include "Video/Gl/Input/Keyboard.h"
#include "Video/Gl/Input/MousePointer.h"


static size_t g_referenceCount = 0;
static Machine_List* g_events = NULL;

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_KeyboardKeyEvent* event = Machine_Video_Gl_Input_mapKeyboardKeyEvent(window, key, scancode, action, mods);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
    
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
    Machine_MousePointerEvent* event = Machine_Video_Gl_Input_mapMousePointerEvent(window, x, y);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
  }
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    int buttonIndexInternal = -1;
    switch (button) {
    case GLFW_MOUSE_BUTTON_1:
      buttonIndexInternal = 0;
      break;
    case GLFW_MOUSE_BUTTON_2:
      buttonIndexInternal = 1;
      break;
    case GLFW_MOUSE_BUTTON_3:
      buttonIndexInternal = 2;
      break;
    case GLFW_MOUSE_BUTTON_4:
      buttonIndexInternal = 3;
      break;
    case GLFW_MOUSE_BUTTON_5:
      buttonIndexInternal = 4;
      break;
    case GLFW_MOUSE_BUTTON_6:
      buttonIndexInternal = 5;
      break;
    case GLFW_MOUSE_BUTTON_7:
      buttonIndexInternal = 6;
      break;
    case GLFW_MOUSE_BUTTON_8:
      buttonIndexInternal = 7;
      break;
    default:
      MACHINE_ASSERT_UNREACHABLE();
    };
    int buttonActionInternal = Machine_MouseButtonActions_Undetermined;
    switch (action) {
    case GLFW_PRESS:
      buttonActionInternal = Machine_MouseButtonActions_Press;
      break;
    case GLFW_RELEASE:
      buttonActionInternal = Machine_MouseButtonActions_Release;
      break;
    default:
      MACHINE_ASSERT_UNREACHABLE();
    };
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    Machine_MouseButtonEvent* event = Machine_MouseButtonEvent_create(buttonIndexInternal, buttonActionInternal, x, y);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
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
    Machine_JumpTarget jumpTarget;
    Machine_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      g_events = (Machine_List *)Machine_ArrayList_create();
      Machine_Gc_lock(g_events);
      Machine_popJumpTarget();
    }
    else {
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

Machine_Integer Machine_Glfw_getNumberOfEvents();

Machine_Object* Machine_Glfw_peekEvent();

Machine_Object* Machine_Glfw_popEvent();
