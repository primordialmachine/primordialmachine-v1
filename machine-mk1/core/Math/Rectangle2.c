#include "Math/Rectangle2.h"

#include "Math/Vector2.h"

struct Machine_Math_Rectangle2 {
  float x, y;
  float w, h;
};

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

void Machine_Math_Rectangle2_copy(Machine_Math_Rectangle2* self, Machine_Math_Rectangle2* other) {
  self->x = other->x;
  self->y = other->y;
  self->w = other->w;
  self->h = other->h;
}

void Machine_Math_Rectangle2_setPosition(Machine_Math_Rectangle2* self, Machine_Math_Vector2* position) {
  self->x = Machine_Math_Vector2_getX(position);
  self->y = Machine_Math_Vector2_getY(position);
}

void Machine_Math_Rectangle2_setSize(Machine_Math_Rectangle2* self, Machine_Math_Vector2* size) {
  self->w = Machine_Math_Vector2_getX(size);
  self->h = Machine_Math_Vector2_getY(size);
}

Machine_Math_Vector2* Machine_Math_Rectangle2_getSize(Machine_Math_Rectangle2* self) {
  Machine_Math_Vector2* size = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(size, self->w, self->h);
  return size;
}

Machine_Math_Vector2 *Machine_Math_Rectangle2_getCenter(Machine_Math_Rectangle2 *self) {
  Machine_Math_Vector2 *center = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(center, self->x + self->w * 0.5f, self->y + self->h * 0.5f);
  return center;
}

void Machine_Math_Rectangle2_addPoint(Machine_Math_Rectangle2* self, Machine_Math_Vector2* point) {
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

Machine_Math_Vector2* Machine_Math_Rectangle2_getLeftTop(Machine_Math_Rectangle2* self) {
  Machine_Math_Vector2* p = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(p, self->x, self->y);
  return p;
}
