#include "Video.h"



#include <malloc.h>
#include <stdio.h>
#include "./GL/CanvasInput.h"
#include "./UtilitiesGL.h"
#include "GL/Binding.h"
#include "GL/Buffer.h"
#include "GL/ShaderProgram.h"
#include "GL/Texture.h"



typedef struct _ClipDistance {
  bool enabled;
} _ClipDistance;

typedef struct _ClipDistances {
  size_t n;
  _ClipDistance* a;
} _ClipDistances;

static _ClipDistances* g_clipDistances = NULL;

static struct {
  Machine_Real r, g, b, a;
} g_clearColor = { 0.9f, 0.9f, 0.9f, 1.f };

static Machine_Material* g_material = NULL;

static Machine_Real g_clearDepth = 1.f;

static struct {
  Machine_Real left, bottom, width, height;
} g_viewport = { 0.f, 0.f, 0.f, 0.f };


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

void Machine_Video_startup() {
  Machine_GLFW_startupCanvas();
  {
    Machine_JumpTarget jumpTarget;
    Machine_pushJumpTarget(&jumpTarget);
    if (!setjmp(jumpTarget.environment)) {
      g_material = Machine_Material_create();
      Machine_lock(g_material);

      {
        GLint v;
        Machine_UtilitiesGl_call(glGetIntegerv(GL_MAX_CLIP_DISTANCES, &v));
        if (v <= 0) {
          Machine_setStatus(Machine_Status_EnvironmentFailed);
          Machine_jump();
        }
        g_clipDistances = malloc(sizeof(_ClipDistances));
        if (!g_clipDistances) {
          Machine_setStatus(Machine_Status_AllocationFailed);
          Machine_jump();
        }
        g_clipDistances->a = malloc(((size_t)v) * sizeof(_ClipDistance));
        if (!g_clipDistances->a) {
          free(g_clipDistances);
          g_clipDistances = NULL;
          Machine_setStatus(Machine_Status_AllocationFailed);
          Machine_jump();
        }
        g_clipDistances->n = (size_t)v;
        for (size_t i = 0; i < g_clipDistances->n; ++i) {
          g_clipDistances->a[i].enabled = false;
        }
      }

      // Enable depth testing.
      // Fragments always pass.
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(Machine_DepthTestFunction_toGL(Machine_Material_getDepthTestFunction(g_material)));

      // Disable depth writing.
      glDepthMask(Machine_Material_getDepthWriteEnabled(g_material) ? GL_TRUE : GL_FALSE);

      // Enable blending.
      glEnable(GL_BLEND);
      glBlendFunc(Machine_BlendFunction_toGL(Machine_Material_getIncomingBlendFunction(g_material)), Machine_BlendFunction_toGL(Machine_Material_getExistingBlendFunction(g_material)));

      // Set clear color.
      glClearColor(g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);

      Machine_popJumpTarget();
    } else {
      Machine_popJumpTarget();
      if (g_clipDistances) {
        free(g_clipDistances->a);
        g_clipDistances->a = NULL;
        free(g_clipDistances);
        g_clipDistances = NULL;
      }
      if (g_material) {
        Machine_unlock(g_material);
        g_material = NULL;
      }
      Machine_GLFW_shutdownCanvas();
      Machine_jump();
    }
  }
}

void Machine_Video_shutdown() {
  if (g_clipDistances) {
    free(g_clipDistances->a);
    g_clipDistances->a = NULL;
    free(g_clipDistances);
    g_clipDistances = NULL;
  }
  Machine_unlock(g_material);
  g_material = NULL;
  Machine_GLFW_shutdownCanvas();
}

Machine_Texture* Machine_Video_createTextureFromImage(Machine_Images_Image* image) {
  return (Machine_Texture*)Machine_GL_Texture_create(image);
}

Machine_VideoBuffer* Machine_Video_createBuffer() {
  return (Machine_VideoBuffer*)Machine_GL_VideoBuffer_create();
}

