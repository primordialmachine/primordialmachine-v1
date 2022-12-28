/// @file Video/Gl/VideoContext.c
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "Video/Gl/VideoContext.h"


#include "Ring1/All/_Include.h"
#include "Video/Gl/UtilitiesGL.h"
#include "Video/Gl/Binding.h"
#include "Video/Gl/Buffer.h"
#include "Video/Gl/Canvas.h"
#include "Video/Gl/CanvasUtilities.h"
#include "Video/Gl/ShaderProgram.h"
#include "Video/Gl/Texture.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void setDepthTestFunction(Machine_Gl_VideoContext* self, Ring3_DepthTestFunction depthTestFunction) {
  self->depthTestFunction = depthTestFunction;
}

static Ring3_DepthTestFunction getDepthTestFunction(Machine_Gl_VideoContext const* self) {
  return self->depthTestFunction;
}



static void setDepthWriteEnabled(Machine_Gl_VideoContext* self, Ring2_Boolean depthWriteEnabled) {
  self->depthWriteEnabled = depthWriteEnabled;
}

static Ring2_Boolean getDepthWriteEnabled(Machine_Gl_VideoContext const* self) {
  return self->depthWriteEnabled;
}



static void setClearDepth(Machine_Gl_VideoContext* self, Ring2_Real32 clearDepth) {
  self->clearDepth = clearDepth;
}

static Ring2_Real32 getClearDepth(Machine_Gl_VideoContext const* self) {
  return self->clearDepth;
}



static Ring2_Integer getMaximalClipDistanceCount(Machine_Gl_VideoContext const* self) {
  return self->clipDistances->n;
}

static void setClipDistanceEnabled(Machine_Gl_VideoContext* self, Ring2_Integer index, Ring2_Boolean enabled) {
  if (index < 0 || index >= self->clipDistances->n) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  self->clipDistances->a[index].enabled = enabled;
}

static Ring2_Boolean getClipDistanceEnabled(Machine_Gl_VideoContext const* self, Ring2_Integer index) {
  if (index < 0 || index >= self->clipDistances->n) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->clipDistances->a[index].enabled;
}



static void setIncomingBlendFunction(Machine_Gl_VideoContext* self, Ring3_BlendFunction incomingBlendFunction) {
  self->incomingBlendFunction = incomingBlendFunction;
}

static Ring3_BlendFunction getIncomingBlendFunction(Machine_Gl_VideoContext const* self) {
  return self->incomingBlendFunction;
}



static void setExistingBlendFunction(Machine_Gl_VideoContext* self, Ring3_BlendFunction existingBlendFunction) {
  self->existingBlendFunction = existingBlendFunction;
}

static Ring3_BlendFunction getExistingBlendFunction(Machine_Gl_VideoContext const* self) {
  return self->existingBlendFunction;
}



static void setClearColor(Machine_Gl_VideoContext* self, Ring3_Math_Vector4f32 const* clearColor) {
  self->clearColor[0] = Ring3_Math_Vector4f32_getX(clearColor);
  self->clearColor[1] = Ring3_Math_Vector4f32_getY(clearColor);
  self->clearColor[2] = Ring3_Math_Vector4f32_getZ(clearColor);
  self->clearColor[3] = Ring3_Math_Vector4f32_getW(clearColor);
}

Ring3_Math_Vector4f32 const* getClearColor(Machine_Gl_VideoContext const* self) {
  Ring3_Math_Vector4f32* clearColor = Ring3_Math_Vector4f32_create();
  Ring3_Math_Vector4f32_set(clearColor, self->clearColor[0], self->clearColor[1], 
                                        self->clearColor[2], self->clearColor[3]);
  return clearColor;
}



static void setViewportRectangle(Machine_Gl_VideoContext* self, Ring2_Real32 left, Ring2_Real32 bottom, Ring2_Real32 width, Ring2_Real32 height) {
  self->viewportRectangle->x = left;
  self->viewportRectangle->y = bottom;
  self->viewportRectangle->w = width;
  self->viewportRectangle->h = height;
}

static void getViewportRectangle(Machine_Gl_VideoContext const* self, Ring2_Real32* left, Ring2_Real32* bottom, Ring2_Real32* width, Ring2_Real32* height) {
  *left = self->viewportRectangle->x;
  *bottom = self->viewportRectangle->y;
  *width = self->viewportRectangle->w;
  *height = self->viewportRectangle->h;
}



static void drawDirect(Machine_Gl_VideoContext* self, Ring2_Integer i, Ring2_Integer n) {
  if (i < 0 || n < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (n > 0) {
    Machine_Gl_VideoContext_write(self);
    Machine_UtilitiesGl_call(glDrawArrays(GL_TRIANGLES, i, n));
  }
}

static void drawIndirect(Machine_Gl_VideoContext* self, Ring2_Integer i, Ring2_Integer n, uint8_t const* indices) {
  if (i < 0 || n < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (n > 0) {
    Machine_Gl_VideoContext_write(self);
    Machine_UtilitiesGl_call(glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_BYTE, indices + i));
  }
}

static void clearColorBuffer(Machine_Gl_VideoContext* self) {
  Machine_Gl_VideoContext_write(self);
  glEnable(GL_SCISSOR_TEST);
  glScissor(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));
  glDisable(GL_SCISSOR_TEST);
}

