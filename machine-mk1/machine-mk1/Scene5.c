#include "Scene5.h"



#include <stddef.h>
#include <malloc.h>

#include "UtilitiesGl.h"

#include "Fonts.h"
#include "Shape2.h"
#include "Images.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexDescriptor.h"
#include "Binding.h"
#include "GUI/TextLabel.h"
#include "GUI/Border.h"

static const float OUTER_BORDER_SIZE = 4.f;
static const float INNER_BORDER_SIZE = 16.f;


typedef struct Scene5 Scene5;

struct Scene5 {
  Scene parent;
  Machine_Fonts_Font* font;
  /// @brief Border of text label #1.
  Machine_GUI_Border* border1;
  /// @brief Border of text label #2.
  Machine_GUI_Border* border2;
  /// @brief Border of text label #3.
  Machine_GUI_Border* border3;
};

void Scene5_destruct(Scene5* self);

static void Scene5_visit(Scene5* self) {
  if (self->font) {
    Machine_visit(self->font);
  }
  if (self->border1) {
    Machine_visit(self->border1);
  }
  if (self->border2) {
    Machine_visit(self->border2);
  }
  if (self->border3) {
    Machine_visit(self->border3);
  }
}

static void Scene5_finalize(Scene5* self) {
  Scene5_destruct(self);
}

static Machine_GUI_Widget* create(const char* text, Machine_Fonts_Font *font) {
  Machine_GUI_TextLabel* label;
  //
  label = Machine_GUI_TextLabel_create();
  {
    Machine_GUI_TextLabel_setText(label, Machine_String_create(text, strlen(text)));
  }

  Machine_Math_Vector2* sz = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(sz, 5.5, 5.f);

  Machine_GUI_Border* border0 = Machine_GUI_Border_create();
  Machine_GUI_Border_setBorderWidth(border0, INNER_BORDER_SIZE);
  Machine_GUI_Border_setChild(border0, (Machine_GUI_Widget *)label);
  Machine_Math_Vector3* color = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(color, 1.f, 1.f, 1.f);
  Machine_GUI_Border_setBorderColor(border0, color);

  Machine_GUI_Border *border1 = Machine_GUI_Border_create();
  Machine_GUI_Border_setBorderWidth(border1, OUTER_BORDER_SIZE);
  //Machine_Math_Vector3_set(color, 0.f, 0.5f, 0.5f);
  //Machine_GUI_Border_setBorderColor(border1, color);
  Machine_GUI_Border_setChild(border1, (Machine_GUI_Widget*)border0);
  
  
  return border1;
}

static void Scene5_startup(Scene5* scene) {
  scene->font = Machine_Fonts_createFont("RobotoSlab-Regular.ttf", 20);
  //
  scene->border1 = create("Nanobox IV\n400 units of unprimed nanites.", scene->font);
  //
  scene->border2 = create("13 of 18 units\n7 of 9 units", scene->font);
  //
  scene->border3 = create("Nanobox IV\n400 units of unprimed nanites.", scene->font);
}

static Machine_Math_Vector2 *getOuterBorderWidths() {
  Machine_Math_Vector2* v = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(v, OUTER_BORDER_SIZE, OUTER_BORDER_SIZE);
  return v;
}

static Machine_Math_Vector2* getInnerBorderWidths() {
  Machine_Math_Vector2* v = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(v, INNER_BORDER_SIZE, INNER_BORDER_SIZE);
  return v;
}

static void updateText1(Scene5* scene, float width, float height) {
  Machine_Math_Vector2* HALF = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(HALF, 0.5f, 0.5f);
  Machine_Math_Vector2* CANVAS_SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(CANVAS_SIZE, width, height);
  Machine_Math_Vector2* CANVAS_HALF_SIZE = Machine_Math_Vector2_product(CANVAS_SIZE, HALF);
  Machine_Math_Vector2* CANVAS_CENTER = Machine_Math_Vector2_clone(CANVAS_HALF_SIZE);
  // Set the size to the best size.
  const Machine_Math_Vector2* size = Machine_GUI_Widget_getPreferredSize(scene->border1);
  Machine_GUI_Widget_setSize((Machine_GUI_Widget*)scene->border1, size);
  // Get the bounds.
  Machine_Math_Rectangle2* bounds = Machine_GUI_Widget_getRectangle((Machine_GUI_Widget*)scene->border1);
  Machine_Math_Vector2* center = Machine_Math_Rectangle2_getCenter(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(CANVAS_CENTER, center);
  const Machine_Math_Vector2* oldPosition = Machine_GUI_Widget_getPosition((Machine_GUI_Widget*)scene->border1);
  const Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_GUI_Widget_setPosition((Machine_GUI_Widget*)scene->border1, newPosition);
}

static void updateText2(Scene5* scene, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, 5.f);
  // Set the size to the best size.
  const Machine_Math_Vector2* size = Machine_GUI_Widget_getPreferredSize(scene->border2);
  Machine_GUI_Widget_setSize((Machine_GUI_Widget*)scene->border2, size);
  // Set the position to the margins.
  Machine_GUI_Widget_setPosition((Machine_GUI_Widget*)scene->border2, MARGIN);
}

static void updateText3(Scene5* scene, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, height * 0.5f);
  Machine_Math_Vector2* SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(SIZE, 64, 64);
  Machine_GUI_Widget_setSize((Machine_GUI_Widget*)scene->border3, SIZE);
  const Machine_Math_Rectangle2* bounds = Machine_GUI_Widget_getRectangle((Machine_GUI_Widget*)scene->border3);
  const Machine_Math_Vector2* leftTop = Machine_Math_Rectangle2_getPosition(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(MARGIN, leftTop);
  const Machine_Math_Vector2* oldPosition = Machine_GUI_Widget_getPosition((Machine_GUI_Widget*)scene->border3);
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_GUI_Widget_setPosition((Machine_GUI_Widget*)scene->border3, newPosition);
}

static void Scene5_onCanvasSizeChanged(Scene5* self, float width, float height) {
  updateText1(self, width, height);
  updateText2(self, width, height);
  updateText3(self, width, height);
}

static void Scene5_update(Scene5* self, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_UtilitiesGl_call(glViewport(0, 0, width, height));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));

  Machine_GUI_Widget_render((Machine_GUI_Widget*)self->border1, width, height);
  Machine_GUI_Widget_render((Machine_GUI_Widget*)self->border2, width, height);
  Machine_GUI_Widget_render((Machine_GUI_Widget*)self->border3, width, height);
}

static void Scene5_shutdown(Scene5* scene) {
  scene->font = NULL;
}

int Scene5_construct(Scene5* self) {
  if (Scene_construct((Scene*)self)) {
    return 1;
  }
  ((Scene*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene5_onCanvasSizeChanged;
  ((Scene*)self)->startup = (Scene_StartupCallback*)&Scene5_startup;
  ((Scene*)self)->update = (Scene_UpdateCallback*)&Scene5_update;
  ((Scene*)self)->shutdown = (Scene_ShutdownCallback*)&Scene5_shutdown;
  return 0;
}

void Scene5_destruct(Scene5* self) {
  self->font = NULL;
  Scene_destruct((Scene*)self);
}

Scene* Scene5_create() {
  Scene5* scene = Machine_allocate(sizeof(Scene5), (void (*)(void*)) & Scene5_visit, (void (*)(void*)) & Scene5_finalize);
  if (!scene) {
    return NULL;
  }
  if (Scene5_construct(scene)) {
    return NULL;
  }
  return (Scene*)scene;
}
