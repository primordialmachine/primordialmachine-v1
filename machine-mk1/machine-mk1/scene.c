#include "scene.h"

#include <malloc.h>

static void Scene_destruct(Scene* self);

static void Scene_visit(Scene* self);

static void onMousePointerEvent(Scene* self, Machine_MousePointerEvent *event);

static void onMouseButtonEvent(Scene* self, Machine_MouseButtonEvent *event);

void Scene_construct(Scene* self, size_t numberOfArguments, const Machine_Value *arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->onMouseButtonEvent = &onMouseButtonEvent;
  self->onMousePointerEvent = &onMousePointerEvent;
  Machine_setClassType((Machine_Object*)self, Scene_getClassType());
}

// TODO: Make static.
void Scene_destruct(Scene* self)
{/*Intentionally empty.*/}

// TODO: Make static.
static void Scene_visit(Scene* self)
{/*Intentionally empty.*/}

MACHINE_DEFINE_CLASSTYPE_EX(Scene, Machine_Object, &Scene_visit, &Scene_construct, &Scene_destruct)

static void onMousePointerEvent(Scene* self, Machine_MousePointerEvent *event)
{/*Intentionally empty.*/}

static void onMouseButtonEvent(Scene* self, Machine_MouseButtonEvent *event)
{/*Intentionally empty.*/}

void Scene_onStartup(Scene* self) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onStartup);
  self->onStartup(self);
}

void Scene_onCanvasSizeChanged(Scene* self, Machine_CanvasSizeChangedEvent* event) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onCanvasSizeChanged);
  self->onCanvasSizeChanged(self, event);
}

void Scene_onMousePointerEvent(Scene* self, Machine_MousePointerEvent *event) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onMousePointerEvent);
  self->onMousePointerEvent(self, event);
}

void Scene_onMouseButtonEvent(Scene* self, Machine_MouseButtonEvent *event) {
  MACHINE_ASSERT_NOTNULL(self);
  MACHINE_ASSERT_NOTNULL(self->onMouseButtonEvent);
  self->onMouseButtonEvent(self, event);
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
