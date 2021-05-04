#include "scene2.h"



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
#include "Video.h"


static const struct {
  float x, y;
  float r, g, b;
}
vertices[] =
{
  { -0.6f, -0.4f, 1.f, 0.f, 0.f }, // left/bottom
  { +0.6f, -0.4f, 0.f, 1.f, 0.f }, // right/bottom
  { -0.6f, +0.6f, 0.f, 0.f, 1.f }, // left/top
  { +0.6f, +0.6f, 1.f, 1.f, 1.f }, // right/top
};

static const uint8_t indices[] = {
  0, 1, 2,
  2, 1, 3,
};

typedef struct Scene2 Scene2;

struct Scene2 {
  Scene parent;
  Machine_ShaderProgram* shaderProgram;
  GLint mvp_location;
  Machine_Binding* binding;
  Machine_FloatBuffer* vertices;
};

static void Scene2_destruct(Scene2* self);

static void Scene2_visit(Scene2* self) {
  if (self->binding) {
    Machine_visit(self->binding);
  }
  if (self->shaderProgram) {
    Machine_visit(self->shaderProgram);
  }
  if (self->vertices) {
    Machine_visit(self->vertices);
  }
}

static void Scene2_finalize(Scene2* self) {
  Scene2_destruct(self);
}

static int Scene2_startup(Scene2* scene) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    scene->vertices = Machine_FloatBuffer_create();
    Machine_FloatBuffer_setData(scene->vertices, sizeof(vertices) / sizeof(float), vertices);

    scene->shaderProgram = Machine_ShaderProgram_generate(false, true, false, false);
    scene->mvp_location = glGetUniformLocation(scene->shaderProgram->programId, "modelToProjectionMatrix");

    Machine_VertexDescriptor* vd = Machine_VertexDescriptor_create();
    Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_XfYf);
    Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_RfGfBf);

    scene->binding = Machine_Binding_create(scene->shaderProgram, vd, scene->vertices);
    Machine_Binding_set(scene->binding, Machine_String_create_noraise("vertex_position", strlen("vertex_position") + 1), 0);
    Machine_Binding_set(scene->binding, Machine_String_create_noraise("vertex_color", strlen("vertex_color") + 1), 1);

    Machine_popJumpTarget();
    return 0;
  }
  else {
    Machine_popJumpTarget();
    return 1;
  }

  return 0;
}

static int Scene2_update(Scene2* scene, float width, float height) {
  float ratio;
  mat4x4 m, p, mvp;

  ratio = width / height;

  glViewport(0, 0, width, height);
  glClear(GL_COLOR_BUFFER_BIT);

  mat4x4_identity(m);
  mat4x4_rotate_Z(m, m, (float)glfwGetTime());
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);

  Machine_Binding_activate(scene->binding);
  Machine_Video_bindShaderProgram(scene->shaderProgram);
  Machine_Binding_bindMatrix4x4(scene->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), mvp);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, &indices);

  return 0;
}

static void Scene2_shutdown(Scene2* scene) {
  scene->vertices = NULL;
  scene->shaderProgram = NULL;
  scene->binding = NULL;
}

int Scene2_construct(Scene2* self) {
  if (Scene_construct((Scene*)self)) {
    return 1;
  }
  ((Scene*)self)->startup = (Scene_StartupCallback*)&Scene2_startup;
  ((Scene*)self)->update = (Scene_UpdateCallback*)&Scene2_update;
  ((Scene*)self)->shutdown = (Scene_ShutdownCallback*)&Scene2_shutdown;
  return 0;
}

void Scene2_destruct(Scene2* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
  Scene_destruct((Scene*)self);
}

Scene* Scene2_create() {
  Scene2* scene = Machine_allocate(sizeof(Scene2), (void (*)(void*)) & Scene2_visit, (void (*)(void*)) & Scene2_finalize);
  if (!scene) {
    return NULL;
  }
  if (Scene2_construct(scene)) {
    return NULL;
  }
  return (Scene*)scene;
}
