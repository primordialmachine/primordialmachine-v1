/// @file Math/Vector4.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_MATH_VECTOR4_H_INCLUDED)
#define MACHINE_MATH_VECTOR4_H_INCLUDED

#include "./../Machine.h"

/// C-level definition of a 3D vector.
/// The HLL-level definition is
/// @code
/// class Machine.Math.Vector4 { ... }
/// @endcode
typedef struct Machine_Math_Vector4 Machine_Math_Vector4;

Machine_Math_Vector4* Machine_Math_Vector4_create();

Machine_Math_Vector4* Machine_Math_Vector4_clone(Machine_Math_Vector4* self);

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void Machine_Math_Vector4_copy(Machine_Math_Vector4* self, const Machine_Math_Vector4* other);

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector4_add(Machine_Math_Vector4* c, Machine_Math_Vector4* a, Machine_Math_Vector4* b);
Machine_Math_Vector4* Machine_Math_Vector4_sum(Machine_Math_Vector4* a, Machine_Math_Vector4* b);

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector4_subtract(Machine_Math_Vector4* c, Machine_Math_Vector4* a, Machine_Math_Vector4* b);
Machine_Math_Vector4* Machine_Math_Vector4_sum(Machine_Math_Vector4* a, Machine_Math_Vector4* b);

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector4_multiply(Machine_Math_Vector4* c, Machine_Math_Vector4* a, Machine_Math_Vector4* b);
Machine_Math_Vector4* Machine_Math_Vector4_product(Machine_Math_Vector4* a, Machine_Math_Vector4* b);

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
float Machine_Math_Vector4_dot(const Machine_Math_Vector4* a, const Machine_Math_Vector4* b);



void Machine_Math_Vector4_set(Machine_Math_Vector4* a, float x, float y, float z, float w);

float Machine_Math_Vector4_getX(const Machine_Math_Vector4* a);

float Machine_Math_Vector4_getY(const Machine_Math_Vector4* a);

float Machine_Math_Vector4_getZ(const Machine_Math_Vector4* a);

float Machine_Math_Vector4_getW(const Machine_Math_Vector4* a);



#endif // MACHINE_MATH_VECTOR4_H_INCLUDED
