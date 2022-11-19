#include "Scenes/Rectangle2Scene.h"


#include "Ring1/Intrinsic.h"
#include "_Gui.h"
#include "_Images.h"
#include "_Text.h"
#include "_Video.h"
#include "_Fonts.h"
#include "_Graphics2.h"


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
    Ring2_Gc_visit(Ring2_Gc_get(), self->context2);
  }
  if (self->rectangle2) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->rectangle2);
  }
}

MACHINE_DEFINE_CLASSTYPE(Rectangle2Scene, Scene, &Rectangle2Scene_visit, &Rectangle2Scene_construct,
                         NULL, &Rectangle2Scene_constructClass, NULL)

static void Rectangle2Scene_onStartup(Rectangle2Scene* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  // Create the 2D context.
  self->context2 = Machine_Context2_create(videoContext);
  // Create the 2D rectangle.
  self->rectangle2 = Machine_Rectangle2_create();
  // Set the clear color.
  Ring3_Math_Vector4* c = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void Rectangle2Scene_onCanvasSizeChanged(Rectangle2Scene* self,
                                                Machine_CanvasSizeChangedEvent* event) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  // Set the 2D context's target size.
  Machine_Context2_setTargetSize(self->context2, event->width, event->height);
  // Set the viewport rectangle.
  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, event->width, event->height);
  // Set the 2D rectangle's rectangle.
  Ring3_Math_Rectangle2* r = Ring3_Math_Rectangle2_create();
  Ring3_Math_Vector2* v = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(v, event->width / 2.f - event->width / 4.f,
                           event->height / 2.f - event->height / 4.f);
  Ring3_Math_Rectangle2_setPosition(r, v);
  Ring3_Math_Vector2_set(v, event->width / 2.f, event->height / 2.f);
  Ring3_Math_Rectangle2_setSize(r, v);
  Machine_Rectangle2_setRectangle(self->rectangle2, r);
}

static void Rectangle2Scene_onUpdate(Rectangle2Scene* self, Ring2_Real32 width,
                                     Ring2_Real32 height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  Rectangle2Scene_onCanvasSizeChanged(self, Machine_CanvasSizeChangedEvent_create(width, height));
  // Clear color buffer.
  Machine_VideoContext_clearColorBuffer(videoContext);
  // Render the rectangle.
  Machine_Shape2_render((Machine_Shape2*)self->rectangle2, self->context2);
}

static void Rectangle2Scene_onShutdown(Rectangle2Scene* self) {
  self->rectangle2 = NULL;
  self->context2 = NULL;
}

static void Rectangle2Scene_constructClass(Rectangle2Scene_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&Rectangle2Scene_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Rectangle2Scene_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Rectangle2Scene_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Rectangle2Scene_onShutdown;
}

void Rectangle2Scene_construct(Rectangle2Scene* self, size_t numberOfArguments,
                               Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Rectangle2Scene_getType());
}

void Rectangle2Scene_destruct(Rectangle2Scene* self) {
  self->rectangle2 = NULL;
  self->context2 = NULL;
}

Rectangle2Scene* Rectangle2Scene_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = Rectangle2Scene_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)videoContext);
  Rectangle2Scene* self = (Rectangle2Scene*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Ring2_jump();
  }
  return self;
}
