#include "Video.h"

#include <stdio.h>
#include "Images.h"
#include "Fonts.h"
#include "ShaderProgram.h"

static GLFWwindow* g_window = NULL;
static struct {
  float r, g, b, a;
} g_clearColor = { 0.9f, 0.9f, 0.9f, 1.f };

static Machine_BlendFunction g_existingBlendFunction = Machine_BlendFunction_OneMinusIncomingAlpha;
static Machine_BlendFunction g_incomingBlendFunction = Machine_BlendFunction_IncomingAlpha;

static Machine_DepthTestFunction g_depthTestFunction = Machine_DepthTestFunction_Always;
static float g_clearDepth = 1.f;
static bool g_depthWriteEnabled = false;

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

int Machine_Video_startup() {
  int result;

  if (!glfwInit()) {
    fprintf(stderr, "%s:%d: glfwInit() failed\n", __FILE__, __LINE__);
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

  g_window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
  if (!g_window) {
    fprintf(stderr, "%s:%d: glfwCreateWindow() failed\n", __FILE__, __LINE__);
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(Machine_Video_getMainWindow());
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "%s:%d: gladLoadGLLoader() failed\n", __FILE__, __LINE__);
    glfwDestroyWindow(g_window);
    g_window = NULL;
    glfwTerminate();
    return 1;
  }

  // Enable depth testing.
  // Fragments always pass.
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(Machine_DepthTestFunction_toGL(g_depthTestFunction));
  
  // Disable depth writing.
  glDepthMask(g_depthWriteEnabled ? GL_TRUE : GL_FALSE);

  // Enable blending.
  glEnable(GL_BLEND);
  glBlendFunc(Machine_BlendFunction_toGL(g_incomingBlendFunction), Machine_BlendFunction_toGL(g_existingBlendFunction));

  // Set clear color.
  glClearColor(g_clearColor.r, g_clearColor.g, g_clearColor.b, g_clearColor.a);

  glfwSwapInterval(1);


  result = Machine_Images_startup();
  if (result) {
    fprintf(stderr, "%s:%d: Machine_Images_startup() failed\n", __FILE__, __LINE__);
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(g_window);
    g_window = NULL;
    glfwTerminate();
    return result;
  }
  result = Machine_Fonts_startup();
  if (result) {
    fprintf(stderr, "%s:%d: Machine_Fonts_startup() failed\n", __FILE__, __LINE__);
    Machine_Images_shutdown();
    glfwMakeContextCurrent(NULL);
    glfwDestroyWindow(g_window);
    g_window = NULL;
    glfwTerminate();
    return result;
  }

  return 0;
}

void Machine_Video_shutdown() {
  Machine_Fonts_shutdown();
  Machine_Images_shutdown();
  glfwMakeContextCurrent(NULL);
  glfwDestroyWindow(g_window);
  g_window = NULL;
  glfwTerminate();
}

void Machine_Video_bindTexture(size_t textureUnit, Machine_Texture* texture) {
  Machine_UtilitiesGl_call(glActiveTexture(GL_TEXTURE0 + textureUnit));
  Machine_UtilitiesGl_call(glBindTexture(GL_TEXTURE_2D, texture->id));
}

void Machine_Video_bindShaderProgram(Machine_ShaderProgram* shaderProgram) {
  Machine_UtilitiesGl_call(glUseProgram(shaderProgram->programId));
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
  g_incomingBlendFunction = incomingBlendFunction;
  glBlendFunc(Machine_BlendFunction_toGL(g_incomingBlendFunction), Machine_BlendFunction_toGL(g_existingBlendFunction));
}

Machine_BlendFunction Machine_Video_getIncomingBlendFunction() {
  return g_incomingBlendFunction;
}


void Machine_Video_setExistingBlendFunction(Machine_BlendFunction existingBlendFunction) {
  g_existingBlendFunction = existingBlendFunction;
  glBlendFunc(Machine_BlendFunction_toGL(g_incomingBlendFunction), Machine_BlendFunction_toGL(g_existingBlendFunction));
}

Machine_BlendFunction Machine_Video_getExistingBlendFunction() {
  return g_existingBlendFunction;
}


void Machine_Video_setDepthWriteEnabled(bool depthWriteEnabled) {
  g_depthWriteEnabled = depthWriteEnabled;
  glDepthMask(g_depthWriteEnabled ? GL_TRUE : GL_FALSE);
}

bool Machine_Video_getDepthWriteEnabled() {
  return g_depthWriteEnabled;
}


void Machine_Video_setDepthTestFunction(Machine_DepthTestFunction depthTestFunction) {
  g_depthTestFunction = depthTestFunction;
  glDepthFunc(Machine_DepthTestFunction_toGL(g_depthTestFunction));
}

Machine_DepthTestFunction Machine_Video_getDepthTestFunction() {
  return g_depthTestFunction;
}


void Machine_Video_setClearDepth(float clearDepth) {
  g_clearDepth = clearDepth;
  glClearDepth(g_clearDepth);
}

float Machine_Video_getClearDepth() {
  return g_clearDepth;
}


GLFWwindow* Machine_Video_getMainWindow() {
  return g_window;
}
