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
/// class Machine.Math.Rectangle2 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Machine_Math_Matrix4)

struct Machine_Math_Matrix4_Class {
  Machine_Object_Class parent;
};

struct Machine_Math_Matrix4 {
  Machine_Object parent;
  float e[4][4];
};

Machine_Math_Matrix4* Machine_Math_Matrix4_create();

Machine_Math_Matrix4* Machine_Math_Matrix4_clone(const Machine_Math_Matrix4* self);

void Machine_Math_Matrix4_copy(Machine_Math_Matrix4* self, const Machine_Math_Matrix4* other);

void Machine_Math_Matrix4_setIdentity(Machine_Math_Matrix4* self);

void Machine_Math_Matrix4_transpose(Machine_Math_Matrix4* self);

void Machine_Math_Matrix4_add(Machine_Math_Matrix4* c, Machine_Math_Matrix4* a, Machine_Math_Matrix4* b);
Machine_Math_Matrix4* Machine_Math_Matrix4_sum(Machine_Math_Matrix4* a, Machine_Math_Matrix4* b);

void Machine_Math_Matrix4_subtract(Machine_Math_Matrix4* c, Machine_Math_Matrix4* a, Machine_Math_Matrix4* b);
Machine_Math_Matrix4* Machine_Math_Matrix4_difference(Machine_Math_Matrix4* a, Machine_Math_Matrix4* b);

void Machine_Math_Matrix4_setOrtho(Machine_Math_Matrix4* a, float l, float r, float b, float t, float n, float f);

void Machine_Math_Matrix4_multiply(Machine_Math_Matrix4* c, Machine_Math_Matrix4* a, Machine_Math_Matrix4* b);
Machine_Math_Matrix4* Machine_Math_Matrix4_product(Machine_Math_Matrix4* a, Machine_Math_Matrix4* b);

/// @brief 
/// @param a 
/// @param d The angle, in radians.
void Machine_Math_Matrix4_rotateZ(Machine_Math_Matrix4* a, float r);

#endif // RING3_MATH_MATRIX4_H_INCLUDED
