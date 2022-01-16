/// @file Video/Gl/Canvas.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/Canvas.h"

#include "Video/Gl/CanvasUtilities.h"
#include <stdio.h>

#include "Video/Gl/Amd/PowerExpress.i"
#include "Video/Gl/Nvidia/Optimus.i"

static size_t g_referenceCount = 0;
static GLFWwindow* g_window = NULL;

/// @brief Startup canvas.
/// An undefined-op if the canvas is already started.
void Machine_Glfw_startupCanvas();

/// @brief Shutdown canvas.
/// An undefined-op if the canvas is not yet started.
void Machine_Glfw_shutdownCanvas();

void Machine_Glfw_startupCanvas() {
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

void Machine_Glfw_shutdownCanvas() {
  if (0 == --g_referenceCount) {
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(g_window);
    g_window = NULL;
    glfwTerminate();
  }
}

GLFWwindow* Machine_Glfw_getWindow() {
  return g_window;
}

static void Machine_Video_Gl_Canvas_getFrameBuffersSize(Machine_Video_Gl_Canvas* self,
                                                        Machine_Integer* width,
                                                        Machine_Integer* height) {
  int w, h;
  glfwGetFramebufferSize(Machine_Glfw_getWindow(), &w, &h);
  *width = w;
  *height = h;
}

static void Machine_Video_Gl_Canvas_maximizeCanvas(Machine_Video_Gl_Canvas* self) {
  glfwMaximizeWindow(Machine_Glfw_getWindow());
}

static void Machine_Video_Gl_Canvas_swapFrameBuffers(Machine_Video_Gl_Canvas* self) {
  glfwSwapBuffers(Machine_Glfw_getWindow());
}

static void Machine_Video_Gl_Canvas_setCanvasIcons(Machine_Video_Gl_Canvas* self,
                                                   Machine_List* images) {
  GLFWimage* targetImages = NULL;

  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    size_t numberOfImages = Machine_Collection_getSize((Machine_Collection*)images);
    targetImages = Machine_Eal_Memory_allocateArray(sizeof(GLFWimage), numberOfImages);
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
      Machine_Eal_Memory_deallocate(targetImages);
      targetImages = NULL;
    }
    Machine_popJumpTarget();
  } else {
    if (targetImages) {
      Machine_Eal_Memory_deallocate(targetImages);
      targetImages = NULL;
    }
    Machine_popJumpTarget();
    Machine_jump();
  }
}

static void Machine_Video_Gl_Canvas_pollEvents(Machine_Video_Gl_Canvas* self) {
  Machine_Glfw_pollEvents();
}

static Machine_Boolean Machine_Video_Gl_Canvas_getQuitRequested(Machine_Video_Gl_Canvas* self) {
  return glfwWindowShouldClose(Machine_Glfw_getWindow());
}

static void Machine_Video_Gl_Canvas_destruct(Machine_Video_Gl_Canvas* self) {
  Machine_Glfw_shutdownCanvasInput();
  Machine_Glfw_shutdownCanvas();
}

static void Machine_Video_Gl_Canvas_constructClass(Machine_Video_Gl_Canvas_Class* self) {
  ((Machine_Video_Canvas_Class*)self)->getFrameBuffersSize = (void (*)(Machine_Video_Canvas*, Machine_Integer *,Machine_Integer *))&Machine_Video_Gl_Canvas_getFrameBuffersSize;
  ((Machine_Video_Canvas_Class*)self)->maximizeCanvas = (void (*)(Machine_Video_Canvas*)) &Machine_Video_Gl_Canvas_maximizeCanvas;
  ((Machine_Video_Canvas_Class*)self)->swapFrameBuffers = (void (*)(Machine_Video_Canvas*)) &Machine_Video_Gl_Canvas_swapFrameBuffers;
  ((Machine_Video_Canvas_Class*)self)->setCanvasIcons = (void (*)(Machine_Video_Canvas*, Machine_List *)) &Machine_Video_Gl_Canvas_setCanvasIcons;
  ((Machine_Video_Canvas_Class*)self)->pollEvents = (void (*)(Machine_Video_Canvas*)) & Machine_Video_Gl_Canvas_pollEvents;
  ((Machine_Video_Canvas_Class*)self)->getQuitRequested = (Machine_Boolean(*)(Machine_Video_Canvas*)) & Machine_Video_Gl_Canvas_getQuitRequested;
}

void Machine_Video_Gl_Canvas_construct(Machine_Video_Gl_Canvas* self, size_t numberOfArguments, Machine_Value const* arguments) {
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Video_Canvas_construct((Machine_Video_Canvas*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Machine_Glfw_startupCanvas();
  Machine_Glfw_startupCanvasInput();
  Machine_setClassType((Machine_Object*)self, Machine_Video_Gl_Canvas_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Video_Gl_Canvas, Machine_Video_Canvas, NULL,
                         &Machine_Video_Gl_Canvas_construct, &Machine_Video_Gl_Canvas_destruct,
                         &Machine_Video_Gl_Canvas_constructClass, NULL)

Machine_Video_Gl_Canvas* Machine_Video_Gl_Canvas_create() {
  Machine_ClassType* ty = Machine_Video_Gl_Canvas_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { Machine_Value_StaticInitializerVoid() };
  Machine_Video_Gl_Canvas* self = (Machine_Video_Gl_Canvas*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}