/// @file Ring3/Visuals/Gl/Input/Keyboard.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/Input/Keyboard.h"

#include "Ring3/Visuals/Gl/Canvas.package.h"
#undef RING3_VISUALS_GL_PRIVATE


static bool const g_verbose = false;


static Ring1_Result
mapAction
  (
    int source,
    Ring3_KeyboardKeyAction* target
  );

static Ring3_KeyboardKeyEvent*
mapEvent
  (
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int modifiers
  );

static Ring1_Result
mapKey
  (
    int source,
    Ring3_KeyboardKey* target
  );

static Ring1_Result
mapAction
  (
    int source,
    Ring3_KeyboardKeyAction* target
  )
{
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

static Ring3_KeyboardKeyEvent*
mapEvent
  (
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int modifiers
  )
{
  Ring3_KeyboardKey keyInternal;
  Ring3_KeyboardKeyAction actionInternal;
  if (mapKey(key, &keyInternal) || mapAction(action, &actionInternal)) {
    Ring2_jump();
  }
  Ring3_KeyboardKeyEvent* event = Ring3_KeyboardKeyEvent_create(keyInternal, actionInternal);
  return event;
}

static Ring1_Result
mapKey
  (
    int source,
    Ring3_KeyboardKey* target
  )
{
  switch (source) {
#define Define(from, to)                                                                          \
  case GLFW_KEY_##from: {                                                                         \
    *target = Ring3_KeyboardKey_##to;                                                             \
    return Ring1_Result_Success;                                                                  \
  } break;

    Define(ESCAPE, Escape)

    Define(F1, F1)
    Define(F2, F2)
    Define(F3, F3)
    Define(F4, F4)
    Define(F5, F5)
    Define(F6, F6)
    Define(F7, F7)
    Define(F8, F8)
    Define(F9, F9)
    Define(F10, F10)
    Define(F11, F11)
    Define(F12, F12)

    Define(0, 0)
    Define(1, 1)
    Define(2, 2)
    Define(3, 3)
    Define(4, 4)
    Define(5, 5)
    Define(6, 6)
    Define(7, 7)
    Define(8, 8)
    Define(9, 9)

    Define(A, A)
    Define(B, B)
    Define(C, C)
    Define(D, D)

    Define(E, E)
    Define(F, F)
    Define(G, G)
    Define(H, H)

    Define(I, I)
    Define(J, J)
    Define(K, K)
    Define(L, L)

    Define(M, M)
    Define(N, N)
    Define(O, O)
    Define(P, P)

    Define(Q, Q)
    Define(R, R)
    Define(S, S)
    Define(T, T)

    Define(U, U)
    Define(V, V)
    Define(W, W)
    Define(X, X)

    Define(Y, Y)
    Define(Z, Z)

    default:
      Ring1_Status_set(Ring1_Status_NotYetImplemented);
      return Ring1_Result_Failure;
  };
}

void
Ring3_Visuals_Gl_Glfw_keyCallback
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
    Ring3_KeyboardKeyEvent* event = mapEvent(window,
                                             key,
                                             scancode,
                                             action,
                                             modifiers);
    Ring3_Canvas_addKeyboardKeyEvent(Ring1_cast(Ring3_Canvas*,canvas), event);
    if (g_verbose) {
      Ring2_String* zeroTerminatorString = Ring2_String_create("", 1);
      Ring2_String* eventString = Machine_Object_toString(Ring2_Context_get(), Ring1_cast(Machine_Object*, event));
      eventString = Ring2_String_concatenate(Ring2_Context_get(), eventString, zeroTerminatorString);
      Ring2_log(Ring2_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n",
                Ring2_String_getBytes(eventString));
    }
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