Machine_ShaderProgram* Machine_Video_createProgram(Machine_String* vertexProgramText, Machine_String* geometryProgramText, Machine_String* fragmentProgramText) {
  return (Machine_ShaderProgram*)Machine_GL_ShaderProgram_create(vertexProgramText, geometryProgramText, fragmentProgramText);
}

Machine_Binding* Machine_Video_createBinding(Machine_ShaderProgram* program, Machine_VertexDescriptor* vertexDescriptor, Machine_VideoBuffer* buffer) {
  return (Machine_Binding*)Machine_GL_Binding_create(program, vertexDescriptor, buffer);
}

void Machine_Video_bindTexture(size_t textureUnit, Machine_Texture* texture) {
  Machine_GL_Texture* textureGL = (Machine_GL_Texture*)texture;
  Machine_UtilitiesGl_call(glActiveTexture(GL_TEXTURE0 + textureUnit));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, textureGL->id));
}



void Machine_Video_setClearColor(Machine_Math_Vector4* clearColor) {
  g_clearColor.r = clearColor->x;
  g_clearColor.g = clearColor->y;
  g_clearColor.b = clearColor->z;
  g_clearColor.a = clearColor->w;
  glClearColor(g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);
}

Machine_Math_Vector4* Machine_Video_getClearColor() {
  Machine_Math_Vector4* clearColor = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(clearColor, g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);
  return clearColor;
}


void Machine_Video_setIncomingBlendFunction(Machine_BlendFunction incomingBlendFunction) {
  Machine_Material_setIncomingBlendFunction(g_material, incomingBlendFunction);
  glBlendFunc(Machine_BlendFunction_toGL(Machine_Material_getIncomingBlendFunction(g_material)), Machine_BlendFunction_toGL(Machine_Material_getExistingBlendFunction(g_material)));
}

Machine_BlendFunction Machine_Video_getIncomingBlendFunction() {
  return Machine_Material_getIncomingBlendFunction(g_material);
}


void Machine_Video_setExistingBlendFunction(Machine_BlendFunction existingBlendFunction) {
  Machine_Material_setExistingBlendFunction(g_material, existingBlendFunction);
  glBlendFunc(Machine_BlendFunction_toGL(Machine_Material_getIncomingBlendFunction(g_material)), Machine_BlendFunction_toGL(Machine_Material_getExistingBlendFunction(g_material)));
}

Machine_BlendFunction Machine_Video_getExistingBlendFunction() {
  return Machine_Material_getExistingBlendFunction(g_material);
}


void Machine_Video_setDepthWriteEnabled(bool depthWriteEnabled) {
  Machine_Material_setDepthWriteEnabled(g_material, depthWriteEnabled);
  glDepthMask(Machine_Material_getDepthWriteEnabled(g_material) ? GL_TRUE : GL_FALSE);
}

bool Machine_Video_getDepthWriteEnabled() {
  return Machine_Material_getDepthWriteEnabled(g_material);
}


void Machine_Video_setDepthTestFunction(Machine_DepthTestFunction depthTestFunction) {
  Machine_Material_setDepthTestFunction(g_material, depthTestFunction);
  glDepthFunc(Machine_DepthTestFunction_toGL(Machine_Material_getDepthTestFunction(g_material)));
}

Machine_DepthTestFunction Machine_Video_getDepthTestFunction() {
  return Machine_Material_getDepthTestFunction(g_material);
}


void Machine_Video_setClearDepth(Machine_Real clearDepth) {
  g_clearDepth = clearDepth;
  glClearDepth(g_clearDepth);
}

Machine_Real Machine_Video_getClearDepth() {
  return g_clearDepth;
}

