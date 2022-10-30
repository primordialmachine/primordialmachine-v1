/// @file Graphics2/Context2.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_GRAPHICS2_PRIVATE (1)
#include "Graphics2/Context2.h"


#include "Ring1/Intrinsic.h"


static void Machine_Context2_visit(Machine_Context2* self) {
  if (self->modelSpaceToProjectiveSpace) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->modelSpaceToProjectiveSpace);
  }
  if (self->modelSpaceToWorldSpace) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->modelSpaceToWorldSpace);
  }
  if (self->shader) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->shader);
  }
  if (self->vertices) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->vertices);
  }
  if (self->binding) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->binding);
  }
  if (self->videoContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->videoContext);
  }
}

MACHINE_DEFINE_CLASSTYPE(Machine_Context2, Machine_Object, &Machine_Context2_visit,
                         Machine_Context2_construct, NULL, NULL, NULL)

void Machine_Context2_construct(Machine_Context2* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Ring2_assert(numberOfArguments == 1, Ring1_Status_InvalidNumberOfArguments);
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  Machine_VideoContext* videoContext = (Machine_VideoContext*)Ring2_Value_getObject(&arguments[0]);

  self->videoContext = videoContext;

  self->width = 0.f;
  self->height = 0.f;
  self->aspectRatio = 0.f;

  self->modelSpaceToProjectiveSpace = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_setIdentity(self->modelSpaceToProjectiveSpace);

  self->modelSpaceToWorldSpace = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_setIdentity(self->modelSpaceToWorldSpace);

  self->originBottomLeft = true;

  //
  self->vertices = Machine_VideoContext_createBuffer(videoContext);
  self->shader = Machine_VideoContext_generateShape2Shader(videoContext);

  Machine_VertexDescriptor* vertexDescriptor = Machine_VertexDescriptor_create();
  Machine_VertexDescriptor_append(vertexDescriptor, Machine_VertexElementSemantics_XfYf);

  self->binding = Machine_VideoContext_createBinding(videoContext, self->shader, vertexDescriptor, self->vertices);
  Machine_Binding_setVariableBinding(self->binding, Ring2_String_create("vertex_position", crt_strlen("vertex_position") + 1), 0);

  //
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Context2_getType());
}

Machine_Context2* Machine_Context2_create(Machine_VideoContext* videoContext) {
  Machine_ClassType* ty = Machine_Context2_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 1;
  Ring2_Value arguments[1];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)videoContext);
  Machine_Context2* self = (Machine_Context2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments);
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

void Machine_Context2_setTargetSize(Machine_Context2* self, Ring2_Real32 width, Ring2_Real32 height) {
  if (width < 0.f) width = 0.f;
  self->width = width;
  if (height < 0.f) height = 0.f;
  self->height = height;
  self->aspectRatio = height != 0.f ? width / height : 0.f;
  updateModelSpaceToProjectiveSpace(self);
}

Ring2_Real32 Machine_Context2_getTargetWidth(Machine_Context2 const* self) {
  return self->width;
}

Ring2_Real32 Machine_Context2_getTargetHeight(Machine_Context2 const* self) {
  return self->height;
}

Machine_Math_Matrix4 const* Machine_Context2_getModelSpaceToProjectiveSpaceMatrix(Machine_Context2 const* self) {
  return self->modelSpaceToProjectiveSpace;
}

Machine_Math_Matrix4 const* Machine_Context2_getModelSpaceToWorldSpaceMatrix(Machine_Context2 const* self) {
  return self->modelSpaceToWorldSpace;
}

void Machine_Context2_setOriginBottomLeft(Machine_Context2* self, Ring2_Boolean originBottomLeft) {
  self->originBottomLeft = originBottomLeft;
  updateModelSpaceToProjectiveSpace(self);
}

Ring2_Boolean Machine_Context2_getOriginBottomLeft(Machine_Context2 const* self) {
  return self->originBottomLeft;
}
