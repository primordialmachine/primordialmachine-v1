#include "_Launcher.h"



#include "_Video_Gl.h"



static Machine_VideoContext* g_videoContext = NULL;
static Machine_Video_Canvas* g_videoCanvas = NULL;

static void initCanvas() {
  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    g_videoCanvas = (Machine_Video_Canvas*)Machine_Video_Gl_Canvas_create();
    Ring2_Gc_lock(g_videoCanvas);
    g_videoContext = (Machine_VideoContext*)Machine_Gl_VideoContext_create();
    Ring2_Gc_lock(g_videoContext);
    Ring2_popJumpTarget();
  } else {
    Ring2_popJumpTarget();
    if (g_videoContext) {
      Ring2_Gc_unlock(g_videoContext);
      g_videoContext = NULL;
    }
    if (g_videoCanvas) {
      Ring2_Gc_unlock(g_videoCanvas);
      g_videoCanvas = NULL;
    }
    Ring2_jump();
  }
}

static void uninitCanvas() {
  if (g_videoContext) {
    Ring2_Gc_unlock(g_videoContext);
    g_videoContext = NULL;
  }
  if (g_videoCanvas) {
    Ring2_Gc_unlock(g_videoCanvas);
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