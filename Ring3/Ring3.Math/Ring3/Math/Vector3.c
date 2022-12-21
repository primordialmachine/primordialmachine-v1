/// @file Ring3/Math/Vector3.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector3.h"

#include "Ring1/All/_Include.h"
#include <math.h>

static void
Ring3_Math_Vector3_construct
  (
    Ring3_Math_Vector3* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  self->z = 0.f;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Vector3_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Vector3,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Vector3_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Vector3_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Vector3* self = Ring1_cast(Ring3_Math_Vector3*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_clone
  (
    const Ring3_Math_Vector3* self
  )
{
  Ring3_Math_Vector3* other = Ring3_Math_Vector3_create();
  Ring3_Math_Vector3_copy(other, self);
  return other;
}

void
Ring3_Math_Vector3_copy
  (
    Ring3_Math_Vector3* self,
    const Ring3_Math_Vector3* other
  )
{
  self->x = other->x;
  self->y = other->y;
  self->z = other->z;
}

void
Ring3_Math_Vector3_add
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3 *
Ring3_Math_Vector3_sum
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  Ring3_Math_Vector3* c = Ring3_Math_Vector3_create();
  Ring3_Math_Vector3_set(c, a->x + b->x,
                            a->y + b->y,
                            a->z + b->z);
  return c;
}

void
Ring3_Math_Vector3_subtract
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_difference
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  Ring3_Math_Vector3* c = Ring3_Math_Vector3_create();
  Ring3_Math_Vector3_set(c, a->x - b->x,
                            a->y - b->y,
                            a->z - b->z);
  return c;
}

void
Ring3_Math_Vector3_multiply
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  c->x = a->x * b->x;
  c->y = a->y * b->y;
  c->z = a->z * b->z;
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3*
Ring3_Math_Vector3_product
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  Ring3_Math_Vector3* c = Ring3_Math_Vector3_create();
  Ring3_Math_Vector3_set(c, a->x * b->x,
                            a->y * b->y,
                            a->z * b->z);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3_dot
  (
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z;
}

void
Ring3_Math_Vector3_maxima
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
#define MAX(x,y) ((x) > (y) ? (x) : (y))
  c->x = MAX(a->x, b->x);
  c->y = MAX(a->y, b->y);
  c->z = MAX(a->z, b->z);
#undef MAX
}

void
Ring3_Math_Vector3_minima
  (
    Ring3_Math_Vector3* c,
    const Ring3_Math_Vector3* a,
    const Ring3_Math_Vector3* b
  )
{
#define MIN(x,y) ((x) < (y) ? (x) : (y))
  c->x = MIN(a->x, b->x);
  c->y = MIN(a->y, b->y);
  c->z = MIN(a->z, b->z);
#undef MIN
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3 *
Ring3_Math_Vector3_divideScalar
  (
    Ring3_Math_Vector3 const* a,
    Ring2_Real32 b
  )
{
  return Ring3_Math_Vector3_create(a->x / b, a->y / b, a->z / b);
}

void
Ring3_Math_Vector3_divideScalarInSitu
  (
    Ring3_Math_Vector3 *a,
    Ring2_Real32 b
  )
{
  a->x /= b;
  a->y /= b;
  a->z /= b;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3_length
  (
    const Ring3_Math_Vector3* a
  )
{ return sqrtf(Ring3_Math_Vector3_squaredLength(a)); }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3_squaredLength
  (
    const Ring3_Math_Vector3* a
  )
{
  return (a->x * a->x)
       + (a->y * a->y)
       + (a->z * a->z);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector3 *
Ring3_Math_Vector3_normalize
  (
    Ring3_Math_Vector3 const* a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector3_length(a);
  return Ring3_Math_Vector3_divideScalar(a, l);
}

void
Ring3_Math_Vector3_normalizeInSitu
  (
    Ring3_Math_Vector3 *a
  )
{
  Ring2_Real32 l = Ring3_Math_Vector3_length(a);
  Ring3_Math_Vector3_divideScalarInSitu(a, l);
}

void
Ring3_Math_Vector3_set
  (
    Ring3_Math_Vector3* self,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z
  )
{
  self->x = x;
  self->y = y;
  self->z = z;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3_getX
  (
    const Ring3_Math_Vector3* self
  )
{ return self->x; }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3_getY
  (
    const Ring3_Math_Vector3* self
  )
{ return self->y; }

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Vector3_getZ
  (
    const Ring3_Math_Vector3* self
  )
{ return self->z; }

Ring1_NoDiscardReturn() Ring3_Math_Vector3 *
Ring3_Math_Vector3_cross
  (
    Ring3_Math_Vector3 const *a,
    Ring3_Math_Vector3 const *b
  )
{
  float temporary[] = {
    a->y * b->z - a->z * b->y,
    a->z * b->x - a->x * b->z,
    a->x * b->y - a->y * b->x,
  };
  return Ring3_Math_Vector3_create(temporary[0], temporary[1], temporary[2]);
}

void
Ring3_Math_Vector3_crossInSitu
  (
    Ring3_Math_Vector3 *a,
    Ring3_Math_Vector3 const *b
  )
{
  float temporary[] = {
    a->y * b->z - a->z * b->y,
    a->z * b->x - a->x * b->z,
    a->x * b->y - a->y * b->x,
  };
  Ring3_Math_Vector3_set(a, temporary[0], temporary[1], temporary[2]);
}
