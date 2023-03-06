/// @file Ring3/Math/Rectangle2.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_RECTANGLE2_H_INCLUDED)
#define RING3_MATH_RECTANGLE2_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Rectangle2.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"
typedef struct Ring3_Math_Vector2f32 Ring3_Math_Vector2f32;
typedef struct Ring3_Math_Vector3f32 Ring3_Math_Vector3f32;

/// C-level definition of a 2D rectangle.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Rectangle2 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Rectangle2)

struct Ring3_Math_Rectangle2_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Rectangle2 {
  Machine_Object parent;
  Ring2_Real32 x, y;
  Ring2_Real32 w, h;
};

Ring1_CheckReturn() Ring3_Math_Rectangle2*
Ring3_Math_Rectangle2_create
  (
  );

Ring1_CheckReturn() Ring3_Math_Rectangle2*
Ring3_Math_Rectangle2_clone
  (
    const Ring3_Math_Rectangle2* self
  );

void
Ring3_Math_Rectangle2_copy
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Rectangle2* other
  );

/// @brief Set the position of this rectangle.
/// @param self This rectangle.
/// @param position The position.
void
Ring3_Math_Rectangle2_setPosition
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* position
  );

/// @brief Get the position of this rectangle.
/// @param self This rectangle.
/// @return The position.
Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getPosition
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
void
Ring3_Math_Rectangle2_setSize
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* size
  );

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size of this rectangle.
Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getSize
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Get the center of this rectangle.
/// @param self This rectangle.
/// @return The center of this rectangle.
Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getCenter
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Add a pointer to this rectangle.
/// @param self This rectangle.
/// @param point The point.
void
Ring3_Math_Rectangle2_addPoint
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* point
  );

/// @brief Add a rectangle to this rectangle.
/// @param self This rectangle.
/// @param rectangle The rectangle.
void
Ring3_Math_Rectangle2_addRectangle
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Rectangle2* rectangle
  );

/// @brief Translate this rectangle such that its center is the specified point.
/// @param self This rectangle.
/// @param x, y The point.
void
Ring3_Math_Rectangle2_setCenter
  (
    Ring3_Math_Rectangle2* self,
    Ring2_Real32 x,
    Ring2_Real32 y
  );

/// @brief Get the minimum of this rectangle.
/// @param self This rectangle.
/// @return The minimum.
Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getMin
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Get the maximum of this rectangle.
/// @param self This rectangle.
/// @return The maximum.
Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getMax
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Get the minimum of this rectangle along the x-axis.
/// @param self This rectangle.
/// @return The minimum along the x-axis.
Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMinX
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Get the minimum of this rectangle along the y-axis.
/// @param self This rectangle.
/// @return The minimum along the y-axis.
Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMinY
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Get the minimum of this rectangle along the x-axis.
/// @param self This rectangle.
/// @return The maximum along the x-axis.
Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMaxX
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Get the maximum of this rectangle along the y-axis.
/// @param self This rectangle.
/// @return The maximum along the y-axis.
Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMaxY
  (
    const Ring3_Math_Rectangle2* self
  );

/// @brief Reduce the width and the height of this rectangle.
/// @param self This rectangle.
/// @param minx The amount to add to the x-axis minimum side.
/// @param miny The amount to add to the y-axis minimum side.
/// @param maxx The amount to subtract from the x-axis maximum side.
/// @param maxy The amount to subtract from the y-axis maximum side.
/// @error @a minx, @a miny, @a maxx, or @a maxy is negative.
void
Ring3_Math_Rectangle2_inset
  (
    Ring3_Math_Rectangle2* self,
    Ring2_Real32 minx,
    Ring2_Real32 miny,
    Ring2_Real32 maxx,
    Ring2_Real32 maxy
  );

/// @brief Translate this rectangle.
/// @param self This rectangle.
/// @param t The translation vector.
void
Ring3_Math_Rectangle2_translate
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* t
  );

#endif // RING3_MATH_RECTANGLE2_H_INCLUDED
