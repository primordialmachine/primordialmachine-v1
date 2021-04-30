/**
 * @author Michael Heilmann (<michaelheilmann@primordialmachine.com>)
 * @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
 */
#if defined(__cplusplus)
extern "C" {
#endif



#include <stdlib.h>
#include <stdio.h>

#include <Windows.h>

#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Video.h"
#include "Fonts.h"
#include "Images.h"
#include "Machine.h"

#include "UtilitiesGL.h"

#include <linmath.h>



  static int loadIcons(GLFWwindow* window) {
    static const char* PATHS[] = {
      "primordialmachine-16x16.png",
      "primordialmachine-24x24.png",
      "primordialmachine-32x32.png",
      "primordialmachine-64x64.png",
      "primordialmachine-110x110.png",
      "primordialmachine-114x114.png",
      "primordialmachine-135x135.png",
    };
  #define N (sizeof(PATHS) / sizeof(const char*))
    Machine_Images_Image* IMAGES[N] = { NULL };
    size_t i;

    i = 0;
    for (; i < N; ++i) {
      if (Machine_Images_createImage(PATHS[i], &IMAGES[i])) {
        while (i > 0) {
          if (IMAGES[i - 1]) {
            IMAGES[i - 1] = NULL;
          }
          i--;
        }
        fprintf(stderr, "%s:%d: Machine_Images_createImage() failed\n", __FILE__, __LINE__);
        return 1;
      }
    }

    GLFWimage images[N];
    i = 0;
    for (; i < N; ++i) {
      int w, h;
      void* p;
      Machine_Images_Image_getSize(IMAGES[i], &w, &h);
      p = Machine_Images_Image_getPixels(IMAGES[i]);
      images[i].width = w;
      images[i].height = h;
      images[i].pixels = p;
    }
    glfwSetWindowIcon(window, N, images);

    i = N;
    while (i > 0) {
      if (IMAGES[i - 1]) {
        IMAGES[i - 1] = NULL;
      }
      i--;
    }
  #undef N
    return 0;
  }

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  int main() {
    if (!glfwInit()) {
      fprintf(stderr, "%s:%d: glfwInit() failed\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
    if (!window) {
      fprintf(stderr, "%s:%d: glfwCreateWindow() failed\n", __FILE__, __LINE__);
      glfwTerminate();
      return EXIT_FAILURE;
    }

    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      fprintf(stderr, "%s:%d: gladLoadGLLoader() failed\n", __FILE__, __LINE__);
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    glfwSwapInterval(1);
    // Enable blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set clear color.
    glClearColor(0.9f, 0.9f, 0.9f, 1.f);

    if (Machine_Video_startup()) {
      fprintf(stderr, "%s:%d: Machine_Video_startup() failed\n", __FILE__, __LINE__);
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    if (Machine_startup()) {
      fprintf(stderr, "%s:%d: Machine_startup() failed\n", __FILE__, __LINE__);
      Machine_Video_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    if (loadIcons(window)) {
      fprintf(stderr, "%s:%d: loadIcons() failed\n", __FILE__, __LINE__);
      Machine_shutdown();
      Machine_Video_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }

    Scene* scene = Scene4_create();
    if (!scene) {
      fprintf(stderr, "%s:%d: Scene1_create() failed\n", __FILE__, __LINE__);
      Machine_shutdown();
      Machine_Video_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    Machine_setRoot(scene, true);

    if (Scene_startup(scene)) {
      fprintf(stderr, "%s:%d: Scene_startup() failed\n", __FILE__, __LINE__);
      Machine_setRoot(scene, false);
      Machine_shutdown();
      Machine_Video_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }

    Machine_update();

    while (!glfwWindowShouldClose(window)) {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      if (Scene_update(scene, (float)width, (float)height)) {
        fprintf(stderr, "%s:%d: Scene_update() failed\n", __FILE__, __LINE__);
        Scene_shutdown(scene);
        Machine_setRoot(scene, false);
        Machine_shutdown();
        Machine_Video_shutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
      }

      Machine_update();
      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    Scene_shutdown(scene);
    Machine_setRoot(scene, false);
    Machine_shutdown();
    Machine_Video_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
  }

#if defined(__cplusplus)
}
#endif
