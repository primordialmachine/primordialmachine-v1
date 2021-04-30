#include "Scene4.h"



#include <stddef.h>
#include <malloc.h>

#include "UtilitiesGl.h"

#include <linmath.h>

#include "Fonts.h"
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
};

void Scene4_destruct(Scene4* self);

static void Scene4_visit(Scene4* self) {
  if (self->font) {
    Machine_visit(self->font);
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
    Machine_popJumpTarget();
    return 0;
  }
  else {
    Machine_popJumpTarget();
    return 1;
  }
}

static int Scene4_update(Scene4* scene, float width, float height) {
  Machine_Math_Vector3* color = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(color, .1f, .1f, .1f);
  vec2 center = { width * 0.5f, height * 0.5f };

  const char* text = "Nanobox IV\n400 units of unprimed nanites.";
  Machine_Text_Layout* layout = Machine_Text_Layout_create(Machine_String_create(text, strlen(text)), scene->font);

  Machine_Math_Rectangle2* bounds = Machine_Text_Layout_getBounds(layout);
  Machine_Math_Rectangle2_setCenter(bounds, center[0], center[1]);
  {
    Machine_Text_Layout_setColor(layout, color);
  }
  {
    Machine_Math_Vector2* leftTop = Machine_Math_Rectangle2_getLeftTop(bounds);
    Machine_Text_Layout_setPosition(layout, leftTop);
  }
  Machine_Text_Layout_render(layout, width, height);
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
