#include "Math/Rectangle2.h"

#include "Math/Vector2.h"

static void Machine_Math_Rectangle2_construct(Machine_Math_Rectangle2* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->x = 0.f;
  self->y = 0.f;
  self->w = 0.f;
  self->h = 0.f;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Math_Rectangle2)

Machine_ClassType* Machine_Math_Rectangle2_getClassType() {
  if (!g_Machine_Math_Rectangle2_ClassType) {
    g_Machine_Math_Rectangle2_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_Math_Rectangle2),
          (Machine_ClassTypeRemovedCallback*)&Machine_Math_Rectangle2_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)NULL,
          (Machine_ClassObjectConstructCallback*)&Machine_Math_Rectangle2_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_Math_Rectangle2_ClassType;
}

Machine_Math_Rectangle2* Machine_Math_Rectangle2_create() {
  Machine_ClassType* ty = Machine_Math_Rectangle2_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_Math_Rectangle2* self = (Machine_Math_Rectangle2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Rectangle2* Machine_Math_Rectangle2_clone(const Machine_Math_Rectangle2* self) {
  Machine_Math_Rectangle2* clone = Machine_Math_Rectangle2_create();
  Machine_Math_Rectangle2_setPosition(clone, Machine_Math_Rectangle2_getPosition(self));
  Machine_Math_Rectangle2_setSize(clone, Machine_Math_Rectangle2_getSize(self));
  return clone;
}

void Machine_Math_Rectangle2_copy(Machine_Math_Rectangle2* self, const Machine_Math_Rectangle2* other) {
  self->x = other->x;
  self->y = other->y;
  self->w = other->w;
  self->h = other->h;
}

void Machine_Math_Rectangle2_setPosition(Machine_Math_Rectangle2* self, const Machine_Math_Vector2* position) {
  self->x = Machine_Math_Vector2_getX(position);
  self->y = Machine_Math_Vector2_getY(position);
}

Machine_Math_Vector2* Machine_Math_Rectangle2_getPosition(const Machine_Math_Rectangle2* self) {
  Machine_Math_Vector2* p = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(p, self->x, self->y);
  return p;
}

void Machine_Math_Rectangle2_setSize(Machine_Math_Rectangle2* self, const Machine_Math_Vector2* size) {
  self->w = Machine_Math_Vector2_getX(size);
  self->h = Machine_Math_Vector2_getY(size);
}

const Machine_Math_Vector2* Machine_Math_Rectangle2_getSize(const Machine_Math_Rectangle2* self) {
  Machine_Math_Vector2* size = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(size, self->w, self->h);
  return size;
}

const Machine_Math_Vector2 *Machine_Math_Rectangle2_getCenter(const Machine_Math_Rectangle2 *self) {
  Machine_Math_Vector2 *center = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(center, self->x + self->w * 0.5f, self->y + self->h * 0.5f);
  return center;
}

void Machine_Math_Rectangle2_addPoint(Machine_Math_Rectangle2* self, const Machine_Math_Vector2* point) {
  if (self->x > Machine_Math_Vector2_getX(point)) {
    float d = self->x - Machine_Math_Vector2_getX(point);
    self->x = Machine_Math_Vector2_getX(point);
    self->w += d;
  }

  if (self->x + self->w < Machine_Math_Vector2_getX(point)) {
    self->w = Machine_Math_Vector2_getX(point) - self->x;
  }

  if (self->y > Machine_Math_Vector2_getY(point)) {
    float d = self->y - Machine_Math_Vector2_getY(point);
    self->y = Machine_Math_Vector2_getY(point);
    self->h += d;
  }

  if (self->y + self->h < Machine_Math_Vector2_getY(point)) {
    self->h = Machine_Math_Vector2_getY(point) - self->y;
  }
}

void Machine_Math_Rectangle2_setCenter(Machine_Math_Rectangle2* self, float x, float y) {
  self->x = x - self->w * .5f;
  self->y = y - self->h * .5f;
}

float Machine_Math_Rectangle2_getMinX(const Machine_Math_Rectangle2* self) {
  return self->x;
}

float Machine_Math_Rectangle2_getMinY(const Machine_Math_Rectangle2* self) {
  return self->y;
}

float Machine_Math_Rectangle2_getMaxX(const Machine_Math_Rectangle2* self) {
  return self->x + self->w;
}

float Machine_Math_Rectangle2_getMaxY(const Machine_Math_Rectangle2* self) {
  return self->y + self->h;
}

static void swap(float* a, float* b) {
  float t = *a;
  *a = *b;
  *b = t;
}

void Machine_Math_Rectangle2_inset(Machine_Math_Rectangle2* self, float minx, float miny, float maxx, float maxy) {
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
