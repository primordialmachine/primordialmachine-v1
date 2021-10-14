/// @file Math/Vector3.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_MATH_VECTOR3_H_INCLUDED)
#define MACHINE_MATH_VECTOR3_H_INCLUDED

#if !defined(MACHINE_MATH_PRIVATE)
#error("Do not include this file directly, include `_Math.h` instead.")
#endif

#include "_Runtime.h"

/// C-level definition of a 3D vector.
/// The HLL-level definition is
/// @code
/// class Machine.Math.Vector3 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Machine_Math_Vector3)

struct Machine_Math_Vector3_Class {
  Machine_Object_Class parent;
};

struct Machine_Math_Vector3 {
  Machine_Object parent;
  float x, y, z;
};

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
Machine_Math_Vector3* Machine_Math_Vector3_difference(Machine_Math_Vector3* a, Machine_Math_Vector3* b);

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector3_multiply(Machine_Math_Vector3* c, Machine_Math_Vector3* a, Machine_Math_Vector3* b);
Machine_Math_Vector3* Machine_Math_Vector3_product(Machine_Math_Vector3* a, Machine_Math_Vector3* b);

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
float Machine_Math_Vector3_dot(const Machine_Math_Vector3* a, const Machine_Math_Vector3* b);

/// @brief Get the component-wise maxima vector of two vectors i.e. a vector \f$c_i = \max(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector3_maxima(Machine_Math_Vector3* c, const Machine_Math_Vector3* a, const Machine_Math_Vector3* b);

/// @brief Get the component-wise minima vector of two vectors i.e. a vector \f$c_i = \min(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void Machine_Math_Vector3_minima(Machine_Math_Vector3* c, const Machine_Math_Vector3* a, const Machine_Math_Vector3* b);



void Machine_Math_Vector3_set(Machine_Math_Vector3* a, float x, float y, float z);

float Machine_Math_Vector3_getX(const Machine_Math_Vector3* a);

float Machine_Math_Vector3_getY(const Machine_Math_Vector3* a);

float Machine_Math_Vector3_getZ(const Machine_Math_Vector3* a);



#endif // MACHINE_MATH_VECTOR3_H_INCLUDED
