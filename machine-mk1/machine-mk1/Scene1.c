#include "Scene1.h"



#include <string.h>

#include "_Text.h"
#include "_Gui.h"
#include "_Images.h"
#include "_Video.h"

#include "_Fonts.h"
#include "_Graphics2.h"
#include "Video.h"



static const struct {
  Machine_Real x, y;
  Machine_Real r, g, b;
}
vertices[] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

struct Scene1_Class {
  Scene_Class __parent;
};

struct Scene1 {
  Scene __parent;

  Machine_ShaderProgram* shaderProgram;
  Machine_Binding* binding;
  Machine_VideoBuffer* vertices;
};

static void Scene1_constructClass(Scene1_Class* self);

static void Scene1_destruct(Scene1* self);

static void Scene1_visit(Scene1* self) {
  if (self->binding) {
    Machine_Gc_visit(self->binding);
  }
  if (self->shaderProgram) {
    Machine_Gc_visit(self->shaderProgram);
  }
  if (self->vertices) {
    Machine_Gc_visit(self->vertices);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene1, Scene, &Scene1_visit, &Scene1_construct, NULL, &Scene1_constructClass)

static void Scene1_onStartup(Scene1* scene) {
  scene->vertices = Machine_VideoContext_createBuffer(Machine_getVideoContext());
  Machine_VideoBuffer_setData(scene->vertices, sizeof(vertices), (void const *)vertices);

  scene->shaderProgram = Machine_VideoContext_generateDefaultShader(Machine_getVideoContext(), false, true, false, false);

  Machine_VertexDescriptor* vd = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_XfYf);
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_RfGfBf);

  scene->binding = Machine_VideoContext_createBinding(Machine_getVideoContext(), scene->shaderProgram, vd, scene->vertices);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create_noraise("vertex_position", strlen("vertex_position") + 1), 0);
  Machine_Binding_setVariableBinding(scene->binding, Machine_String_create_noraise("vertex_color", strlen("vertex_color") + 1), 1);

  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(Machine_getVideoContext(), c);
}

static void Scene1_onCanvasSizeChanged(Scene1* self, Machine_CanvasSizeChangedEvent *event) {
}

static void Scene1_onUpdate(Scene1* self, Machine_Real width, Machine_Real height) {
  float ratio = width / height;

  Machine_VideoContext_setViewportRectangle(Machine_getVideoContext(), 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(Machine_getVideoContext());

  Machine_Math_Matrix4* m2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_rotateZ(m2, Machine_Video_getTime());
  Machine_Math_Matrix4* p2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_setOrtho(p2, -ratio, +ratio, -1.f, +1.f, 1.f, -1.f);
  Machine_Math_Matrix4* mvp2 = Machine_Math_Matrix4_product(p2, m2);

  Machine_Binding_activate(self->binding);
  Machine_Binding_bindMatrix4(self->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), mvp2);

  Machine_VideoContext_drawDirect(Machine_getVideoContext(), 0, 3);
}

static void Scene1_onShutdown(Scene1* self) {
  self->vertices = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

static void Scene1_constructClass(Scene1_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene1_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene1_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene1_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene1_onShutdown;
}

void Scene1_construct(Scene1* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Scene1_getType());
}

void Scene1_destruct(Scene1* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene1* Scene1_create() {
  Machine_ClassType* ty = Scene1_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene1* scene = (Scene1*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!scene) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return scene;
}