void Machine_Video_setViewportRectangle(Machine_Real left, Machine_Real bottom, Machine_Real width, Machine_Real height) {
  g_viewport.left = left;
  g_viewport.bottom = bottom;
  g_viewport.width = width;
  g_viewport.height = height;
  glViewport(left, bottom, width, height);
  glScissor(left, bottom, width, height);
}

void Machine_Video_getViewportRectangle(Machine_Real *left, Machine_Real *bottom, Machine_Real *width, Machine_Real *height) {
  *left = g_viewport.left;
  *bottom = g_viewport.bottom;
  *width = g_viewport.width;
  *height = g_viewport.height;
}

Machine_Integer Machine_Video_getMaximalClipDistanceCount() {
  return g_clipDistances->n;
}

void Machine_Video_setClipDistanceEnabled(Machine_Integer index, Machine_Boolean enabled) {
  if (index < 0 || index >= Machine_Video_getMaximalClipDistanceCount()) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  g_clipDistances->a[index].enabled = enabled;
  if (enabled) {
    glEnable(GL_CLIP_DISTANCE0 + index);
  }
  else {
    glDisable(GL_CLIP_DISTANCE0 + index);
  }
}

Machine_Boolean Machine_Video_getClipDistanceEnabled(Machine_Integer index) {
  if (index < 0 || index >= Machine_Video_getMaximalClipDistanceCount()) {
    Machine_setStatus(Machine_Status_IndexOutOfBounds);
    Machine_jump();
  }
  return g_clipDistances->a[index].enabled;
}

void Machine_Video_clearColorBuffer() {
  Machine_UtilitiesGl_call(glViewport(g_viewport.left, g_viewport.bottom, g_viewport.width, g_viewport.height));
  Machine_UtilitiesGl_call(glScissor(g_viewport.left, g_viewport.bottom, g_viewport.width, g_viewport.height));
  Machine_UtilitiesGl_call(glEnable(GL_SCISSOR_TEST));
  Machine_UtilitiesGl_call(glClear(GL_COLOR_BUFFER_BIT));
}

void Machine_Video_clearDepthBuffer() {
  Machine_UtilitiesGl_call(glViewport(g_viewport.left, g_viewport.bottom, g_viewport.width, g_viewport.height));
  Machine_UtilitiesGl_call(glScissor(g_viewport.left, g_viewport.bottom, g_viewport.width, g_viewport.height));
  Machine_UtilitiesGl_call(glEnable(GL_SCISSOR_TEST));
  Machine_UtilitiesGl_call(glClear(GL_DEPTH_BUFFER_BIT));
}

void Machine_Video_drawDirect(Machine_Integer i, Machine_Integer n) {
  if (i < 0 || n < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (n > 0) {
    Machine_UtilitiesGl_call(glDrawArrays(GL_TRIANGLES, i, n));
  }
}

void Machine_Video_drawIndirect(Machine_Integer i, Machine_Integer n, uint8_t const* indices) {
  if (i < 0 || n < 0) {
    Machine_setStatus(Machine_Status_InvalidArgument);
    Machine_jump();
  }
  if (n > 0) {
    Machine_UtilitiesGl_call(glDrawElements(GL_TRIANGLES, n, GL_UNSIGNED_BYTE, indices + i));
  }
}

Machine_ShaderProgram*
Machine_Video_generateDefaultShader
  (
    bool withMeshColor,
    bool withVertexColor,
    bool withTextureCoordinate,
    bool withTexture
  )
{
  return (Machine_ShaderProgram *)Machine_GL_ShaderProgram_generateDefaultShader(withMeshColor, withVertexColor, withTextureCoordinate, withTexture);
}

Machine_ShaderProgram* Machine_Video_generateShape2Shader() {
  return (Machine_ShaderProgram *)Machine_GL_ShaderProgram_generateShape2Shader();
}

Machine_ShaderProgram* Machine_Video_generateText2Shader(bool highPrecision) {
  return (Machine_ShaderProgram *)Machine_GL_ShaderProgram_generateText2Shader(highPrecision);
}
