#include "Scene1.h"



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
}
vertices[] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

struct Scene1 {
  Scene parent;
  Machine_ShaderProgram* shaderProgram;
  Machine_Binding* binding;
  Machine_VideoBuffer* vertices;
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

MACHINE_DEFINE_CLASSTYPE_EX(Scene1, Scene, &Scene1_visit, &Scene1_construct, NULL)

static void Scene1_onStartup(Scene1* scene) {
  scene->vertices = Machine_Video_createBuffer();
  Machine_VideoBuffer_setData(scene->vertices, sizeof(vertices), (void const *)vertices);

  scene->shaderProgram = Machine_GL_ShaderProgram_generateDefaultShader(false, true, false, false);

  Machine_VertexDescriptor* vd = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_XfYf);
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_RfGfBf);

  scene->binding = Machine_Video_createBinding(scene->shaderProgram, vd, scene->vertices);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create_noraise("vertex_position", strlen("vertex_position") + 1), 0);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create_noraise("vertex_color", strlen("vertex_color") + 1), 1);
}

static void Scene1_onCanvasSizeChanged(Scene1* self, Machine_CanvasSizeChangedEvent *event) {
}

static void Scene1_onUpdate(Scene1* self, float width, float height) {
  float ratio = width / height;

  Machine_Video_setViewportRectangle(0, 0, width, height);
  Machine_Video_clearColorBuffer();

  Machine_Math_Matrix4* m2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_rotateZ(m2, (float)glfwGetTime());
  Machine_Math_Matrix4* p2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_setOrtho(p2, -ratio, +ratio, -1.f, +1.f, 1.f, -1.f);
  Machine_Math_Matrix4* mvp2 = Machine_Math_Matrix4_product(p2, m2);

  Machine_Binding_activate(self->binding);
  Machine_Binding_bindMatrix4(self->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), mvp2);

  Machine_Video_drawDirect(0, 3);
}

static void Scene1_onShutdown(Scene1* self) {
  self->vertices = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

void Scene1_construct(Scene1* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  ((Scene*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene1_onCanvasSizeChanged;
  ((Scene*)self)->onStartup = (Scene_OnStartupCallback*)&Scene1_onStartup;
  ((Scene*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene1_onUpdate;
  ((Scene*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene1_onShutdown;
  Machine_setClassType((Machine_Object*)self, Scene1_getClassType());
}

void Scene1_destruct(Scene1* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene1* Scene1_create() {
  Machine_ClassType* ty = Scene1_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene1* scene = (Scene1*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
