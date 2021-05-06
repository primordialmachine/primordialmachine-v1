#include "scene.h"

#include <malloc.h>

void Scene_visit(Scene* self) {}

int Scene_construct(Scene* self) {
  return 0;
}

void Scene_destruct(Scene* self) {}

void Scene_startup(Scene* self) {
  self->startup(self);
}

void Scene_onCanvaSizeChanged(Scene* self, float width, float height) {
  self->onCanvasSizeChanged(self, width, height);
}

void Scene_update(Scene* self, float width, float height) {
  self->update(self, width, height);
}

void Scene_shutdown(Scene* self) {
  self->shutdown(self);
}
