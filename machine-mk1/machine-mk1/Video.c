#include "Video.h"



#include "Video/GL/VideoContext.h"
#include "Video/GL/CanvasInput.h"
#include "Video/GL/ShaderProgram.h"



static Machine_VideoContext* g_videoContext = NULL;

void Machine_Video_startup() {
  Machine_GLFW_startupCanvas();
  {
    Machine_JumpTarget jumpTarget;
    Machine_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      g_videoContext = (Machine_VideoContext *)Machine_GL_VideoContext_create();
      Machine_lock(g_videoContext);
      {
        Machine_GL_VideoContext_write((Machine_GL_VideoContext*)g_videoContext);
      }
      Machine_popJumpTarget();
    } else {
      Machine_popJumpTarget();
      Machine_GLFW_shutdownCanvas();
      Machine_jump();
    }
  }
}

void Machine_Video_shutdown() {
  Machine_unlock(g_videoContext);
  g_videoContext = NULL;
  Machine_GLFW_shutdownCanvas();
}

Machine_VideoContext* Machine_Video_getContext() {
  return g_videoContext;
}

Machine_Real Machine_Video_getTime() {
  return (Machine_Real)glfwGetTime();
}
