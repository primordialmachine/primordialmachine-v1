#include "Scene2.h"



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
  { -0.6f, -0.4f, 1.f, 0.f, 0.f }, // left/bottom
  { +0.6f, -0.4f, 0.f, 1.f, 0.f }, // right/bottom
  { -0.6f, +0.6f, 0.f, 0.f, 1.f }, // left/top
  { +0.6f, +0.6f, 1.f, 1.f, 1.f }, // right/top
};

static const uint8_t indices[] = {
  0, 1, 2,
  2, 1, 3,
};

struct Scene2_Class {
  Scene_Class __parent;
};

struct Scene2 {
  Scene __parent;

  Machine_ShaderProgram* shaderProgram;
  Machine_Binding* binding;
  Machine_VideoBuffer* vertices;
};

static void Scene2_constructClass(Scene2_Class* self);

static void Scene2_destruct(Scene2* self);

static void Scene2_visit(Scene2* self) {
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

MACHINE_DEFINE_CLASSTYPE(Scene2, Scene, &Scene2_visit, &Scene2_construct, NULL,
                         &Scene2_constructClass, NULL)

static void Scene2_onStartup(Scene2* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  self->vertices = Machine_VideoContext_createBuffer(videoContext);
  Machine_VideoBuffer_setData(self->vertices, sizeof(vertices), (void const *)vertices);

  self->shaderProgram = Machine_VideoContext_generateDefaultShader(videoContext, false, true, false, false);

  Machine_VertexDescriptor* vd = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_XfYf);
  Machine_VertexDescriptor_append(vd, Machine_VertexElementSemantics_RfGfBf);

  self->binding = Machine_VideoContext_createBinding(videoContext, self->shaderProgram, vd, self->vertices);
  Machine_Binding_setVariableBinding(self->binding, Machine_String_create_noraise("vertex_position", strlen("vertex_position") + 1), 0);
  Machine_Binding_setVariableBinding(self->binding, Machine_String_create_noraise("vertex_color", strlen("vertex_color") + 1), 1);

  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void Scene2_onCanvasSizeChanged(Scene2* self, Machine_CanvasSizeChangedEvent* event) {
}

static void Scene2_onUpdate(Scene2* self, Machine_Real width, Machine_Real height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  Machine_Real ratio = width / height;

  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(videoContext);

  Machine_Math_Matrix4* m2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_rotateZ(m2, Machine_Video_getTime());
  Machine_Math_Matrix4* p2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_setOrtho(p2, -ratio, +ratio, -1.f, +1.f, 1.f, -1.f);
  Machine_Math_Matrix4* mvp2 = Machine_Math_Matrix4_product(p2, m2);

  Machine_Binding_activate(self->binding);
  Machine_Binding_bindMatrix4(self->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), mvp2);

  Machine_VideoContext_drawIndirect(videoContext, 0, 6, indices);
}

static void Scene2_onShutdown(Scene2* self) {
  self->vertices = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

static void Scene2_constructClass(Scene2_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged = (Scene_OnCanvaSizeChangedCallback*)&Scene2_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene2_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene2_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene2_onShutdown;
}

void Scene2_construct(Scene2* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Scene2_getType());
}

void Scene2_destruct(Scene2* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene2* Scene2_create() {
  Machine_ClassType* ty = Scene2_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Machine_Value const ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Scene2* self = (Scene2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Machine_setStatus(Machine_Status_AllocationFailed);
    Machine_jump();
  }
  return self;
}
