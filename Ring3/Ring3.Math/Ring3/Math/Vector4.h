/// @file Ring3/Math/Vector4.h
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_VECTOR4_H_INCLUDED)
#define RING3_MATH_VECTOR4_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Vector4.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// C-level definition of a 3D vector.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Vector4 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Vector4)

struct Ring3_Math_Vector4_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Vector4 {
  Machine_Object parent;
  Ring2_Real32 x, y, z, w;
};

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_create
  (
  );

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_clone
  (
    const Ring3_Math_Vector4* self
  );

/// @brief Copy the values of another vector into this vector.
/// @param self This vector.
/// @param other The other vector.
void
Ring3_Math_Vector4_copy
  (
    Ring3_Math_Vector4* self,
    const Ring3_Math_Vector4* other
  );

/// @brief Compute the sum of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4_add
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_sum
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Compute the difference of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4_subtract
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Compute the difference of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The difference vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_difference
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4_multiply
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Compute the component-wise product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The component-wise protect vector.
Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_product
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Compute the dot product of two vectors.
/// @param a The first vector.
/// @param b The second vector.
/// @return The dot product of the vectors.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_dot
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Get the component-wise maxima vector of two vectors i.e. a vector \f$c_i = \max(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4_maxima
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

/// @brief Get the component-wise minima vector of two vectors i.e. a vector \f$c_i = \min(a_i,b_i)\f$
/// @param c The vector to store the result in.
/// @param a The first vector.
/// @param b The second vector.
void
Ring3_Math_Vector4_minima
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  );

void
Ring3_Math_Vector4_set
  (
    Ring3_Math_Vector4* a,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z,
    Ring2_Real32 w
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getX
  (
    const Ring3_Math_Vector4* a
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getY
  (
    const Ring3_Math_Vector4* a
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getZ
  (
    const Ring3_Math_Vector4* a
  );

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getW
  (
    const Ring3_Math_Vector4* a
  );

#endif // RING3_MATH_VECTOR4_H_INCLUDED
