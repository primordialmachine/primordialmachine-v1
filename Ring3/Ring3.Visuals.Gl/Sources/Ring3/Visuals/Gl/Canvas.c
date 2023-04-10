/// @file Ring3/Visuals/Gl/Canvas.c
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_VISUALS_GL_PRIVATE (1)
#include "Ring3/Visuals/Gl/Canvas.h"

#include "Ring3/Visuals/Gl/Amd/PowerExpress.i"
#include "Ring3/Visuals/Gl/Nvidia/Optimus.i"
#include "Ring3/Visuals/Gl/Input/_Include.h"
#include "Ring3/Visuals/Gl/Canvas.package.h"
#undef RING3_VISUALS_GL_PRIVATE

#include "Ring1/All/_Include.h"
#include "Ring2/Library/_Include.h"
#include <stdio.h>


static bool g_inputStarted = false;

static void
Ring3_Visuals_Gl_Canvas_getFrameBuffersSize
  (
    Machine_Video_Gl_Canvas* self,
    Ring2_Integer* width,
    Ring2_Integer* height
  )
{
  int w, h;
  glfwGetFramebufferSize(Ring3_Visuals_Gl_Glfw_getWindow(), &w, &h);
  *width = w;
  *height = h;
}

static void
Ring3_Visuals_Gl_Canvas_maximizeCanvas
  (
    Machine_Video_Gl_Canvas* self
  )
{ glfwMaximizeWindow(Ring3_Visuals_Gl_Glfw_getWindow()); }

static void
Ring3_Visuals_Gl_Canvas_swapFrameBuffers
  (
    Machine_Video_Gl_Canvas* self
  )
{ glfwSwapBuffers(Ring3_Visuals_Gl_Glfw_getWindow()); }

static void
Ring3_Visuals_Gl_Canvas_setCanvasIcons
  (
    Machine_Video_Gl_Canvas* self,
    Ring2_Collections_List* images
  )
{
  GLFWimage* targetImages = NULL;

  Ring2_JumpTarget jumpTarget;
  Ring2_pushJumpTarget(&jumpTarget);
  if (!setjmp(jumpTarget.environment)) {
    size_t numberOfImages = Ring2_Collections_Collection_getSize((Ring2_Collections_Collection*)images);
    if (Ring1_Memory_allocateArray(&targetImages, numberOfImages, sizeof(GLFWimage))) {
      Ring2_jump();
    }
    for (size_t i = 0, n = numberOfImages; i < n; ++i) {
      Ring2_Value temporary = Ring2_Collections_List_getAt(images, i);
      Ring3_Image* image = (Ring3_Image*)Ring2_Value_getObject(&temporary);
      Ring2_Integer w, h;
      void const* p;
      Ring3_Image_getSize(image, &w, &h);
      p = Ring3_Image_getPixels(image);
      targetImages[i].width = w;
      targetImages[i].height = h;
      targetImages[i].pixels = (unsigned char*)p;
    }
    glfwSetWindowIcon(Ring3_Visuals_Gl_Glfw_getWindow(), numberOfImages, targetImages);
    if (targetImages) {
      Ring1_Memory_deallocate(targetImages);
      targetImages = NULL;
    }
    Ring2_popJumpTarget();
  } else {
    if (targetImages) {
      Ring1_Memory_deallocate(targetImages);
      targetImages = NULL;
    }
    Ring2_popJumpTarget();
    Ring2_jump();
  }
}

static void
Ring3_Visuals_Gl_Canvas_pollEvents
  (
    Machine_Video_Gl_Canvas* self
  )
{
  glfwSetWindowUserPointer(Ring3_Visuals_Gl_Glfw_getWindow(), self);
  Ring3_Visuals_Gl_Glfw_pollEvents();
  Ring3_Canvas_pumpEvents(Ring1_cast(Ring3_Canvas*,self));
}

static Ring2_Boolean
Ring3_Visuals_Gl_Canvas_getQuitRequested
  (
    Machine_Video_Gl_Canvas* self
  )
{ return glfwWindowShouldClose(Ring3_Visuals_Gl_Glfw_getWindow()); }

static void
Ring3_Visuals_Gl_Canvas_destruct
  (
    Machine_Video_Gl_Canvas* self
  )
{
  if (g_inputStarted) {
    Ring3_Visuals_Gl_Glfw_shutdownInput();
  }
  Ring3_Visuals_Gl_Glfw_shutdownCanvas();
}

static void
Ring3_Visuals_Gl_Canvas_constructClass
  (
    Machine_Video_Gl_Canvas_Class* self
  )
{
  ((Ring3_Canvas_Class*)self)->getFrameBuffersSize
      = (void (*)(Ring3_Canvas*, Ring2_Integer*, Ring2_Integer*))
        & Ring3_Visuals_Gl_Canvas_getFrameBuffersSize;
  ((Ring3_Canvas_Class*)self)->maximizeCanvas
      = (void (*)(Ring3_Canvas*)) & Ring3_Visuals_Gl_Canvas_maximizeCanvas;
  ((Ring3_Canvas_Class*)self)->swapFrameBuffers
      = (void (*)(Ring3_Canvas*)) & Ring3_Visuals_Gl_Canvas_swapFrameBuffers;
  ((Ring3_Canvas_Class*)self)->setCanvasIcons
      = (void (*)(Ring3_Canvas*, Ring2_Collections_List*)) & Ring3_Visuals_Gl_Canvas_setCanvasIcons;
  ((Ring3_Canvas_Class*)self)->pollEvents
      = (void (*)(Ring3_Canvas*)) & Ring3_Visuals_Gl_Canvas_pollEvents;
  ((Ring3_Canvas_Class*)self)->getQuitRequested
      = (Ring2_Boolean(*)(Ring3_Canvas*)) & Ring3_Visuals_Gl_Canvas_getQuitRequested;
}

void
Ring3_Visuals_Gl_Canvas_construct
  (
    Machine_Video_Gl_Canvas* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Canvas_construct((Ring3_Canvas*)self, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  Ring3_Visuals_Gl_Glfw_startupCanvas();
  Ring3_Visuals_Gl_Glfw_startupInput(); g_inputStarted = true;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Machine_Video_Gl_Canvas_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Video_Gl_Canvas,
                         Ring3_Canvas,
                         NULL,
                         &Ring3_Visuals_Gl_Canvas_construct,
                         &Ring3_Visuals_Gl_Canvas_destruct,
                         &Ring3_Visuals_Gl_Canvas_constructClass,
                         NULL)

Machine_Video_Gl_Canvas*
Machine_Video_Gl_Canvas_create
  (
  )
{
  Machine_Type* ty = Machine_Video_Gl_Canvas_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Machine_Video_Gl_Canvas* self = Ring1_cast(Machine_Video_Gl_Canvas*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}
