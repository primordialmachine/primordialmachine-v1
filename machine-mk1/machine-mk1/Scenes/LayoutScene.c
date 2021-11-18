#include "LayoutScene.h"



#include <string.h>
#include "_Text.h"
#include "_Images.h"
#include "_Fonts.h"
#include "./../Video.h"



static void LayoutScene_constructClass(LayoutScene_Class* self);

static void LayoutScene_destruct(LayoutScene* self);

static void LayoutScene_visit(LayoutScene* self);

struct LayoutScene_Class {
  Scene_Class __parent;
};

struct LayoutScene {
  Scene __parent;

  // The 2D context.
  Machine_Context2* context2;
  // The font.
  Machine_Font* font;
  /// @brief Text layout #1.
  Machine_Text_Layout* textLayout1;
  /// @brief Text layout #2.
  Machine_Text_Layout* textLayout2;
};

static void LayoutScene_visit(LayoutScene* self) {
  if (self->context2) {
    Machine_Gc_visit(self->context2);
  }
  if (self->font) {
    Machine_Gc_visit(self->font);
  }
  if (self->textLayout1) {
    Machine_Gc_visit(self->textLayout1);
  }
  if (self->textLayout2) {
    Machine_Gc_visit(self->textLayout2);
  }
}

MACHINE_DEFINE_CLASSTYPE(LayoutScene, Scene, &LayoutScene_visit, &LayoutScene_construct, NULL, &LayoutScene_constructClass)

static void LayoutScene_onStartup(LayoutScene* scene) {
  //
  scene->context2 = Machine_Context2_create(Machine_getVideoContext());
  //
  scene->font = Machine_FontsContext_createFont(Machine_DefaultFonts_createContext(Machine_getVideoContext(), Machines_DefaultImages_createContext()),
                                                Machine_String_create("RobotoSlab-Regular.ttf", strlen("RobotoSlab-Regular.ttf")), 20);
  //
  scene->textLayout1 = Machine_Text_Layout_create(Machine_String_create("", strlen("")), scene->font);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Text_Layout_setText(scene->textLayout1, Machine_String_create(text, strlen(text)));
  }
  //
  scene->textLayout2 = Machine_Text_Layout_create(Machine_String_create("", strlen("")), scene->font);
  {
    const char* text = "13 of 18 units\n7 of 9 units";
    Machine_Text_Layout_setText(scene->textLayout2, Machine_String_create(text, strlen(text)));
  }
  //
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(Machine_getVideoContext(), c);
}

static void alignLeftTop(Machine_Text_Layout* layout, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, 5.f);

  const Machine_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  const Machine_Math_Vector2* position = Machine_Math_Rectangle2_getPosition(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(MARGIN, position);
  Machine_Math_Vector2* position2 = Machine_Math_Vector2_sum(Machine_Text_Layout_getPosition(layout), delta);
  Machine_Text_Layout_setPosition(layout, position2);
}

static void alignCenter(Machine_Text_Layout* layout, float width, float height) {
  Machine_Math_Vector2* HALF = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(HALF, 0.5f, 0.5f);
  Machine_Math_Vector2* CANVAS_SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(CANVAS_SIZE, width, height);
  Machine_Math_Vector2* CANVAS_HALF_SIZE = Machine_Math_Vector2_product(CANVAS_SIZE, HALF);
  Machine_Math_Vector2* CANVAS_CENTER = Machine_Math_Vector2_clone(CANVAS_HALF_SIZE);

  const Machine_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  const Machine_Math_Vector2* center = Machine_Math_Rectangle2_getCenter(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(CANVAS_CENTER, center);
  const Machine_Math_Vector2* oldPosition = Machine_Text_Layout_getPosition(layout);
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_Text_Layout_setPosition(layout, newPosition);
}

static void LayoutScene_onCanvasSizeChanged(LayoutScene* self, Machine_CanvasSizeChangedEvent* event) {
  // Set the 2D context's target size.
  Machine_Context2_setTargetSize(self->context2, event->width, event->height);
  // Set the viewport rectangle.
  Machine_VideoContext_setViewportRectangle(Machine_getVideoContext(), 0, 0, event->width, event->height);
  alignCenter(self->textLayout1, event->width, event->height);
  alignLeftTop(self->textLayout2, event->width, event->height);
}

static void LayoutScene_onUpdate(LayoutScene* self, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(Machine_getVideoContext(), 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(Machine_getVideoContext());

  Machine_Context2* context2 = Machine_Context2_create(Machine_getVideoContext());
  Machine_Context2_setTargetSize(context2, width, height);
  Machine_Text_Layout_render(self->textLayout1, context2);
  Machine_Text_Layout_render(self->textLayout2, context2);
}

static void LayoutScene_onShutdown(LayoutScene* self) {
  self->textLayout2 = NULL;
  self->textLayout1 = NULL;
  self->font = NULL;
  self->context2 = NULL;
}

static void LayoutScene_constructClass(LayoutScene_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&LayoutScene_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&LayoutScene_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&LayoutScene_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&LayoutScene_onShutdown;
}

void LayoutScene_construct(LayoutScene* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, LayoutScene_getClassType());
}

void LayoutScene_destruct(LayoutScene* self) {
  self->textLayout2 = NULL;
  self->textLayout1 = NULL;
  self->font = NULL;
  self->context2 = NULL;
}

LayoutScene* LayoutScene_create() {
  Machine_ClassType* ty = LayoutScene_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  LayoutScene* scene = (LayoutScene*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