static void clearDepthBuffer(Machine_Gl_VideoContext* self) {
  Machine_Gl_VideoContext_write(self);
  glEnable(GL_SCISSOR_TEST);
  glScissor(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
  Machine_UtilitiesGl_call(glClear(GL_DEPTH_BUFFER_BIT));
  glDisable(GL_SCISSOR_TEST);
}


static Machine_VideoBuffer* createBuffer(Machine_Gl_VideoContext *self) {
  return (Machine_VideoBuffer*)Machine_Gl_VideoBuffer_create();
}

static Ring3_Texture* createTextureFromImage(Machine_Gl_VideoContext* self, Ring3_Image* image) {
  return (Ring3_Texture*)Machine_Gl_Texture_create(image);
}

static Machine_ShaderProgram* createProgram(Machine_Gl_VideoContext* self, Ring2_String* vertexProgramText, Ring2_String* geometryProgramText, Ring2_String* fragmentProgramText) {
  return (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_create(vertexProgramText, geometryProgramText, fragmentProgramText);
}

static Machine_Binding* createBinding(Machine_Gl_VideoContext* self, Machine_ShaderProgram* program, Ring3_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  return (Machine_Binding*)Machine_Gl_Binding_create(program, vertexDescriptor, buffer);
}



static void bindTexture(Machine_Gl_VideoContext* self, size_t textureUnit, Ring3_Texture* texture) {
  Machine_Gl_Texture* textureGL = (Machine_Gl_Texture*)texture;
  Machine_UtilitiesGl_call(glActiveTexture(GL_TEXTURE0 + textureUnit));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, textureGL->id));
}



