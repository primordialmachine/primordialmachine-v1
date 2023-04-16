/// @@file Ring3/Math/Vector@(dimensionality)@(scalarTypeSuffix).c
/// @@copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @@author Michael Heilmann (michaelheilmann@@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector@(dimensionality)@(scalarTypeSuffix).h"

#include "Ring3/Math/Kernels/VectorKernel.h"

#define RING3_MATH_VECTOR_DIMENSIONALITY (@(dimensionality))

static void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_construct
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self,
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
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix),
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create
  (
  )
{
  Machine_Type* ty = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self = Ring1_cast(Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*,
                                                                           Machine_allocateClassObject(ty,
                                                                                                       NUMBER_OF_ARGUMENTS,
                                                                                                       ARGUMENTS));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_clone
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* other = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_copy(other, self);
  return other;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_copy
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  copy_vv_f32(other->e, self->e, @(dimensionality));
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_add
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target
  )
{
  add_vv_f32(self->e, other->e, target->e, @(dimensionality));
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_sum
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  add_vv_f32(self->e, other->e, target->e, @(dimensionality));
  return target;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_subtract
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target
  )
{
  sub_vv_f32(self->e, other->e, target->e, @(dimensionality));
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_difference
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  sub_vv_f32(self->e, other->e, target->e, @(dimensionality));
  return target;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiply
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  mul_vv_f32(self->e, other->e, target->e, @(dimensionality));
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_product
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  mul_vv_f32(self->e, other->e, target->e, @(dimensionality));
  return target;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_divide
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  div_vv_f32(self->e, other->e, target->e, @(dimensionality));
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_quotient
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  div_vv_f32(self->e, other->e, target->e, @(dimensionality));
  return target;
}

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_dot
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  @(scalarType) target;
  dot_vv_f32(self->e, other->e, &target, @(dimensionality));
  return target;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_maxima
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  max_vv_f32(self->e, other->e, target->e, @(dimensionality));
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_minima
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other
  )
{
  min_vv_f32(self->e, other->e, target->e, @(dimensionality));
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiplyScalar
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    @(scalarType) other
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  mul_vs_f32(self->e, other, target->e, @(dimensionality));
  return target;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiplyScalarInSitu
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self,
    @(scalarType) other
  )
{
  mul_vs_f32(self->e, other, self->e, @(dimensionality));
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_divideScalar
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    @(scalarType) other
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* target = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create();
  div_vs_f32(self->e, other, target->e, @(dimensionality));
  return target;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_divideScalarInSitu
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self,
    @(scalarType) other
  )
{
  div_vs_f32(self->e, other, self->e, @(dimensionality));
}

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_length
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self
  )
{
  @(scalarType) t;
  length_vs_f32(self->e, &t, @(dimensionality));
  return t;
}

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_squaredLength
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self
  )
{
  @(scalarType) t;
  squaredLength_vs_f32(self->e, &t, @(dimensionality));
  return t;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_normalize
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_length(a);
  return Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_divideScalar(a, l);
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_normalizeInSitu
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_length(a);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_divideScalarInSitu(a, l);
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* other,
    @(scalarType) absolute,
    @(scalarType) relative
  )
{
  if (!self || !other || absolute <= 0. || relative <= 0.) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (self == other) {
    return true;
  }
  for (size_t i = 0, n = @(dimensionality); i < n; ++i) {
    bool equal;
    if (Ring1_Fp_equalToWithTolerance_f32(&equal, self->e[i], other->e[i], absolute, relative)) {
      Ring2_jump();
    }
    if (!equal) {
      return false;
    }
  }
  return true;
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_extrema
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* a,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* b,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* min,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* max
  )
{
  if (!a || !b || !min || !max) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  minMax_vv_f32(a->e, b->e, min->e, max->e, @(dimensionality));
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_set
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self,
    @(scalarType) x
#if RING3_MATH_VECTOR_DIMENSIONALITY > 1
    ,@(scalarType) y
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 2
    ,@(scalarType) z
#endif
#if RING3_MATH_VECTOR_DIMENSIONALITY > 3
    ,@(scalarType) w
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

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getX
  (
    const Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self
  )
{ return self->e[0]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 1

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getY
  (
    const Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self
  )
{ return self->e[1]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 2

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getZ
  (
    const Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self
  )
{ return self->e[2]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY > 3

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getW
  (
    const Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* self
  )
{ return self->e[3]; }

#endif

#if RING3_MATH_VECTOR_DIMENSIONALITY == 3

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_cross
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* a,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* b
  )
{
  @(scalarType) temporary[] = {
    a->e[1] * b->e[2] - a->e[2] * b->e[1],
    a->e[2] * b->e[0] - a->e[0] * b->e[2],
    a->e[0] * b->e[1] - a->e[1] * b->e[0],
  };
  return Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_create(temporary[0], temporary[1], temporary[2]);
}

void
Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_crossInSitu
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* a,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) const* b
  )
{
  @(scalarType) temporary[] = {
    a->e[1] * b->e[2] - a->e[2] * b->e[1],
    a->e[2] * b->e[0] - a->e[0] * b->e[2],
    a->e[0] * b->e[1] - a->e[1] * b->e[0],
  };
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_set(a, temporary[0], temporary[1], temporary[2]);
}

#endif

#undef RING3_MATH_VECTOR_DIMENSIONALITY
