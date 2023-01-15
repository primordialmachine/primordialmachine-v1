#include "Scene3.h"


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
  Ring2_Real32 u, v;
} vertices[] = {
  {
      -0.6f,
      -0.4f,
      1.f,
      0.f,
      0.f,
      0.f,
      0.f,
  }, // left/bottom
  {
      +0.6f,
      -0.4f,
      0.f,
      1.f,
      0.f,
      1.f,
      0.f,
  }, // right/bottom
  {
      -0.6f,
      +0.6f,
      0.f,
      0.f,
      1.f,
      0.f,
      1.f,
  }, // left/top
  {
      +0.6f,
      +0.6f,
      1.f,
      1.f,
      1.f,
      1.f,
      1.f,
  }, // right/top
};

static const uint8_t indices[] = {
  0, 1, 2, 2, 1, 3,
};

struct Scene3_Class {
  Scene_Class __parent;
};

struct Scene3 {
  Scene __parent;

  Machine_ShaderProgram* shaderProgram;
  Machine_Binding* binding;
  Machine_VideoBuffer* vertices;
  Ring3_Image* image;
  Ring3_Texture* texture;
};

static void Scene3_constructClass(Scene3_Class* self);

static void Scene3_destruct(Scene3* self);

static void Scene3_visit(Scene3* self) {
  if (self->binding) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->binding);
  }
  if (self->texture) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->texture);
  }
  if (self->image) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->image);
  }
  if (self->shaderProgram) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->shaderProgram);
  }
  if (self->vertices) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->vertices);
  }
}

MACHINE_DEFINE_CLASSTYPE(Scene3, Scene, &Scene3_visit, &Scene3_construct, NULL,
                         &Scene3_constructClass, NULL)

static void Scene3_startup(Scene3* self) {
  Machine_VideoContext* videoContext = Scene_getVideoContext((Scene*)self);

  self->image = Ring3_ImagesContext_createFromPath(Machines_DefaultImages_createContext(),
                                                   Ring2_String_fromC("test-transparency-1.png"));
  self->texture = Machine_VideoContext_createTextureFromImage(videoContext, self->image);

  self->vertices = Machine_VideoContext_createBuffer(videoContext);
  Machine_VideoBuffer_setData(self->vertices, sizeof(vertices), (void const*)vertices);

  self->shaderProgram
      = Machine_VideoContext_generateDefaultShader(videoContext, false, true, true, true);

  Ring3_VertexDescriptor* vd = Ring3_VertexDescriptor_create();
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_XfYf);
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_RfGfBf);
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_UfVf);

  self->binding = Machine_VideoContext_createBinding(videoContext, self->shaderProgram, vd, self->vertices);

  Machine_Binding_setVariableBinding(self->binding, Ring2_String_create("vertex_position",
                                                             crt_strlen("vertex_position") + 1), 0);
  Machine_Binding_setVariableBinding(self->binding, Ring2_String_create("vertex_color",
                                                             crt_strlen("vertex_color") + 1), 1);
  Machine_Binding_setVariableBinding(self->binding, Ring2_String_create("vertex_texture_coordinate_1",
                                                             crt_strlen("vertex_texture_coordinate_1") + 1), 2);

  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Machine_VideoContext_setClearColor(videoContext, c);
}

static void Scene3_onCanvasSizeChanged(Scene3* self, Ring3_CanvasSizeChangedEvent* event) {
}

static void Scene3_update(Scene3* self, Ring2_Real32 width, Ring2_Real32 height) {
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
  Machine_Binding_bindMatrix4(self->binding,
                              Ring2_String_create("modelToProjectionMatrix",
                                                   crt_strlen("modelToProjectionMatrix") + 1),
                              mvp2);
  Machine_Binding_bindSampler(self->binding,
                              Ring2_String_create("texture_1",
                                                   crt_strlen("texture_1") + 1),
                              0);
  Machine_VideoContext_bindTexture(videoContext, 0, self->texture);

  Machine_VideoContext_drawIndirect(videoContext, 0, 6, indices);
}

static void Scene3_shutdown(Scene3* self) {
  self->vertices = NULL;
  self->image = NULL;
  self->texture = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

static void Scene3_constructClass(Scene3_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&Scene3_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene3_startup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene3_update;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene3_shutdown;
}

void Scene3_construct(Scene3* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scene3_getType());
}

void Scene3_destruct(Scene3* self) {
  self->binding = NULL;
  self->image = NULL;
  self->texture = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene3* Scene3_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = Scene3_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value ARGUMENTS[1];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)videoContext);
  Scene3* self = (Scene3*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  if (!self) {
    Ring2_jump();
  }
  return self;
}
