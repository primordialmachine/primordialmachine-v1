/// @file Ring3/Math/Vector3.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector3.h"

#include "Ring1/Intrinsic.h"
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

Ring1_CheckReturn() Ring3_Math_Vector3*
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

Ring1_CheckReturn() Ring3_Math_Vector3*
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

Ring1_CheckReturn() Ring3_Math_Vector3 *
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

Ring1_CheckReturn() Ring3_Math_Vector3*
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

Ring1_CheckReturn() Ring3_Math_Vector3*
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

Ring1_CheckReturn() float
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

void
Ring3_Math_Vector3_set
  (
    Ring3_Math_Vector3* self,
    float x,
    float y,
    float z
  )
{
  self->x = x;
  self->y = y;
  self->z = z;
}

Ring1_CheckReturn() float
Ring3_Math_Vector3_getX
  (
    const Ring3_Math_Vector3* self
  )
{ return self->x; }

Ring1_CheckReturn() float
Ring3_Math_Vector3_getY
  (
    const Ring3_Math_Vector3* self
  )
{ return self->y; }

Ring1_CheckReturn() float
Ring3_Math_Vector3_getZ
  (
    const Ring3_Math_Vector3* self
  )
{ return self->z; }
