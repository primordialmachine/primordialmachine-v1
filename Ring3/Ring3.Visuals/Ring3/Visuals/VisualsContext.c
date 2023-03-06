/// @file Ring3/Visuals/VisualsContext.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_PRIVATE (1)
#include "Ring3/Visuals/VisualsContext.h"
#undef RING3_VISUALS_PRIVATE

static void
Ring3_VisualsContext_visit
  (
    Ring3_VisualsContext* self
  );

MACHINE_DEFINE_CLASSTYPE(Ring3_VisualsContext,
                         Machine_Object,
                         &Ring3_VisualsContext_visit,
                         &Ring3_VisualsContext_construct,
                         NULL,
                         NULL,
                         NULL)

static void
Ring3_VisualsContext_visit
  (
    Ring3_VisualsContext* self
  )
{/*Intentionally empty.*/}

void
Ring3_VisualsContext_construct
  (
    Ring3_VisualsContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_VisualsContext_getType());
}

void
Ring3_VisualsContext_setClearColor
  (
    Ring3_VisualsContext* self,
    Ring3_Math_Vector4f32 const* clearColor
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setClearColor, clearColor); }

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32 const*
Ring3_VisualsContext_getClearColor
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getClearColor); }

void
Ring3_VisualsContext_setIncomingBlendFunction
  (
    Ring3_VisualsContext* self,
    Ring3_BlendFunction incomingBlendFunction
  )
{
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setIncomingBlendFunction,
                                    incomingBlendFunction);
}

Ring1_NoDiscardReturn() Ring3_BlendFunction
Ring3_VisualsContext_getIncomingBlendFunction
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getIncomingBlendFunction); }

void
Ring3_VisualsContext_setExistingBlendFunction
  (
    Ring3_VisualsContext* self,
    Ring3_BlendFunction existingBlendFunction
  )
{
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setExistingBlendFunction,
                                    existingBlendFunction);
}

Ring1_NoDiscardReturn() Ring3_BlendFunction
Ring3_VisualsContext_getExistingBlendFunction
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getExistingBlendFunction); }

void
Ring3_VisualsContext_setDepthWriteEnabled
  (
    Ring3_VisualsContext* self,
    Ring2_Boolean depthWriteEnabled
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setDepthWriteEnabled, depthWriteEnabled); }

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_VisualsContext_getDepthWriteEnabled
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getDepthWriteEnabled); }

void
Ring3_VisualsContext_setDepthTestFunction
  (
    Ring3_VisualsContext* self,
    Ring3_DepthTestFunction depthTestFunction
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setDepthTestFunction, depthTestFunction); }

Ring1_NoDiscardReturn() Ring3_DepthTestFunction
Ring3_VisualsContext_getDepthTestFunction
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getDepthTestFunction); }

void
Ring3_VisualsContext_setClearDepth
  (
    Ring3_VisualsContext* self,
    Ring2_Real32 clearDepth
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setClearDepth, clearDepth); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_VisualsContext_getClearDepth
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getClearDepth); }

void
Ring3_VisualsContext_setViewportRectangle
  (
    Ring3_VisualsContext* self,
    Ring2_Real32 left,
    Ring2_Real32 bottom,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext,
                                    setViewportRectangle,
                                    left,
                                    bottom,
                                    width,
                                    height);
}

void
Ring3_VisualsContext_getViewportRectangle
  (
    Ring3_VisualsContext const* self,
    Ring2_Real32* left,
    Ring2_Real32* bottom,
    Ring2_Real32* width,
    Ring2_Real32* height
  )
{
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext,
                                    getViewportRectangle,
                                    left,
                                    bottom,
                                    width,
                                    height);
}

Ring1_NoDiscardReturn() Ring2_Integer
Ring3_VisualsContext_getMaximalClipDistanceCount
  (
    Ring3_VisualsContext const* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, getMaximalClipDistanceCount); }

void
Ring3_VisualsContext_setClipDistanceEnabled
  (
    Ring3_VisualsContext* self,
    Ring2_Integer index,
    Ring2_Boolean enabled
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, setClipDistanceEnabled, index, enabled); }

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_VisualsContext_getClipDistanceEnabled
  (
    Ring3_VisualsContext const* self,
    Ring2_Integer index
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_VisualsContext, getClipDistanceEnabled, index); }

void
Ring3_VisualsContext_clearColorBuffer
  (
    Ring3_VisualsContext* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Ring3_VisualsContext, clearColorBuffer); }

void
Ring3_VisualsContext_clearDepthBuffer
  (
    Ring3_VisualsContext* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Ring3_VisualsContext, clearDepthBuffer); }

Ring1_NoDiscardReturn() Ring3_Texture*
Ring3_VisualsContext_createTextureFromImage
  (
    Ring3_VisualsContext* self,
    Ring3_Image* image
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_VisualsContext, createTextureFromImage, image); }

Ring1_NoDiscardReturn() Ring3_GpuBuffer*
Ring3_VisualsContext_createBuffer
  (
    Ring3_VisualsContext* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, createBuffer); }

Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_createProgram
  (
    Ring3_VisualsContext* self,
    Ring2_String* vertexProgramText,
    Ring2_String* geometryProgramText,
    Ring2_String* fragmentProgramText
  )
{
  MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_VisualsContext,
                                  createProgram,
                                  vertexProgramText,
                                  geometryProgramText,
                                  fragmentProgramText);
}

Ring1_NoDiscardReturn() Ring3_Binding*
Ring3_VisualsContext_createBinding
  (
    Ring3_VisualsContext* self,
    Ring3_GpuProgram* program,
    Ring3_VertexDescriptor* vertexDescriptor,
    Ring3_GpuBuffer* buffer
  )
{
  MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_VisualsContext,
                                  createBinding,
                                  program,
                                  vertexDescriptor,
                                  buffer);
}

void
Ring3_VisualsContext_drawDirect
  (
    Ring3_VisualsContext* self,
    Ring2_Integer i,
    Ring2_Integer n
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, drawDirect, i, n); }

void
Ring3_VisualsContext_drawIndirect
  (
    Ring3_VisualsContext* self,
    Ring2_Integer i,
    Ring2_Integer n,
    uint8_t const* indices
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, drawIndirect, i, n, indices); }

void
Ring3_VisualsContext_bindTexture
  (
    Ring3_VisualsContext* self,
    size_t unit,
    Ring3_Texture* texture
  )
{ MACHINE_VIRTUALCALL_NORETURN_ARGS(Ring3_VisualsContext, bindTexture, unit, texture); }

Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_generateDefaultShader
  (
    Ring3_VisualsContext* self,
    Ring2_Boolean withMeshColor,
    Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate,
    Ring2_Boolean withTexture
  )
{
  MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_VisualsContext,
                                  generateDefaultShader,
                                  withMeshColor,
                                  withVertexColor,
                                  withTextureCoordinate,
                                  withTexture);
}

Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_generateShape2Shader
  (
    Ring3_VisualsContext* self
  )
{ MACHINE_VIRTUALCALL_RETURN_NOARGS(Ring3_VisualsContext, generateShape2Shader); }

Ring1_NoDiscardReturn() Ring3_GpuProgram*
Ring3_VisualsContext_generateText2Shader
  (
    Ring3_VisualsContext* self,
    Ring2_Boolean highPrecision
  )
{ MACHINE_VIRTUALCALL_RETURN_ARGS(Ring3_VisualsContext, generateText2Shader, highPrecision); }
