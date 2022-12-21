/// @file Ring3/Math/Vector4.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector4.h"

#include "Ring1/All/_Include.h"
#include <math.h>

static void
Ring3_Math_Vector4_construct
  (
    Ring3_Math_Vector4* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  self->z = 0.f;
  self->w = 0.f;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Vector4_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Vector4,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Vector4_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Vector4_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Vector4* self = (Ring3_Math_Vector4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_clone
  (
    const Ring3_Math_Vector4* self
  )
{
  Ring3_Math_Vector4* other = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_copy(other, self);
  return other;
}

void
Ring3_Math_Vector4_copy
  (
    Ring3_Math_Vector4* self,
    const Ring3_Math_Vector4* other
  )
{
  self->x = other->x;
  self->y = other->y;
  self->z = other->z;
  self->w = other->w;
}

void
Ring3_Math_Vector4_add
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
  c->w = a->w + b->w;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_sum
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  Ring3_Math_Vector4* c = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_set(c, a->x + b->x,
                            a->y + b->y,
                            a->z + b->z,
                            a->w + b->w);
  return c;
}

void
Ring3_Math_Vector4_subtract
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
  c->w = a->w - b->w;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_difference
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  Ring3_Math_Vector4* c = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_set(c, a->x - b->x,
                            a->y - b->y,
                            a->z - b->z,
                            a->w - b->w);
  return c;
}

void
Ring3_Math_Vector4_multiply
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  c->x = a->x * b->x;
  c->y = a->y * b->y;
  c->z = a->z * b->z;
  c->w = a->w * b->w;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4*
Ring3_Math_Vector4_product
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  Ring3_Math_Vector4* c = Ring3_Math_Vector4_create();
  Ring3_Math_Vector4_set(c, a->x * b->x,
                            a->y * b->y,
                            a->z * b->z,
                            a->w * b->w);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_dot
  (
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z
       + a->w * b->w;
}

void
Ring3_Math_Vector4_maxima
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
#define MAX(x,y) ((x) > (y) ? (x) : (y))
  c->x = MAX(a->x, b->x);
  c->y = MAX(a->y, b->y);
  c->z = MAX(a->z, b->z);
  c->w = MAX(a->w, b->w);
#undef MAX
}

void
Ring3_Math_Vector4_minima
  (
    Ring3_Math_Vector4* c,
    const Ring3_Math_Vector4* a,
    const Ring3_Math_Vector4* b
  )
{
#define MIN(x,y) ((x) < (y) ? (x) : (y))
  c->x = MIN(a->x, b->x);
  c->y = MIN(a->y, b->y);
  c->z = MIN(a->z, b->z);
  c->w = MIN(a->w, b->w);
#undef MIN
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4 *
Ring3_Math_Vector4_divideScalar
  (
    Ring3_Math_Vector4 const* a,
    Ring2_Real32 b
  )
{
  return Ring3_Math_Vector4_create(a->x / b, a->y / b, a->z / b, a->w / b);
}

void
Ring3_Math_Vector4_divideScalarInSitu
  (
    Ring3_Math_Vector4 *a,
    Ring2_Real32 b
  )
{
  a->x /= b;
  a->y /= b;
  a->z /= b;
  a->w /= b;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_length
  (
    const Ring3_Math_Vector4* a
  )
{ return sqrtf(Ring3_Math_Vector4_squaredLength(a)); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_squaredLength
  (
    const Ring3_Math_Vector4* a
  )
{
  return (a->x * a->x)
       + (a->y * a->y)
       + (a->z * a->z)
       + (a->w * a->w);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector4 *
Ring3_Math_Vector4_normalize
  (
    Ring3_Math_Vector4 const* a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector4_length(a);
  return Ring3_Math_Vector4_divideScalar(a, l);
}

void
Ring3_Math_Vector4_normalizeInSitu
  (
    Ring3_Math_Vector4 *a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector4_length(a);
  Ring3_Math_Vector4_divideScalarInSitu(a, l);
}

void
Ring3_Math_Vector4_set
  (
    Ring3_Math_Vector4* self,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z,
    Ring2_Real32 w
  )
{
  self->x = x;
  self->y = y;
  self->z = z;
  self->w = w;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getX
  (
    const Ring3_Math_Vector4* self
  )
{ return self->x; }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getY
  (
    const Ring3_Math_Vector4* self
  )
{ return self->y; }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getZ
  (
    const Ring3_Math_Vector4* self
  )
{ return self->z; }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector4_getW
  (
    const Ring3_Math_Vector4* self
  )
{ return self->w; }
