/// @file Ring3/Math/Rectangle2.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Rectangle2.h"

#include "Ring1/All/_Include.h"
#include "Ring3/Math/Vector2f32.h"

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
  Machine_Type* ty = Ring3_Math_Rectangle2_getType();
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
    const Ring3_Math_Vector2f32* position
  )
{
  self->x = Ring3_Math_Vector2f32_getX(position);
  self->y = Ring3_Math_Vector2f32_getY(position);
}

Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getPosition
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, self->x, self->y);
  return p;
}

void
Ring3_Math_Rectangle2_setSize
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* size
  )
{
  self->w = Ring3_Math_Vector2f32_getX(size);
  self->h = Ring3_Math_Vector2f32_getY(size);
}

Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getSize
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2f32* size = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(size, self->w, self->h);
  return size;
}

Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getCenter
  (
    const Ring3_Math_Rectangle2 *self
  )
{
  Ring3_Math_Vector2f32 *center = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(center, self->x + self->w * 0.5f, self->y + self->h * 0.5f);
  return center;
}

void
Ring3_Math_Rectangle2_addPoint
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* point
  )
{
  if (self->x > Ring3_Math_Vector2f32_getX(point)) {
    Ring2_Real32 d = self->x - Ring3_Math_Vector2f32_getX(point);
    self->x = Ring3_Math_Vector2f32_getX(point);
    self->w += d;
  }

  if (self->x + self->w < Ring3_Math_Vector2f32_getX(point)) {
    self->w = Ring3_Math_Vector2f32_getX(point) - self->x;
  }

  if (self->y > Ring3_Math_Vector2f32_getY(point)) {
    Ring2_Real32 d = self->y - Ring3_Math_Vector2f32_getY(point);
    self->y = Ring3_Math_Vector2f32_getY(point);
    self->h += d;
  }

  if (self->y + self->h < Ring3_Math_Vector2f32_getY(point)) {
    self->h = Ring3_Math_Vector2f32_getY(point) - self->y;
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
    Ring2_Real32 x,
    Ring2_Real32 y
  )
{
  self->x = x - self->w * .5f;
  self->y = y - self->h * .5f;
}

Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getMin
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, self->x, self->y);
  return p;
}

Ring1_CheckReturn() Ring3_Math_Vector2f32*
Ring3_Math_Rectangle2_getMax
  (
    const Ring3_Math_Rectangle2* self
  )
{
  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(p, self->x + self->w, self->y + self->h);
  return p;
}

Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMinX
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->x; }

Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMinY
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->y; }

Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMaxX
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->x + self->w; }

Ring1_CheckReturn() Ring2_Real32
Ring3_Math_Rectangle2_getMaxY
  (
    const Ring3_Math_Rectangle2* self
  )
{ return self->y + self->h; }

static void
swap
  (
    Ring2_Real32* a,
    Ring2_Real32* b
  )
{
  Ring2_Real32 t = *a;
  *a = *b;
  *b = t;
}

void
Ring3_Math_Rectangle2_inset
  (
    Ring3_Math_Rectangle2* self,
    Ring2_Real32 minx,
    Ring2_Real32 miny,
    Ring2_Real32 maxx,
    Ring2_Real32 maxy
  )
{
  Ring2_Real32 minx0 = self->x;
  Ring2_Real32 miny0 = self->y;
  Ring2_Real32 maxx0 = self->x + self->w;
  Ring2_Real32 maxy0 = self->y + self->h;
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
    const Ring3_Math_Vector2f32* t
  )
{
  self->x += Ring3_Math_Vector2f32_getX(t);
  self->y += Ring3_Math_Vector2f32_getY(t);
}

void
Ring3_Math_Rectangle2_alignCenter
  (
    Ring3_Math_Rectangle2* self,
    const Ring3_Math_Vector2f32* p
  )
{
  Ring3_Math_Vector2f32* c = Ring3_Math_Rectangle2_getCenter(self);
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, c, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignMinXMinY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Rectangle2_getMinX(self),
                               Ring3_Math_Rectangle2_getMinY(self));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignMinXMaxY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Rectangle2_getMinX(self),
                               Ring3_Math_Rectangle2_getMaxY(self));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignMaxXMinY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Rectangle2_getMaxX(self),
                               Ring3_Math_Rectangle2_getMinY(self));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignMaxXMaxY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Rectangle2_getMaxX(self),
                               Ring3_Math_Rectangle2_getMaxY(self));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignCenterXMinY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getCenter(self)),
                               Ring3_Math_Rectangle2_getMinY(self));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignCenterXMaxY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Vector2f32_getX(Ring3_Math_Rectangle2_getCenter(self)),
                               Ring3_Math_Rectangle2_getMaxY(self));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignMinXCenterY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Rectangle2_getMinX(self),
                               Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getCenter(self)));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}

void
Ring3_Math_Rectangle2_alignMaxXCenterY
  (
    Ring3_Math_Rectangle2* self,
    Ring3_Math_Vector2f32 const* p
  )
{
  Ring3_Math_Vector2f32* q = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_set(q, Ring3_Math_Rectangle2_getMaxX(self),
                               Ring3_Math_Vector2f32_getY(Ring3_Math_Rectangle2_getCenter(self)));
  Ring3_Math_Vector2f32* t = Ring3_Math_Vector2f32_create();
  Ring3_Math_Vector2f32_subtract(p, q, t);
  Ring3_Math_Rectangle2_translate(self, t);
}
