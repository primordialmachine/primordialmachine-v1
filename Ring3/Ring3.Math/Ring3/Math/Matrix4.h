/// @file Ring3/Math/Matrix4.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_MATRIX4_H_INCLUDED)
#define RING3_MATH_MATRIX4_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Matrix4.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

/// C-level definition of a 2D rectangle.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Rectangle2 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Matrix4)

struct Ring3_Math_Matrix4_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Matrix4 {
  Machine_Object parent;
  float e[4][4];
};

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_create
  (
  );

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_clone
  (
    const Ring3_Math_Matrix4* self
  );

void
Ring3_Math_Matrix4_copy
  (
    Ring3_Math_Matrix4* self,
    const Ring3_Math_Matrix4* other
  );

void
Ring3_Math_Matrix4_setIdentity
  (
    Ring3_Math_Matrix4* self
  );

void
Ring3_Math_Matrix4_transpose
  (
    Ring3_Math_Matrix4* self
  );

void
Ring3_Math_Matrix4_add
  (
    Ring3_Math_Matrix4* c,
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  );

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_sum
  (
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  );

void
Ring3_Math_Matrix4_subtract
  (
    Ring3_Math_Matrix4* c,
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  );

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_difference
  (
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  );

void
Ring3_Math_Matrix4_setOrtho
  (
    Ring3_Math_Matrix4* a,
    float l,
    float r,
    float b,
    float t,
    float n,
    float f
  );

void
Ring3_Math_Matrix4_multiply
  (
    Ring3_Math_Matrix4* c,
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  );

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_product
  (
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  );

/// @brief 
/// @param a 
/// @param d The angle, in radians.
void
Ring3_Math_Matrix4_rotateZ
  (
    Ring3_Math_Matrix4* a,
    float r
  );

#endif // RING3_MATH_MATRIX4_H_INCLUDED
