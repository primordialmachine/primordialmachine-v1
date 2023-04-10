/// @file Ring3/Visuals/Gl/Canvas.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_VISUALS_GL_CANVAS_H_INCLUDED)
#define RING3_VISUALS_GL_CANVAS_H_INCLUDED


#if !defined(RING3_VISUALS_GL_PRIVATE)
#error("Do not include `Ring3/Visuals/Gl/Canvas.h` directly. Include `Ring3/Visuals/Gl/_Include.h` instead.")
#endif

#include "Ring3/Visuals/_Include.h"


MACHINE_DECLARE_CLASSTYPE(Machine_Video_Gl_Canvas);

struct Machine_Video_Gl_Canvas_Class {
  Ring3_Canvas_Class _parent;
};

struct Machine_Video_Gl_Canvas {
  Ring3_Canvas _parent;
};

void
Machine_Video_Gl_Canvas_construct
  (
    Machine_Video_Gl_Canvas* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Machine_Video_Gl_Canvas*
Machine_Video_Gl_Canvas_create
  (
  );

#endif // RING3_VISUALS_GL_CANVAS_H_INCLUDED
