#include "Scene4.h"



#include <string.h>

#include "_Text.h"
#include "_Gui.h"
#include "_Images.h"
#include "_Video.h"

#include "_Fonts.h"
#include "_Graphics2.h"


#define FONT_FILE "fonts/RobotoSlab/RobotoSlab-Regular.ttf"
#define FONT_SIZE 20

static void Scene4_destruct(Scene4* self);

static void Scene4_visit(Scene4* self);

static void Scene4_constructClass(Scene4_Class* self);

struct Scene4_Class {
  Scene_Class __parent;
};

struct Scene4 {
  Scene __parent;
  
  //
  Machine_Gui_Context* guiContext;
  //
  Machine_Font* font;
  /// @brief Text layout #1.
  Machine_Text_Layout* text1;
  /// @brief Text layout #2.
  Machine_Text_Layout* text2;
  /// @brief Text node #1.
  Machine_Gui_TextNode* textNode1;
};

static void Scene4_destruct(Scene4* self);

static void Scene4_constructClass(Scene4_Class* self);

static void Scene4_visit(Scene4* self) {
  if (self->guiContext) {
    Machine_Gc_visit(self->guiContext);
  }
  if (self->font) {
    Machine_Gc_visit(self->font);
  }
  if (self->text1) {
    Machine_Gc_visit(self->text1);
  }
  if (self->text2) {
    Machine_Gc_visit(self->text2);
  }
  if (self->textNode1) {
    Machine_Gc_visit(self->textNode1);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene4, Scene, &Scene4_visit, &Scene4_construct, NULL,
                         &Scene4_constructClass, NULL)

static void Scene4_onStartup(Scene4* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);
  //
  self->guiContext = Machine_Gui_Context_create(Machine_Gdl_Context_create(), Machine_Context2_create(videoContext));
  //
  self->font = Machine_FontsContext_createFont(Machine_DefaultFonts_createContext(videoContext, Machines_DefaultImages_createContext()),
                                                Machine_String_create(FONT_FILE, strlen(FONT_FILE)), FONT_SIZE);
  //
  self->text1 = Machine_Text_Layout_create(Machine_String_create("", strlen("")), self->font);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Text_Layout_setText(self->text1, Machine_String_create(text, strlen(text)));
  }
  //
  self->text2 = Machine_Text_Layout_create(Machine_String_create("", strlen("")), self->font);
  {
    const char* text = "13 of 18 units\n7 of 9 units";
    Machine_Text_Layout_setText(self->text2, Machine_String_create(text, strlen(text)));
  }
  //
  self->textNode1 = Machine_Gui_TextNode_create(self->guiContext);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Gui_TextNode_setText(self->textNode1, Machine_String_create(text, strlen(text)));
  }
  //
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void alignLeftTop(Machine_Text_Layout* layout, Machine_Real width, Machine_Real height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, 5.f);

  const Machine_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  const Machine_Math_Vector2* position = Machine_Math_Rectangle2_getPosition(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(MARGIN, position);
  Machine_Math_Vector2* position2 = Machine_Math_Vector2_sum(Machine_Text_Layout_getPosition(layout), delta);
  Machine_Text_Layout_setPosition(layout, position2);
}

static void alignCenter(Machine_Text_Layout* layout, Machine_Real width, Machine_Real height) {
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

static void updateText1(Scene4* self, Machine_Real width, Machine_Real height) {
  alignCenter(self->text1, width, height);
}

static void updateText2(Scene4* self, Machine_Real width, Machine_Real height) {
  alignLeftTop(self->text2, width, height);
}

static void updateText3(Scene4* self, Machine_Real width, Machine_Real height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, height * 0.5f);
  Machine_Math_Vector2* SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(SIZE, 64, 64);

  Machine_Gui_Widget_setSize((Machine_Gui_Widget*)self->textNode1, SIZE);
  const Machine_Math_Rectangle2* bounds = Machine_Gui_Widget_getRectangle((Machine_Gui_Widget *)self->textNode1);
  const Machine_Math_Vector2* leftTop = Machine_Math_Rectangle2_getPosition(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(MARGIN, leftTop);
  const Machine_Math_Vector2* oldPosition = Machine_Gui_Widget_getPosition((Machine_Gui_Widget *)self->textNode1);
  const Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_Gui_Widget_setPosition((Machine_Gui_Widget*)self->textNode1, newPosition);
}

static void Scene4_onCanvasSizeChanged(Scene4* self, Machine_CanvasSizeChangedEvent* event) {
  Machine_Gui_Context_onCanvasSizechanged(self->guiContext, event);
  updateText1(self, event->width, event->height);
  updateText2(self, event->width, event->height);
  updateText3(self, event->width, event->height);
}

static void Scene4_onUpdate(Scene4* self, Machine_Real width, Machine_Real height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(videoContext);

  Machine_Context2* context2 = Machine_Context2_create(videoContext);
  Machine_Context2_setTargetSize(context2, width, height);
  Machine_Text_Layout_render(self->text1, context2);
  Machine_Text_Layout_render(self->text2, context2);
  Machine_Gui_Widget_render((Machine_Gui_Widget*)self->textNode1, context2);
}

static void Scene4_onShutdown(Scene4* self) {
  self->font = NULL;
}

static void Scene4_constructClass(Scene4_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene4_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene4_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene4_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene4_onShutdown;
}

void Scene4_construct(Scene4* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Scene4_getType());
}

void Scene4_destruct(Scene4* self) {
  self->font = NULL;
}

Scene4* Scene4_create() {
  Machine_ClassType* ty = Scene4_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene4* self = (Scene4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return self;
}
