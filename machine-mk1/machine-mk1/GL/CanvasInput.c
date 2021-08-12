#include "./../GL/CanvasInput.h"

#include "_Collections.h"
#include "_Input.h"
#include "./../Video.h"
#include "./../GL/UtilitiesGL.h"

static Machine_List* g_events = NULL;

static bool mapKeyboardKey(int source, Machine_KeyboardKeys* target) {
  switch (source) {
  #define MAP(FROM, TO) \
      case GLFW_KEY_##FROM:  { \
        *target = Machine_KeyboardKeys_##TO; \
        return true; \
      } break;

    MAP(ESCAPE, Escape)

      MAP(0, 0)
      MAP(1, 1)
      MAP(2, 2)
      MAP(3, 3)
      MAP(4, 4)
      MAP(5, 5)
      MAP(6, 6)
      MAP(7, 7)
      MAP(8, 8)
      MAP(9, 9)

      MAP(A, A)
      MAP(B, B)
      MAP(C, C)
      MAP(D, D)

      MAP(E, E)
      MAP(F, F)
      MAP(G, G)
      MAP(H, H)

      MAP(I, I)
      MAP(J, J)
      MAP(K, K)
      MAP(L, L)

      MAP(M, M)
      MAP(N, N)
      MAP(O, O)
      MAP(P, P)

      MAP(Q, Q)
      MAP(R, R)
      MAP(S, S)
      MAP(T, T)

      MAP(U, U)
      MAP(V, V)
      MAP(W, W)
      MAP(X, X)

      MAP(Y, Y)
      MAP(Z, Z)

  default:
    return false;
  };
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Machine_KeyboardKeys keyInternal;
  if (!mapKeyboardKey(key, &keyInternal)) {
    return;
  }
  Machine_KeyboardKeyActions keyActionInternal;
  switch (action) {
  case GLFW_PRESS:
    keyActionInternal = Machine_KeyboardKeyActions_Press;
    break;
  case GLFW_RELEASE:
    keyActionInternal = Machine_KeyboardKeyActions_Release;
    break;
  case GLFW_REPEAT:
    keyActionInternal = Machine_KeyboardKeyActions_Repeat;
    break;
  default:
    return;
  }
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_KeyboardKeyEvent* event = Machine_KeyboardKeyEvent_create(keyInternal, keyActionInternal);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
    Machine_popJumpTarget();
  }
  else {
    Machine_popJumpTarget();
  }
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    Machine_MousePointerEvent* event = Machine_MousePointerEvent_create(x, y);
    Machine_String* zeroTerminatorString = Machine_String_create("", 1);
    Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
    eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
    Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
    Machine_popJumpTarget();
  }
  else {
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

void Machine_GLFW_startupCanvasInput() {
  Machine_GLFW_startupCanvas();
  glfwSetKeyCallback(Machine_GLFW_getWindow(), keyCallback);
  glfwSetMouseButtonCallback(Machine_GLFW_getWindow(), mouseButtonCallback);
  glfwSetCursorPosCallback(Machine_GLFW_getWindow(), cursorPositionCallback);
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    g_events = Machine_List_create();
    Machine_setRoot(g_events, true);
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
    Machine_GLFW_shutdownCanvas();
    Machine_jump();
  }
}

void Machine_GLFW_shutdownCanvasInput() {
  Machine_setRoot(g_events, false);
  g_events = NULL;
  Machine_GLFW_shutdownCanvas();
}

void Machine_GLFW_pollEvents() {
  glfwPollEvents();
  if (Machine_getStatus() != Machine_Status_Success) {
    Machine_jump();
  }
}

Machine_Integer Machine_GLFW_getNumberOfEvents();

Machine_Object* Machine_GLFW_peekEvent();

Machine_Object* Machine_GLFW_popEvent();
