/// @file Ring3/Math/Vector2.h
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_VECTOR2_H_INCLUDED)
#define RING3_MATH_VECTOR2_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Vector2.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// C-level definition of a 2D vector.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Vector2 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Vector2)

struct Ring3_Math_Vector2_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Vector2 {
  Machine_Object parent;
  Ring2_Real32 x, y;
};

Ring1_NoDiscardReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_create
  (
  );

Ring1_NoDiscardReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_clone
  (
    const Ring3_Math_Vector2 *self
  );

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector2_copy
  (
    Ring3_Math_Vector2* self,
    const Ring3_Math_Vector2* other
  );

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector2_add
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Compute the sum of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The sum vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_sum
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector2_subtract
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Compute the difference of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The difference vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_difference
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector2_multiply
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

Ring1_NoDiscardReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_product
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector2_dot
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Get the component-wise maxima vector of two vectors i.e. a vector \f$c_i = \max(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector2_maxima
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Get the component-wise minima vector of two vectors i.e. a vector \f$c_i = \min(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector2_minima
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  );

/// @brief Compute the quotient of a vector and a scalar.
/// @param a The vector.
/// @param b The scalar.
/// @return The quotient.
Ring1_NoDiscardReturn() Ring3_Math_Vector2 *
Ring3_Math_Vector2_divideScalar
  (
    Ring3_Math_Vector2 const* a,
    Ring2_Real32 b
  );

/// @brief Compute the quotient of a vector and a scalar.
/// Store the result in the vector.
/// @param a The vector.
/// @param b The scalar.
void
Ring3_Math_Vector2_divideScalarInSitu
  (
    Ring3_Math_Vector2 *a,
    Ring2_Real32 b
  );

/// @brief Get the length of a vector.
/// @param a The vector.
/// @return The length of the vector.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector2_length
  (
    const Ring3_Math_Vector2* a
  );

/// @brief Get the squared length of a vector.
/// @param a The vector.
/// @return The squared length of the vector.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector2_squaredLength
  (
    const Ring3_Math_Vector2* a
  );

void
Ring3_Math_Vector2_set
  (
    Ring3_Math_Vector2* a,
    Ring2_Real32 x,
    Ring2_Real32 y
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector2_getX
  (
    const Ring3_Math_Vector2* a
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector2_getY
  (
    const Ring3_Math_Vector2* a
  );

#endif // RING3_MATH_VECTOR2_H_INCLUDED
