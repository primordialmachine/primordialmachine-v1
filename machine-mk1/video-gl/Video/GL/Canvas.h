#if !defined(MACHINE_VIDEO_GL_CANVAS_H_INCLUDED)
#define MACHINE_VIDEO_GL_CANVAS_H_INCLUDED


#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include this file directly, include `_Video_GL.h` instead.")
#endif
#include "_Video.h"



#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>



/// @brief Get the canvas.
/// @return The canvas.
/// @todo Remove this from here.
DEPRECATED
GLFWwindow* Machine_Glfw_getWindow();

MACHINE_DECLARE_CLASSTYPE(Machine_Video_GL_Canvas);

struct Machine_Video_GL_Canvas_Class {
  Machine_Video_Canvas_Class __parent__;
};

struct Machine_Video_GL_Canvas {
  Machine_Video_Canvas_Class __parent__;
};

void Machine_Video_GL_Canvas_construct(Machine_Video_GL_Canvas* self, size_t numberOfArguments, Machine_Value const* arguments);

Machine_Video_GL_Canvas*Machine_Video_GL_Canvas_create();

#endif // MACHINE_VIDEO_GL_CANVAS_H_INCLUDED
