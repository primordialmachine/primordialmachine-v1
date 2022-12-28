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
    Ring3_Math_Vector4f32 const* self
  );

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_copy
  (
    Ring3_Math_Vector4f32* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the sum of two vectors.
/// @param self This vector.
/// @param other The other vector.
/// @param target The vector to store the result in.
void
Ring3_Math_Vector4f32_add
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other,
    Ring3_Math_Vector4f32* target
  );

/// @brief Compute the sum of this vector and another vector.
/// @param self This vector.
/// @param other The other vector.
/// @return The sum vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_sum
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the difference of this vector and another vector.
/// @param self This vector.
/// @param other The other vector.
/// @param target The vector to store the result in.
void
Ring3_Math_Vector4f32_subtract
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other,
    Ring3_Math_Vector4f32* target
  );

/// @brief Compute the difference of this vector and another vector.
/// @param self This vector.
/// @param other The other vector.
/// @return The difference vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_difference
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the component-wise product of this vector and another vector.
/// @param target The vector to store the result in.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_multiply
  (
    Ring3_Math_Vector4f32* target,
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the component-wise product of this vector with another vector.
/// @param self This vector.
/// @param other The other vector.
/// @return The component-wise product vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_product
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the component-wise quotient of two vectors.
/// @param target The vector to store the result in.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_divide
  (
    Ring3_Math_Vector4f32* target,
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the component-wise quotient of this vector and another vectors.
/// @param self This vector.
/// @param other The other vector.
/// @return The component-wise quotient vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_quotient
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the dot product of two vectors.
/// @param self This vector.
/// @param other The other vector.
/// @return The dot product of the vectors.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_dot
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Get the component-wise maxima of this vector and another vector i.e. a vector \f$c_i = \max(a_i,b_i)\f$
/// @param target The vector to store the result in.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_maxima
  (
    Ring3_Math_Vector4f32* target,
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Get the component-wise minima vector of this vector and another vector i.e. a vector \f$c_i = \min(a_i,b_i)\f$
/// @param target The vector to store the result in.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_minima
  (
    Ring3_Math_Vector4f32* target,
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the product of this vector and a scalar.
/// @param self The vector.
/// @param other The scalar.
/// @return The product.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_multiplyScalar
  (
    Ring3_Math_Vector4f32 const* self,
    Ring2_Real32 other
  );

/// @brief Compute the product of this vector and a scalar.
/// Store the result in this vector.
/// @param self This vector.
/// @param other The scalar.
void
Ring3_Math_Vector4f32_multiplyScalarInSitu
  (
    Ring3_Math_Vector4f32* self,
    Ring2_Real32 other
  );

/// @brief Compute the quotient of this vector and a scalar.
/// @param self This vector.
/// @param other The scalar.
/// @return The quotient.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_divideScalar
  (
    Ring3_Math_Vector4f32 const* self,
    Ring2_Real32 other
  );

/// @brief Compute the quotient of this vector and a scalar.
/// Store the result in this vector.
/// @param self This vector.
/// @param other The scalar.
void
Ring3_Math_Vector4f32_divideScalarInSitu
  (
    Ring3_Math_Vector4f32* self,
    Ring2_Real32 other
  );

/// @brief Get the length of this vector.
/// @param self This vector.
/// @return The length of this vector.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_length
  (
    Ring3_Math_Vector4f32 const* self
  );

/// @brief Get the squared length of this vector.
/// @param self This vector.
/// @return The squared length of this vector.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_squaredLength
  (
    Ring3_Math_Vector4f32 const* self
  );

/// @brief Compute the normalized vector of this vector.
/// @param self This vector.
/// @return The normalized vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_normalize
  (
    Ring3_Math_Vector4f32 const* self
  );

/// @brief Compute the normalized vector of this vector.
/// Store the result in this vector.
/// @param self This vector.
void
Ring3_Math_Vector4f32_normalizeInSitu
  (
    Ring3_Math_Vector4f32* self
  );

/// @brief Compare this vector and another vector with tolerance.
/// @param self This vector.
/// @param other The other vector.
/// @param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @return @a true if the vectors are equal. @a false otherwise.
/// @remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Vector4f32_isEqualToWithTolerance
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  );

/// @brief Swap the component of this vector with the component of another vector depending on which component value is greater.
/// That is, given two vectors $u$ and $v$, compute \f$u'\f$ and \f$v'\f$ such that \f$u'_i = \min(u_i, v_i)\f$ and \f$v'_i = \max(u_i, v_i)\f$.
/// @param self This vector.
/// @param other The other vector.
/// @param min, max Pointers to vectors variables.
/// @success @a *min was assigned the minimum vector, @a *max was assigned the maximum vector.
void
Ring3_Math_Vector4f32_extrema
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other,
    Ring3_Math_Vector4f32* min,
    Ring3_Math_Vector4f32* max
  );

#if RING3_MATH_VECTOR_DIMENSIONALITY == 1
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* self,
    Ring2_Real32 x
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 2
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* self,
    Ring2_Real32 x,
    Ring2_Real32 y
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 3
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* self,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z
  );
#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 4
void
Ring3_Math_Vector4f32_set
  (
    Ring3_Math_Vector4f32* self,
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
    Ring3_Math_Vector4f32 const* self
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 1

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getY
  (
    Ring3_Math_Vector4f32 const* self
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 2

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getZ
  (
    Ring3_Math_Vector4f32 const* self
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 3

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4f32_getW
  (
    Ring3_Math_Vector4f32 const* self
  );

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 3

/// @brief Compute the cross product of this vector and another vectors.
/// @param self This vector.
/// @param other The other vector.
/// @return The cross product of this vector and another vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4f32*
Ring3_Math_Vector4f32_cross
  (
    Ring3_Math_Vector4f32 const* self,
    Ring3_Math_Vector4f32 const* other
  );

/// @brief Compute the cross product of this vector and another vector.
/// Store the result in this vector.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4f32_crossInSitu
  (
    Ring3_Math_Vector4f32* self,
    Ring3_Math_Vector4f32 const* other
  );

#endif

#undef RING3_MATH_VECTOR_DIMENSIONALITY

#endif // RING3_MATH_VECTOR4F32_H_INCLUDED
