#include "Ring4/Scenes/Scene1.h"


#include "Ring1/All/_Include.h"
#include "Ring3/Graphics2/_Include.h"
#include "Ring3/Text/_Include.h"
#include "Ring3/Visuals/_Include.h"
#include "Ring3/Gui/_Include.h"


static const struct {
  Ring2_Real32 x, y;
  Ring2_Real32 r, g, b;
} vertices[] = { { -0.6f, -0.4f, 1.f, 0.f, 0.f },
                 { 0.6f, -0.4f, 0.f, 1.f, 0.f },
                 { 0.f, 0.6f, 0.f, 0.f, 1.f } };

struct Scene1_Class {
  Scene_Class __parent;
};

struct Scene1 {
  Scene __parent;

  Ring3_GpuProgram* shaderProgram;
  Ring3_Binding* binding;
  Ring3_GpuBuffer* vertices;
};

static void Scene1_constructClass(Scene1_Class* self);

static void Scene1_destruct(Scene1* self);

static void Scene1_visit(Scene1* self) {
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

MACHINE_DEFINE_CLASSTYPE(Scene1, Scene, &Scene1_visit, &Scene1_construct, NULL,
                         &Scene1_constructClass, NULL)

static void Scene1_onStartup(Scene1* self) {
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);

  self->vertices = Ring3_VisualsContext_createBuffer(visualsContext);
  Ring3_GpuBuffer_setData(self->vertices, sizeof(vertices), (void const*)vertices);

  self->shaderProgram = Ring3_VisualsContext_generateDefaultShader(visualsContext, false, true, false, false);

  Ring3_VertexDescriptor* vd = Ring3_VertexDescriptor_create();
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_XfYf);
  Ring3_VertexDescriptor_append(vd, Ring3_VertexElementSemantics_RfGfBf);

  self->binding = Ring3_VisualsContext_createBinding(visualsContext, self->shaderProgram, vd, self->vertices);
  Ring3_Binding_setVariableBinding(self->binding,
                                   Ring2_String_fromC(true, "vertexPosition"),
                                   Ring3_GpuProgramLocationType_Vector2Variable,
                                   0);
  Ring3_Binding_setVariableBinding(self->binding,
                                   Ring2_String_fromC(true, "vertexColor"),
                                   Ring3_GpuProgramLocationType_Vector3Variable,
                                   1);

  Ring3_Math_Vector4f32* c = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(c, 0.9f, 0.9f, 0.9f, 1.0f);
  Ring3_VisualsContext_setClearColor(visualsContext, c);
}

static void Scene1_onCanvasSizeChanged(Scene1* self, Ring3_CanvasSizeChangedEvent* event) {
}

static void Scene1_onUpdate(Scene1* self, Ring2_Real32 width, Ring2_Real32 height) {
  Ring3_VisualsContext* visualsContext = Scene_getVisualsContext((Scene*)self);

  Ring2_Real32 ratio = width / height;

  Ring3_VisualsContext_setViewportRectangle(visualsContext, 0, 0, width, height);
  Ring3_VisualsContext_clearColorBuffer(visualsContext);

  Ring3_Math_Matrix4x4f32* m2 = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_setRotationZ(m2, Machine_Time_getNowSecondsFloat());
  Ring3_Math_Matrix4x4f32* p2 = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_setOrtho(p2, -ratio, +ratio, -1.f, +1.f, 1.f, -1.f);
  Ring3_Math_Matrix4x4f32* mvp2 = Ring3_Math_Matrix4x4f32_product(p2, m2);

  Ring3_Binding_bindMatrix4(self->binding,
                            Ring2_String_fromC(true, "modelToProjectionMatrix"),
                            mvp2);
  Ring3_Binding_activate(self->binding);
  Ring3_VisualsContext_drawDirect(visualsContext, 0, 3);
}

static void Scene1_onShutdown(Scene1* self) {
  self->vertices = NULL;
  self->shaderProgram = NULL;
  self->binding = NULL;
}

static void Scene1_constructClass(Scene1_Class* self) {
  ((Scene_Class*)self)->onCanvasSizeChanged
      = (Scene_OnCanvaSizeChangedCallback*)&Scene1_onCanvasSizeChanged;
  ((Scene_Class*)self)->onStartup = (Scene_OnStartupCallback*)&Scene1_onStartup;
  ((Scene_Class*)self)->onUpdate = (Scene_OnUpdateCallback*)&Scene1_onUpdate;
  ((Scene_Class*)self)->onShutdown = (Scene_OnShutdownCallback*)&Scene1_onShutdown;
}

void Scene1_construct(Scene1* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Scene_construct((Scene*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Scene1_getType());
}

void Scene1_destruct(Scene1* self) {
  self->binding = NULL;
  self->shaderProgram = NULL;
  self->vertices = NULL;
}

Scene1*
Scene1_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  )
{
  Machine_Type* ty = Scene1_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value ARGUMENTS[3];
  Ring2_Value_setObject(&(ARGUMENTS[0]), (Machine_Object*)visualsContext);
  Ring2_Value_setObject(&(ARGUMENTS[1]), (Machine_Object*)imagesContext);
  Ring2_Value_setObject(&(ARGUMENTS[2]), (Machine_Object*)fontsContext);
  Scene1* self = (Scene1*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
