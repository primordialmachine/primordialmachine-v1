#define MACHINE_MATH_PRIVATE (1)
#include "Math/Vector2.h"

static void Machine_Math_Vector2_construct(Machine_Math_Vector2* self, size_t numberOfArguments, const Ring2_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  Machine_setClassType((Machine_Object*)self, Machine_Math_Vector2_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Math_Vector2, Machine_Object, NULL,
                         &Machine_Math_Vector2_construct, NULL, NULL, NULL)

Machine_Math_Vector2* Machine_Math_Vector2_create() {
  Machine_ClassType* ty = Machine_Math_Vector2_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Machine_Math_Vector2* self = (Machine_Math_Vector2*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Vector2* Machine_Math_Vector2_clone(const Machine_Math_Vector2* self) {
  Machine_Math_Vector2* other = Machine_Math_Vector2_create();
  Machine_Math_Vector2_copy(other, self);
  return other;
}

void Machine_Math_Vector2_copy(Machine_Math_Vector2* self, const Machine_Math_Vector2* other) {
  self->x = other->x;
  self->y = other->y;
}

void Machine_Math_Vector2_add(Machine_Math_Vector2* c, const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  c->x = a->x + b->x;
  c->y = a->y + b->y;
}

Machine_Math_Vector2* Machine_Math_Vector2_sum(const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  Machine_Math_Vector2* c = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(c, a->x + b->x,
                              a->y + b->y);
  return c;
}

void Machine_Math_Vector2_subtract(Machine_Math_Vector2* c, const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  c->x = a->x - b->x;
  c->y = a->y - b->y;
}

Machine_Math_Vector2* Machine_Math_Vector2_difference(const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  Machine_Math_Vector2* c = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(c, a->x - b->x,
                              a->y - b->y);
  return c;
}

void Machine_Math_Vector2_multiply(Machine_Math_Vector2* c, const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  c->x = a->x * b->x;
  c->y = a->y * b->y;
}

Machine_Math_Vector2* Machine_Math_Vector2_product(const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  Machine_Math_Vector2* c = Machine_Math_Vector2_create();
  Machine_Math_Vector2_set(c, a->x * b->x,
                              a->y * b->y);
  return c;
}

float Machine_Math_Vector2_dot(const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
  return a->x * b->x
       + a->y * b->y;
}

void Machine_Math_Vector2_maxima(Machine_Math_Vector2* c, const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
#define MAX(x,y) ((x) > (y) ? (x) : (y)) 
  c->x = MAX(a->x, b->x);
  c->y = MAX(a->y, b->y);
#undef MAX
}

void Machine_Math_Vector2_minima(Machine_Math_Vector2* c, const Machine_Math_Vector2* a, const Machine_Math_Vector2* b) {
#define MIN(x,y) ((x) < (y) ? (x) : (y))
  c->x = MIN(a->x, b->x);
  c->y = MIN(a->y, b->y);
#undef MIN
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
