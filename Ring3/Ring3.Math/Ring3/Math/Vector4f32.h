/// @file Ring3/Math/Vector4f32.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_VECTOR4F32_H_INCLUDED)
#define RING3_MATH_VECTOR4F32_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Vector4f32.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

#define RING3_MATH_VECTOR_DIMENSIONALITY (4)

/// C-level definition of a 4D vector.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Vector4f32 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Vector4f32)

struct Ring3_Math_Vector4f32_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Vector4f32 {
  Machine_Object parent;
  Ring2_Real32 e[4];
};

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_create
  (
  );

Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_clone
  (
    const Ring3_Math_Vector4f32* self
  );

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_copy
  (
    Ring3_Math_Vector4f32* self,
    const Ring3_Math_Vector4f32* other
  );

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4f32_add
  (
    Ring3_Math_Vector4f32* c,
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the sum of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The sum vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_sum
  (
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4f32_subtract
  (
    Ring3_Math_Vector4f32* c,
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the difference of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The difference vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_difference
  (
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4f32_multiply
  (
    Ring3_Math_Vector4f32* c,
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The component-wise product vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_product
  (
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_dot
  (
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Get the component-wise maxima vector of two vectors i.e. a vector \f$c_i = \max(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4f32_maxima
  (
    Ring3_Math_Vector4f32* c,
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Get the component-wise minima vector of two vectors i.e. a vector \f$c_i = \min(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4f32_minima
  (
    Ring3_Math_Vector4f32* c,
    const Ring3_Math_Vector4f32* a,
    const Ring3_Math_Vector4f32* b
  );

/// @brief Compute the product of a vector and a scalar.
/// @param a The vector.
/// @param b The scalar.
/// @return The product.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_multiplyScalar
  (
    Ring3_Math_Vector4f32 const* a,
    Ring2_Real32 b
  );

/// @brief Compute the product of a vector and a scalar.
/// Store the result in the vector.
/// @param a The vector.
/// @param b The scalar.
void
Ring3_Math_Vector4f32_multiplyScalarInSitu
  (
    Ring3_Math_Vector4f32* a,
    Ring2_Real32 b
  );

/// @brief Compute the quotient of a vector and a scalar.
/// @param a The vector.
/// @param b The scalar.
/// @return The quotient.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_divideScalar
  (
    Ring3_Math_Vector4f32 const* a,
    Ring2_Real32 b
  );

/// @brief Compute the quotient of a vector and a scalar.
/// Store the result in the vector.
/// @param a The vector.
/// @param b The scalar.
void
Ring3_Math_Vector4f32_divideScalarInSitu
  (
    Ring3_Math_Vector4f32* a,
    Ring2_Real32 b
  );

/// @brief Get the length of a vector.
/// @param a The vector.
/// @return The length of the vector.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_length
  (
    const Ring3_Math_Vector4f32* a
  );

/// @brief Get the squared length of a vector.
/// @param a The vector.
/// @return The squared length of the vector.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_squaredLength
  (
    const Ring3_Math_Vector4f32* a
  );

/// @brief Compute the normalized vector of a vector.
/// @param a The vector.
/// @return The normalized vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_normalize
  (
    Ring3_Math_Vector4f32 const* a
  );

/// @brief Compute the normalized vector of a vector.
/// Store the result in the vector.
/// @param a The vector.
void
Ring3_Math_Vector4f32_normalizeInSitu
  (
    Ring3_Math_Vector4f32* a
  );

/// @brief Compare two vectors with tolerance.
/// @param result A pointer to a <code>bool</code> variable.
/// @param a The first vector.
/// @param b The second vector.
/// @param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @return @a true if the vectors are equal. @a false otherwise.
/// @remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Vector4f32_isEqualToWithTolerance
  (
    Ring3_Math_Vector4f32 const* a,
    Ring3_Math_Vector4f32 const* b,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  );

/// @brief Swap the component of this vector with the component of another vector depending on which component value is greater.
/// That is, given two vectors $u$ and $v$, compute \f$u'\f$ and \f$v'\f$ such that \f$u'_i = \min(u_i, v_i)\f$ and \f$v'_i = \max(u_i, v_i)\f$.
/// @param a, b The vectors.
/// @param min, max Pointers to vectors variables.
/// @success @a *min was assigned the minimum vector, @a *max was assigned the maximum vector.
void
Ring3_Math_Vector4f32_extrema
  (
    Ring3_Math_Vector4f32 const* a,
    Ring3_Math_Vector4f32 const* b,
    Ring3_Math_Vector4f32* min,
    Ring3_Math_Vector4f32* max
  );

#if RING3_MATH_VECTOR_DIMENSIONALITY == 1
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* a,
    Ring2_Real32 x
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 2
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* a,
    Ring2_Real32 x,
    Ring2_Real32 y
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 3
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* a,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 4
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* a,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z,
    Ring2_Real32 w
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 0

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getX
  (
    const Ring3_Math_Vector4f32* a
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 1

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getY
  (
    const Ring3_Math_Vector4f32* a
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 2

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getZ
  (
    const Ring3_Math_Vector4f32* a
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 3

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getW
  (
    const Ring3_Math_Vector4f32* a
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 3

/// @brief Compute the cross product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The cross product of the first vector and the second vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_cross
  (
    Ring3_Math_Vector4f32 const* a,
    Ring3_Math_Vector4f32 const* b
  );

/// @brief Compute the cross product of two vectors.
/// Store the result in the first vector.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4f32_crossInSitu
  (
    Ring3_Math_Vector4f32* a,
    Ring3_Math_Vector4f32 const* b
  );

#endif

#undef RING3_MATH_VECTOR_DIMENSIONALITY

#endif // RING3_MATH_VECTOR4F32_H_INCLUDED
