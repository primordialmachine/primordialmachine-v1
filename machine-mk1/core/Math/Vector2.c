#include "Math/Vector2.h"

struct Machine_Math_Vector2 {
  float x, y;
};

static void Machine_Math_Vector2_construct(Machine_Math_Vector2* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->x = 0.f;
  self->y = 0.f;
}

MACHINE_DEFINE_CLASSTYPE(Machine_Math_Vector2)

Machine_ClassType* Machine_Math_Vector2_getClassType() {
  if (!g_Machine_Math_Vector2_ClassType) {
    g_Machine_Math_Vector2_ClassType =
      Machine_createClassType
        (
          NULL,
          sizeof(Machine_Math_Vector2),
          (Machine_ClassTypeRemovedCallback*)&Machine_Math_Vector2_onTypeDestroyed,
          (Machine_ClassObjectVisitCallback*)NULL,
          (Machine_ClassObjectConstructCallback*)&Machine_Math_Vector2_construct,
          (Machine_ClassObjectDestructCallback*)NULL
        );
  }
  return g_Machine_Math_Vector2_ClassType;
}

Machine_Math_Vector2* Machine_Math_Vector2_create() {
  Machine_ClassType* ty = Machine_Math_Vector2_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_Math_Vector2* self = (Machine_Math_Vector2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Vector2* Machine_Math_Vector2_clone(Machine_Math_Vector2* self) {
  Machine_Math_Vector2* other = Machine_Math_Vector2_create();
  Machine_Math_Vector2_copy(other, self);
  return other;
}

void Machine_Math_Vector2_copy(Machine_Math_Vector2* self, const Machine_Math_Vector2* other) {
  self->x = other->x;
  self->y = other->y;
}

void Machine_Math_Vector2_add(Machine_Math_Vector2* c, Machine_Math_Vector2* a, Machine_Math_Vector2* b) {
  c->x = a->x + b->x;
  c->y = a->y + b->y;
}

Machine_Math_Vector2* Machine_Math_Vector2_sum(Machine_Math_Vector2* a, Machine_Math_Vector2* b) {
  Machine_Math_Vector2* c = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(c, a->x + b->x,
                              a->y + b->y);
  return c;
}

void Machine_Math_Vector2_subtract(Machine_Math_Vector2* c, Machine_Math_Vector2* a, Machine_Math_Vector2* b) {
  c->x = a->x - b->x;
  c->y = a->y - b->y;
}

Machine_Math_Vector2* Machine_Math_Vector2_difference(Machine_Math_Vector2* a, Machine_Math_Vector2* b) {
  Machine_Math_Vector2* c = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(c, a->x - b->x,
                              a->y - b->y);
  return c;
}

void Machine_Math_Vector2_multiply(Machine_Math_Vector2* c, Machine_Math_Vector2* a, Machine_Math_Vector2* b) {
  c->x = a->x * b->x;
  c->y = a->y * b->y;
}

Machine_Math_Vector2* Machine_Math_Vector2_product(Machine_Math_Vector2* a, Machine_Math_Vector2* b) {
  Machine_Math_Vector2* c = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(c, a->x * b->x,
                              a->y * b->y);
  return c;
}

float Machine_Math_Vector2_dot(const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  return a->x * b->x
       + a->y * b->y;
}



void Machine_Math_Vector2_set(Machine_Math_Vector2* self, float x, float y) {
  self->x = x;
  self->y = y;
}

float Machine_Math_Vector2_getX(const Machine_Math_Vector2* self) {
  return self->x;
}

float Machine_Math_Vector2_getY(const Machine_Math_Vector2* self) {
  return self->y;
}
