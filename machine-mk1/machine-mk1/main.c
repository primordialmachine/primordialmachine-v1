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

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <linmath.h>

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

    Scene* scene = Scene1_create();
    if (!scene) {
      fprintf(stderr, "%s:%d: Scene1_create() failed\n", __FILE__, __LINE__);
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }
    if (Scene_startup(scene)) {
      fprintf(stderr, "%s:%d: Scene_startup() failed\n", __FILE__, __LINE__);
      Scene_destroy(scene);
      glfwDestroyWindow(window);
      glfwTerminate();
      return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window))
    {
      int width, height;
      glfwGetFramebufferSize(window, &width, &height);
      if (Scene_update(scene, (float)width, (float)height)) {
        fprintf(stderr, "%s:%d: scene1_startup() failed\n", __FILE__, __LINE__);
        Scene_shutdown(scene);
        Scene_destroy(scene);
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
      }

      glfwSwapBuffers(window);
      glfwPollEvents();
    }

    Scene_shutdown(scene);
    Scene_destroy(scene);
    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
  }

#if defined(__cplusplus)
}
#endif
