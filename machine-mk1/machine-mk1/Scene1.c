#include "scene1.h"



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
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

typedef struct Scene1 Scene1;

struct Scene1 {
  Scene parent;
  Machine_ShaderProgram* shaderProgram;
  GLint mvp_location;
  Machine_Binding* binding;
  Machine_FloatBuffer* vertices;
};

static void Scene1_destruct(Scene1* self);

static void Scene1_visit(Scene1* self) {
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

static void Scene1_finalize(Scene1* self) {
  Scene1_destruct(self);
}

static int Scene1_startup(Scene1* scene) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    scene->vertices = Machine_FloatBuffer_create();
    Machine_FloatBuffer_setData(scene->vertices, sizeof(vertices) / sizeof(float), vertices);

    scene->shaderProgram = Machine_ShaderProgram_generate(false, true, false, false);
    scene->mvp_location = glGetUniformLocation(scene->shaderProgram->programId, "mvp");

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

static int Scene1_update(Scene1* scene, float width, float height) {
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
  Machine_Binding_bindMatrix4x4(scene->binding, Machine_String_create("mvp", strlen("mvp") + 1), mvp);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  return 0;
}

static void Scene1_shutdown(Scene1* scene) {
  scene->vertices = NULL;
  scene->shaderProgram = NULL;
  scene->binding = NULL;
}

int Scene1_construct(Scene1* self) {
  if (Scene_construct((Scene*)self)) {
    return 1;
  }
  ((Scene*)self)->startup = (Scene_StartupCallback*)&Scene1_startup;
  ((Scene*)self)->update = (Scene_UpdateCallback*)&Scene1_update;
  ((Scene*)self)->shutdown = (Scene_ShutdownCallback*)&Scene1_shutdown;
  return 0;
}

void Scene1_destruct(Scene1* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
  Scene_destruct((Scene*)self);
}

Scene* Scene1_create() {
  Scene1* scene = Machine_allocate(sizeof(Scene1), (void (*)(void*)) & Scene1_visit, (void (*)(void*)) & Scene1_finalize);
  if (!scene) {
    return NULL;
  }
  if (Scene1_construct(scene)) {
    return NULL;
  }
  return (Scene*)scene;
}
