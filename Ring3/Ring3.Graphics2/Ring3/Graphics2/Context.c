/// @file Ring3/Graphics2/Context.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_GRAPHICS2_PRIVATE (1)
#include "Ring3/Graphics2/Context.h"
#undef RING3_GRAPHICS2_PRIVATE

#include "Ring1/All/_Include.h"

static void
Ring3_Graphics2_Context_visit
  (
    Ring3_Graphics2_Context* self
  )
{
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
  if (self->fontsContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->fontsContext);
  }
  if (self->imagesContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->imagesContext);
  }
  if (self->visualsContext) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->visualsContext);
  }
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Graphics2_Context,
                         Machine_Object,
                         &Ring3_Graphics2_Context_visit,
                         &Ring3_Graphics2_Context_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Graphics2_Context_construct
  (
    Ring3_Graphics2_Context* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring2_assert(numberOfArguments == 3, Ring1_Status_InvalidNumberOfArguments);
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);

  Ring3_VisualsContext* visualsContext = (Ring3_VisualsContext*)Ring2_Value_getObject(&arguments[0]);
  Ring3_ImagesContext* imagesContext = (Ring3_ImagesContext*)Ring2_Value_getObject(&arguments[1]);
  Ring3_FontsContext* fontsContext = (Ring3_FontsContext*)Ring2_Value_getObject(&arguments[2]);

  self->visualsContext = visualsContext;
  self->imagesContext = imagesContext;
  self->fontsContext = fontsContext;

  self->width = 0.f;
  self->height = 0.f;
  self->aspectRatio = 0.f;

  self->modelSpaceToProjectiveSpace = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_setIdentity(self->modelSpaceToProjectiveSpace);

  self->modelSpaceToWorldSpace = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_setIdentity(self->modelSpaceToWorldSpace);

  self->originBottomLeft = true;

  //
  self->vertices = Ring3_VisualsContext_createBuffer(visualsContext);
  self->shader = Ring3_VisualsContext_generateShape2Shader(visualsContext);

  Ring3_VertexDescriptor* vertexDescriptor = Ring3_VertexDescriptor_create();
  Ring3_VertexDescriptor_append(vertexDescriptor, Ring3_VertexElementSemantics_XfYf);

  self->binding = Ring3_VisualsContext_createBinding(self->visualsContext, self->shader, vertexDescriptor, self->vertices);
  Ring3_Binding_setVariableBinding(self->binding, Ring2_String_fromC(true, "vertexPosition"), 
                                                  Ring3_GpuProgramLocationType_Vector2Variable,
                                                  0);

  //
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Graphics2_Context_getType());
}

Ring1_NoDiscardReturn() Ring3_Graphics2_Context*
Ring3_Graphics2_Context_create
  (
    Ring3_VisualsContext* visualsContext,
    Ring3_ImagesContext* imagesContext,
    Ring3_FontsContext* fontsContext
  )
{
  Machine_Type* ty = Ring3_Graphics2_Context_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 3;
  Ring2_Value arguments[3];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,visualsContext));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,imagesContext));
  Ring2_Value_setObject(&arguments[2], Ring1_cast(Machine_Object*,fontsContext));
  Ring3_Graphics2_Context* self = Ring1_cast(Ring3_Graphics2_Context*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

static void
updateModelSpaceToProjectiveSpace
  (
    Ring3_Graphics2_Context* self
  )
{
  if (self->width > 0.f && self->height > 0.f) {
    if (self->originBottomLeft) {
      Ring3_Math_Matrix4x4f32_setOrtho(self->modelSpaceToProjectiveSpace, 0.f, self->width, self->height, 0.f, 1.f, -1.f);
    } else {
      Ring3_Math_Matrix4x4f32_setOrtho(self->modelSpaceToProjectiveSpace, 0.f, self->width, 0.f, self->height, 1.f, -1.f);
    }
  } else {
    Ring3_Math_Matrix4x4f32_setIdentity(self->modelSpaceToProjectiveSpace);
  }
}

void
Ring3_Graphics2_Context_setTargetSize
  (
    Ring3_Graphics2_Context* self,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  if (width < 0.f) width = 0.f;
  self->width = width;
  if (height < 0.f) height = 0.f;
  self->height = height;
  self->aspectRatio = height != 0.f ? width / height : 0.f;
  updateModelSpaceToProjectiveSpace(self);
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Graphics2_Context_getTargetWidth
  (
    Ring3_Graphics2_Context const* self
  )
{ return self->width; }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Graphics2_Context_getTargetHeight
  (
    Ring3_Graphics2_Context const* self
  )
{ return self->height; }

Ring1_NoDiscardReturn() Ring3_Math_Matrix4x4f32*
Ring3_Graphics2_Context_getModelSpaceToProjectiveSpaceMatrix
  (
    Ring3_Graphics2_Context const* self
  )
{ return Ring3_Math_Matrix4x4f32_clone(self->modelSpaceToProjectiveSpace); }

Ring1_NoDiscardReturn() Ring3_Math_Matrix4x4f32*
Ring3_Graphics2_Context_getModelSpaceToWorldSpaceMatrix
  (
    Ring3_Graphics2_Context const* self
  )
{ return Ring3_Math_Matrix4x4f32_clone(self->modelSpaceToWorldSpace); }

void
Ring3_Graphics2_Context_setOriginBottomLeft
  (
    Ring3_Graphics2_Context* self,
    Ring2_Boolean originBottomLeft
  )
{
  self->originBottomLeft = originBottomLeft;
  updateModelSpaceToProjectiveSpace(self);
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Graphics2_Context_getOriginBottomLeft
  (
    Ring3_Graphics2_Context const* self
  )
{ return self->originBottomLeft; }

Ring1_NoDiscardReturn() Ring3_VisualsContext*
Ring3_Graphics2_Context_getVisualsContext
  (
    Ring3_Graphics2_Context const* self
  )
{ return self->visualsContext; }

Ring1_NoDiscardReturn() Ring3_ImagesContext*
Ring3_Graphics2_Context_getImagesContext
  (
    Ring3_Graphics2_Context const* self
  )
{ return self->imagesContext; }

Ring1_NoDiscardReturn() Ring3_FontsContext*
Ring3_Graphics2_Context_getFontsContext
  (
    Ring3_Graphics2_Context const* self
  )
{ return self->fontsContext; }
