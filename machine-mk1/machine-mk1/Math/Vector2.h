#if !defined(MACHINE_MATH_VECTOR2_H_INCLUDED)
#define MACHINE_MATH_VECTOR2_H_INCLUDED

#include "./../Machine.h"

typedef struct Machine_Math_Vector2 Machine_Math_Vector2;

Machine_Math_Vector2* Machine_Math_Vector2_create();

void Machine_Math_Vector2_set(Machine_Math_Vector2* self, float x, float y);

float Machine_Math_Vector2_getX(Machine_Math_Vector2* self);

float Machine_Math_Vector2_getY(Machine_Math_Vector2* self);

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

float Machine_Math_Vector2_dot(Machine_Math_Vector2* c);

#endif // MACHINE_MATH_VECTOR2_H_INCLUDED
