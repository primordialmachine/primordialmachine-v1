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
  self->setClearColor(self, clearColor);
}

Machine_Math_Vector4 const* Machine_VideoContext_getClearColor(Machine_VideoContext const* self) {
  return self->getClearColor(self);
}



void Machine_VideoContext_setIncomingBlendFunction(Machine_VideoContext* self, Machine_BlendFunction incomingBlendFunction) {
  self->setIncomingBlendFunction(self, incomingBlendFunction);
}

Machine_BlendFunction Machine_VideoContext_getIncomingBlendFunction(Machine_VideoContext const* self) {
  return self->getIncomingBlendFunction(self);
}



void Machine_VideoContext_setExistingBlendFunction(Machine_VideoContext* self, Machine_BlendFunction existingBlendFunction) {
  self->setExistingBlendFunction(self, existingBlendFunction);
}

Machine_BlendFunction Machine_VideoContext_getExistingBlendFunction(Machine_VideoContext const* self) {
  return self->getExistingBlendFunction(self);
}



void Machine_VideoContext_setDepthWriteEnabled(Machine_VideoContext* self, Machine_Boolean depthWriteEnabled) {
  self->setDepthWriteEnabled(self, depthWriteEnabled);
}

Machine_Boolean Machine_VideoContext_getDepthWriteEnabled(Machine_VideoContext const* self) {
  return self->getDepthWriteEnabled(self);
}



void Machine_VideoContext_setDepthTestFunction(Machine_VideoContext* self, Machine_DepthTestFunction depthTestFunction) {
  self->setDepthTestFunction(self, depthTestFunction);
}

Machine_DepthTestFunction Machine_VideoContext_getDepthTestFunction(Machine_VideoContext const* self) {
  return self->getDepthTestFunction(self);
}



void Machine_VideoContext_setClearDepth(Machine_VideoContext* self, Machine_Real clearDepth) {
  self->setClearDepth(self, clearDepth);
}

Machine_Real Machine_VideoContext_getClearDepth(Machine_VideoContext const* self) {
  return self->getClearDepth(self);
}



void Machine_VideoContext_setViewportRectangle(Machine_VideoContext* self, Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height) {
  self->setViewportRectangle(self, left, bottom, width, height);
}

void Machine_VideoContext_getViewportRectangle(Machine_VideoContext const* self, Machine_Real* left, Machine_Real* bottom, Machine_Real* width, Machine_Real* height) {
  self->getViewportRectangle(self, left, bottom, width, height);
}



Machine_Integer Machine_VideoContext_getMaximalClipDistanceCount(Machine_VideoContext const* self) {
  return self->getMaximalClipDistanceCount(self);
}

void Machine_VideoContext_setClipDistanceEnabled(Machine_VideoContext* self, Machine_Integer index, Machine_Boolean enabled) {
  self->setClipDistanceEnabled(self, index, enabled);
}

Machine_Boolean Machine_VideoContext_getClipDistanceEnabled(Machine_VideoContext const* self, Machine_Integer index) {
  return self->getClipDistanceEnabled(self, index);
}



void Machine_VideoContext_clearColorBuffer(Machine_VideoContext* self) {
  self->clearColorBuffer(self);
}

void Machine_VideoContext_clearDepthBuffer(Machine_VideoContext* self) {
  self->clearDepthBuffer(self);
}

Machine_Texture* Machine_VideoContext_createTextureFromImage(Machine_VideoContext* self, Machine_Image* image) {
  return self->createTextureFromImage(self, image);
}

Machine_VideoBuffer* Machine_VideoContext_createBuffer(Machine_VideoContext* self) {
  return self->createBuffer(self);
}

Machine_ShaderProgram* Machine_VideoContext_createProgram(Machine_VideoContext* self, Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText) {
  return self->createProgram(self, vertexProgramText, geometryProgramText, fragmentProgramText);
}

Machine_Binding* Machine_VideoContext_createBinding(Machine_VideoContext* self, Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  return self->createBinding(self, program, vertexDescriptor, buffer);
}

void Machine_VideoContext_drawDirect(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n) {
  self->drawDirect(self, i, n);
}

void Machine_VideoContext_drawIndirect(Machine_VideoContext* self, Machine_Integer i, Machine_Integer n, uint8_t const* indices) {
  self->drawIndirect(self, i, n, indices);
}



void Machine_VideoContext_bindTexture(Machine_VideoContext* self, size_t unit, Machine_Texture* texture) {
  self->bindTexture(self, unit, texture);
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
  return self->generateDefaultShader(self, withMeshColor, withVertexColor, withTextureCoordinate, withTexture);
}

Machine_ShaderProgram*
Machine_VideoContext_generateShape2Shader
  (
    Machine_VideoContext* self
  )
{
  return self->generateShape2Shader(self);
}

Machine_ShaderProgram*
Machine_VideoContext_generateText2Shader
  (
    Machine_VideoContext* self,
    Machine_Boolean highPrecision
  )
{
  return self->generateText2Shader(self, highPrecision);
}
