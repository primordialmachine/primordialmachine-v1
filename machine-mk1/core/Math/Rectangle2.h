/// @file Math/Rectangle2.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_MATH_RECTANGLE2_H_INCLUDED)
#define MACHINE_MATH_RECTANGLE2_H_INCLUDED

#include "_Runtime.h"
typedef struct Machine_Math_Vector2 Machine_Math_Vector2;
typedef struct Machine_Math_Vector3 Machine_Math_Vector3;

/// C-level definition of a 2D rectangle.
/// The HLL-level definition is
/// @code
/// class Machine.Math.Rectangle2 { ... }
/// @endcode
typedef struct Machine_Math_Rectangle2 Machine_Math_Rectangle2;

struct Machine_Math_Rectangle2 {
  float x, y;
  float w, h;
};

Machine_Math_Rectangle2* Machine_Math_Rectangle2_create();

Machine_Math_Rectangle2* Machine_Math_Rectangle2_clone(const Machine_Math_Rectangle2* self);

void Machine_Math_Rectangle2_copy(Machine_Math_Rectangle2* self, const Machine_Math_Rectangle2* other);

/// @brief Set the position of this rectangle.
/// @param self This rectangle.
/// @param position The position.
void Machine_Math_Rectangle2_setPosition(Machine_Math_Rectangle2* self, const Machine_Math_Vector2* position);

/// @brief Get the position of this rectangle.
/// @param self This rectangle.
/// @return The position.
Machine_Math_Vector2* Machine_Math_Rectangle2_getPosition(const Machine_Math_Rectangle2* self);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
void Machine_Math_Rectangle2_setSize(Machine_Math_Rectangle2* self, const Machine_Math_Vector2* size);

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size of this rectangle.
const Machine_Math_Vector2* Machine_Math_Rectangle2_getSize(const Machine_Math_Rectangle2* self);

/// @brief Get the center of this rectangle.
/// @param self This rectangle.
/// @return The center of this rectangle.
const Machine_Math_Vector2* Machine_Math_Rectangle2_getCenter(const Machine_Math_Rectangle2* self);

/// @brief Add a pointer to this rectangle.
/// @param self This rectangle.
/// @param point The point.
void Machine_Math_Rectangle2_addPoint(Machine_Math_Rectangle2* self, const Machine_Math_Vector2* point);

/// @brief Add a rectangle to this rectangle.
/// @param self This rectangle.
/// @param rectangle The rectangle.
void Machine_Math_Rectangle2_addRectangle(Machine_Math_Rectangle2* self, const Machine_Math_Rectangle2* rectangle);

/// @brief Translate this rectangle such that its center is the specified point.
/// @param self This rectangle.
/// @param x, y The point.
void Machine_Math_Rectangle2_setCenter(Machine_Math_Rectangle2* self, float x, float y);

/// @brief Get the minimum of this rectangle.
/// @param self This rectangle.
/// @return The minimum.
Machine_Math_Vector2* Machine_Math_Rectangle2_getMin(const Machine_Math_Rectangle2* self);

/// @brief Get the maximum of this rectangle.
/// @param self This rectangle.
/// @return The maximum.
Machine_Math_Vector2* Machine_Math_Rectangle2_getMax(const Machine_Math_Rectangle2* self);

/// @brief Get the minimum of this rectangle along the x-axis.
/// @param self This rectangle.
/// @return The minimum along the x-axis.
float Machine_Math_Rectangle2_getMinX(const Machine_Math_Rectangle2* self);

/// @brief Get the minimum of this rectangle along the y-axis.
/// @param self This rectangle.
/// @return The minimum along the y-axis.
float Machine_Math_Rectangle2_getMinY(const Machine_Math_Rectangle2* self);

/// @brief Get the minimum of this rectangle along the x-axis.
/// @param self This rectangle.
/// @return The maximum along the x-axis.
float Machine_Math_Rectangle2_getMaxX(const Machine_Math_Rectangle2* self);

/// @brief Get the maximum of this rectangle along the y-axis.
/// @param self This rectangle.
/// @return The maximum along the y-axis.
float Machine_Math_Rectangle2_getMaxY(const Machine_Math_Rectangle2* self);

/// @brief Reduce the width and the height of this rectangle.
/// @param self This rectangle.
/// @param minx The amount to add to the x-axis minimum side.
/// @param miny The amount to add to the y-axis minimum side.
/// @param maxx The amount to subtract from the x-axis maximum side.
/// @param maxy The amount to subtract from the y-axis maximum side.
/// @error @a minx, @a miny, @a maxx, or @a maxy is negative.
void Machine_Math_Rectangle2_inset(Machine_Math_Rectangle2* self, float minx, float miny, float maxx, float maxy);

#endif // MACHINE_MATH_RECTANGLE2_H_INCLUDED
