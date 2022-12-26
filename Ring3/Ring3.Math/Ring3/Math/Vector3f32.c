/// @file Ring3/Math/Vector3f32.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector3f32.h"

#include "Ring3/Math/Kernels/VectorKernel.h"

#define RING3_MATH_VECTOR_DIMENSIONALITY (3)

static void
Ring3_Math_Vector3f32_construct
  (
    Ring3_Math_Vector3f32* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->e[0] = 0.f;
#if RING3_MATH_VECTOR_DIMENSIONALITY > 1
  self->e[1] = 0.f;
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 2
  self->e[2] = 0.f;
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 3
  self->e[3] = 0.f;
#endif
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Vector3f32_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Vector3f32,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Vector3f32_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Vector3f32_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Vector3f32* self = Ring1_cast(Ring3_Math_Vector3f32*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_clone
  (
    const Ring3_Math_Vector3f32* self
  )
{
  Ring3_Math_Vector3f32* other = Ring3_Math_Vector3f32_create();
  Ring3_Math_Vector3f32_copy(other, self);
  return other;
}

void
Ring3_Math_Vector3f32_copy
  (
    Ring3_Math_Vector3f32* self,
    const Ring3_Math_Vector3f32* other
  )
{
  copy_vv_f32(other->e, self->e, 3);
}

void
Ring3_Math_Vector3f32_add
  (
    Ring3_Math_Vector3f32* c,
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  add_vv_f32(a->e, b->e, c->e, 3);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_sum
  (
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  Ring3_Math_Vector3f32* c = Ring3_Math_Vector3f32_create();
  add_vv_f32(a->e, b->e, c->e, 3);
  return c;
}

void
Ring3_Math_Vector3f32_subtract
  (
    Ring3_Math_Vector3f32* c,
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  sub_vv_f32(a->e, b->e, c->e, 3);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_difference
  (
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  Ring3_Math_Vector3f32* c = Ring3_Math_Vector3f32_create();
  sub_vv_f32(a->e, b->e, c->e, 3);
  return c;
}

void
Ring3_Math_Vector3f32_multiply
  (
    Ring3_Math_Vector3f32* c,
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  mul_vv_f32(a->e, b->e, c->e, 3);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_product
  (
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  Ring3_Math_Vector3f32* c = Ring3_Math_Vector3f32_create();
  mul_vv_f32(a->e, b->e, c->e, 3);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_dot
  (
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  Ring2_Real32 s;
  dot_vv_f32(a->e, b->e, &s, 3);
  return s;  
}

void
Ring3_Math_Vector3f32_maxima
  (
    Ring3_Math_Vector3f32* c,
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  max_vv_f32(a->e, b->e, c->e, 3);
}

void
Ring3_Math_Vector3f32_minima
  (
    Ring3_Math_Vector3f32* c,
    const Ring3_Math_Vector3f32* a,
    const Ring3_Math_Vector3f32* b
  )
{
  min_vv_f32(a->e, b->e, c->e, 3);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_multiplyScalar
  (
    Ring3_Math_Vector3f32 const* a,
    Ring2_Real32 b
  )
{
  Ring3_Math_Vector3f32* c = Ring3_Math_Vector3f32_create();
  mul_vs_f32(a->e, b, c->e, 3);
  return c;
}

void
Ring3_Math_Vector3f32_multiplyScalarInSitu
  (
    Ring3_Math_Vector3f32* a,
    Ring2_Real32 b
  )
{
  mul_vs_f32(a->e, b, a->e, 3);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_divideScalar
  (
    Ring3_Math_Vector3f32 const* a,
    Ring2_Real32 b
  )
{
  Ring3_Math_Vector3f32* c = Ring3_Math_Vector3f32_create();
  div_vs_f32(a->e, b, c->e, 3);
  return c;
}

void
Ring3_Math_Vector3f32_divideScalarInSitu
  (
    Ring3_Math_Vector3f32* a,
    Ring2_Real32 b
  )
{
  div_vs_f32(a->e, b, a->e, 3);
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_length
  (
    const Ring3_Math_Vector3f32* a
  )
{
  Ring2_Real32 t;
  length_vs_f32(a->e, &t, 3);
  return t;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_squaredLength
  (
    const Ring3_Math_Vector3f32* a
  )
{
  Ring2_Real32 t;
  squaredLength_vs_f32(a->e, &t, 3);
  return t;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_normalize
  (
    Ring3_Math_Vector3f32 const* a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector3f32_length(a);
  return Ring3_Math_Vector3f32_divideScalar(a, l);
}

void
Ring3_Math_Vector3f32_normalizeInSitu
  (
    Ring3_Math_Vector3f32* a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector3f32_length(a);
  Ring3_Math_Vector3f32_divideScalarInSitu(a, l);
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Vector3f32_isEqualToWithTolerance
  (
    Ring3_Math_Vector3f32 const* a,
    Ring3_Math_Vector3f32 const* b,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  )
{
  if (!a || !b || absolute <= 0. || relative <= 0.) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (a == b) {
    return true;
  }
  for (size_t i = 0, n = 3; i < n; ++i) {
    bool equal;
    if (Ring1_Fp_equalToWithTolerance_f32(&equal, a->e[i], b->e[i], absolute, relative)) {
      Ring2_jump();
    }
    if (!equal) {
      return false;
    }
  }
  return true;
}

void
Ring3_Math_Vector3f32_extrema
  (
    Ring3_Math_Vector3f32 const* a,
    Ring3_Math_Vector3f32 const* b,
    Ring3_Math_Vector3f32* min,
    Ring3_Math_Vector3f32* max
  )
{
  if (!a || !b || !min || !max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  minMax_vv_f32(a->e, b->e, min->e, max->e, 3);
}

void
Ring3_Math_Vector3f32_set
  (
    Ring3_Math_Vector3f32* self,
    Ring2_Real32 x
#if RING3_MATH_VECTOR_DIMENSIONALITY > 1
    ,Ring2_Real32 y
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 2
    ,Ring2_Real32 z
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 3
    ,Ring2_Real32 w
#endif
  )
{
  self->e[0] = x;
#if RING3_MATH_VECTOR_DIMENSIONALITY > 1
  self->e[1] = y;
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 2
  self->e[2] = z;
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 3
  self->e[3] = w;
#endif
}

#if RING3_MATH_VECTOR_DIMENSIONALITY > 0

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_getX
  (
    const Ring3_Math_Vector3f32* self
  )
{ return self->e[0]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 1

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_getY
  (
    const Ring3_Math_Vector3f32* self
  )
{ return self->e[1]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 2

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_getZ
  (
    const Ring3_Math_Vector3f32* self
  )
{ return self->e[2]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 3

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3f32_getW
  (
    const Ring3_Math_Vector3f32* self
  )
{ return self->e[3]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 3

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Vector3f32_cross
  (
    Ring3_Math_Vector3f32 const* a,
    Ring3_Math_Vector3f32 const* b
  )
{
  Ring2_Real32 temporary[] = {
    a->e[1] * b->e[2] - a->e[2] * b->e[1],
    a->e[2] * b->e[0] - a->e[0] * b->e[2],
    a->e[0] * b->e[1] - a->e[1] * b->e[0],
  };
  return Ring3_Math_Vector3f32_create(temporary[0], temporary[1], temporary[2]);
}

void
Ring3_Math_Vector3f32_crossInSitu
  (
    Ring3_Math_Vector3f32* a,
    Ring3_Math_Vector3f32 const* b
  )
{
  Ring2_Real32 temporary[] = {
    a->e[1] * b->e[2] - a->e[2] * b->e[1],
    a->e[2] * b->e[0] - a->e[0] * b->e[2],
    a->e[0] * b->e[1] - a->e[1] * b->e[0],
  };
  Ring3_Math_Vector3f32_set(a, temporary[0], temporary[1], temporary[2]);
}

#endif

#undef RING3_MATH_VECTOR_DIMENSIONALITY
