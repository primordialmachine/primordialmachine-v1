/// @file Video/Gl/Input/Keyboard.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Input/Keyboard.h"
#undef MACHINE_VIDEO_GL_PRIVATE


static Ring1_Result mapKey(int source, Ring3_KeyboardKey* target) {
  switch (source) {
#define MAP(FROM, TO)                                                                             \
  case GLFW_KEY_##FROM: {                                                                         \
    *target = Ring3_KeyboardKey_##TO;                                                             \
    return Ring1_Result_Success;                                                                  \
  } break;

    MAP(ESCAPE, Escape)

    MAP(F1, F1)
    MAP(F2, F2)
    MAP(F3, F3)
    MAP(F4, F4)
    MAP(F5, F5)
    MAP(F6, F6)
    MAP(F7, F7)
    MAP(F8, F8)
    MAP(F9, F9)
    MAP(F10, F10)
    MAP(F11, F11)
    MAP(F12, F12)

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
      Ring1_Status_set(Ring1_Status_NotYetImplemented);
      return Ring1_Result_Failure;
  };
}

static Ring1_Result mapKeyAction(int source, Ring3_KeyboardKeyAction* target) {
  switch (source) {
    case GLFW_PRESS: {
      *target = Ring3_KeyboardKeyAction_Press;
      return Ring1_Result_Success;
    } break;
    case GLFW_RELEASE: {
      *target = Ring3_KeyboardKeyAction_Release;
      return Ring1_Result_Success;
    } break;
    case GLFW_REPEAT: {
      *target = Ring3_KeyboardKeyAction_Repeat;
      return Ring1_Result_Success;
    } break;
    default:
      Ring1_Status_set(Ring1_Status_NotYetImplemented);
      return Ring1_Result_Failure;
  };
}

Ring3_KeyboardKeyEvent* Machine_Video_Gl_Input_mapKeyboardKeyEvent(GLFWwindow* window, int key,
                                                                   int scancode, int action,
                                                                   int modifiers) {
  Ring3_KeyboardKey keyInternal;
  Ring3_KeyboardKeyAction actionInternal;
  if (mapKey(key, &keyInternal) || mapKeyAction(action, &actionInternal)) {
    Ring2_jump();
  }
  Ring3_KeyboardKeyEvent* event = Ring3_KeyboardKeyEvent_create(keyInternal, actionInternal);
  return event;
}
