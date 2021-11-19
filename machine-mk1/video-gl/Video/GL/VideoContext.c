#define MACHINE_VIDEO_GL_PRIVATE (1)
#include "./../GL/VideoContext.h"



#include <malloc.h>
#include "./../GL/UtilitiesGL.h"
#include "./../GL/Binding.h"
#include "./../GL/Buffer.h"
#include "./../GL/Canvas.h"
#include "./../GL/ShaderProgram.h"
#include "./../GL/Texture.h"



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void setDepthTestFunction(Machine_Gl_VideoContext* self, Machine_DepthTestFunction depthTestFunction) {
  self->depthTestFunction = depthTestFunction;
}

static Machine_DepthTestFunction getDepthTestFunction(Machine_Gl_VideoContext const* self) {
  return self->depthTestFunction;
}



static void setDepthWriteEnabled(Machine_Gl_VideoContext* self, Machine_Boolean depthWriteEnabled) {
  self->depthWriteEnabled = depthWriteEnabled;
}

static Machine_Boolean getDepthWriteEnabled(Machine_Gl_VideoContext const* self) {
  return self->depthWriteEnabled;
}



static void setClearDepth(Machine_Gl_VideoContext* self, Machine_Real clearDepth) {
  self->clearDepth = clearDepth;
}

static Machine_Real getClearDepth(Machine_Gl_VideoContext const* self) {
  return self->clearDepth;
}



static Machine_Integer getMaximalClipDistanceCount(Machine_Gl_VideoContext const* self) {
  return self->clipDistances->n;
}

static void setClipDistanceEnabled(Machine_Gl_VideoContext* self, Machine_Integer index, Machine_Boolean enabled) {
  if (index < 0 || index >= self->clipDistances->n) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  self->clipDistances->a[index].enabled = enabled;
}

static Machine_Boolean getClipDistanceEnabled(Machine_Gl_VideoContext const* self, Machine_Integer index) {
  if (index < 0 || index >= self->clipDistances->n) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return self->clipDistances->a[index].enabled;
}



static void setIncomingBlendFunction(Machine_Gl_VideoContext* self, Machine_BlendFunction incomingBlendFunction) {
  self->incomingBlendFunction = incomingBlendFunction;
}

static Machine_BlendFunction getIncomingBlendFunction(Machine_Gl_VideoContext const* self) {
  return self->incomingBlendFunction;
}



static void setExistingBlendFunction(Machine_Gl_VideoContext* self, Machine_BlendFunction existingBlendFunction) {
  self->existingBlendFunction = existingBlendFunction;
}

static Machine_BlendFunction getExistingBlendFunction(Machine_Gl_VideoContext const* self) {
  return self->existingBlendFunction;
}



static void setClearColor(Machine_Gl_VideoContext* self, Machine_Math_Vector4 const* clearColor) {
  self->clearColor[0] = Machine_Math_Vector4_getX(clearColor);
  self->clearColor[1] = Machine_Math_Vector4_getY(clearColor);
  self->clearColor[2] = Machine_Math_Vector4_getZ(clearColor);
  self->clearColor[3] = Machine_Math_Vector4_getW(clearColor);
}

Machine_Math_Vector4 const* getClearColor(Machine_Gl_VideoContext const* self) {
  Machine_Math_Vector4* clearColor = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(clearColor, self->clearColor[0], self->clearColor[1], 
                                       self->clearColor[2], self->clearColor[3]);
  return clearColor;
}



static void setViewportRectangle(Machine_Gl_VideoContext* self, Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height) {
  self->viewportRectangle->x = left;
  self->viewportRectangle->y = bottom;
  self->viewportRectangle->w = width;
  self->viewportRectangle->h = height;
}

static void getViewportRectangle(Machine_Gl_VideoContext const* self, Machine_Real* left, Machine_Real* bottom, Machine_Real* width, Machine_Real* height) {
  *left = self->viewportRectangle->x;
  *bottom = self->viewportRectangle->y;
  *width = self->viewportRectangle->w;
  *height = self->viewportRectangle->h;
}



