/// @file Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Video/GL/UtilitiesGL.h"
#include "Video/GL/CanvasInput.h"

#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scenes/LayoutScene.h"
#include "Scenes/Rectangle2Scene.h"
#include "Video.h"
#include "_Fonts.h"
#include "_Images.h"
#include "_Collections.h"
#include "_Runtime.h"

  static Scene* g_scene = NULL;

  static void loadIcons() {
    static const char* PATHS[] = {
    #define WINDOWS10_BLURRYICONHACK (1)
    #if WINDOWS10_BLURRYICONHACK == 0
      "primordialmachine-16x16.png",
      "primordialmachine-20x20.png",
    #endif
      "primordialmachine-24x24.png",
      "primordialmachine-32x32.png",
      "primordialmachine-40x40.png",
      "primordialmachine-48x48.png",
      "primordialmachine-64x64.png",
      "primordialmachine-96x96.png",
      "primordialmachine-110x110.png",
      "primordialmachine-114x114.png",
      "primordialmachine-135x135.png",
      "primordialmachine-140x140.png",
      "primordialmachine-180x180.png",
      "primordialmachine-256x256.png",
    };
    Machine_List* vals = Machine_List_create();
    for (size_t i = 0, n = (sizeof(PATHS) / sizeof(const char*)); i < n; ++i) {
      Machine_Image* image = Machine_ImagesContext_createFromPath(Machines_DefaultImages_createContext(), Machine_String_create(PATHS[i], strlen(PATHS[i])));
      Machine_Value val;
      Machine_Value_setObject(&val, (Machine_Object *)image);
      Machine_List_append(vals, val);
    }
    Machine_GLFW_setCanvasIcons(vals);
  }

  static void run(Scene* scene, GLFWwindow* window) {
    Machine_Integer oldWidth, oldHeight;
    Machine_GLFW_getFrameBufferSize(&oldWidth, &oldHeight);

    while (!glfwWindowShouldClose(window)) {
      Machine_Integer newWidth, newHeight;
      Machine_GLFW_getFrameBufferSize(&newWidth, &newHeight);
      if (oldWidth != newWidth || oldHeight != newHeight) {
        Scene_onCanvasSizeChanged(scene, Machine_CanvasSizeChangedEvent_create((float)newWidth, (float)newHeight));
        oldWidth = newWidth;
        oldHeight = newHeight;
      }
      Scene_onUpdate(scene, (float)oldWidth, (float)oldHeight);
      Machine_update();
      Machine_GLFW_swapBuffers();
      Machine_GLFW_pollEvents();
    }
  }

  void main0() {
    Machine_GLFW_maximizeCanvas();
    loadIcons();
    Machine_GLFW_startupCanvasInput();
    Machine_JumpTarget jumpTarget1; // To shutdown input.
    Machine_pushJumpTarget(&jumpTarget1);
    if (!setjmp(jumpTarget1.environment)) {
      g_scene = (Scene*)Scene5_create();
      Scene_onStartup(g_scene);

      Machine_JumpTarget jumpTarget2; // To shutdown scene.
      Machine_pushJumpTarget(&jumpTarget2);
      if (!setjmp(jumpTarget2.environment)) {
        Machine_setRoot(g_scene, true);
        Machine_update();

        Machine_Integer width, height;
        Machine_GLFW_getFrameBufferSize(&width, &height);
        Scene_onCanvasSizeChanged(g_scene, Machine_CanvasSizeChangedEvent_create((float)width, (float)height));

        run(g_scene, Machine_GLFW_getWindow());
        Machine_popJumpTarget();


        Machine_setRoot(g_scene, false);
        Scene* s = g_scene;
        g_scene = NULL;
        Scene_onShutdown(s);
      } else {
        Machine_setRoot(g_scene, false);
        Scene* s = g_scene;
        g_scene = NULL;
        Scene_onShutdown(s);
        Machine_popJumpTarget();
        Machine_jump();
      }
      Machine_GLFW_shutdownCanvasInput();
      Machine_popJumpTarget();
    } else {
      Machine_GLFW_shutdownCanvasInput();
      Machine_popJumpTarget();
      Machine_jump();
    }
  }

  int main1() {
    Machine_JumpTarget jumpTarget1;
    bool videoStartedUp = false;
    Machine_pushJumpTarget(&jumpTarget1);
    if (!setjmp(jumpTarget1.environment)) {
      Machine_Video_startup(); videoStartedUp = true;
      main0();
    }
    Machine_popJumpTarget();
    if (videoStartedUp) {
      Machine_Video_shutdown();
      videoStartedUp = false;
    }
    return Machine_getStatus();
  }

  int main() {
    if (Machine_startup()) {
      fprintf(stderr, "%s:%d: Machine_startup() failed\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
    }
    int status = main1();
    Machine_shutdown();
    return status == Machine_Status_Success ? EXIT_SUCCESS : EXIT_FAILURE;
  }

#if defined(__cplusplus)
}
#endif
