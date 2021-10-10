/// @file Video/VideoContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_PRIVATE (1)
#include "./../Video/VideoContext.h"

static void Machine_VideoContext_visit(Machine_VideoContext* self)
{/*Intentionally empty.*/}

static void Machine_VideoContext_destruct(Machine_VideoContext* self)
{/*Intentionally empty.*/}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_VideoContext, Machine_Object, &Machine_VideoContext_visit, &Machine_VideoContext_construct, &Machine_VideoContext_destruct)

static void Machine_VideoContext_constructClass(Machine_VideoContext_Class *self)
{/*Intentionally empty.*/}

void Machine_VideoContext_construct(Machine_VideoContext* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  Machine_setClassType((Machine_Object*)self, Machine_VideoContext_getClassType());
}

void Machine_VideoContext_setClearColor(Machine_VideoContext* self, Machine_Math_Vector4 const* clearColor) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setClearColor, clearColor);
}

Machine_Math_Vector4 const* Machine_VideoContext_getClearColor(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getClearColor);
}



void Machine_VideoContext_setIncomingBlendFunction(Machine_VideoContext* self, Machine_BlendFunction incomingBlendFunction) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setIncomingBlendFunction, incomingBlendFunction);
}

Machine_BlendFunction Machine_VideoContext_getIncomingBlendFunction(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getIncomingBlendFunction);
}



void Machine_VideoContext_setExistingBlendFunction(Machine_VideoContext* self, Machine_BlendFunction existingBlendFunction) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setExistingBlendFunction, existingBlendFunction);
}

Machine_BlendFunction Machine_VideoContext_getExistingBlendFunction(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getExistingBlendFunction);
}



void Machine_VideoContext_setDepthWriteEnabled(Machine_VideoContext* self, Machine_Boolean depthWriteEnabled) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setDepthWriteEnabled, depthWriteEnabled);
}

Machine_Boolean Machine_VideoContext_getDepthWriteEnabled(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getDepthWriteEnabled);
}



void Machine_VideoContext_setDepthTestFunction(Machine_VideoContext* self, Machine_DepthTestFunction depthTestFunction) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setDepthTestFunction, depthTestFunction);
}

Machine_DepthTestFunction Machine_VideoContext_getDepthTestFunction(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getDepthTestFunction);
}



void Machine_VideoContext_setClearDepth(Machine_VideoContext* self, Machine_Real clearDepth) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setClearDepth, clearDepth);
}

Machine_Real Machine_VideoContext_getClearDepth(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getClearDepth);
}



void Machine_VideoContext_setViewportRectangle(Machine_VideoContext* self, Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setViewportRectangle, left, bottom, width, height);
}

void Machine_VideoContext_getViewportRectangle(Machine_VideoContext const* self, Machine_Real* left, Machine_Real* bottom, Machine_Real* width, Machine_Real* height) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, getViewportRectangle, left, bottom, width, height);
}



Machine_Integer Machine_VideoContext_getMaximalClipDistanceCount(Machine_VideoContext const* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, getMaximalClipDistanceCount);
}

void Machine_VideoContext_setClipDistanceEnabled(Machine_VideoContext* self, Machine_Integer index, Machine_Boolean enabled) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, setClipDistanceEnabled, index, enabled);
}

Machine_Boolean Machine_VideoContext_getClipDistanceEnabled(Machine_VideoContext const* self, Machine_Integer index) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, getClipDistanceEnabled, index);
}



void Machine_VideoContext_clearColorBuffer(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_VideoContext, clearColorBuffer);
}

void Machine_VideoContext_clearDepthBuffer(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_VideoContext, clearDepthBuffer);
}

Machine_Texture* Machine_VideoContext_createTextureFromImage(Machine_VideoContext* self, Machine_Image* image) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, createTextureFromImage, image);
}

Machine_VideoBuffer* Machine_VideoContext_createBuffer(Machine_VideoContext* self) {
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, createBuffer);
}

Machine_ShaderProgram* Machine_VideoContext_createProgram(Machine_VideoContext* self, Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, createProgram, vertexProgramText, geometryProgramText, fragmentProgramText);
}

Machine_Binding* Machine_VideoContext_createBinding(Machine_VideoContext* self, Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, createBinding, program, vertexDescriptor, buffer);
}

void Machine_VideoContext_drawDirect(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, drawDirect, i, n);
}

void Machine_VideoContext_drawIndirect(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n, uint8_t const* indices) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, drawIndirect, i, n, indices);
}



void Machine_VideoContext_bindTexture(Machine_VideoContext* self, size_t unit, Machine_Texture* texture) {
  MACHINE_VIRTUALCALL_NORETURN_ARGS(Machine_VideoContext, bindTexture, unit, texture);
}



Machine_ShaderProgram*
Machine_VideoContext_generateDefaultShader
  (
    Machine_VideoContext* self,
    Machine_Boolean withMeshColor,
    Machine_Boolean withVertexColor,
    Machine_Boolean withTextureCoordinate,
    Machine_Boolean withTexture
  )
{
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, generateDefaultShader, withMeshColor, withVertexColor, withTextureCoordinate, withTexture);
}

Machine_ShaderProgram*
Machine_VideoContext_generateShape2Shader
  (
    Machine_VideoContext* self
  )
{
  MACHINE_VIRTUALCALL_RETURN_NOARGS(Machine_VideoContext, generateShape2Shader);
}

Machine_ShaderProgram*
Machine_VideoContext_generateText2Shader
  (
    Machine_VideoContext* self,
    Machine_Boolean highPrecision
  )
{
  MACHINE_VIRTUALCALL_RETURN_ARGS(Machine_VideoContext, generateText2Shader, highPrecision);
}
