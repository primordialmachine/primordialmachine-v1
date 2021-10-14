#include "./../Scenes/Rectangle2Scene.h"



#include <string.h>
#include "_Graphics2.h"
#include "./../Video.h"



static void Rectangle2Scene_destruct(Rectangle2Scene* self);

static void Rectangle2Scene_visit(Rectangle2Scene* self);

static void Rectangle2Scene_constructClass(Rectangle2Scene_Class* self);

struct Rectangle2Scene_Class {
  Scene_Class parent;
};

struct Rectangle2Scene {
  Scene parent;
  
  // The 2D context.
  Machine_Context2* context2;

  // The 2D rectangle.
  Machine_Rectangle2* rectangle2;

};

static void Rectangle2Scene_visit(Rectangle2Scene* self) {
  if (self->context2) {
    Machine_visit(self->context2);
  }
  if (self->rectangle2) {
    Machine_visit(self->rectangle2);
  }
}

MACHINE_DEFINE_CLASSTYPE(Rectangle2Scene, Scene, &Rectangle2Scene_visit, &Rectangle2Scene_construct, NULL, &Rectangle2Scene_constructClass)

static void Rectangle2Scene_onStartup(Rectangle2Scene* scene) {
  // Create the 2D context.
  scene->context2 = Machine_Context2_create(Machine_Video_getContext());
  // Create the 2D rectangle.
  scene->rectangle2 = Machine_Rectangle2_create();
  // Set the clear color.
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(Machine_Video_getContext(), c);
}

static void Rectangle2Scene_onCanvasSizeChanged(Rectangle2Scene* self, Machine_CanvasSizeChangedEvent* event) {
  // Set the 2D context's target size.
  Machine_Context2_setTargetSize(self->context2, event->width, event->height);
  // Set the viewport rectangle.
  Machine_VideoContext_setViewportRectangle(Machine_Video_getContext(), 0, 0, event->width, event->height);
  // Set the 2D rectangle's rectangle.
  Machine_Math_Rectangle2* r = Machine_Math_Rectangle2_create();
  Machine_Math_Vector2* v = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(v, event->width / 2.f - event->width / 4.f, event->height / 2.f - event->height / 4.f);
  Machine_Math_Rectangle2_setPosition(r, v);
  Machine_Math_Vector2_set(v, event->width / 2.f, event->height / 2.f);
  Machine_Math_Rectangle2_setSize(r, v);
  Machine_Rectangle2_setRectangle(self->rectangle2, r);
}

static void Rectangle2Scene_onUpdate(Rectangle2Scene* self, float width, float height) {
  Rectangle2Scene_onCanvasSizeChanged(self, Machine_CanvasSizeChangedEvent_create(width, height));
  // Clear color buffer.
  Machine_VideoContext_clearColorBuffer(Machine_Video_getContext());
  // Render the rectangle.
  Machine_Shape2_render((Machine_Shape2*)self->rectangle2, self->context2);
}

static void Rectangle2Scene_onShutdown(Rectangle2Scene* self) {
  self->rectangle2 = NULL;
  self->context2 = NULL;
}

static void Rectangle2Scene_constructClass(Rectangle2Scene_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Rectangle2Scene_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Rectangle2Scene_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Rectangle2Scene_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Rectangle2Scene_onShutdown;
}

void Rectangle2Scene_construct(Rectangle2Scene* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Rectangle2Scene_getClassType());
}

void Rectangle2Scene_destruct(Rectangle2Scene* self) {
  self->rectangle2 = NULL;
  self->context2 = NULL;
}

Rectangle2Scene* Rectangle2Scene_create() {
  Machine_ClassType* ty = Rectangle2Scene_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Rectangle2Scene* scene = (Rectangle2Scene*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
