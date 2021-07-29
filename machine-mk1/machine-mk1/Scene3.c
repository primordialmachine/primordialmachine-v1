#include "Scene3.h"



#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "UtilitiesGl.h"

#include "_GUI.h"
#include "_Images.h"
#include "_Video.h"

#include "Fonts.h"
#include "Shape2.h"
#include "Video.h"
#include "GL/ShaderProgram.h"



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

struct Scene3 {
  Scene parent;
  Machine_ShaderProgram* shaderProgram;
  Machine_Binding* binding;
  Machine_VideoBuffer* vertices;
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

MACHINE_DEFINE_CLASSTYPE_EX(Scene3, Scene, &Scene3_visit, &Scene3_construct, NULL)

static void Scene3_startup(Scene3* scene) {
  scene->image = Machine_Images_createImageFromPath(Machine_String_create("test-transparency-1.png", strlen("test-transparency-1.png")));
  scene->texture = Machine_Video_createTextureFromImage(scene->image);

  scene->vertices = Machine_Video_createBuffer();
  Machine_VideoBuffer_setData(scene->vertices, sizeof(vertices), (void const *)vertices);

  scene->shaderProgram = Machine_GL_ShaderProgram_generateDefaultShader(false, true, true, true);

  Machine_VertexDescriptor* vd = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_XfYf);
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_RfGfBf);
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_UfVf);

  scene->binding = Machine_Video_createBinding(scene->shaderProgram, vd, scene->vertices);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create("vertex_position", strlen("vertex_position") + 1), 0);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create("vertex_color", strlen("vertex_color") + 1), 1);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create("vertex_texture_coordinate_1", strlen("vertex_texture_coordinate_1") + 1), 2);
}

static void Scene3_onCanvasSizeChanged(Scene3* self, Machine_CanvasSizeChangedEvent* event) {
}

static void Scene3_update(Scene3* self, float width, float height) {
  float ratio = width / height;

  Machine_Video_setViewportRectangle(0, 0, width, height);
  Machine_Video_clearColorBuffer();

  Machine_Math_Matrix4* m2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_rotateZ(m2, (float)glfwGetTime());
  Machine_Math_Matrix4* p2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_setOrtho(p2, -ratio, +ratio, -1.f, +1.f, 1.f, -1.f);
  Machine_Math_Matrix4* mvp2 = Machine_Math_Matrix4_product(p2, m2);

  Machine_Binding_activate(self->binding);
  Machine_Binding_bindMatrix4(self->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), mvp2);
  Machine_Binding_bindSampler(self->binding, Machine_String_create("texture_1", strlen("texture_1")), 0);
  Machine_Video_bindTexture(0, self->texture);

  Machine_Video_drawIndirect(0, 6, indices);
}

static void Scene3_shutdown(Scene3* self) {
  self->vertices = NULL;
  self->image = NULL;
  self->texture = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

void Scene3_construct(Scene3* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  ((Scene*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene3_onCanvasSizeChanged;
  ((Scene*)self)->onStartup = (Scene_OnStartupCallback*)&Scene3_startup;
  ((Scene*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene3_update;
  ((Scene*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene3_shutdown;
  Machine_setClassType((Machine_Object*)self, Scene3_getClassType());
}

void Scene3_destruct(Scene3* self) {
  self->binding = NULL;
  self->image = NULL;
  self->texture = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene3* Scene3_create() {
  Machine_ClassType* ty = Scene3_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene3* scene = (Scene3*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
