#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "./../Graphics2/Context2.h"
#include "./../Video.h"
#include <string.h>

static void Machine_Context2_visit(Machine_Context2* self) {
  if (self->modelSpaceToProjectiveSpace) {
    Machine_visit(self->modelSpaceToProjectiveSpace);
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
}

static void Machine_Context2_constructClass(Machine_Context2_Class* self)
{/*Intentionally empty.*/}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Context2, Machine_Object, &Machine_Context2_visit, Machine_Context2_construct, NULL)

void Machine_Context2_construct(Machine_Context2* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  
  self->width = 0.f;
  self->height = 0.f;
  self->aspectRatio = 0.f;

  self->modelSpaceToProjectiveSpace = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_setIdentity(self->modelSpaceToProjectiveSpace);

  self->modelSpaceToWorldSpace = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_setIdentity(self->modelSpaceToWorldSpace);

  self->originBottomLeft = true;

  //
  self->vertices = Machine_Video_createBuffer();
  self->shader = Machine_Video_generateShape2Shader(false);

  Machine_VertexDescriptor* vertexDescriptor = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_XfYf);

  self->binding = Machine_Video_createBinding(self->shader, vertexDescriptor, self->vertices);
  Machine_Binding_setVariableBinding(self->binding, Machine_String_create("vertex_position", strlen("vertex_position") + 1), 0);
  //

  Machine_Context2_constructClass(self);
  Machine_setClassType((Machine_Object*)self, Machine_Context2_getClassType());
}

Machine_Context2* Machine_Context2_create() {
  Machine_ClassType* ty = Machine_Context2_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Context2* self = (Machine_Context2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

static void updateModelSpaceToProjectiveSpace(Machine_Context2* self) {
  if (self->width > 0.f && self->height > 0.f) {
    if (self->originBottomLeft) {
      Machine_Math_Matrix4_setOrtho(self->modelSpaceToProjectiveSpace, 0.f, self->width, self->height, 0.f, 1.f, -1.f);
    } else {
      Machine_Math_Matrix4_setOrtho(self->modelSpaceToProjectiveSpace, 0.f, self->width, 0.f, self->height, 1.f, -1.f);
    }
  } else {
    Machine_Math_Matrix4_setIdentity(self->modelSpaceToProjectiveSpace);
  }
}

void Machine_Context2_setTargetSize(Machine_Context2* self, Machine_Real width, Machine_Real height) {
  if (width < 0.f) width = 0.f;
  self->width = width;
  if (height < 0.f) height = 0.f;
  self->height = height;
  self->aspectRatio = height != 0.f ? width / height : 0.f;
  updateModelSpaceToProjectiveSpace(self);
}

Machine_Real Machine_Context2_getTargetWidth(Machine_Context2 const* self) {
  return self->width;
}

Machine_Real Machine_Context2_getTargetHeight(Machine_Context2 const* self) {
  return self->height;
}

Machine_Math_Matrix4 const* Machine_Context2_getModelSpaceToProjectiveSpaceMatrix(Machine_Context2 const* self) {
  return self->modelSpaceToProjectiveSpace;
}

Machine_Math_Matrix4 const* Machine_Context2_getModelSpaceToWorldSpaceMatrix(Machine_Context2 const* self) {
  return self->modelSpaceToWorldSpace;
}

void Machine_Context2_setOriginBottomLeft(Machine_Context2* self, Machine_Boolean originBottomLeft) {
  self->originBottomLeft = originBottomLeft;
  updateModelSpaceToProjectiveSpace(self);
}

Machine_Boolean Machine_Context2_getOriginBottomLeft(Machine_Context2 const* self) {
  return self->originBottomLeft;
}
