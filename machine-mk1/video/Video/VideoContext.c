/// @file Video/VideoContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "Video/VideoContext.h"


#include "Ring1/All/_Include.h"


static void Machine_VideoContext_visit(Machine_VideoContext* self) { /*Intentionally empty.*/
}

MACHINE_DEFINE_CLASSTYPE(Machine_VideoContext, Machine_Object, &Machine_VideoContext_visit,
                         &Machine_VideoContext_construct, NULL, NULL, NULL)

void Machine_VideoContext_construct(Machine_VideoContext* self, size_t numberOfArguments,
                                    Ring2_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_VideoContext_getType());
}

void Machine_VideoContext_setClearColor(Machine_VideoContext* self,
                                        Ring3_Math_Vector4f32 const* clearColor) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setClearColor, clearColor);
}

Ring3_Math_Vector4f32 const* Machine_VideoContext_getClearColor(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getClearColor);
}

void Machine_VideoContext_setIncomingBlendFunction(Machine_VideoContext* self,
                                                   Ring3_BlendFunction incomingBlendFunction) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setIncomingBlendFunction,
                                    incomingBlendFunction);
}

Ring3_BlendFunction Machine_VideoContext_getIncomingBlendFunction(
    Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getIncomingBlendFunction);
}

void Machine_VideoContext_setExistingBlendFunction(Machine_VideoContext* self,
                                                   Ring3_BlendFunction existingBlendFunction) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setExistingBlendFunction,
                                    existingBlendFunction);
}

Ring3_BlendFunction Machine_VideoContext_getExistingBlendFunction(
    Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getExistingBlendFunction);
}

void Machine_VideoContext_setDepthWriteEnabled(Machine_VideoContext* self,
                                               Ring2_Boolean depthWriteEnabled) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setDepthWriteEnabled, depthWriteEnabled);
}

Ring2_Boolean Machine_VideoContext_getDepthWriteEnabled(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getDepthWriteEnabled);
}

void Machine_VideoContext_setDepthTestFunction(Machine_VideoContext* self,
                                               Ring3_DepthTestFunction depthTestFunction) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setDepthTestFunction, depthTestFunction);
}

Ring3_DepthTestFunction Machine_VideoContext_getDepthTestFunction(
    Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getDepthTestFunction);
}

void Machine_VideoContext_setClearDepth(Machine_VideoContext* self, Ring2_Real32 clearDepth) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setClearDepth, clearDepth);
}

Ring2_Real32 Machine_VideoContext_getClearDepth(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getClearDepth);
}

void Machine_VideoContext_setViewportRectangle(Machine_VideoContext* self, Ring2_Real32 left,
                                               Ring2_Real32 bottom, Ring2_Real32 width,
                                               Ring2_Real32 height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setViewportRectangle, left, bottom, width,
                                    height);
}

void Machine_VideoContext_getViewportRectangle(Machine_VideoContext const* self, Ring2_Real32* left,
                                               Ring2_Real32* bottom, Ring2_Real32* width,
                                               Ring2_Real32* height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, getViewportRectangle, left, bottom, width,
                                    height);
}

Ring2_Integer Machine_VideoContext_getMaximalClipDistanceCount(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getMaximalClipDistanceCount);
}

void Machine_VideoContext_setClipDistanceEnabled(Machine_VideoContext* self, Ring2_Integer index,
                                                 Ring2_Boolean enabled) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setClipDistanceEnabled, index, enabled);
}

Ring2_Boolean Machine_VideoContext_getClipDistanceEnabled(Machine_VideoContext const* self,
                                                          Ring2_Integer index) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, getClipDistanceEnabled, index);
}

void Machine_VideoContext_clearColorBuffer(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_VideoContext, clearColorBuffer);
}

void Machine_VideoContext_clearDepthBuffer(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_VideoContext, clearDepthBuffer);
}

Ring3_Texture* Machine_VideoContext_createTextureFromImage(Machine_VideoContext* self,
                                                           Ring3_Image* image) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, createTextureFromImage, image);
}

Ring3_GpuBuffer* Machine_VideoContext_createBuffer(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, createBuffer);
}

Machine_ShaderProgram* Machine_VideoContext_createProgram(Machine_VideoContext* self,
                                                          Ring2_String* vertexProgramText,
                                                          Ring2_String* geometryProgramText,
                                                          Ring2_String* fragmentProgramText) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, createProgram, vertexProgramText,
                                  geometryProgramText, fragmentProgramText);
}

Machine_Binding* Machine_VideoContext_createBinding(Machine_VideoContext* self,
                                                    Machine_ShaderProgram* program,
                                                    Ring3_VertexDescriptor* vertexDescriptor,
                                                    Ring3_GpuBuffer* buffer) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, createBinding, program, vertexDescriptor,
                                  buffer);
}

void Machine_VideoContext_drawDirect(Machine_VideoContext* self, Ring2_Integer i,
                                     Ring2_Integer n) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, drawDirect, i, n);
}

void Machine_VideoContext_drawIndirect(Machine_VideoContext* self, Ring2_Integer i,
                                       Ring2_Integer n, uint8_t const* indices) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, drawIndirect, i, n, indices);
}

void Machine_VideoContext_bindTexture(Machine_VideoContext* self, size_t unit,
                                      Ring3_Texture* texture) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, bindTexture, unit, texture);
}

Machine_ShaderProgram* Machine_VideoContext_generateDefaultShader(
    Machine_VideoContext* self, Ring2_Boolean withMeshColor, Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate, Ring2_Boolean withTexture) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, generateDefaultShader, withMeshColor,
                                  withVertexColor, withTextureCoordinate, withTexture);
}

Machine_ShaderProgram* Machine_VideoContext_generateShape2Shader(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, generateShape2Shader);
}

Machine_ShaderProgram* Machine_VideoContext_generateText2Shader(Machine_VideoContext* self,
                                                                Ring2_Boolean highPrecision) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, generateText2Shader, highPrecision);
}
