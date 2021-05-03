#include "Scene4.h"



#include <stddef.h>
#include <malloc.h>

#include "UtilitiesGl.h"

#include <linmath.h>

#include "Fonts.h"
#include "Shape2.h"
#include "Images.h"
#include "Buffer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "VertexDescriptor.h"
#include "Binding.h"



typedef struct Scene4 Scene4;

struct Scene4 {
  Scene parent;
  Machine_Fonts_Font* font;
  struct {
    Machine_Rectangle2* background;
    Machine_Text_Layout* text;
  } label1;
  struct {
    Machine_Text_Layout* text;
  } label2;
};

void Scene4_destruct(Scene4* self);

static void Scene4_visit(Scene4* self) {
  if (self->font) {
    Machine_visit(self->font);
  }
  if (self->label1.background) {
    Machine_visit(self->label1.background);
  }
  if (self->label1.text) {
    Machine_visit(self->label1.text);
  }
  if (self->label2.text) {
    Machine_visit(self->label2.text);
  }
}

static void Scene4_finalize(Scene4* self) {
  Scene4_destruct(self);
}

static int Scene4_startup(Scene4* scene) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    scene->font = Machine_Fonts_createFont("RobotoSlab-Regular.ttf", 20);
    if (!scene->font) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    scene->label1.background = Machine_Rectangle2_create();
    {
      const char* text = "Nanobox IV\n400 units of unprimed nanites.";
      scene->label1.text = Machine_Text_Layout_create(Machine_String_create("", strlen("")), scene->font);
      Machine_Text_Layout_setText(scene->label1.text, Machine_String_create(text, strlen(text)));
    }
    {
      const char* text = "15 of 15";
      scene->label2.text = Machine_Text_Layout_create(Machine_String_create("", strlen("")), scene->font);
      Machine_Text_Layout_setText(scene->label2.text, Machine_String_create(text, strlen(text)));
    }
    Machine_popJumpTarget();
    return 0;
  }
  else {
    Machine_popJumpTarget();
    return 1;
  }
}

static void updateText1(Scene4* scene, float width, float height) {
  Machine_Math_Vector3* color = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(color, .1f, .1f, .1f);

  Machine_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(scene->label1.text);
  Machine_Math_Vector2* size = Machine_Math_Rectangle2_getSize(bounds);
  Machine_Math_Vector2* halfSize = Machine_Math_Vector2_clone(size);
  Machine_Math_Vector2_set(halfSize, Machine_Math_Vector2_getX(halfSize) * 0.5f, Machine_Math_Vector2_getY(halfSize) * 0.5f);
  
  Machine_Math_Vector2* CENTER = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(CENTER, width * 0.5f, height * 0.5f);
  Machine_Math_Vector2* POSITION = Machine_Math_Vector2_difference(CENTER, halfSize);

  Machine_Text_Layout_setPosition(scene->label1.text, POSITION);
  {
    Machine_Text_Layout_setColor(scene->label1.text, color);
  }
  Machine_Text_Layout_render(scene->label1.text, width, height);
}

static void updateText2(Scene4* scene, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, 5.f);

  Machine_Math_Vector3* COLOR = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(COLOR, .1f, .1f, .1f);

  const char* text = "15 of 15";
  Machine_Text_Layout* layout = Machine_Text_Layout_create(Machine_String_create(text, strlen(text)), scene->font);

  Machine_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  Machine_Math_Vector2* leftTop = Machine_Math_Rectangle2_getLeftTop(bounds);
  if (Machine_Math_Vector2_getX(leftTop) < 0.f) {
    Machine_Math_Vector2_set(leftTop, -Machine_Math_Vector2_getX(leftTop), Machine_Math_Vector2_getY(leftTop));
  }
  if (Machine_Math_Vector2_getY(leftTop) < 0.f) {
    Machine_Math_Vector2_set(leftTop, Machine_Math_Vector2_getX(leftTop), -Machine_Math_Vector2_getY(leftTop));
  }
  Machine_Math_Vector2_add(leftTop, leftTop, MARGIN);
  {
    Machine_Text_Layout_setColor(layout, COLOR);
  }
  {
    Machine_Text_Layout_setPosition(layout, leftTop);
  }
  Machine_Text_Layout_render(layout, width, height);
}

static int Scene4_update(Scene4* scene, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_UtilitiesGl_call(glViewport(0, 0, width, height));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));

  Machine_Math_Vector2* v = Machine_Math_Vector2_create();

  Machine_Math_Vector2_set(v, width * 0.25f, height * 0.25f);
  Machine_Rectangle2_setPosition(scene->label1.background, v);

  Machine_Math_Vector2_set(v, width * 0.5f, height * 0.5f);
  Machine_Rectangle2_setSize(scene->label1.background, v);

  Machine_Shape2_render((Machine_Shape2*)scene->label1.background, width, height);

  updateText1(scene, width, height);
  updateText2(scene, width, height);

  return 0;
}

static void Scene4_shutdown(Scene4* scene) {
  scene->font = NULL;
}

int Scene4_construct(Scene4* self) {
  if (Scene_construct((Scene*)self)) {
    return 1;
  }
  ((Scene*)self)->startup = (Scene_StartupCallback*)&Scene4_startup;
  ((Scene*)self)->update = (Scene_UpdateCallback*)&Scene4_update;
  ((Scene*)self)->shutdown = (Scene_ShutdownCallback*)&Scene4_shutdown;
  return 0;
}

void Scene4_destruct(Scene4* self) {
  self->font = NULL;
  Scene_destruct((Scene*)self);
}

Scene* Scene4_create() {
  Scene4* scene = Machine_allocate(sizeof(Scene4), (void (*)(void*)) & Scene4_visit, (void (*)(void*)) & Scene4_finalize);
  if (!scene) {
    return NULL;
  }
  if (Scene4_construct(scene)) {
    return NULL;
  }
  return (Scene*)scene;
}
