#if !defined(MACHINE_MATH_VECTOR3_H_INCLUDED)
#define MACHINE_MATH_VECTOR3_H_INCLUDED

#include "./../Machine.h"

typedef struct Machine_Math_Vector3 Machine_Math_Vector3;

Machine_Math_Vector3* Machine_Math_Vector3_create();

void Machine_Math_Vector3_set(Machine_Math_Vector3* self, float x, float y, float z);

float Machine_Math_Vector3_getX(Machine_Math_Vector3* self);

float Machine_Math_Vector3_getY(Machine_Math_Vector3* self);

float Machine_Math_Vector3_getZ(Machine_Math_Vector3* self);

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector3_add(Machine_Math_Vector3* c, Machine_Math_Vector3* a, Machine_Math_Vector3* b);
Machine_Math_Vector3* Machine_Math_Vector3_sum(Machine_Math_Vector3* a, Machine_Math_Vector3* b);

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector3_subtract(Machine_Math_Vector3* c, Machine_Math_Vector3* a, Machine_Math_Vector3* b);
Machine_Math_Vector3* Machine_Math_Vector3_sum(Machine_Math_Vector3* a, Machine_Math_Vector3* b);

#endif // MACHINE_MATH_VECTOR3_H_INCLUDED
