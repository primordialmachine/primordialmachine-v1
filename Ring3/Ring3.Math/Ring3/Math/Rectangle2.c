/// @file Ring3/Math/Rectangle2.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Rectangle2.h"

#include "Ring1/Intrinsic.h"
#include "Ring3/Math/Vector2.h"

static void
Ring3_Math_Rectangle2_construct
  (
    Ring3_Math_Rectangle2* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  self->w = 0.f;
  self->h = 0.f;
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Rectangle2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Rectangle2,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Rectangle2_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_CheckReturn() Ring3_Math_Rectangle2*
Ring3_Math_Rectangle2_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Rectangle2_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Rectangle2* self = (Ring3_Math_Rectangle2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_CheckReturn() Ring3_Math_Rectangle2*
Ring3_Math_Rectangle2_clone
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Rectangle2* clone = Ring3_Math_Rectangle2_create();
  Ring3_Math_Rectangle2_setPosition(clone, Ring3_Math_Rectangle2_getPosition(self));
  Ring3_Math_Rectangle2_setSize(clone, Ring3_Math_Rectangle2_getSize(self));
  return clone;
}

void
Ring3_Math_Rectangle2_copy
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Rectangle2* other
  )
{
  self->x = other->x;
  self->y = other->y;
  self->w = other->w;
  self->h = other->h;
}

void
Ring3_Math_Rectangle2_setPosition
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2* position
  )
{
  self->x = Ring3_Math_Vector2_getX(position);
  self->y = Ring3_Math_Vector2_getY(position);
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Rectangle2_getPosition
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2* p = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(p, self->x, self->y);
  return p;
}

void
Ring3_Math_Rectangle2_setSize
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2* size
  )
{
  self->w = Ring3_Math_Vector2_getX(size);
  self->h = Ring3_Math_Vector2_getY(size);
}

Ring1_CheckReturn() const Ring3_Math_Vector2*
Ring3_Math_Rectangle2_getSize
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2* size = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(size, self->w, self->h);
  return size;
}

Ring1_CheckReturn() const Ring3_Math_Vector2 *
Ring3_Math_Rectangle2_getCenter
  (
    const Ring3_Math_Rectangle2 *self
  )
{
  Ring3_Math_Vector2 *center = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(center, self->x + self->w * 0.5f, self->y + self->h * 0.5f);
  return center;
}

void
Ring3_Math_Rectangle2_addPoint
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2* point
  )
{
  if (self->x > Ring3_Math_Vector2_getX(point)) {
    float d = self->x - Ring3_Math_Vector2_getX(point);
    self->x = Ring3_Math_Vector2_getX(point);
    self->w += d;
  }

  if (self->x + self->w < Ring3_Math_Vector2_getX(point)) {
    self->w = Ring3_Math_Vector2_getX(point) - self->x;
  }

  if (self->y > Ring3_Math_Vector2_getY(point)) {
    float d = self->y - Ring3_Math_Vector2_getY(point);
    self->y = Ring3_Math_Vector2_getY(point);
    self->h += d;
  }

  if (self->y + self->h < Ring3_Math_Vector2_getY(point)) {
    self->h = Ring3_Math_Vector2_getY(point) - self->y;
  }
}

void
Ring3_Math_Rectangle2_addRectangle
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Rectangle2* rectangle
  )
{
  Ring3_Math_Rectangle2_addPoint(self, Ring3_Math_Rectangle2_getMin(rectangle));
  Ring3_Math_Rectangle2_addPoint(self, Ring3_Math_Rectangle2_getMax(rectangle));
}

void
Ring3_Math_Rectangle2_setCenter
  (
    Ring3_Math_Rectangle2* self,
    float x,
    float y
  )
{
  self->x = x - self->w * .5f;
  self->y = y - self->h * .5f;
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Rectangle2_getMin
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2* p = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(p, self->x, self->y);
  return p;
}

Ring1_CheckReturn() Ring3_Math_Vector2*
Ring3_Math_Rectangle2_getMax
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2* p = Ring3_Math_Vector2_create();
  Ring3_Math_Vector2_set(p, self->x + self->w, self->y + self->h);
  return p;
}

Ring1_CheckReturn() float
Ring3_Math_Rectangle2_getMinX
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->x; }

Ring1_CheckReturn() float
Ring3_Math_Rectangle2_getMinY
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->y; }

Ring1_CheckReturn() float
Ring3_Math_Rectangle2_getMaxX
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->x + self->w; }

Ring1_CheckReturn() float
Ring3_Math_Rectangle2_getMaxY
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->y + self->h; }

static void
swap
  (
    float* a,
    float* b
  )
{
  float t = *a;
  *a = *b;
  *b = t;
}

void
Ring3_Math_Rectangle2_inset
  (
    Ring3_Math_Rectangle2* self,
    float minx,
    float miny,
    float maxx,
    float maxy
  )
{
  float minx0 = self->x;
  float miny0 = self->y;
  float maxx0 = self->x + self->w;
  float maxy0 = self->y + self->h;
  minx0 += minx;
  miny0 += miny;
  maxx0 -= maxx;
  maxy0 -= maxy;
  if (minx0 > maxx0) {
    swap(&minx0, &maxx0);
  }
  if (miny0 > maxy0) {
    swap(&miny0, &maxy0);
  }
  self->x = minx0;
  self->y = miny0;
  self->w = maxx0 - minx0;
  self->h = maxy0 - miny0;
}

void
Ring3_Math_Rectangle2_translate
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2* t
  )
{
  self->x += Ring3_Math_Vector2_getX(t);
  self->y += Ring3_Math_Vector2_getY(t);
}
