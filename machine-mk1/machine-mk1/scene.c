#include "scene.h"

int Scene_startup(Scene* scene) {
  return scene->startup(scene);
}

int Scene_update(Scene* scene, float width, float height) {
  return scene->update(scene, width, height);
}

void Scene_shutdown(Scene* scene) {
  scene->shutdown(scene);
}

void Scene_destroy(Scene* scene) {
  free(scene);
}
