#include "Scene.h"


#include "Ring1/Intrinsic.h"
#include "_Video.h"


static void Scene_destruct(Scene* self);

static void Scene_visit(Scene* self);

static void onMousePointerEvent(Scene* self, Machine_MousePointerEvent* event);

static void onMouseButtonEvent(Scene* self, Machine_MouseButtonEvent* event);

static void onKeyboardKeyEvent(Scene* self, Machine_KeyboardKeyEvent* event);

static void Scene_constructClass(Scene_Class* self) {
  self->onMouseButtonEvent = &onMouseButtonEvent;
  self->onMousePointerEvent = &onMousePointerEvent;
  self->onKeyboardKeyEvent = &onKeyboardKeyEvent;
}

void Scene_construct(Scene* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->videoContext = (Machine_VideoContext*)Machine_Extensions_getObjectArgument(
      numberOfArguments, arguments, 0, Machine_VideoContext_getType());
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scene_getType());
}

static void Scene_destruct(Scene* self) { /*Intentionally empty.*/
}

static void Scene_visit(Scene* self) { /*Intentionally empty.*/
}

MACHINE_DEFINE_CLASSTYPE(Scene, Machine_Object, &Scene_visit, &Scene_construct, &Scene_destruct,
                         &Scene_constructClass, NULL)

static void onMousePointerEvent(Scene* self,
                                Machine_MousePointerEvent* event) { /*Intentionally empty.*/
}

static void onMouseButtonEvent(Scene* self,
                               Machine_MouseButtonEvent* event) { /*Intentionally empty.*/
}

static void onKeyboardKeyEvent(Scene* self,
                               Machine_KeyboardKeyEvent* event) { /*Intentionally empty.*/
}

void Scene_onStartup(Scene* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Scene, onStartup);
}

void Scene_onCanvasSizeChanged(Scene* self, Machine_CanvasSizeChangedEvent* event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onCanvasSizeChanged, event);
}

void Scene_onMousePointerEvent(Scene* self, Machine_MousePointerEvent* event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onMousePointerEvent, event);
}

void Scene_onMouseButtonEvent(Scene* self, Machine_MouseButtonEvent* event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onMouseButtonEvent, event);
}

void Scene_onKeyboardKeyEvent(Scene* self, Machine_KeyboardKeyEvent* event) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onKeyboardKeyEvent, event);
}

void Scene_onUpdate(Scene* self, Ring2_Real32 width, Ring2_Real32 height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Scene, onUpdate, width, height);
}

void Scene_onShutdown(Scene* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Scene, onShutdown);
}

Machine_VideoContext* Scene_getVideoContext(Scene* self) {
  return self->videoContext;
}