static void drawDirect(Machine_Gl_VideoContext* self, Machine_Integer i, Machine_Integer n) {
  if (i < 0 || n < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (n > 0) {
    Machine_Gl_VideoContext_write(self);
    Machine_UtilitiesGl_call(glDrawArrays(GL_TRIANGLES, i, n));
  }
}

static void drawIndirect(Machine_Gl_VideoContext* self, Machine_Integer i, Machine_Integer n, uint8_t const* indices) {
  if (i < 0 || n < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
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

static Machine_Texture* createTextureFromImage(Machine_Gl_VideoContext* self, Machine_Image* image) {
  return (Machine_Texture*)Machine_Gl_Texture_create(image);
}

static Machine_ShaderProgram* createProgram(Machine_Gl_VideoContext* self, Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText) {
  return (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_create(vertexProgramText, geometryProgramText, fragmentProgramText);
}

static Machine_Binding* createBinding(Machine_Gl_VideoContext* self, Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  return (Machine_Binding*)Machine_Gl_Binding_create(program, vertexDescriptor, buffer);
}



static void bindTexture(Machine_Gl_VideoContext* self, size_t textureUnit, Machine_Texture* texture) {
  Machine_Gl_Texture* textureGL = (Machine_Gl_Texture*)texture;
  Machine_UtilitiesGl_call(glActiveTexture(GL_TEXTURE0 + textureUnit));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, textureGL->id));
}



static Machine_ShaderProgram*
generateDefaultShader
  (
    Machine_Gl_VideoContext* self,
    Machine_Boolean withMeshColor,
    Machine_Boolean withVertexColor,
    Machine_Boolean withTextureCoordinate,
    Machine_Boolean withTexture
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
    Machine_Boolean highPrecision
  )
{
  return (Machine_ShaderProgram*)Machine_Gl_ShaderProgram_generateText2Shader(highPrecision);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static void Machine_Gl_VideoContext_visit(Machine_Gl_VideoContext* self) {
  if (self->viewportRectangle) {
    Machine_Gc_visit(self->viewportRectangle);
  }
}

static void Machine_Gl_VideoContext_destruct(Machine_Gl_VideoContext* self) {
  if (self->clipDistances) {
    free(self->clipDistances->a);
    self->clipDistances->a = NULL;
    free(self->clipDistances);
    self->clipDistances = NULL;
  }
}

/// @EXTENSION 
static GLenum Machine_BlendFunction_toGL(Machine_BlendFunction self) {
  switch (self) {
  case Machine_BlendFunction_IncomingAlpha:
    return GL_SRC_ALPHA;
  case Machine_BlendFunction_OneMinusIncomingAlpha:
    return GL_ONE_MINUS_SRC_ALPHA;
  case Machine_BlendFunction_Zero:
    return GL_ZERO;
  case Machine_BlendFunction_One:
    return GL_ONE;
  default:
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  };
}

/// @EXTENSION
static GLenum Machine_DepthTestFunction_toGL(Machine_DepthTestFunction self) {
  switch (self) {
  case Machine_DepthTestFunction_LessThan:
    return GL_LESS;
  case Machine_DepthTestFunction_LessThanOrEqualTo:
    return GL_LEQUAL;
  case Machine_DepthTestFunction_EqualTo:
    return GL_EQUAL;
  case Machine_DepthTestFunction_GreaterThan:
    return GL_GREATER;
  case Machine_DepthTestFunction_GreaterThanOrEqualTo:
    return GL_GEQUAL;
  case Machine_DepthTestFunction_Always:
    return GL_ALWAYS;
  case Machine_DepthTestFunction_Never:
    return GL_NEVER;
  default:
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
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
    Machine_Boolean enabled = self->clipDistances->a[i].enabled;
    enabled ? glEnable(GL_CLIP_DISTANCE0 + i) : glDisable(GL_CLIP_DISTANCE0 + i);
  }

  // Viewport rectangle.
  glViewport(self->viewportRectangle->x, self->viewportRectangle->y, self->viewportRectangle->w, self->viewportRectangle->h);
}

static void Machine_Gl_VideoContext_constructClass(Machine_Gl_VideoContext_Class* self) {
  self->write = &write;

  ((Machine_VideoContext_Class*)self)->setDepthTestFunction = (void (*)(Machine_VideoContext*, Machine_DepthTestFunction)) & setDepthTestFunction;
  ((Machine_VideoContext_Class*)self)->getDepthTestFunction = (Machine_DepthTestFunction(*)(Machine_VideoContext const*)) & getDepthTestFunction;

  ((Machine_VideoContext_Class*)self)->setDepthWriteEnabled = (void (*)(Machine_VideoContext*, Machine_Boolean)) & setDepthWriteEnabled;
  ((Machine_VideoContext_Class*)self)->getDepthWriteEnabled = (Machine_Boolean(*)(Machine_VideoContext const*)) & getDepthWriteEnabled;

  ((Machine_VideoContext_Class*)self)->setClearDepth = (void (*)(Machine_VideoContext*, Machine_Real)) & setClearDepth;
  ((Machine_VideoContext_Class*)self)->getClearDepth = (Machine_Real(*)(Machine_VideoContext const*)) & getClearDepth;

  ((Machine_VideoContext_Class*)self)->getMaximalClipDistanceCount = (Machine_Integer(*)(Machine_VideoContext const*)) & getMaximalClipDistanceCount;
  ((Machine_VideoContext_Class*)self)->setClipDistanceEnabled = (void (*)(Machine_VideoContext*, Machine_Integer index, Machine_Boolean)) & setClipDistanceEnabled;
  ((Machine_VideoContext_Class*)self)->getClipDistanceEnabled = (Machine_Boolean(*)(Machine_VideoContext const*, Machine_Integer index)) & getClipDistanceEnabled;

  ((Machine_VideoContext_Class*)self)->setIncomingBlendFunction = (void (*)(Machine_VideoContext*, Machine_BlendFunction)) & setIncomingBlendFunction;
  ((Machine_VideoContext_Class*)self)->getIncomingBlendFunction = (Machine_BlendFunction(*)(Machine_VideoContext const*)) & getIncomingBlendFunction;

  ((Machine_VideoContext_Class*)self)->setExistingBlendFunction = (void (*)(Machine_VideoContext*, Machine_BlendFunction)) & setExistingBlendFunction;
  ((Machine_VideoContext_Class*)self)->getExistingBlendFunction = (Machine_BlendFunction(*)(Machine_VideoContext const*)) & getExistingBlendFunction;

  ((Machine_VideoContext_Class*)self)->setClearColor = (void (*)(Machine_VideoContext*, Machine_Math_Vector4 const*)) & setClearColor;
  ((Machine_VideoContext_Class*)self)->getClearColor = (Machine_Math_Vector4 const* (*)(Machine_VideoContext const*)) & getClearColor;

  ((Machine_VideoContext_Class*)self)->setViewportRectangle = (void (*)(Machine_VideoContext*, Machine_Real, Machine_Real, Machine_Real, Machine_Real)) & setViewportRectangle;
  ((Machine_VideoContext_Class*)self)->getViewportRectangle = (void (*)(Machine_VideoContext const*, Machine_Real*, Machine_Real*, Machine_Real*, Machine_Real*)) & getViewportRectangle;

  ((Machine_VideoContext_Class*)self)->drawDirect = (void (*)(Machine_VideoContext*, Machine_Integer, Machine_Integer)) & drawDirect;
  ((Machine_VideoContext_Class*)self)->drawIndirect = (void (*)(Machine_VideoContext*, Machine_Integer, Machine_Integer, uint8_t const*)) & drawIndirect;

  ((Machine_VideoContext_Class*)self)->clearColorBuffer = (void (*)(Machine_VideoContext*)) & clearColorBuffer;
  ((Machine_VideoContext_Class*)self)->clearDepthBuffer = (void (*)(Machine_VideoContext*)) & clearDepthBuffer;

  ((Machine_VideoContext_Class*)self)->createBuffer = (Machine_VideoBuffer * (*)(Machine_VideoContext*)) & createBuffer;
  ((Machine_VideoContext_Class*)self)->createTextureFromImage = (Machine_Texture * (*)(Machine_VideoContext*, Machine_Image*)) & createTextureFromImage;
  ((Machine_VideoContext_Class*)self)->createProgram = (Machine_ShaderProgram * (*)(Machine_VideoContext*, Machine_String*, Machine_String*, Machine_String*)) & createProgram;
  ((Machine_VideoContext_Class*)self)->createBinding = (Machine_Binding * (*)(Machine_VideoContext*, Machine_ShaderProgram*, Machine_VertexDescriptor*, Machine_VideoBuffer*)) & createBinding;

  ((Machine_VideoContext_Class*)self)->bindTexture = (void (*)(Machine_VideoContext*, size_t, Machine_Texture*)) & bindTexture;

  ((Machine_VideoContext_Class*)self)->generateDefaultShader = (Machine_ShaderProgram * (*)(Machine_VideoContext*, Machine_Boolean, Machine_Boolean, Machine_Boolean, Machine_Boolean)) & generateDefaultShader;
  ((Machine_VideoContext_Class*)self)->generateShape2Shader = (Machine_ShaderProgram * (*)(Machine_VideoContext*)) & generateShape2Shader;
  ((Machine_VideoContext_Class*)self)->generateText2Shader = (Machine_ShaderProgram * (*)(Machine_VideoContext*, Machine_Boolean)) & generateText2Shader;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Gl_VideoContext, Machine_VideoContext, &Machine_Gl_VideoContext_visit, &Machine_Gl_VideoContext_construct, &Machine_Gl_VideoContext_destruct, &Machine_Gl_VideoContext_constructClass)

void Machine_Gl_VideoContext_construct(Machine_Gl_VideoContext* self, size_t numberOfArguments, Machine_Value const* arguments) {
  Machine_VideoContext_construct((Machine_VideoContext*)self, numberOfArguments, arguments);
  self->clearColor[0] = 0.f;
  self->clearColor[1] = 0.f;
  self->clearColor[2] = 0.f;
  self->clearColor[3] = 0.f;
  self->clearDepth = 1.f;
  self->depthTestFunction = Machine_DepthTestFunction_Always;
  self->depthWriteEnabled = false;
  self->existingBlendFunction = Machine_BlendFunction_OneMinusIncomingAlpha;
  self->incomingBlendFunction = Machine_BlendFunction_IncomingAlpha;
  {
    Machine_Integer width, height;
    int w, h;
    glfwGetFramebufferSize(Machine_Glfw_getWindow(), &w, &h);
    width = w; height = h;
    self->viewportRectangle = Machine_Math_Rectangle2_create();
    Machine_Math_Vector2* v;
    v = Machine_Math_Vector2_create();
    Machine_Math_Vector2_set(v, 0.f, 0.f);
    Machine_Math_Rectangle2_setPosition(self->viewportRectangle, v);
    Machine_Math_Vector2_set(v, (Machine_Real)width, (Machine_Real)height);
    Machine_Math_Rectangle2_setSize(self->viewportRectangle, v);
  }
  {
    GLint v;
    Machine_UtilitiesGl_call(glGetIntegerv(GL_MAX_CLIP_DISTANCES, &v));
    if (v <= 0) {
      Machine_setStatus(Machine_Status_EnvironmentFailed);
      Machine_jump();
    }
    self->clipDistances = malloc(sizeof(Machine_Gl_VideoContext_ClipDistances));
    if (!self->clipDistances) {
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->clipDistances->a = malloc(((size_t)v) * sizeof(Machine_Gl_VideoContext_ClipDistance));
    if (!self->clipDistances->a) {
      free(self->clipDistances);
      self->clipDistances = NULL;
      Machine_setStatus(Machine_Status_AllocationFailed);
      Machine_jump();
    }
    self->clipDistances->n = (size_t)v;
    for (size_t i = 0; i < self->clipDistances->n; ++i) {
      self->clipDistances->a[i].enabled = false;
    }
  }
  Machine_setClassType((Machine_Object*)self, Machine_Gl_VideoContext_getClassType());
}

Machine_Gl_VideoContext* Machine_Gl_VideoContext_create() {
  Machine_ClassType* ty = Machine_Gl_VideoContext_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Gl_VideoContext* self = (Machine_Gl_VideoContext*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Gl_VideoContext_write(Machine_Gl_VideoContext const* self) {
  MACHINE_VIRTUALCALL_NORETURN_NOARGS(Machine_Gl_VideoContext, write);
}
