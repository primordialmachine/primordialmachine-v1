#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/Canvas.package.h"
#undef RING3_VISUALS_GL_PRIVATE

#include <stdio.h>


static size_t g_referenceCount = 0;
static GLFWwindow* g_window = NULL;

void
Ring3_Visuals_Gl_Glfw_startupCanvas
  (
  )
{
  if (g_referenceCount == 0) {
    if (!glfwInit()) {
      fprintf(stderr, "%s:%d: glfwInit() failed\n", __FILE__, __LINE__);
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    g_window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!g_window) {
      fprintf(stderr, "%s:%d: glfwCreateWindow() failed\n", __FILE__, __LINE__);
      glfwTerminate();
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }

    glfwMakeContextCurrent(g_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      fprintf(stderr, "%s:%d: gladLoadGLLoader() failed\n", __FILE__, __LINE__);
      glfwMakeContextCurrent(NULL);
      glfwDestroyWindow(g_window);
      g_window = NULL;
      glfwTerminate();
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }

    fprintf(stdout, "OpenGL vendor:   %s\n", glGetString(GL_VENDOR));
    fprintf(stdout, "OpenGL renderer: %s\n", glGetString(GL_RENDERER));
  }
  g_referenceCount++;
}

void
Ring3_Visuals_Gl_Glfw_shutdownCanvas
  (
  )
{
  if (0 == --g_referenceCount) {
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(g_window);
    g_window = NULL;
    glfwTerminate();
  }
}

Ring1_NoDiscardReturn() GLFWwindow*
Ring3_Visuals_Gl_Glfw_getWindow
  (
  )
{ return g_window; }
