/// @file Ring3/Graphics2/Shape.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GRAPHICS2_SHAPE_H_INCLUDED)
#define RING3_GRAPHICS2_SHAPE_H_INCLUDED

#if !defined(RING3_GRAPHICS2_PRIVATE)
#error("Do not include `Ring3/Graphics2/Shape.h` directly. Include `Ring3/raphics2/_Include.h` instead.")
#endif
#include "Ring3/Math/_Include.h"
typedef struct Ring3_Graphics2_Context Ring3_Graphics2_Context;

/// @brief
/// C-level representation of a shape in 2D.
/// @details
/// The canvas is a 2D coordinate system.
/// The bottom left corner of the canvas is the origin (0,0),
/// the positive x-axis goes right, the positive y-axis goes up.
/// A shape covers a not-necessarily convex area in the plane.
/// @details
/// Each shape has a position which is the bottom left corner of the bounds of the shape.
/// The bounds are the smallest rectangle enclosing the shape.
/// Examples:
/// - rectangle: bounds are the rectangle itself.
/// - circle: bounds are the smallest rectangle enclosing the circle.
/// @extends Machine.Object
MACHINE_DECLARE_CLASSTYPE(Ring3_Graphics2_Shape);

struct Ring3_Graphics2_Shape_Class {
  Machine_Object_Class parent;

  void (*render)(Ring3_Graphics2_Shape* self, Ring3_Graphics2_Context* context);
};

struct Ring3_Graphics2_Shape {
  Machine_Object parent;
};

/// @brief Construct this shape with default values.
/// @param self This shape.
/// @param numberOfArguments, arguments The arguments.
void
Ring3_Graphics2_Shape_construct
  (
    Ring3_Graphics2_Shape* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Render this shape.
/// @param self This shape.
/// @param context The context.
void
Ring3_Graphics2_Shape_render
  (
    Ring3_Graphics2_Shape* self,
    Ring3_Graphics2_Context* context
  );

#endif // RING3_GRAPHICS2_SHAPE_H_INCLUDED
