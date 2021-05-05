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
#include "GUI/TextLabel.h"


typedef struct Scene4 Scene4;

struct Scene4 {
  Scene parent;
  Machine_Fonts_Font* font;
  /// @brief Text label #1.
  Machine_GUI_TextLabel* textLabel1;
  /// @brief Text label #2.
  Machine_GUI_TextLabel* textLabel2;
  /// @brief Text label #3.
  Machine_GUI_TextLabel* textLabel3;
};

void Scene4_destruct(Scene4* self);

static void Scene4_visit(Scene4* self) {
  if (self->font) {
    Machine_visit(self->font);
  }
  if (self->textLabel1) {
    Machine_visit(self->textLabel1);
  }
  if (self->textLabel2) {
    Machine_visit(self->textLabel2);
  }
  if (self->textLabel3) {
    Machine_visit(self->textLabel3);
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
    //
    scene->textLabel1 = Machine_GUI_TextLabel_create();
    {
      const char* text = "Nanobox IV\n400 units of unprimed nanites.";
      Machine_GUI_TextLabel_setText(scene->textLabel1, Machine_String_create(text, strlen(text)));
    }
    //
    scene->textLabel2 = Machine_GUI_TextLabel_create();
    {
      const char* text = "13 of 18 units\n7 of 9 units";
      Machine_GUI_TextLabel_setText(scene->textLabel2, Machine_String_create(text, strlen(text)));
    }
    //
    scene->textLabel3 = Machine_GUI_TextLabel_create();
    {
      const char* text = "Nanobox IV\n400 units of unprimed nanites.";
      Machine_GUI_TextLabel_setText(scene->textLabel3, Machine_String_create(text, strlen(text)));
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
  Machine_Math_Vector2* HALF = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(HALF, 0.5f, 0.5f);
  Machine_Math_Vector2* CANVAS_SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(CANVAS_SIZE, width, height);
  Machine_Math_Vector2* CANVAS_HALF_SIZE = Machine_Math_Vector2_product(CANVAS_SIZE, HALF);
  Machine_Math_Vector2* CANVAS_CENTER = Machine_Math_Vector2_clone(CANVAS_HALF_SIZE);

  {
    // Set the size to the best size.
    Machine_Math_Vector2* size = Machine_GUI_TextLabel_getBestSize(scene->textLabel1);
    Machine_GUI_TextLabel_setSize(scene->textLabel1, size);
    // Get the bounds.
    Machine_Math_Rectangle2* bounds = Machine_GUI_TextLabel_getRectangle(scene->textLabel1);
    Machine_Math_Vector2* center = Machine_Math_Rectangle2_getCenter(bounds);
    Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(CANVAS_CENTER, center);
    Machine_Math_Vector2* oldPosition = Machine_GUI_TextLabel_getPosition(scene->textLabel1);
    Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
    Machine_GUI_TextLabel_setPosition(scene->textLabel1, newPosition);
    Machine_GUI_TextLabel_render(scene->textLabel1, width, height);
  }
}

static void updateText2(Scene4* scene, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, 5.f);
  // Set the size to the best size.
  Machine_Math_Vector2* size = Machine_GUI_TextLabel_getBestSize(scene->textLabel2);
  Machine_GUI_TextLabel_setSize(scene->textLabel2, size);
  // Set the position to the margins.
  Machine_GUI_TextLabel_setPosition(scene->textLabel2, MARGIN);
  Machine_GUI_TextLabel_render(scene->textLabel2, width, height);
}

static void updateText3(Scene4* scene, float width, float height) {
  Machine_Math_Vector2* MARGIN = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(MARGIN, 5.f, height * 0.5f);
  Machine_Math_Vector2* SIZE = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(SIZE, 64, 64);

  Machine_GUI_TextLabel_setSize(scene->textLabel3, SIZE);
  Machine_Math_Rectangle2* bounds = Machine_GUI_TextLabel_getRectangle(scene->textLabel3);
  Machine_Math_Vector2* leftTop = Machine_Math_Rectangle2_getLeftTop(bounds);
  Machine_Math_Vector2* delta = Machine_Math_Vector2_difference(MARGIN, leftTop);
  Machine_Math_Vector2* oldPosition = Machine_GUI_TextLabel_getPosition(scene->textLabel3);
  Machine_Math_Vector2* newPosition = Machine_Math_Vector2_sum(oldPosition, delta);
  Machine_GUI_TextLabel_setPosition(scene->textLabel3, newPosition);
  Machine_GUI_TextLabel_render(scene->textLabel3, width, height);
}

static int Scene4_update(Scene4* scene, float width, float height) {
  // Set the viewport and clear its color buffer.
  Machine_UtilitiesGl_call(glViewport(0, 0, width, height));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));

  updateText1(scene, width, height);
  updateText2(scene, width, height);
  updateText3(scene, width, height);

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
