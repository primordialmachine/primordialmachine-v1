/// @file Ring3/Visuals/Gl/VideoContext.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/VideoContext.h"

#include "Ring3/Visuals/Gl/Binding.h"
#include "Ring3/Visuals/Gl/Buffer.h"
#include "Ring3/Visuals/Gl/Canvas.package.h"
#include "Ring3/Visuals/Gl/ShaderProgram.h"
#include "Ring3/Visuals/Gl/Texture.h"
#include "Ring3/Visuals/Gl/UtilitiesGL.h"
#undef RING3_VISUALS_GL_PRIVATE

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include <stdio.h>


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
setDepthTestFunction
  (
    Machine_Gl_VideoContext* self,
    Ring3_DepthTestFunction depthTestFunction
  )
{ self->depthTestFunction = depthTestFunction; }

static Ring3_DepthTestFunction
getDepthTestFunction
  (
    Machine_Gl_VideoContext const* self
  )
{ return self->depthTestFunction; }



static void
setDepthWriteEnabled
  (
    Machine_Gl_VideoContext* self,
    Ring2_Boolean depthWriteEnabled
  )
{ self->depthWriteEnabled = depthWriteEnabled; }

static Ring2_Boolean
getDepthWriteEnabled
  (
    Machine_Gl_VideoContext const* self
  )
{ return self->depthWriteEnabled; }



static void
setClearDepth
  (
    Machine_Gl_VideoContext* self,
    Ring2_Real32 clearDepth
  )
{ self->clearDepth = clearDepth; }

static Ring2_Real32
getClearDepth
  (
    Machine_Gl_VideoContext const* self
  )
{ return self->clearDepth; }



static Ring2_Integer
getMaximalClipDistanceCount
  (
    Machine_Gl_VideoContext const* self
  )
{ return self->clipDistances->n; }

static void
setClipDistanceEnabled
  (
    Machine_Gl_VideoContext* self,
    Ring2_Integer index,
    Ring2_Boolean enabled
  )
{
  if (index < 0 || index >= self->clipDistances->n) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  self->clipDistances->a[index].enabled = enabled;
}

static Ring2_Boolean
getClipDistanceEnabled
  (
    Machine_Gl_VideoContext const* self,
    Ring2_Integer index
  )
{
  if (index < 0 || index >= self->clipDistances->n) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->clipDistances->a[index].enabled;
}



static void
setIncomingBlendFunction
  (
    Machine_Gl_VideoContext* self,
    Ring3_BlendFunction incomingBlendFunction
  )
{ self->incomingBlendFunction = incomingBlendFunction; }

static Ring3_BlendFunction
getIncomingBlendFunction
  (
    Machine_Gl_VideoContext const* self
  )
{ return self->incomingBlendFunction; }



static void
setExistingBlendFunction
  (
    Machine_Gl_VideoContext* self,
    Ring3_BlendFunction existingBlendFunction
  )
{ self->existingBlendFunction = existingBlendFunction; }

static Ring3_BlendFunction
getExistingBlendFunction
  (
    Machine_Gl_VideoContext const* self
  )
{ return self->existingBlendFunction; }



static void
setClearColor
  (
    Machine_Gl_VideoContext* self,
    Ring3_Math_Vector4f32 const* clearColor
  )
{
  self->clearColor[0] = Ring3_Math_Vector4f32_getX(clearColor);
  self->clearColor[1] = Ring3_Math_Vector4f32_getY(clearColor);
  self->clearColor[2] = Ring3_Math_Vector4f32_getZ(clearColor);
  self->clearColor[3] = Ring3_Math_Vector4f32_getW(clearColor);
}

Ring3_Math_Vector4f32 const*
getClearColor
  (
    Machine_Gl_VideoContext const* self
  )
{
  Ring3_Math_Vector4f32* clearColor = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(clearColor, self->clearColor[0], self->clearColor[1], 
                                        self->clearColor[2], self->clearColor[3]);
  return clearColor;
}



