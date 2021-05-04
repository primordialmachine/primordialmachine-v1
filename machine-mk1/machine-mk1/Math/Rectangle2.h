/// @file Math/Rectangle2.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_MATH_RECTANGLE2_H_INCLUDED)
#define MACHINE_MATH_RECTANGLE2_H_INCLUDED

#include "./../Machine.h"
typedef struct Machine_Math_Vector2 Machine_Math_Vector2;
typedef struct Machine_Math_Vector3 Machine_Math_Vector3;

/// C-level definition of a 2D rectangle.
/// The HLL-level definition is
/// @code
/// class Machine.Math.Rectangle2 { ... }
/// @endcode
typedef struct Machine_Math_Rectangle2 Machine_Math_Rectangle2;

Machine_Math_Rectangle2* Machine_Math_Rectangle2_create();

void Machine_Math_Rectangle2_copy(Machine_Math_Rectangle2* self, Machine_Math_Rectangle2* other);

/// @brief Set the position of this rectangle.
/// @param self This rectangle.
/// @param position The position.
void Machine_Math_Rectangle2_setPosition(Machine_Math_Rectangle2* self, Machine_Math_Vector2* position);

/// @brief Set the size of this rectangle.
/// @param self This rectangle.
/// @param size The size.
void Machine_Math_Rectangle2_setSize(Machine_Math_Rectangle2* self, Machine_Math_Vector2* size);

/// @brief Get the size of this rectangle.
/// @param self This rectangle.
/// @return The size of this rectangle.
Machine_Math_Vector2* Machine_Math_Rectangle2_getSize(Machine_Math_Rectangle2* self);

/// @brief Get the center of this rectangle.
/// @param self This rectangle.
/// @return The center of this rectangle.
Machine_Math_Vector2* Machine_Math_Rectangle2_getCenter(Machine_Math_Rectangle2* self);

/// @brief Add a pointer to this rectangle.
/// @param self This rectangle.
/// @param point The point.
void Machine_Math_Rectangle2_addPoint(Machine_Math_Rectangle2* self, Machine_Math_Vector2* point);

/// @brief Translate this rectangle such that its center is the specified point.
/// @param self This rectangle.
/// @param x, y The point.
void Machine_Math_Rectangle2_setCenter(Machine_Math_Rectangle2* self, float x, float y);

Machine_Math_Vector2* Machine_Math_Rectangle2_getLeftTop(Machine_Math_Rectangle2* self);

#endif // MACHINE_MATH_RECTANGLE2_H_INCLUDED
