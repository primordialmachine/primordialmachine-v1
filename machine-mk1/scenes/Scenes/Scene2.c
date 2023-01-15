#include "Scene2.h"


#include "Ring1/All/_Include.h"
#include "Gui/_Include.h"
#include "_Images.h"
#include "_Text.h"
#include "_Video.h"
#include "_Fonts.h"
#include "Graphics2/_Include.h"


static const struct {
  Ring2_Real32 x, y;
  Ring2_Real32 r, g, b;
} vertices[] = {
  { -0.6f, -0.4f, 1.f, 0.f, 0.f }, // left/bottom
  { +0.6f, -0.4f, 0.f, 1.f, 0.f }, // right/bottom
  { -0.6f, +0.6f, 0.f, 0.f, 1.f }, // left/top
  { +0.6f, +0.6f, 1.f, 1.f, 1.f }, // right/top
};

static const uint8_t indices[] = {
  0, 1, 2, 2, 1, 3,
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
    Ring2_Gc_visit(Ring2_Gc_get(), self->binding);
  }
  if (self->shaderProgram) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->shaderProgram);
  }
  if (self->vertices) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->vertices);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene2, Scene, &Scene2_visit, &Scene2_construct, NULL,
                         &Scene2_constructClass, NULL)

static void Scene2_onStartup(Scene2* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  self->vertices = Machine_VideoContext_createBuffer(videoContext);
  Machine_VideoBuffer_setData(self->vertices, sizeof(vertices), (void const*)vertices);

  self->shaderProgram
      = Machine_VideoContext_generateDefaultShader(videoContext, false, true, false, false);

  Ring3_VertexDescriptor* vd = Ring3_VertexDescriptor_create();
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_XfYf);
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_RfGfBf);

  self->binding
      = Machine_VideoContext_createBinding(videoContext, self->shaderProgram, vd, self->vertices);
  Machine_Binding_setVariableBinding(
      self->binding, 
      Ring2_String_create("vertex_position", crt_strlen("vertex_position") + 1), 0);
  Machine_Binding_setVariableBinding(
      self->binding, 
      Ring2_String_create("vertex_color", crt_strlen("vertex_color") + 1), 1);

  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void Scene2_onCanvasSizeChanged(Scene2* self, Ring3_CanvasSizeChangedEvent* event) {
}

static void Scene2_onUpdate(Scene2* self, Ring2_Real32 width, Ring2_Real32 height) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  Ring2_Real32 ratio = width / height;

  Machine_VideoContext_setViewportRectangle(videoContext, 0, 0, width, height);
  Machine_VideoContext_clearColorBuffer(videoContext);

  Ring3_Math_Matrix4x4f32* m2 = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_setRotationZ(m2, Machine_Time_getNowSecondsFloat());
  Ring3_Math_Matrix4x4f32* p2 = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_setOrtho(p2, -ratio, +ratio, -1.f, +1.f, 1.f, -1.f);
  Ring3_Math_Matrix4x4f32* mvp2 = Ring3_Math_Matrix4x4f32_product(p2, m2);

  Machine_Binding_activate(self->binding);
  Machine_Binding_bindMatrix4(
      self->binding,
      Ring2_String_create("modelToProjectionMatrix", crt_strlen("modelToProjectionMatrix") + 1),
      mvp2);

  Machine_VideoContext_drawIndirect(videoContext, 0, 6, indices);
}

static void Scene2_onShutdown(Scene2* self) {
  self->vertices = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

static void Scene2_constructClass(Scene2_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&Scene2_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene2_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene2_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene2_onShutdown;
}

void Scene2_construct(Scene2* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scene2_getType());
}

void Scene2_destruct(Scene2* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene2* Scene2_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = Scene2_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)videoContext);
  Scene2* self = (Scene2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Ring2_jump();
  }
  return self;
}
