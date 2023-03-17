/// @file Ring3/Graphics2/Rectangle.h
/// @copyright Copyright (c) 2021-2023 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GRAPHICS2_RECTANGLE_H_INCLUDED)
#define RING3_GRAPHICS2_RECTANGLE_H_INCLUDED

#if !defined(RING3_GRAPHICS2_PRIVATE)
#error("Do not include `Ring3/Graphics2/Rectangle.h` directly. Include `Ring3/raphics2/_Include.h` instead.")
#endif
#include "Ring3/Graphics2/Shape.h"

/// @brief
/// C-level representation of a rectangle.
/// @details
/// The default position is (0,0).
/// The default size is (0,0).
/// The default color is opaque white.
/// @extends Machine.Shape2
MACHINE_DECLARE_CLASSTYPE(Ring3_Graphics2_Rectangle);

struct Ring3_Graphics2_Rectangle_Class {
  Ring3_Graphics2_Shape_Class _parent;
};

struct Ring3_Graphics2_Rectangle {
  Ring3_Graphics2_Shape _parent;
  Ring3_Math_Vector2f32* position;
  Ring3_Math_Vector2f32* size;
  Ring3_Math_Vector4f32* color;
};

void
Ring3_Graphics2_Rectangle_construct
  (
    Ring3_Graphics2_Rectangle* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );

Ring1_NoDiscardReturn() Ring3_Graphics2_Rectangle*
Ring3_Graphics2_Rectangle_create
  (
  );

/// @brief Set  the rectangle.
/// @param self This rectangle.
/// @param rectangle The rectangle.
/// @remarks A copy is stored.
void
Ring3_Graphics2_Rectangle_setRectangle
  (
    Ring3_Graphics2_Rectangle* self,
    Ring3_Math_Rectangle2 const* rectangle
  );

/// @brief Get the rectangle.
/// @param self This rectangle.
/// @return The rectangle.
/// @remarks A copy is returned.
Ring1_NoDiscardReturn() Ring3_Math_Rectangle2*
Ring3_Graphics2_Rectangle_getRectangle
  (
    Ring3_Graphics2_Rectangle const* self
  );

/// @brief Set the color of this rectangle.
/// @param self This rectangle. 
/// @param color The color.
/// @remarks A copy is stored.
void
Ring3_Graphics2_Rectangle_setColor
  (
    Ring3_Graphics2_Rectangle* self,
    Ring3_Math_Vector4f32 const* color
  );

/// @brief Get the color of this rectangle.
/// @param self This rectangle.
/// @return The color.
/// @remarks A copy is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Graphics2_Rectangle_getColor
  (
    Ring3_Graphics2_Rectangle const* self
  );

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
/// @remarks A copy is stored.
void
Ring3_Graphics2_Rectangle_setSize
  (
    Ring3_Graphics2_Rectangle* self,
    Ring3_Math_Vector2f32 const* size
  );

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size.
/// @remarks A copy is returned..
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Graphics2_Rectangle_getSize
  (
    Ring3_Graphics2_Rectangle const* self
  );

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param position The position.
/// @remarks A copy is stored.
void
Ring3_Graphics2_Rectangle_setPosition
  (
    Ring3_Graphics2_Rectangle* self,
    Ring3_Math_Vector2f32 const* position
  );

/// @brief Get the position of this rectangle.
/// @param self This rectangle.
/// @return The position.
/// @remarks A copy is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Graphics2_Rectangle_getPosition
  (
    Ring3_Graphics2_Rectangle const* self
  );

#endif // RING3_GRAPHICS2_RECTANGLE_H_INCLUDED