static Machine_ShaderProgram*
generateDefaultShader
  (
    Machine_Gl_VideoContext* self,
    Ring2_Boolean withMeshColor,
    Ring2_Boolean withVertexColor,
    Ring2_Boolean withTextureCoordinate,
    Ring2_Boolean withTexture
  )
{
  return (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_generateDefaultShader(withMeshColor, withVertexColor, withTextureCoordinate, withTexture);
}

static Machine_ShaderProgram*
generateShape2Shader
  (
    Machine_Gl_VideoContext* self
  )
{
  return (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_generateShape2Shader();
}

static Machine_ShaderProgram*
generateText2Shader
  (
    Machine_Gl_VideoContext* self,
    Ring2_Boolean highPrecision
  )
{
  return (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_generateText2Shader(highPrecision);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Gl_VideoContext_visit(Machine_Gl_VideoContext* self) {
  if (self->viewportRectangle) {
    Ring2_Gc_visit(Ring2_Gc_get(), self->viewportRectangle);
  }
}

static void Machine_Gl_VideoContext_destruct(Machine_Gl_VideoContext* self) {
  if (self->clipDistances) {
    Ring1_Memory_deallocate(self->clipDistances->a);
    self->clipDistances->a = NULL;
    Ring1_Memory_deallocate(self->clipDistances);
    self->clipDistances = NULL;
  }
}

/// @EXTENSION 
static GLenum Machine_BlendFunction_toGL(Ring3_BlendFunction self) {
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
static GLenum Machine_DepthTestFunction_toGL(Ring3_DepthTestFunction self) {
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

static void write(Machine_Gl_VideoContext const* self) {
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

static void Machine_Gl_VideoContext_constructClass(Machine_Gl_VideoContext_Class* self) {
  self->write = &write;

  ((Machine_VideoContext_Class*)self)->setDepthTestFunction = (void (*)(Machine_VideoContext*, Ring3_DepthTestFunction)) & setDepthTestFunction;
  ((Machine_VideoContext_Class*)self)->getDepthTestFunction = (Ring3_DepthTestFunction(*)(Machine_VideoContext const*)) & getDepthTestFunction;

  ((Machine_VideoContext_Class*)self)->setDepthWriteEnabled = (void (*)(Machine_VideoContext*, Ring2_Boolean)) & setDepthWriteEnabled;
  ((Machine_VideoContext_Class*)self)->getDepthWriteEnabled = (Ring2_Boolean(*)(Machine_VideoContext const*)) & getDepthWriteEnabled;

  ((Machine_VideoContext_Class*)self)->setClearDepth = (void (*)(Machine_VideoContext*, Ring2_Real32)) & setClearDepth;
  ((Machine_VideoContext_Class*)self)->getClearDepth = (Ring2_Real32(*)(Machine_VideoContext const*)) & getClearDepth;

  ((Machine_VideoContext_Class*)self)->getMaximalClipDistanceCount = (Ring2_Integer(*)(Machine_VideoContext const*)) & getMaximalClipDistanceCount;
  ((Machine_VideoContext_Class*)self)->setClipDistanceEnabled = (void (*)(Machine_VideoContext*, Ring2_Integer index, Ring2_Boolean)) & setClipDistanceEnabled;
  ((Machine_VideoContext_Class*)self)->getClipDistanceEnabled = (Ring2_Boolean(*)(Machine_VideoContext const*, Ring2_Integer index)) & getClipDistanceEnabled;

  ((Machine_VideoContext_Class*)self)->setIncomingBlendFunction = (void (*)(Machine_VideoContext*, Ring3_BlendFunction)) & setIncomingBlendFunction;
  ((Machine_VideoContext_Class*)self)->getIncomingBlendFunction = (Ring3_BlendFunction(*)(Machine_VideoContext const*)) & getIncomingBlendFunction;

  ((Machine_VideoContext_Class*)self)->setExistingBlendFunction = (void (*)(Machine_VideoContext*, Ring3_BlendFunction)) & setExistingBlendFunction;
  ((Machine_VideoContext_Class*)self)->getExistingBlendFunction = (Ring3_BlendFunction(*)(Machine_VideoContext const*)) & getExistingBlendFunction;

  ((Machine_VideoContext_Class*)self)->setClearColor = (void (*)(Machine_VideoContext*, Ring3_Math_Vector4f32 const*)) & setClearColor;
  ((Machine_VideoContext_Class*)self)->getClearColor = (Ring3_Math_Vector4f32 const* (*)(Machine_VideoContext const*)) & getClearColor;

  ((Machine_VideoContext_Class*)self)->setViewportRectangle = (void (*)(Machine_VideoContext*, Ring2_Real32, Ring2_Real32, Ring2_Real32, Ring2_Real32)) & setViewportRectangle;
  ((Machine_VideoContext_Class*)self)->getViewportRectangle = (void (*)(Machine_VideoContext const*, Ring2_Real32*, Ring2_Real32*, Ring2_Real32*, Ring2_Real32*)) & getViewportRectangle;

  ((Machine_VideoContext_Class*)self)->drawDirect = (void (*)(Machine_VideoContext*, Ring2_Integer, Ring2_Integer)) & drawDirect;
  ((Machine_VideoContext_Class*)self)->drawIndirect = (void (*)(Machine_VideoContext*, Ring2_Integer, Ring2_Integer, uint8_t const*)) & drawIndirect;

  ((Machine_VideoContext_Class*)self)->clearColorBuffer = (void (*)(Machine_VideoContext*)) & clearColorBuffer;
  ((Machine_VideoContext_Class*)self)->clearDepthBuffer = (void (*)(Machine_VideoContext*)) & clearDepthBuffer;

  ((Machine_VideoContext_Class*)self)->createBuffer = (Machine_VideoBuffer * (*)(Machine_VideoContext*)) & createBuffer;
  ((Machine_VideoContext_Class*)self)->createTextureFromImage = (Ring3_Texture * (*)(Machine_VideoContext*, Ring3_Image*)) & createTextureFromImage;
  ((Machine_VideoContext_Class*)self)->createProgram = (Machine_ShaderProgram * (*)(Machine_VideoContext*, Ring2_String*, Ring2_String*, Ring2_String*)) & createProgram;
  ((Machine_VideoContext_Class*)self)->createBinding = (Machine_Binding * (*)(Machine_VideoContext*, Machine_ShaderProgram*, Ring3_VertexDescriptor*, Machine_VideoBuffer*)) & createBinding;

  ((Machine_VideoContext_Class*)self)->bindTexture = (void (*)(Machine_VideoContext*, size_t, Ring3_Texture*)) & bindTexture;

  ((Machine_VideoContext_Class*)self)->generateDefaultShader = (Machine_ShaderProgram * (*)(Machine_VideoContext*, Ring2_Boolean, Ring2_Boolean, Ring2_Boolean, Ring2_Boolean)) & generateDefaultShader;
  ((Machine_VideoContext_Class*)self)->generateShape2Shader = (Machine_ShaderProgram * (*)(Machine_VideoContext*)) & generateShape2Shader;
  ((Machine_VideoContext_Class*)self)->generateText2Shader = (Machine_ShaderProgram * (*)(Machine_VideoContext*, Ring2_Boolean)) & generateText2Shader;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_VideoContext, Machine_VideoContext,
                         &Machine_Gl_VideoContext_visit, &Machine_Gl_VideoContext_construct,
                         &Machine_Gl_VideoContext_destruct, &Machine_Gl_VideoContext_constructClass,
                         NULL)

void Machine_Gl_VideoContext_construct(Machine_Gl_VideoContext* self, size_t numberOfArguments, Ring2_Value const* arguments) {
  Machine_VideoContext_construct((Machine_VideoContext*)self, numberOfArguments, arguments);
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
    glfwGetFramebufferSize(Machine_Glfw_getWindow(), &w, &h);
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

Machine_Gl_VideoContext* Machine_Gl_VideoContext_create() {
  Machine_ClassType* ty = Machine_Gl_VideoContext_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Gl_VideoContext* self = (Machine_Gl_VideoContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Gl_VideoContext_write(Machine_Gl_VideoContext const* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Gl_VideoContext, write);
}
