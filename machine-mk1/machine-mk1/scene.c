#include "scene.h"

#include <malloc.h>

// TODO: Make static.
void Scene_visit(Scene* self) {}

static void onMousePointerEvent(Scene* self, float x, float y);

static void onMouseButtonEvent(Scene* self, float x, float y, int button, int action);

void Scene_construct(Scene* self, size_t numberOfArguments, const Machine_Value *arguments) {
  self->onMouseButtonEvent = &onMouseButtonEvent;
  self->onMousePointerEvent = &onMousePointerEvent;
}

void Scene_destruct(Scene* self) {}

MACHINE_DEFINE_CLASSTYPE(Scene)

Machine_ClassType* Scene_getClassType() {
  if (!g_Scene_ClassType) {
    g_Scene_ClassType =
      Machine_createClassType
      (
        NULL,
        sizeof(Scene),
        (Machine_ClassTypeRemovedCallback*)&Scene_onTypeDestroyed,
        (Machine_ClassObjectVisitCallback*)&Scene_visit,
        (Machine_ClassObjectConstructCallback*)&Scene_construct,
        (Machine_ClassObjectDestructCallback*)NULL
      );
  }
  return g_Scene_ClassType;
}

static void onMousePointerEvent(Scene* self, float x, float y)
{/*Intentionally empty.*/}

static void onMouseButtonEvent(Scene* self, float x, float y, int button, int action)
{/*Intentionally empty.*/}

void Scene_onStartup(Scene* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onStartup);
  self->onStartup(self);
}

void Scene_onCanvaSizeChanged(Scene* self, float width, float height) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onCanvasSizeChanged);
  self->onCanvasSizeChanged(self, width, height);
}

void Scene_onMousePointerEvent(Scene* self, float x, float y) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onMousePointerEvent);
  self->onMousePointerEvent(self, x, y);
}

void Scene_onMouseButtonEvent(Scene* self, float x, float y, int index, int action) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onMouseButtonEvent);
  self->onMouseButtonEvent(self, x, y, index, action);
}

void Scene_onUpdate(Scene* self, float width, float height) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onUpdate);
  self->onUpdate(self, width, height);
}

void Scene_onShutdown(Scene* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onShutdown);
  self->onShutdown(self);
}
