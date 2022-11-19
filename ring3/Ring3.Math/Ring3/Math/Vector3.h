/// @file Ring3/Math/Vector3.h
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_VECTOR3_H_INCLUDED)
#define RING3_MATH_VECTOR3_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Vector3.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// C-level definition of a 3D vector.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Vector3 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Vector3)

struct Ring3_Math_Vector3_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Vector3 {
  Machine_Object parent;
  float x, y, z;
};

Ring1_CheckReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_create
  (
  );

Ring1_CheckReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_clone
  (
    const Ring3_Math_Vector3* self
  );

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector3_copy
  (
    Ring3_Math_Vector3* self,
    const Ring3_Math_Vector3* other
  );

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector3_add
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Compute the sum of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The sum vector.
Ring1_CheckReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_sum
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector3_subtract
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Compute the difference of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The difference vector.
Ring1_CheckReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_difference
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector3_multiply
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The component-wise product vector.
Ring1_CheckReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_product
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
Ring1_CheckReturn() float
Ring3_Math_Vector3_dot
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Get the component-wise maxima vector of two vectors i.e. a vector \f$c_i = \max(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector3_maxima
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

/// @brief Get the component-wise minima vector of two vectors i.e. a vector \f$c_i = \min(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector3_minima
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  );

void
Ring3_Math_Vector3_set
  (
    Ring3_Math_Vector3* a,
    float x,
    float y,
    float z
  );

Ring1_CheckReturn() float
Ring3_Math_Vector3_getX
  (
    const Ring3_Math_Vector3* a
  );

Ring1_CheckReturn() float
Ring3_Math_Vector3_getY
  (
    const Ring3_Math_Vector3* a
  );

Ring1_CheckReturn() float
Ring3_Math_Vector3_getZ
  (
    const Ring3_Math_Vector3* a
  );

#endif // RING3_MATH_VECTOR3_H_INCLUDED