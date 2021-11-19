#include "Video.h"



#include "_Video_GL.h"



static Machine_VideoContext* g_videoContext = NULL;
static Machine_Video_Canvas* g_videoCanvas = NULL;

static void initCanvas() {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    g_videoCanvas = (Machine_Video_Canvas*)Machine_Video_GL_Canvas_create();
    Machine_lock(g_videoCanvas);
    g_videoContext = (Machine_VideoContext*)Machine_Gl_VideoContext_create();
    Machine_lock(g_videoContext);
    Machine_popJumpTarget();
  } else {
    Machine_popJumpTarget();
    if (g_videoContext) {
      Machine_unlock(g_videoContext);
      g_videoContext = NULL;
    }
    if (g_videoCanvas) {
      Machine_unlock(g_videoCanvas);
      g_videoCanvas = NULL;
    }
    Machine_jump();
  }
}

static void uninitCanvas() {
  if (g_videoContext) {
    Machine_unlock(g_videoContext);
    g_videoContext = NULL;
  }
  if (g_videoCanvas) {
    Machine_unlock(g_videoCanvas);
    g_videoCanvas = NULL;
  }
}

void Machine_Video_startup() {
  initCanvas();
}

void Machine_Video_shutdown() {
  uninitCanvas();
}

Machine_Video_Canvas* Machine_getVideoCanvas() {
  return g_videoCanvas;
}

Machine_VideoContext* Machine_getVideoContext() {
  return g_videoContext;
}

Machine_Real Machine_Video_getTime() {
  return (Machine_Real)glfwGetTime();
}
