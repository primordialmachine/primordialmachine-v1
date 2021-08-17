#include "./../GL/Canvas.h"
#include "_Images.h"
#include "_Video.h"
#include <malloc.h>

static size_t g_referenceCount = 0;
static GLFWwindow* g_window = NULL;

void Machine_GLFW_startupCanvas() {
  if (g_referenceCount == 0) {
    if (!glfwInit()) {
      fprintf(stderr, "%s:%d: glfwInit() failed\n", __FILE__, __LINE__);
      Machine_setStatus(Machine_Status_EnvironmentFailed);
      Machine_jump();
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    g_window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!g_window) {
      fprintf(stderr, "%s:%d: glfwCreateWindow() failed\n", __FILE__, __LINE__);
      glfwTerminate();
      Machine_setStatus(Machine_Status_EnvironmentFailed);
      Machine_jump();
    }

    glfwMakeContextCurrent(g_window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      fprintf(stderr, "%s:%d: gladLoadGLLoader() failed\n", __FILE__, __LINE__);
      glfwMakeContextCurrent(NULL);
      glfwDestroyWindow(g_window);
      g_window = NULL;
      glfwTerminate();
      Machine_setStatus(Machine_Status_EnvironmentFailed);
      Machine_jump();
    }
  }
  g_referenceCount++;
}

void Machine_GLFW_shutdownCanvas() {
  if (0 == --g_referenceCount) {
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(g_window);
    g_window = NULL;
    glfwTerminate();
  }
}

GLFWwindow* Machine_GLFW_getWindow() {
  return g_window;
}

void Machine_GLFW_maximizeCanvas() {
  glfwMaximizeWindow(Machine_GLFW_getWindow());
}

void Machine_GLFW_getFrameBufferSize(Machine_Integer* width, Machine_Integer* height) {
  int w, h;
  glfwGetFramebufferSize(Machine_GLFW_getWindow(), &w, &h);
  *width = w;
  *height = h;
}

void Machine_GLFW_swapBuffers() {
  glfwSwapBuffers(Machine_GLFW_getWindow());
}

void Machine_GLFW_setCanvasIcons(Machine_List* images) {
  GLFWimage* targetImages = NULL;

  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    size_t numberOfImages = Machine_Collection_getSize((Machine_Collection*)images);
    targetImages = malloc(numberOfImages * sizeof(GLFWimage));
    if (!targetImages) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    for (size_t i = 0, n = numberOfImages; i < n; ++i) {
      Machine_Value temporary = Machine_List_getAt(images, i);
      Machine_Image* image = (Machine_Image*)Machine_Value_getObject(&temporary);
      Machine_Integer w, h;
      void const* p;
      Machine_Image_getSize(image, &w, &h);
      p = Machine_Image_getPixels(image);
      targetImages[i].width = w;
      targetImages[i].height = h;
      targetImages[i].pixels = p;
    }
    glfwSetWindowIcon(g_window, numberOfImages, targetImages);
    if (targetImages) {
      free(targetImages);
      targetImages = NULL;
    }
    Machine_popJumpTarget();
  }
  else {
    if (targetImages) {
      free(targetImages);
      targetImages = NULL;
    }
    Machine_popJumpTarget();
    Machine_jump();
  }
}
