/// @file Ring3/Math/Vector2.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector2.h"

#include "Ring1/Intrinsic.h"
#include <math.h>

static void
Ring3_Math_Vector2_construct
  (
    Ring3_Math_Vector2* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Vector2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Vector2,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Vector2_construct,
                         NULL,
                         NULL, NULL)

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Vector2_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Vector2* self = (Ring3_Math_Vector2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_clone
  (
    const Ring3_Math_Vector2* self
  )
{
  Ring3_Math_Vector2* other = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_copy(other, self);
  return other;
}

void
Ring3_Math_Vector2_copy
  (
    Ring3_Math_Vector2* self,
    const Ring3_Math_Vector2* other
  )
{
  self->x = other->x;
  self->y = other->y;
}

void
Ring3_Math_Vector2_add
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_sum
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  Ring3_Math_Vector2* c = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(c, a->x + b->x,
                            a->y + b->y);
  return c;
}

void
Ring3_Math_Vector2_subtract
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  c->x = a->x - b->x;
  c->y = a->y - b->y;
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_difference
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  Ring3_Math_Vector2* c = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(c, a->x - b->x,
                            a->y - b->y);
  return c;
}

void
Ring3_Math_Vector2_multiply
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  c->x = a->x * b->x;
  c->y = a->y * b->y;
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Vector2_product
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  Ring3_Math_Vector2* c = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(c, a->x * b->x,
                            a->y * b->y);
  return c;
}

Ring1_CheckReturn() float
Ring3_Math_Vector2_dot
  (
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
  return a->x * b->x
       + a->y * b->y;
}

void
Ring3_Math_Vector2_maxima
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
#define MAX(x,y) ((x) > (y) ? (x) : (y)) 
  c->x = MAX(a->x, b->x);
  c->y = MAX(a->y, b->y);
#undef MAX
}

void
Ring3_Math_Vector2_minima
  (
    Ring3_Math_Vector2* c,
    const Ring3_Math_Vector2* a,
    const Ring3_Math_Vector2* b
  )
{
#define MIN(x,y) ((x) < (y) ? (x) : (y))
  c->x = MIN(a->x, b->x);
  c->y = MIN(a->y, b->y);
#undef MIN
}

void
Ring3_Math_Vector2_set
  (
    Ring3_Math_Vector2* self,
    float x,
    float y
  )
{
  self->x = x;
  self->y = y;
}

Ring1_CheckReturn() float
Ring3_Math_Vector2_getX
  (
    const Ring3_Math_Vector2* self
  )
{ return self->x; }

Ring1_CheckReturn() float
Ring3_Math_Vector2_getY
  (
    const Ring3_Math_Vector2* self
  )
{ return self->y; }
