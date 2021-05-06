/// @file Math/Vector2.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_MATH_VECTOR2_H_INCLUDED)
#define MACHINE_MATH_VECTOR2_H_INCLUDED

#include "Machine.h"

/// C-level definition of a 2D vector.
/// The HLL-level definition is
/// @code
/// class Machine.Math.Vector2 { ... }
/// @endcode
typedef struct Machine_Math_Vector2 Machine_Math_Vector2;

Machine_Math_Vector2* Machine_Math_Vector2_create();

Machine_Math_Vector2* Machine_Math_Vector2_clone(Machine_Math_Vector2 *self);

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void Machine_Math_Vector2_copy(Machine_Math_Vector2* self, const Machine_Math_Vector2* other);

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector2_add(Machine_Math_Vector2* c, Machine_Math_Vector2* a, Machine_Math_Vector2* b);
Machine_Math_Vector2* Machine_Math_Vector2_sum(Machine_Math_Vector2* a, Machine_Math_Vector2* b);

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector2_subtract(Machine_Math_Vector2* c, Machine_Math_Vector2* a, Machine_Math_Vector2* b);
Machine_Math_Vector2* Machine_Math_Vector2_difference(Machine_Math_Vector2* a, Machine_Math_Vector2* b);

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector2_multiply(Machine_Math_Vector2* c, Machine_Math_Vector2* a, Machine_Math_Vector2* b);
Machine_Math_Vector2* Machine_Math_Vector2_product(Machine_Math_Vector2* a, Machine_Math_Vector2* b);

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
float Machine_Math_Vector2_dot(const Machine_Math_Vector2* a, const Machine_Math_Vector2* b);



void Machine_Math_Vector2_set(Machine_Math_Vector2* a, float x, float y);

float Machine_Math_Vector2_getX(const Machine_Math_Vector2* a);

float Machine_Math_Vector2_getY(const Machine_Math_Vector2* a);



#endif // MACHINE_MATH_VECTOR2_H_INCLUDED
