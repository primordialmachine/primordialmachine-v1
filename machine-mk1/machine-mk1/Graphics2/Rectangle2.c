#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "./../Graphics2/Rectangle2.h"



#include <string.h>
#include "./../GL/ShaderProgram.h"



static void Machine_Rectangle2_visit(Machine_Rectangle2* self) {
  if (self->position) {
    Machine_visit(self->position);
  }
  if (self->size) {
    Machine_visit(self->size);
  }
  if (self->shader) {
    Machine_visit(self->shader);
  }
  if (self->vertices) {
    Machine_visit(self->vertices);
  }
  if (self->binding) {
    Machine_visit(self->binding);
  }
  if (self->color) {
    Machine_visit(self->color);
  }
}

static void Machine_Rectangle2_render(Machine_Rectangle2* self, float width, float height) {
  float ratio = width / height;

  // Set the world matrix, view matrix, and projection matrix.
  Machine_Math_Matrix4* world2, * view2, * projection2, * wvp2;
  world2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_setIdentity(world2); // world matrix is identity.
  view2 = Machine_Math_Matrix4_create(); Machine_Math_Matrix4_setIdentity(view2); // view matrix is identity.
  projection2 = Machine_Math_Matrix4_create();
#if defined(true)
  Machine_Math_Matrix4_setOrtho(projection2, 0.f, width, height, 0.f, 1.f, -1.f); // projection matrix
#else
  Machine_Math_Matrix4_setOrtho(projection2, 0.f, width, 0.f, height, 1.f, -1.f); // projection matrix
#endif
  // Compute combined world view projection matrix.
  wvp2 = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_multiply(wvp2, projection2, view2);
  Machine_Math_Matrix4_multiply(wvp2, wvp2, world2);

  float l = Machine_Math_Vector2_getX(self->position);
  float r = l + Machine_Math_Vector2_getX(self->size);
  float b = Machine_Math_Vector2_getY(self->position);
  float t = b + Machine_Math_Vector2_getY(self->size);

  static const uint8_t indices[] = {
    0, 1, 2,
    2, 1, 3,
  };

  struct {
    Machine_Real x, y;
  }
  VERTICES[] =
  {
    { l, b, }, // left/bottom
    { r, b, }, // right/bottom
    { l, t, }, // left/top
    { r, t, }, // right/top
  };

  Machine_VideoBuffer_setData(self->vertices, sizeof(VERTICES), (void const*)VERTICES);

  Machine_Binding_activate(self->binding);
  {
    Machine_Binding_bindMatrix4(self->binding, Machine_String_create("modelToProjectionMatrix", strlen("modelToProjectionMatrix") + 1), wvp2);
  }
  {
    Machine_Binding_bindVector4(self->binding, Machine_String_create("mesh_color", strlen("mesh_color") + 1), self->color);
  }

  Machine_Video_drawIndirect(0, 6, indices);
}

static void Machine_Rectangle2_constructClass(Machine_Rectangle2_Class* self) {
  ((Machine_Shape2_Class*)self)->render = (void(*)(Machine_Shape2*, float, float)) & Machine_Rectangle2_render;
}

void Machine_Rectangle2_construct(Machine_Rectangle2* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Shape2_construct((Machine_Shape2*)self, numberOfArguments, arguments);
  self->position = Machine_Math_Vector2_create();
  self->size = Machine_Math_Vector2_create();

  self->vertices = Machine_Video_createBuffer();
  self->shader = Machine_GL_ShaderProgram_generateShape2Shader(false);

  Machine_VertexDescriptor* vertexDescriptor = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_XfYf);

  self->binding = Machine_Video_createBinding(self->shader, vertexDescriptor, self->vertices);
  Machine_Binding_setVariableBinding(self->binding, Machine_String_create("vertex_position", strlen("vertex_position") + 1), 0);

  self->color = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(self->color, 1.f, 1.f, 1.f, 1.f);

  Machine_Rectangle2_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_Rectangle2_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Rectangle2, Machine_Shape2, &Machine_Rectangle2_visit, &Machine_Rectangle2_construct, NULL)

Machine_Rectangle2* Machine_Rectangle2_create() {
  Machine_ClassType* ty = Machine_Rectangle2_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Rectangle2* self = (Machine_Rectangle2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Rectangle2_setRectangle(Machine_Rectangle2* self, Machine_Math_Rectangle2 const* rectangle) {
  Machine_Math_Vector2_copy(self->position, Machine_Math_Rectangle2_getPosition(rectangle));
  Machine_Math_Vector2_copy(self->size, Machine_Math_Rectangle2_getSize(rectangle));
}

Machine_Math_Rectangle2* Machine_Rectangle2_getRectangle(Machine_Rectangle2 const* self) {
  Machine_Math_Rectangle2* rectangle = Machine_Math_Rectangle2_create();
  Machine_Math_Rectangle2_setPosition(rectangle, self->position);
  Machine_Math_Rectangle2_setSize(rectangle, self->size);
  return rectangle;
}

void Machine_Rectangle2_setColor(Machine_Rectangle2* self, Machine_Math_Vector4 const* color) {
  Machine_Math_Vector4_copy(self->color, color);
}

Machine_Math_Vector4 const* Machine_Rectangle2_getColor(Machine_Rectangle2 const* self) {
  return self->color;
}

void Machine_Rectangle2_setSize(Machine_Rectangle2* self, Machine_Math_Vector2 const* size) {
  Machine_Math_Vector2_copy(self->size, size);
}

Machine_Math_Vector2 const* Machine_Rectangle2_getSize(Machine_Rectangle2 const* self) {
  return self->size;
}

void Machine_Rectangle2_setPosition(Machine_Rectangle2* self, Machine_Math_Vector2 const* position) {
  Machine_Math_Vector2_copy(self->position, position);
}

Machine_Math_Vector2 const* Machine_Rectangle2_getPosition(Machine_Rectangle2 const* self) {
  return self->position;
}
