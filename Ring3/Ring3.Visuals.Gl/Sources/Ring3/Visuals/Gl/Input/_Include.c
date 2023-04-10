#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/Input/_Include.h"

#include "Ring3/Visuals/Gl/Input/Keyboard.h"
#include "Ring3/Visuals/Gl/Input/MouseButton.h"
#include "Ring3/Visuals/Gl/Input/MousePointer.h"

#include "Ring3/Visuals/Gl/Canvas.package.h"
#undef RING3_VISUALS_GL_PRIVATE


static const bool g_verbose = false;
static size_t g_referenceCount = 0;


void
Ring3_Visuals_Gl_Glfw_startupInput
  (
  )
{
  if (0 == g_referenceCount) {
    while (glfwGetError(NULL)) {
    }
    glfwSetKeyCallback(Ring3_Visuals_Gl_Glfw_getWindow(), Ring3_Visuals_Gl_Glfw_keyCallback);
    if (glfwGetError(NULL)) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    glfwSetMouseButtonCallback(Ring3_Visuals_Gl_Glfw_getWindow(), Ring3_Visuals_Gl_Glfw_mouseButtonCallback);
    if (glfwGetError(NULL)) {
      glfwSetKeyCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    glfwSetCursorPosCallback(Ring3_Visuals_Gl_Glfw_getWindow(), Ring3_Visuals_Gl_Glfw_cursorPositionCallback);
    if (glfwGetError(NULL)) {
      glfwSetMouseButtonCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
      glfwSetKeyCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    glfwSetCursorEnterCallback(Ring3_Visuals_Gl_Glfw_getWindow(), Ring3_Visuals_Gl_Glfw_cursorEnterCallback);
    if (glfwGetError(NULL)) {
      glfwSetCursorPosCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
      glfwSetMouseButtonCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
      glfwSetKeyCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    g_referenceCount++;
  }
}

void
Ring3_Visuals_Gl_Glfw_shutdownInput
  (
  )
{
  if (0 == --g_referenceCount) {
    glfwSetCursorEnterCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
    glfwSetCursorPosCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
    glfwSetMouseButtonCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
    glfwSetKeyCallback(Ring3_Visuals_Gl_Glfw_getWindow(), NULL);
  }
}

void
Ring3_Visuals_Gl_Glfw_pollEvents
  (
  )
{
  glfwPollEvents();
  if (Ring1_Status_get() != Ring1_Status_Success) {
    Ring2_jump();
  }
}
