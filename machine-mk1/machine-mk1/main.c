/// @file Main.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if defined(__cplusplus)
extern "C" {
#endif



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Video.h"
#include "Fonts.h"
#include "_Images.h"
#include "Machine.h"

  static Scene* g_scene = NULL;

  static void loadIcons(GLFWwindow* window) {
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

  #define N (sizeof(PATHS) / sizeof(const char*))

    Machine_Images_Image* IMAGES[N] = { NULL };
    size_t i;

    Machine_JumpTarget jt;
    Machine_pushJumpTarget(&jt);
    if (!setjmp(jt.environment)) {

      i = 0;
      for (; i < N; ++i) {
        IMAGES[i] = Machine_Images_createImageFromPath(Machine_String_create(PATHS[i], strlen(PATHS[i])));
      }

      GLFWimage images[N];
      for (size_t i = 0, n = N; i < N; ++i) {
        Machine_Integer w, h;
        void* p;
        Machine_Images_Image_getSize(IMAGES[i], &w, &h);
        p = Machine_Images_Image_getPixels(IMAGES[i]);
        images[i].width = w;
        images[i].height = h;
        images[i].pixels = p;
      }
      glfwSetWindowIcon(window, N, images);

      // Cleanup.
      for (size_t i = N; i > 0; --i) {
        if (IMAGES[i - 1]) {
          IMAGES[i - 1] = NULL;
        }
      }
      Machine_popJumpTarget();
    }
    else {
      Machine_popJumpTarget();

      // Cleanup.
      for (size_t i = N; i > 0; --i) {
        if (IMAGES[i - 1]) {
          IMAGES[i - 1] = NULL;
        }
      }
    }

  #undef N

  }

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  static void cursor_position_callback(GLFWwindow* window, double x, double y) {
    Machine_JumpTarget jumpTarget;
    Machine_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      Machine_MousePointerEvent *event = Machine_MousePointerEvent_create(x, y);
      Machine_String* zeroTerminatorString = Machine_String_create("", 1);
      Machine_String* eventString = Machine_Object_toString((Machine_Object*)event);
      eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
      Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
      Machine_popJumpTarget();
    } else {
      Machine_popJumpTarget();
    }
  }

  static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    Machine_JumpTarget jumpTarget;
    Machine_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      int buttonIndexInternal = -1;
      switch (button) {
      case GLFW_MOUSE_BUTTON_1:
        buttonIndexInternal = 0;
        break;
      case GLFW_MOUSE_BUTTON_2:
        buttonIndexInternal = 1;
        break;
      case GLFW_MOUSE_BUTTON_3:
        buttonIndexInternal = 2;
        break;
      case GLFW_MOUSE_BUTTON_4:
        buttonIndexInternal = 3;
        break;
      case GLFW_MOUSE_BUTTON_5:
        buttonIndexInternal = 4;
        break;
      case GLFW_MOUSE_BUTTON_6:
        buttonIndexInternal = 5;
        break;
      case GLFW_MOUSE_BUTTON_7:
        buttonIndexInternal = 6;
        break;
      case GLFW_MOUSE_BUTTON_8:
        buttonIndexInternal = 7;
        break;
      default:
        MACHINE_ASSERT_UNREACHABLE();
      };
      int buttonActionInternal = Machine_MouseButtonActions_Undetermined;
      switch (action) {
      case GLFW_PRESS:
        buttonActionInternal = Machine_MouseButtonActions_Press;
        break;
      case GLFW_RELEASE:
        buttonActionInternal = Machine_MouseButtonActions_Release;
        break;
      default:
        MACHINE_ASSERT_UNREACHABLE();
      };
      double x, y;
      glfwGetCursorPos(window, &x, &y);
      Machine_MouseButtonEvent *event = Machine_MouseButtonEvent_create(buttonIndexInternal, buttonActionInternal, x, y);
      Machine_String* zeroTerminatorString = Machine_String_create("", 1);
      Machine_String* eventString = Machine_Object_toString((Machine_Object *)event);
      eventString = Machine_String_concatenate(eventString, zeroTerminatorString);
      Machine_log(Machine_LogFlags_ToInformations, __FILE__, __LINE__, "%s\n", Machine_String_getBytes(eventString));
      Machine_popJumpTarget();
    }
    else {
      Machine_popJumpTarget();
    }
  }

  static void run(Scene* scene, GLFWwindow* window) {
    int oldWidth, oldHeight;
    glfwGetFramebufferSize(window, &oldWidth, &oldHeight);

    while (!glfwWindowShouldClose(window)) {
      int newWidth, newHeight;
      glfwGetFramebufferSize(window, &newWidth, &newHeight);
      if (oldWidth != newWidth || oldHeight != newHeight) {
        Scene_onCanvasSizeChanged(scene, Machine_CanvasSizeChangedEvent_create((float)newWidth, (float)newHeight));
        oldWidth = newWidth;
        oldHeight = newHeight;
      }
      Scene_onUpdate(scene, (float)oldWidth, (float)oldHeight);
      Machine_update();
      glfwSwapBuffers(window);
      glfwPollEvents();
      if (Machine_getStatus() != Machine_Status_Success) {
        Machine_jump();
      }
    }
  }

  int main0() {
    if (Machine_Video_startup()) {
      fprintf(stderr, "%s:%d: Machine_Video_startup() failed\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
    }
    glfwMaximizeWindow(Machine_Video_getMainWindow());
    {
      Machine_JumpTarget jumpTarget;
      Machine_pushJumpTarget(&jumpTarget);
      if (!setjmp(jumpTarget.environment)) {
        loadIcons(Machine_Video_getMainWindow());
        Machine_popJumpTarget();
      }
      else {
        Machine_popJumpTarget();
        Machine_Video_shutdown();
        return EXIT_FAILURE;
      }
    }
    glfwSetKeyCallback(Machine_Video_getMainWindow(), key_callback);
    glfwSetMouseButtonCallback(Machine_Video_getMainWindow(), mouse_button_callback);
    glfwSetCursorPosCallback(Machine_Video_getMainWindow(), cursor_position_callback);

    Machine_JumpTarget jumpTarget1; // To shutdown video.
    Machine_pushJumpTarget(&jumpTarget1);
    if (!setjmp(jumpTarget1.environment)) {
      g_scene = (Scene*)Scene5_create();
      Scene_onStartup(g_scene);

      Machine_JumpTarget jumpTarget2; // To shutdown scene.
      Machine_pushJumpTarget(&jumpTarget2);
      if (!setjmp(jumpTarget2.environment)) {
        Machine_setRoot(g_scene, true);
        Machine_update();

        int width, height;
        glfwGetFramebufferSize(Machine_Video_getMainWindow(), &width, &height);
        Scene_onCanvasSizeChanged(g_scene, Machine_CanvasSizeChangedEvent_create((float)width, (float)height));

        run(g_scene, Machine_Video_getMainWindow());
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

      Machine_popJumpTarget();
      Machine_Video_shutdown();
      return EXIT_SUCCESS;
    } else {    
      Machine_popJumpTarget();
      Machine_Video_shutdown();
      return EXIT_FAILURE;
    }
  }

  int main() {
    if (Machine_startup()) {
      fprintf(stderr, "%s:%d: Machine_startup() failed\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
    }
    int exitCode = main0();
    Machine_shutdown();
    return exitCode;
  }

#if defined(__cplusplus)
}
#endif
