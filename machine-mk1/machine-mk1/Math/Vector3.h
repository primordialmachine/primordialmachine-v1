/// @file Math/Vector3.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_MATH_VECTOR3_H_INCLUDED)
#define MACHINE_MATH_VECTOR3_H_INCLUDED

#include "./../Machine.h"

/// C-level definition of a 3D vector.
/// The HLL-level definition is
/// @code
/// class Machine.Math.Vector3 { ... }
/// @endcode
typedef struct Machine_Math_Vector3 Machine_Math_Vector3;

Machine_Math_Vector3* Machine_Math_Vector3_create();

Machine_Math_Vector3* Machine_Math_Vector3_clone(Machine_Math_Vector3* self);

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void Machine_Math_Vector3_copy(Machine_Math_Vector3* self, const Machine_Math_Vector3* other);

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

float Machine_Math_Vector3_dot(Machine_Math_Vector3* c);



void Machine_Math_Vector3_set(Machine_Math_Vector3* self, float x, float y, float z);

float Machine_Math_Vector3_getX(Machine_Math_Vector3* self);

float Machine_Math_Vector3_getY(Machine_Math_Vector3* self);

float Machine_Math_Vector3_getZ(Machine_Math_Vector3* self);



#endif // MACHINE_MATH_VECTOR3_H_INCLUDED
