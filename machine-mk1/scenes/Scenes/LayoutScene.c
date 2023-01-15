#include "LayoutScene.h"


#include "Ring1/All/_Include.h"
#include "Gui/_Include.h"
#include "_Images.h"
#include "_Text.h"
#include "_Video.h"
#include "_Fonts.h"
#include "Graphics2/_Include.h"


#define FONT_FILE "fonts/RobotoSlab/RobotoSlab-Regular.ttf"
#define FONT_SIZE 20

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
    Ring2_Gc_visit(Ring2_Gc_get(), self->context2);
  }
  if (self->font) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->font);
  }
  if (self->textLayout1) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->textLayout1);
  }
  if (self->textLayout2) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->textLayout2);
  }
}

MACHINE_DEFINE_CLASSTYPE(LayoutScene, Scene, &LayoutScene_visit, &LayoutScene_construct, NULL,
                         &LayoutScene_constructClass, NULL)

static void LayoutScene_onStartup(LayoutScene* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  //
  self->context2 = Machine_Context2_create(videoContext);
  //
  self->font = Machine_FontsContext_createFont(Machine_DefaultFonts_createContext(videoContext,
                                                                                  Machines_DefaultImages_createContext()),
                                               Ring2_String_fromC(FONT_FILE), FONT_SIZE);
  //
  self->textLayout1 = Machine_Text_Layout_create(Ring2_String_fromC(""), self->font);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Text_Layout_setText(self->textLayout1, Ring2_String_fromC(text));
  }
  //
  self->textLayout2 = Machine_Text_Layout_create(Ring2_String_fromC(""), self->font);
  {
    const char* text = "13 of 18 units\n7 of 9 units";
    Machine_Text_Layout_setText(self->textLayout2, Ring2_String_fromC(text));
  }
  //
  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void alignLeftTop(Machine_Text_Layout* layout, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_Math_Vector2f32* MARGIN = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(MARGIN, 5.f, 5.f);

  Ring3_Math_Rectangle2 const* bounds = Machine_Text_Layout_getBounds(layout);
  Ring3_Math_Vector2f32 const* position = Ring3_Math_Rectangle2_getPosition(bounds);
  Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_difference(MARGIN, position);
  Ring3_Math_Vector2f32* position2 = Ring3_Math_Vector2f32_sum(Machine_Text_Layout_getPosition(layout), delta);
  Machine_Text_Layout_setPosition(layout, position2);
}

static void alignCenter(Machine_Text_Layout* layout, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_Math_Vector2f32* HALF = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(HALF, 0.5f, 0.5f);
  Ring3_Math_Vector2f32* CANVAS_SIZE = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(CANVAS_SIZE, width, height);
  Ring3_Math_Vector2f32* CANVAS_HALF_SIZE = Ring3_Math_Vector2f32_product(CANVAS_SIZE, HALF);
  Ring3_Math_Vector2f32* CANVAS_CENTER = Ring3_Math_Vector2f32_clone(CANVAS_HALF_SIZE);

  const Ring3_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  const Ring3_Math_Vector2f32* center = Ring3_Math_Rectangle2_getCenter(bounds);
  Ring3_Math_Vector2f32* delta = Ring3_Math_Vector2f32_difference(CANVAS_CENTER, center);
  const Ring3_Math_Vector2f32* oldPosition = Machine_Text_Layout_getPosition(layout);
  Ring3_Math_Vector2f32* newPosition = Ring3_Math_Vector2f32_sum(oldPosition, delta);
  Machine_Text_Layout_setPosition(layout, newPosition);
}

static void LayoutScene_onCanvasSizeChanged(LayoutScene* self,
                                            Ring3_CanvasSizeChangedEvent* event) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  // Set the 2D context's target size.
  Machine_Context2_setTargetSize(self->context2, event->width, event->height);
  // Set the viewport rectangle.
  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, event->width, event->height);
  alignCenter(self->textLayout1, event->width, event->height);
  alignLeftTop(self->textLayout2, event->width, event->height);
}

static void LayoutScene_onUpdate(LayoutScene* self, Ring2_Real32 width, Ring2_Real32 height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(videoContext);

  Machine_Context2* context2 = Machine_Context2_create(videoContext);
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
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&LayoutScene_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&LayoutScene_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&LayoutScene_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&LayoutScene_onShutdown;
}

void LayoutScene_construct(LayoutScene* self, size_t numberOfArguments,
                           Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), LayoutScene_getType());
}

void LayoutScene_destruct(LayoutScene* self) {
  self->textLayout2 = NULL;
  self->textLayout1 = NULL;
  self->font = NULL;
  self->context2 = NULL;
}

LayoutScene* LayoutScene_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = LayoutScene_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)videoContext);
  LayoutScene* self = (LayoutScene*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Ring2_jump();
  }
  return self;
}
