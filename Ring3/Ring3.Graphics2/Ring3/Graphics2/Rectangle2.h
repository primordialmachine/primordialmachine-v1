/// @file Ring3/Graphics2/Rectangle2.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_GRAPHICS2_RECTANGLE2_H_INCLUDED)
#define RING3_GRAPHICS2_RECTANGLE2_H_INCLUDED

#if !defined(RING3_GRAPHICS2_PRIVATE)
#error("Do not include `Ring3/Graphics2/Rectangle2.h` directly. Include `Ring3/raphics2/_Include.h` instead.")
#endif
#include "Ring3/Graphics2/Shape2.h"

/// @brief
/// C-level representation of a rectangle.
/// @details
/// The default position is (0,0).
/// The default size is (0,0).
/// The default color is opaque white.
/// @extends Machine.Shape2
MACHINE_DECLARE_CLASSTYPE(Ring3_Rectangle2);

struct Ring3_Rectangle2_Class {
  Ring3_Shape2_Class __parent;
};

struct Ring3_Rectangle2 {
  Ring3_Shape2 __parent;
  Ring3_Math_Vector2f32* position;
  Ring3_Math_Vector2f32* size;
  Ring3_Math_Vector4f32* color;
};

void
Ring3_Rectangle2_construct
  (
    Ring3_Rectangle2* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );

Ring3_Rectangle2*
Ring3_Rectangle2_create
  (
  );

/// @brief Set  the rectangle.
/// @param self This rectangle.
/// @param rectangle The rectangle.
void
Ring3_Rectangle2_setRectangle
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Rectangle2 const* rectangle
  );

/// @brief Get the rectangle.
/// @param self This rectangle.
/// @return The rectangle.
Ring3_Math_Rectangle2*
Ring3_Rectangle2_getRectangle
  (
    Ring3_Rectangle2 const* self
  );

/// @brief Set the color of this rectangle.
/// @param self This rectangle. 
/// @param color The color.
void
Ring3_Rectangle2_setColor
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Vector4f32 const* color
  );

/// @brief Get the color of this rectangle.
/// @param self This rectangle.
/// @return The color.
Ring3_Math_Vector4f32*
Ring3_Rectangle2_getColor
  (
    Ring3_Rectangle2 const* self
  );

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
/// @todo Validate arguments.
void
Ring3_Rectangle2_setSize
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Vector2f32 const* size
  );

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size.
/// @todo Validate arguments.
Ring3_Math_Vector2f32*
Ring3_Rectangle2_getSize
  (
    Ring3_Rectangle2 const* self
  );

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param position The position.
/// @todo Validate arguments.
void
Ring3_Rectangle2_setPosition
  (
    Ring3_Rectangle2* self,
    Ring3_Math_Vector2f32 const* position
  );

/// @brief Get the position of this rectangle.
/// @param self This rectangle.
/// @return The position.
/// @todo Validate arguments.
Ring3_Math_Vector2f32*
Ring3_Rectangle2_getPosition
  (
    Ring3_Rectangle2 const* self
  );

#endif // RING3_GRAPHICS2_RECTANGLE2_H_INCLUDED
