/// @file Video/Gl/Input/Keyboard.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/Keyboard.h"

static bool mapKey(int source, Machine_KeyboardKeys* target) {
  switch (source) {
#define MAP(FROM, TO)                                                                              \
  case GLFW_KEY_##FROM: {                                                                          \
    *target = Machine_KeyboardKeys_##TO;                                                           \
    return true;                                                                                   \
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

static bool mapKeyAction(int source, Machine_KeyboardKeyActions* target) {
  switch (source) {
    case GLFW_PRESS: {
      *target = Machine_KeyboardKeyActions_Press;
      return true;
    } break;
    case GLFW_RELEASE: {
      *target = Machine_KeyboardKeyActions_Release;
      return true;
    } break;
    case GLFW_REPEAT: {
      *target = Machine_KeyboardKeyActions_Repeat;
      return true;
    } break;
    default:
      return false;
  };
}

Machine_KeyboardKeyEvent* Machine_Video_Gl_Input_mapKeyboardKeyEvent(GLFWwindow* window, int key,
                                                                     int scancode, int action,
                                                                     int modifiers) {
  Machine_KeyboardKeys keyInternal;
  Machine_KeyboardKeyActions actionInternal;
  if (!mapKey(key, &keyInternal) || !mapKeyAction(action, &actionInternal)) {
    Machine_setStatus(Machine_Status_InternalError);
    Machine_jump();
  }
  Machine_KeyboardKeyEvent* event = Machine_KeyboardKeyEvent_create(keyInternal, actionInternal);
  return event;
}
