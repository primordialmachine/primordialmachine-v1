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
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Scene, onStartup);
}

void Scene_onCanvasSizeChanged(Scene* self, Machine_CanvasSizeChangedEvent* event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onCanvasSizeChanged, event);
}

void Scene_onMousePointerEvent(Scene* self, Machine_MousePointerEvent *event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onMousePointerEvent, event);
}

void Scene_onMouseButtonEvent(Scene* self, Machine_MouseButtonEvent *event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onMouseButtonEvent, event);
}

void Scene_onUpdate(Scene* self, float width, float height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onUpdate, width, height);
}

void Scene_onShutdown(Scene* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Scene, onShutdown);
}
