/// @file Graphics2/Shape2.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED)
#define MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED



#if !defined(MACHINE_GRAPHICS2_PRIVATE)
#error("Do not include `Graphics2/Shape2.h` directly, include `_Graphics2.h` instead.")
#endif
#include "Math/_Include.h"
typedef struct Machine_Context2 Machine_Context2;



/// C-level representation of a shape in 2D.
/// 
/// The canvas is a 2D coordinate system.
/// The bottom left corner of the canvas is the origin (0,0),
/// the positive x-axis goes right, the positive y-axis goes up.
/// A shape covers a not-necessarily convex area in the plane.
/// 
/// Each shape has a position which is the bottom left corner of the bounds of the shape.
/// The bounds are the smallest rectangle enclosing the shape.
/// Examples:
/// - rectangle: bounds are the rectangle itself.
/// - circle: bounds are the smallest rectangle enclosing the circle.
MACHINE_DECLARE_CLASSTYPE(Machine_Shape2);

struct Machine_Shape2_Class {
  Machine_Object_Class parent;

  void (*render)(Machine_Shape2* self, Machine_Context2* context);
};

struct Machine_Shape2 {
  Machine_Object parent;
};

/// @brief Construct this shape with default values.
/// @param self This shape.
/// @param numberOfArguments, arguments The arguments.
void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, Ring2_Value const* arguments);

/// @brief Render this shape.
/// @param self This shape.
/// @param context The context.
void Machine_Shape2_render(Machine_Shape2* self, Machine_Context2* context);



#endif // MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED
