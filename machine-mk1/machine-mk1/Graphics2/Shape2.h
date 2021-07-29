#if !defined(MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED)
#define MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED



#if !defined(MACHINE_GRAPHICS2_PRIVATE)
#error("Do not include this file directly, include `_Graphics2.h` instead.")
#endif
#include "_Math.h"



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

struct Machine_Shape2 {
  Machine_Object parent;
  void (*render)(Machine_Shape2* self, float width, float height);
};

/// @brief Construct this shape with default values.
/// @param self This shape.
/// @param numberOfArguments, arguments The arguments.
void Machine_Shape2_construct(Machine_Shape2* self, size_t numberOfArguments, Machine_Value const* arguments);

void Machine_Shape2_render(Machine_Shape2* self, float width, float height);



#endif // MACHINE_GRAPHICS2_SHAPE2_H_INCLUDED