static void
setViewportRectangle
  (
    Machine_Gl_VideoContext* self,
    Ring2_Real32 left,
    Ring2_Real32 bottom,
    Ring2_Real32 width,
    Ring2_Real32 height
  )
{
  self->viewportRectangle->x = left;
  self->viewportRectangle->y = bottom;
  self->viewportRectangle->w = width;
  self->viewportRectangle->h = height;
}

static void
getViewportRectangle
  (
    Machine_Gl_VideoContext const* self,
    Ring2_Real32* left,
    Ring2_Real32* bottom,
    Ring2_Real32* width,
    Ring2_Real32* height
  )
{
  *left = self->viewportRectangle->x;
  *bottom = self->viewportRectangle->y;
  *width = self->viewportRectangle->w;
  *height = self->viewportRectangle->h;
}



static void
drawDirect
  (
    Machine_Gl_VideoContext* self,
    Ring2_Integer i,
    Ring2_Integer n
  )
{
  if (i < 0 || n < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (n > 0) {
    Machine_Gl_VideoContext_write(self);
    Machine_UtilitiesGl_call(glDrawArrays(GL_TRIANGLES, i, n));
  }
}

static void
drawIndirect
  (
    Machine_Gl_VideoContext* self,
    Ring2_Integer i,
    Ring2_Integer n,
    uint8_t const* indices
  )
{
  if (i < 0 || n < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (n > 0) {
    Machine_Gl_VideoContext_write(self);
    Machine_UtilitiesGl_call(glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_BYTE, indices + i));
  }
}

static void
clearColorBuffer
  (
    Machine_Gl_VideoContext* self
  )
{
  Machine_Gl_VideoContext_write(self);
  glEnable(GL_SCISSOR_TEST);
  glScissor(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));
  glDisable(GL_SCISSOR_TEST);
}

static void
clearDepthBuffer
  (
    Machine_Gl_VideoContext* self
  )
{
  Machine_Gl_VideoContext_write(self);
  glEnable(GL_SCISSOR_TEST);
  glScissor(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
  Machine_UtilitiesGl_call(glClear(GL_DEPTH_BUFFER_BIT));
  glDisable(GL_SCISSOR_TEST);
}


static Ring3_GpuBuffer*
createBuffer
  (
    Machine_Gl_VideoContext *self
  )
{ return (Ring3_GpuBuffer*)Machine_Gl_VideoBuffer_create(); }

static Ring3_Texture*
createTextureFromImage
  (
    Machine_Gl_VideoContext* self, Ring3_Image* image
  )
{ return (Ring3_Texture*)Machine_Gl_Texture_create(image); }

static Ring3_GpuProgram*
createProgram
  (
    Machine_Gl_VideoContext* self,
    Ring2_String* vertexProgramText,
    Ring2_String* geometryProgramText,
    Ring2_String* fragmentProgramText
  )
{ return (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_create(vertexProgramText, geometryProgramText, fragmentProgramText); }

static Ring3_Binding*
createBinding
  (
    Machine_Gl_VideoContext* self,
    Ring3_GpuProgram* program,
    Ring3_VertexDescriptor* vertexDescriptor,
    Ring3_GpuBuffer* buffer
  )
{ return (Ring3_Binding*)Machine_Gl_Binding_create(program, vertexDescriptor, buffer); }



static void
bindTexture
  (
    Machine_Gl_VideoContext* self,
    size_t textureUnit,
    Ring3_Texture* texture
  )
{
  Machine_Gl_Texture* textureGL = (Machine_Gl_Texture*)texture;
  Machine_UtilitiesGl_call(glActiveTexture(GL_TEXTURE0 + textureUnit));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, textureGL->id));
}



static Ring3_GpuProgram*
generateDefaultShader
  (
    Machine_Gl_VideoContext* self,
    Ring2_Boolean withMeshColor,
    Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate,
    Ring2_Boolean withTexture
  )
{
  return (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_generateDefaultShader(withMeshColor, withVertexColor, withTextureCoordinate, withTexture);
}

static Ring3_GpuProgram*
generateShape2Shader
  (
    Machine_Gl_VideoContext* self
  )
{
  return (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_generateShape2Shader();
}

static Ring3_GpuProgram*
generateText2Shader
  (
    Machine_Gl_VideoContext* self,
    Ring2_Boolean highPrecision
  )
{
  return (Ring3_GpuProgram*)Machine_Gl_ShaderProgram_generateText2Shader(highPrecision);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void
Machine_Gl_VideoContext_visit
  (
    Machine_Gl_VideoContext* self
  )
{
  if (self->viewportRectangle) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->viewportRectangle);
  }
}

static void
Machine_Gl_VideoContext_destruct
  (
    Machine_Gl_VideoContext* self
  )
{
  if (self->clipDistances) {
    Ring1_Memory_deallocate(self->clipDistances->a);
    self->clipDistances->a = NULL;
    Ring1_Memory_deallocate(self->clipDistances);
    self->clipDistances = NULL;
  }
}

/// @EXTENSION 
static GLenum
Machine_BlendFunction_toGL
  (
    Ring3_BlendFunction self
  )
{
  switch (self) {
  case Ring3_BlendFunction_IncomingAlpha:
    return GL_SRC_ALPHA;
  case Ring3_BlendFunction_OneMinusIncomingAlpha:
    return GL_ONE_MINUS_SRC_ALPHA;
  case Ring3_BlendFunction_Zero:
    return GL_ZERO;
  case Ring3_BlendFunction_One:
    return GL_ONE;
  default:
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  };
}

/// @EXTENSION
static GLenum
Machine_DepthTestFunction_toGL
  (
    Ring3_DepthTestFunction self
  )
{
  switch (self) {
  case Ring3_DepthTestFunction_LessThan:
    return GL_LESS;
  case Ring3_DepthTestFunction_LessThanOrEqualTo:
    return GL_LEQUAL;
  case Ring3_DepthTestFunction_EqualTo:
    return GL_EQUAL;
  case Ring3_DepthTestFunction_GreaterThan:
    return GL_GREATER;
  case Ring3_DepthTestFunction_GreaterThanOrEqualTo:
    return GL_GEQUAL;
  case Ring3_DepthTestFunction_Always:
    return GL_ALWAYS;
  case Ring3_DepthTestFunction_Never:
    return GL_NEVER;
  default:
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  };
}

static void
write
  (
    Machine_Gl_VideoContext const* self
  )
{
  // Depth testing.
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(Machine_DepthTestFunction_toGL(self->depthTestFunction));

  // Depth writing.
  glDepthMask(self->depthWriteEnabled ? GL_TRUE : GL_FALSE);

  // Blending.
  glEnable(GL_BLEND);
  glBlendFunc(Machine_BlendFunction_toGL(self->incomingBlendFunction), Machine_BlendFunction_toGL(self->existingBlendFunction));

  // Clear depth.
  glClearDepth(self->clearDepth);

  // Clear color.
  glClearColor(self->clearColor[0], self->clearColor[1], self->clearColor[2], self->clearColor[3]);

  // Clip distances.
  for (size_t i = 0, n = self->clipDistances->n; i < n; ++i) {
    Ring2_Boolean enabled = self->clipDistances->a[i].enabled;
    enabled ? glEnable(GL_CLIP_DISTANCE0 + i) : glDisable(GL_CLIP_DISTANCE0 + i);
  }

  // Viewport rectangle & scissor rectangle.
  glViewport(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
  glEnable(GL_SCISSOR_TEST);
  glScissor(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
}

static void
Machine_Gl_VideoContext_constructClass
  (
    Machine_Gl_VideoContext_Class* self
  )
{
  self->write = &write;

  ((Ring3_VisualsContext_Class*)self)->setDepthTestFunction = (void (*)(Ring3_VisualsContext*, Ring3_DepthTestFunction)) & setDepthTestFunction;
  ((Ring3_VisualsContext_Class*)self)->getDepthTestFunction = (Ring3_DepthTestFunction(*)(Ring3_VisualsContext const*)) & getDepthTestFunction;

  ((Ring3_VisualsContext_Class*)self)->setDepthWriteEnabled = (void (*)(Ring3_VisualsContext*, Ring2_Boolean)) & setDepthWriteEnabled;
  ((Ring3_VisualsContext_Class*)self)->getDepthWriteEnabled = (Ring2_Boolean(*)(Ring3_VisualsContext const*)) & getDepthWriteEnabled;

  ((Ring3_VisualsContext_Class*)self)->setClearDepth = (void (*)(Ring3_VisualsContext*, Ring2_Real32)) & setClearDepth;
  ((Ring3_VisualsContext_Class*)self)->getClearDepth = (Ring2_Real32(*)(Ring3_VisualsContext const*)) & getClearDepth;

  ((Ring3_VisualsContext_Class*)self)->getMaximalClipDistanceCount = (Ring2_Integer(*)(Ring3_VisualsContext const*)) & getMaximalClipDistanceCount;
  ((Ring3_VisualsContext_Class*)self)->setClipDistanceEnabled = (void (*)(Ring3_VisualsContext*, Ring2_Integer index, Ring2_Boolean)) & setClipDistanceEnabled;
  ((Ring3_VisualsContext_Class*)self)->getClipDistanceEnabled = (Ring2_Boolean(*)(Ring3_VisualsContext const*, Ring2_Integer index)) & getClipDistanceEnabled;

  ((Ring3_VisualsContext_Class*)self)->setIncomingBlendFunction = (void (*)(Ring3_VisualsContext*, Ring3_BlendFunction)) & setIncomingBlendFunction;
  ((Ring3_VisualsContext_Class*)self)->getIncomingBlendFunction = (Ring3_BlendFunction(*)(Ring3_VisualsContext const*)) & getIncomingBlendFunction;

  ((Ring3_VisualsContext_Class*)self)->setExistingBlendFunction = (void (*)(Ring3_VisualsContext*, Ring3_BlendFunction)) & setExistingBlendFunction;
  ((Ring3_VisualsContext_Class*)self)->getExistingBlendFunction = (Ring3_BlendFunction(*)(Ring3_VisualsContext const*)) & getExistingBlendFunction;

  ((Ring3_VisualsContext_Class*)self)->setClearColor = (void (*)(Ring3_VisualsContext*, Ring3_Math_Vector4f32 const*)) & setClearColor;
  ((Ring3_VisualsContext_Class*)self)->getClearColor = (Ring3_Math_Vector4f32 const* (*)(Ring3_VisualsContext const*)) & getClearColor;

  ((Ring3_VisualsContext_Class*)self)->setViewportRectangle = (void (*)(Ring3_VisualsContext*, Ring2_Real32, Ring2_Real32, Ring2_Real32, Ring2_Real32)) & setViewportRectangle;
  ((Ring3_VisualsContext_Class*)self)->getViewportRectangle = (void (*)(Ring3_VisualsContext const*, Ring2_Real32*, Ring2_Real32*, Ring2_Real32*, Ring2_Real32*)) & getViewportRectangle;

  ((Ring3_VisualsContext_Class*)self)->drawDirect = (void (*)(Ring3_VisualsContext*, Ring2_Integer, Ring2_Integer)) & drawDirect;
  ((Ring3_VisualsContext_Class*)self)->drawIndirect = (void (*)(Ring3_VisualsContext*, Ring2_Integer, Ring2_Integer, uint8_t const*)) & drawIndirect;

  ((Ring3_VisualsContext_Class*)self)->clearColorBuffer = (void (*)(Ring3_VisualsContext*)) & clearColorBuffer;
  ((Ring3_VisualsContext_Class*)self)->clearDepthBuffer = (void (*)(Ring3_VisualsContext*)) & clearDepthBuffer;

  ((Ring3_VisualsContext_Class*)self)->createBuffer = (Ring3_GpuBuffer * (*)(Ring3_VisualsContext*)) & createBuffer;
  ((Ring3_VisualsContext_Class*)self)->createTextureFromImage = (Ring3_Texture * (*)(Ring3_VisualsContext*, Ring3_Image*)) & createTextureFromImage;
  ((Ring3_VisualsContext_Class*)self)->createProgram = (Ring3_GpuProgram * (*)(Ring3_VisualsContext*, Ring2_String*, Ring2_String*, Ring2_String*)) & createProgram;
  ((Ring3_VisualsContext_Class*)self)->createBinding = (Ring3_Binding * (*)(Ring3_VisualsContext*, Ring3_GpuProgram*, Ring3_VertexDescriptor*, Ring3_GpuBuffer*)) & createBinding;

  ((Ring3_VisualsContext_Class*)self)->bindTexture = (void (*)(Ring3_VisualsContext*, size_t, Ring3_Texture*)) & bindTexture;

  ((Ring3_VisualsContext_Class*)self)->generateDefaultShader = (Ring3_GpuProgram * (*)(Ring3_VisualsContext*, Ring2_Boolean, Ring2_Boolean, Ring2_Boolean, Ring2_Boolean)) & generateDefaultShader;
  ((Ring3_VisualsContext_Class*)self)->generateShape2Shader = (Ring3_GpuProgram * (*)(Ring3_VisualsContext*)) & generateShape2Shader;
  ((Ring3_VisualsContext_Class*)self)->generateText2Shader = (Ring3_GpuProgram * (*)(Ring3_VisualsContext*, Ring2_Boolean)) & generateText2Shader;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_VideoContext,
                         Ring3_VisualsContext,
                         &Machine_Gl_VideoContext_visit,
                         &Machine_Gl_VideoContext_construct,
                         &Machine_Gl_VideoContext_destruct,
                         &Machine_Gl_VideoContext_constructClass,
                         NULL)

void
Machine_Gl_VideoContext_construct
  (
    Machine_Gl_VideoContext* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Ring3_VisualsContext_construct((Ring3_VisualsContext*)self, numberOfArguments, arguments);
  self->clearColor[0] = 0.f;
  self->clearColor[1] = 0.f;
  self->clearColor[2] = 0.f;
  self->clearColor[3] = 0.f;
  self->clearDepth = 1.f;
  self->depthTestFunction = Ring3_DepthTestFunction_Always;
  self->depthWriteEnabled = false;
  self->existingBlendFunction = Ring3_BlendFunction_OneMinusIncomingAlpha;
  self->incomingBlendFunction = Ring3_BlendFunction_IncomingAlpha;
  {
    Ring2_Integer width, height;
    int w, h;
    glfwGetFramebufferSize(Ring3_Visuals_Gl_Glfw_getWindow(), &w, &h);
    width = w; height = h;
    self->viewportRectangle = Ring3_Math_Rectangle2_create();
    Ring3_Math_Vector2f32* v;
    v = Ring3_Math_Vector2f32_create();
    Ring3_Math_Vector2f32_set(v, 0.f, 0.f);
    Ring3_Math_Rectangle2_setPosition(self->viewportRectangle, v);
    Ring3_Math_Vector2f32_set(v, (Ring2_Real32)width, (Ring2_Real32)height);
    Ring3_Math_Rectangle2_setSize(self->viewportRectangle, v);
  }
  {
    GLint v;
    Machine_UtilitiesGl_call(glGetIntegerv(GL_MAX_CLIP_DISTANCES, &v));
    if (v <= 0) {
      Ring1_Status_set(Ring1_Status_EnvironmentFailed);
      Ring2_jump();
    }
    self->clipDistances = NULL;
    if (Ring1_Memory_allocate(&self->clipDistances, sizeof(Machine_Gl_VideoContext_ClipDistances))) {
      Ring2_jump();
    }
    self->clipDistances->a = NULL;
    if (Ring1_Memory_allocateArray(&self->clipDistances->a, (size_t)v,
                                   sizeof(Machine_Gl_VideoContext_ClipDistance))) {
      Ring1_Memory_deallocate(self->clipDistances);
      self->clipDistances = NULL;
      Ring2_jump();
    }
    self->clipDistances->n = (size_t)v;
    for (size_t i = 0; i < self->clipDistances->n; ++i) {
      self->clipDistances->a[i].enabled = false;
    }
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Gl_VideoContext_getType());
}

Machine_Gl_VideoContext*
Machine_Gl_VideoContext_create
  (
  )
{
  Machine_Type* ty = Machine_Gl_VideoContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Gl_VideoContext* self = Ring1_cast(Machine_Gl_VideoContext*,Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

void
Machine_Gl_VideoContext_write
  (
    Machine_Gl_VideoContext const* self
  )
{ MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Gl_VideoContext, write); }
