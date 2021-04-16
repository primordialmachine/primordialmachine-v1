#include "scene.h"

#include <malloc.h>

void Scene_visit(Scene* self) {}

int Scene_construct(Scene* self) {
  return 0;
}

void Scene_destruct(Scene* self) {}

int Scene_startup(Scene* scene) {
  return scene->startup(scene);
}

int Scene_update(Scene* scene, float width, float height) {
  return scene->update(scene, width, height);
}

void Scene_shutdown(Scene* scene) {
  scene->shutdown(scene);
}
