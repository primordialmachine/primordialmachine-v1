#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "./../GL/Canvas.h"



#include "CanvasUtilities.h"
#include <malloc.h>



#include "AMD/PowerExpress.i"
#include "NVIDIA/Optimus.i"

static size_t g_referenceCount = 0;
static GLFWwindow* g_window = NULL;

/// @brief Startup canvas.
/// An undefined-op if the canvas is already started.
void Machine_GLFW_startupCanvas();

/// @brief Shutdown canvas.
/// An undefined-op if the canvas is not yet started.
void Machine_GLFW_shutdownCanvas();

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

    fprintf(stdout, "OpenGL vendor:   %s\n", glGetString(GL_VENDOR));
    fprintf(stdout, "OpenGL renderer: %s\n", glGetString(GL_RENDERER));
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

static void Machine_Video_GL_Canvas_getFrameBuffersSize(Machine_Video_GL_Canvas* self, Machine_Integer* width, Machine_Integer* height) {
  int w, h;
  glfwGetFramebufferSize(Machine_GLFW_getWindow(), &w, &h);
  *width = w;
  *height = h;
}

static void Machine_Video_GL_Canvas_maximizeCanvas(Machine_Video_GL_Canvas* self) {
  glfwMaximizeWindow(Machine_GLFW_getWindow());
}

static void Machine_Video_GL_Canvas_swapFrameBuffers(Machine_Video_GL_Canvas* self) {
  glfwSwapBuffers(Machine_GLFW_getWindow());
}

static void Machine_Video_GL_Canvas_setCanvasIcons(Machine_Video_GL_Canvas* self, Machine_List* images) {
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
      targetImages[i].pixels = (unsigned char*)p;
    }
    glfwSetWindowIcon(g_window, numberOfImages, targetImages);
    if (targetImages) {
      free(targetImages);
      targetImages = NULL;
    }
    Machine_popJumpTarget();
  } else {
    if (targetImages) {
      free(targetImages);
      targetImages = NULL;
    }
    Machine_popJumpTarget();
    Machine_jump();
  }
}

static void Machine_Video_GL_Canvas_pollEvents(Machine_Video_GL_Canvas* self) {
  Machine_GLFW_pollEvents();
}

static Machine_Boolean Machine_Video_GL_Canvas_getQuitRequested(Machine_Video_GL_Canvas* self) {
  return glfwWindowShouldClose(Machine_GLFW_getWindow());
}

static void Machine_Video_GL_Canvas_destruct(Machine_Video_GL_Canvas* self) {
  Machine_GLFW_shutdownCanvasInput();
  Machine_GLFW_shutdownCanvas();
}

static void Machine_Video_GL_Canvas_constructClass(Machine_Video_GL_Canvas_Class* self) {
  ((Machine_Video_Canvas_Class*)self)->getFrameBuffersSize = (void (*)(Machine_Video_Canvas*, Machine_Integer *,Machine_Integer *))&Machine_Video_GL_Canvas_getFrameBuffersSize;
  ((Machine_Video_Canvas_Class*)self)->maximizeCanvas = (void (*)(Machine_Video_Canvas*)) &Machine_Video_GL_Canvas_maximizeCanvas;
  ((Machine_Video_Canvas_Class*)self)->swapFrameBuffers = (void (*)(Machine_Video_Canvas*)) &Machine_Video_GL_Canvas_swapFrameBuffers;
  ((Machine_Video_Canvas_Class*)self)->setCanvasIcons = (void (*)(Machine_Video_Canvas*, Machine_List *)) &Machine_Video_GL_Canvas_setCanvasIcons;
  ((Machine_Video_Canvas_Class*)self)->pollEvents = (void (*)(Machine_Video_Canvas*)) & Machine_Video_GL_Canvas_pollEvents;
  ((Machine_Video_Canvas_Class*)self)->getQuitRequested = (Machine_Boolean(*)(Machine_Video_Canvas*)) & Machine_Video_GL_Canvas_getQuitRequested;
}

void Machine_Video_GL_Canvas_construct(Machine_Video_GL_Canvas* self, size_t numberOfArguments, Machine_Value const* arguments) {
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Video_Canvas_construct((Machine_Video_Canvas*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_GLFW_startupCanvas();
  Machine_GLFW_startupCanvasInput();
  Machine_setClassType((Machine_Object*)self, Machine_Video_GL_Canvas_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Video_GL_Canvas, Machine_Video_Canvas, NULL, &Machine_Video_GL_Canvas_construct, &Machine_Video_GL_Canvas_destruct, &Machine_Video_GL_Canvas_constructClass)

Machine_Video_GL_Canvas* Machine_Video_GL_Canvas_create() {
  Machine_ClassType* ty = Machine_Video_GL_Canvas_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Video_GL_Canvas* self = (Machine_Video_GL_Canvas*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
