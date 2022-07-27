/// @file Video/Gl/Canvas.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_VIDEO_GL_CANVAS_H_INCLUDED)
#define MACHINE_VIDEO_GL_CANVAS_H_INCLUDED

#if !defined(MACHINE_VIDEO_GL_PRIVATE)
#error("Do not include `Video/Gl/Canvas.h` directly, include `_Video_Gl.h` instead.")
#endif
#include "_Video.h"

MACHINE_DECLARE_CLASSTYPE(Machine_Video_Gl_Canvas);

struct Machine_Video_Gl_Canvas_Class {
  Machine_Video_Canvas_Class _parent;
};

struct Machine_Video_Gl_Canvas {
  Machine_Video_Canvas _parent;
};

void Machine_Video_Gl_Canvas_construct(Machine_Video_Gl_Canvas* self, size_t numberOfArguments,
                                       Machine_Value const* arguments);

Machine_Video_Gl_Canvas* Machine_Video_Gl_Canvas_create();

#endif // MACHINE_VIDEO_GL_CANVAS_H_INCLUDED
