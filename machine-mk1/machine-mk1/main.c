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

#include "scene1.h"
#include "Fonts.h"
#include "Images.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath.h>

#include <ft2build.h>
#include FT_FREETYPE_H

  static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  int main()
  {
    if (!glfwInit()) {
      fprintf(stderr, "%s:%d: glfwInit() failed\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
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

    if (Machine_Fonts_startup()) {
      fprintf(stderr, "%s:%d: Machine_Fonts_startup() failed\n", __FILE__, __LINE__);
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    if (Machine_Images_startup()) {
      fprintf(stderr, "%s:%d: Machine_Images_startup() failed\n", __FILE__, __LINE__);
      Machine_Fonts_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }

    Scene* scene = Scene1_create();
    if (!scene) {
      fprintf(stderr, "%s:%d: Scene1_create() failed\n", __FILE__, __LINE__);
      Machine_Images_shutdown();
      Machine_Fonts_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    if (Scene_startup(scene)) {
      fprintf(stderr, "%s:%d: Scene_startup() failed\n", __FILE__, __LINE__);
      Scene_destroy(scene);
      Machine_Images_shutdown();
      Machine_Fonts_shutdown();
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window))
    {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      if (Scene_update(scene, (float)width, (float)height)) {
        fprintf(stderr, "%s:%d: Scene_update() failed\n", __FILE__, __LINE__);
        Scene_shutdown(scene);
        Scene_destroy(scene);
        Machine_Images_shutdown();
        Machine_Fonts_shutdown();
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    Scene_shutdown(scene);
    Scene_destroy(scene);
    Machine_Images_shutdown();
    Machine_Fonts_shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
  }

#if defined(__cplusplus)
}
#endif
