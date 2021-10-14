#define MACHINE_MATH_PRIVATE (1)
#include "Math/Vector3.h"

static void Machine_Math_Vector3_construct(Machine_Math_Vector3* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  self->z = 0.f;
  Machine_setClassType((Machine_Object*)self, Machine_Math_Vector3_getClassType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Math_Vector3, Machine_Object, NULL, &Machine_Math_Vector3_construct, NULL, NULL)

Machine_Math_Vector3* Machine_Math_Vector3_create() {
  Machine_ClassType* ty = Machine_Math_Vector3_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Math_Vector3* self = (Machine_Math_Vector3*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Vector3* Machine_Math_Vector3_clone(Machine_Math_Vector3* self) {
  Machine_Math_Vector3* other = Machine_Math_Vector3_create();
  Machine_Math_Vector3_copy(other, self);
  return other;
}

void Machine_Math_Vector3_copy(Machine_Math_Vector3* self, const Machine_Math_Vector3* other) {
  self->x = other->x;
  self->y = other->y;
  self->z = other->z;
}

void Machine_Math_Vector3_add(Machine_Math_Vector3* c, Machine_Math_Vector3* a, Machine_Math_Vector3* b) {
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
}

Machine_Math_Vector3 *Machine_Math_Vector3_sum(Machine_Math_Vector3* a, Machine_Math_Vector3* b) {
  Machine_Math_Vector3* c = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(c, a->x + b->x,
                              a->y + b->y,
                              a->z + b->z);
  return c;
}

void Machine_Math_Vector3_subtract(Machine_Math_Vector3* c, Machine_Math_Vector3* a, Machine_Math_Vector3* b) {
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
}

Machine_Math_Vector3* Machine_Math_Vector3_difference(Machine_Math_Vector3* a, Machine_Math_Vector3* b) {
  Machine_Math_Vector3* c = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(c, a->x - b->x,
                              a->y - b->y,
                              a->z - b->z);
  return c;
}

void Machine_Math_Vector3_multiply(Machine_Math_Vector3* c, Machine_Math_Vector3* a, Machine_Math_Vector3* b) {
  c->x = a->x * b->x;
  c->y = a->y * b->y;
  c->z = a->z * b->z;
}

Machine_Math_Vector3* Machine_Math_Vector3_product(Machine_Math_Vector3* a, Machine_Math_Vector3* b) {
  Machine_Math_Vector3* c = Machine_Math_Vector3_create();
  Machine_Math_Vector3_set(c, a->x * b->x,
                              a->y * b->y,
                              a->z * b->z);
  return c;
}

float Machine_Math_Vector3_dot(const Machine_Math_Vector3* a, const Machine_Math_Vector3* b) {
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z;
}

void Machine_Math_Vector3_maxima(Machine_Math_Vector3* c, const Machine_Math_Vector3* a, const Machine_Math_Vector3* b) {
#define MAX(x,y) ((x) > (y) ? (x) : (y)) 
  c->x = MAX(a->x, b->x);
  c->y = MAX(a->y, b->y);
  c->z = MAX(a->z, b->z);
#undef MAX
}

void Machine_Math_Vector3_minima(Machine_Math_Vector3* c, const Machine_Math_Vector3* a, const Machine_Math_Vector3* b) {
#define MIN(x,y) ((x) < (y) ? (x) : (y))
  c->x = MIN(a->x, b->x);
  c->y = MIN(a->y, b->y);
  c->z = MIN(a->z, b->z);
#undef MIN
}



void Machine_Math_Vector3_set(Machine_Math_Vector3* self, float x, float y, float z) {
  self->x = x;
  self->y = y;
  self->z = z;
}

float Machine_Math_Vector3_getX(const Machine_Math_Vector3* self) {
  return self->x;
}

float Machine_Math_Vector3_getY(const Machine_Math_Vector3* self) {
  return self->y;
}

float Machine_Math_Vector3_getZ(const Machine_Math_Vector3* self) {
  return self->z;
}
