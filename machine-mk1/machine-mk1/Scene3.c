#include "Scene3.h"



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



static const struct {
  float x, y;
  float r, g, b;
  float u, v;
}
vertices[] =
{
  { -0.6f, -0.4f, 1.f, 0.f, 0.f, 0.f, 0.f, }, // left/bottom
  { +0.6f, -0.4f, 0.f, 1.f, 0.f, 1.f, 0.f, }, // right/bottom
  { -0.6f, +0.6f, 0.f, 0.f, 1.f, 0.f, 1.f, }, // left/top
  { +0.6f, +0.6f, 1.f, 1.f, 1.f, 1.f, 1.f, }, // right/top
};

static const uint8_t indices[] = {
  0, 1, 2,
  2, 1, 3,
};

typedef struct Scene3 Scene3;

struct Scene3 {
  Scene parent;
  Machine_ShaderProgram* shaderProgram;
  GLint mvp_location;
  GLint texture_location;
  Machine_Binding* binding;
  Machine_FloatBuffer* vertices;
  Machine_Images_Image* image;
  Machine_Texture* texture;
};

void Scene3_destruct(Scene3* self);

static void Scene3_visit(Scene3* self) {
  if (self->binding) {
    Machine_visit(self->binding);
  }
  if (self->texture) {
    Machine_visit(self->texture);
  }
  if (self->image) {
    Machine_visit(self->image);
  }
  if (self->shaderProgram) {
    Machine_visit(self->shaderProgram);
  }
  if (self->vertices) {
    Machine_visit(self->vertices);
  }
}

static void Scene3_finalize(Scene3* self) {
  Scene3_destruct(self);
}

static int Scene3_startup(Scene3* scene) {
  Machine_JumpTarget jumpTarget;
  Machine_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {

    if (Machine_Images_createImage("test-transparency-1.png", &scene->image)) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    scene->texture = Machine_Texture_create(scene->image);

    scene->vertices = Machine_FloatBuffer_create();
    Machine_FloatBuffer_setData(scene->vertices, sizeof(vertices) / sizeof(float), vertices);

    scene->shaderProgram = Machine_ShaderProgram_generate(true, true, true);
    scene->mvp_location = glGetUniformLocation(scene->shaderProgram->programId, "mvp");
    scene->texture_location = glGetUniformLocation(scene->shaderProgram->programId, "texture_1");

    Machine_VertexDescriptor* vd = Machine_VertexDescriptor_create();
    Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_XfYf);
    Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_RfGfBf);
    Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_UfVf);

    scene->binding = Machine_Binding_create(scene->shaderProgram, vd, scene->vertices);
    Machine_Binding_set(scene->binding, Machine_String_create("vertex_position", strlen("vertex_position") + 1), 0);
    Machine_Binding_set(scene->binding, Machine_String_create("vertex_color", strlen("vertex_color") + 1), 1);
    Machine_Binding_set(scene->binding, Machine_String_create("vertex_texture_coordinate_1", strlen("vertex_texture_coordinate_1") + 1), 2);

    Machine_popJumpTarget();
    return 0;
  }
  else {
    Machine_popJumpTarget();
    return 1;
  }
}

static int Scene3_update(Scene3* scene, float width, float height) {
  float ratio;
  mat4x4 m, p, mvp;

  ratio = width / height;

  Machine_UtilitiesGl_call(glViewport(0, 0, width, height));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));

  mat4x4_identity(m);
  mat4x4_rotate_Z(m, m, (float)glfwGetTime());
  mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
  mat4x4_mul(mvp, p, m);

  Machine_Binding_activate(scene->binding);
  Machine_UtilitiesGl_call(glUseProgram(scene->shaderProgram->programId));
  Machine_Binding_bindMatrix4x4(scene->binding, Machine_String_create("mvp", strlen("mvp") + 1), mvp);
  glUniform1i(scene->texture_location, 0);
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, scene->texture->id);
  Machine_UtilitiesGl_call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, &indices));

  return 0;
}

static void Scene3_shutdown(Scene3* self) {
  self->vertices = NULL;
  self->image = NULL;
  self->texture = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

int Scene3_construct(Scene3* self) {
  if (Scene_construct((Scene*)self)) {
    return 1;
  }
  ((Scene*)self)->startup = (Scene_StartupCallback*)&Scene3_startup;
  ((Scene*)self)->update = (Scene_UpdateCallback*)&Scene3_update;
  ((Scene*)self)->shutdown = (Scene_ShutdownCallback*)&Scene3_shutdown;
  return 0;
}

void Scene3_destruct(Scene3* self) {
  self->binding = NULL;
  self->image = NULL;
  self->texture = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
  Scene_destruct((Scene*)self);
}

Scene* Scene3_create() {
  Scene3* scene = Machine_allocate(sizeof(Scene3), (void (*)(void*)) & Scene3_visit, (void (*)(void*)) & Scene3_finalize);
  if (!scene) {
    return NULL;
  }
  if (Scene3_construct(scene)) {
    return NULL;
  }
  return (Scene*)scene;
}
