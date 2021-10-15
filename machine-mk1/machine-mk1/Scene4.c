#include "Scene4.h"



#include <string.h>

#include "./Text/Layout.h"
#include "_GUI.h"
#include "_Images.h"
#include "_Video.h"

#include "_Fonts.h"
#include "_Graphics2.h"
#include "Video.h"



struct Scene4 {
  Scene parent;
  //
  Machine_GUI_Context* guiContext;
  //
  Machine_Font* font;
  /// @brief Text layout #1.
  Machine_Text_Layout* text1;
  /// @brief Text label #2.
  Machine_Text_Layout* text2;
  /// @brief Text label #3.
  Machine_GUI_TextLabel* textLabel3;
};

void Scene4_destruct(Scene4* self);

static void Scene4_visit(Scene4* self) {
  if (self->guiContext) {
    Machine_visit(self->guiContext);
  }
  if (self->font) {
    Machine_visit(self->font);
  }
  if (self->text1) {
    Machine_visit(self->text1);
  }
  if (self->text2) {
    Machine_visit(self->text2);
  }
  if (self->textLabel3) {
    Machine_visit(self->textLabel3);
  }
}

MACHINE_DEFINE_CLASSTYPE_EX(Scene4, Scene, &Scene4_visit, &Scene4_construct, NULL)

static void Scene4_onStartup(Scene4* scene) {
  //
  scene->guiContext = Machine_GUI_Context_create(Machine_GDL_Context_create(), Machine_Context2_create(Machine_Video_getContext()));
  //
  scene->font = Machine_FontsContext_createFont(Machine_DefaultFonts_createContext(Machine_Video_getContext(), Machines_DefaultImages_createContext()),
                                                Machine_String_create("RobotoSlab-Regular.ttf", strlen("RobotoSlab-Regular.ttf")), 20);
  //
  scene->text1 = Machine_Text_Layout_create(Machine_String_create("", strlen("")), scene->font);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_Text_Layout_setText(scene->text1, Machine_String_create(text, strlen(text)));
  }
  //
  scene->text2 = Machine_Text_Layout_create(Machine_String_create("", strlen("")), scene->font);
  {
    const char* text = "13 of 18 units\n7 of 9 units";
    Machine_Text_Layout_setText(scene->text2, Machine_String_create(text, strlen(text)));
  }
  //
  scene->textLabel3 = Machine_GUI_TextLabel_create(scene->guiContext);
  {
    const char* text = "Nanobox IV\n400 units of unprimed nanites.";
    Machine_GUI_TextLabel_setText(scene->textLabel3, Machine_String_create(text, strlen(text)));
  }
  //
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(Machine_Video_getContext(), c);
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

static void updateText1(Scene4* self, float width, float height) {
  alignCenter(self->text1, width, height);
}

static void updateText2(Scene4* self, float width, float height) {
  alignLeftTop(self->text2, width, height);
}

static void updateText3(Scene4* self, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, height * 0.5f);
  Machine_Math_Vector2* SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(SIZE, 64, 64);

  Machine_GUI_Widget_setSize((Machine_GUI_Widget*)self->textLabel3, SIZE);
  const Machine_Math_Rectangle2* bounds = Machine_GUI_Widget_getRectangle((Machine_GUI_Widget *)self->textLabel3);
  const Machine_Math_Vector2* leftTop = Machine_Math_Rectangle2_getPosition(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(MARGIN, leftTop);
  const Machine_Math_Vector2* oldPosition = Machine_GUI_Widget_getPosition((Machine_GUI_Widget *)self->textLabel3);
  const Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_GUI_Widget_setPosition((Machine_GUI_Widget*)self->textLabel3, newPosition);
}

static void Scene4_onCanvasSizeChanged(Scene4* self, Machine_CanvasSizeChangedEvent* event) {
  Machine_GUI_Context_onCanvasSizechanged(self->guiContext, event);
  updateText1(self, event->width, event->height);
  updateText2(self, event->width, event->height);
  updateText3(self, event->width, event->height);
}

static void Scene4_onUpdate(Scene4* self, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_VideoContext_setViewportRectangle(Machine_Video_getContext(), 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(Machine_Video_getContext());

  Machine_Context2* context2 = Machine_Context2_create(Machine_Video_getContext());
  Machine_Context2_setTargetSize(context2, width, height);
  Machine_Text_Layout_render(self->text1, context2);
  Machine_Text_Layout_render(self->text2, context2);
  Machine_GUI_Widget_render((Machine_GUI_Widget *)self->textLabel3, context2);
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

void Scene4_construct(Scene4* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Scene4_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Scene4_getClassType());
}

void Scene4_destruct(Scene4* self) {
  self->font = NULL;
}

Scene4* Scene4_create() {
  Machine_ClassType* ty = Scene4_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene4* scene = (Scene4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
