#define MACHINE_MATH_PRIVATE (1)
#include "Math/Vector4.h"

static void Machine_Math_Vector4_construct(Machine_Math_Vector4* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  self->x = 0.f;
  self->y = 0.f;
  self->z = 0.f;
  self->w = 0.f;
  Machine_setClassType((Machine_Object *)self, Machine_Math_Vector4_getType());
}

MACHINE_DEFINE_CLASSTYPE(Machine_Math_Vector4, Machine_Object, NULL,
                         &Machine_Math_Vector4_construct, NULL, NULL, NULL)

Machine_Math_Vector4* Machine_Math_Vector4_create() {
  Machine_ClassType* ty = Machine_Math_Vector4_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Math_Vector4* self = (Machine_Math_Vector4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Vector4* Machine_Math_Vector4_clone(Machine_Math_Vector4* self) {
  Machine_Math_Vector4* other = Machine_Math_Vector4_create();
  Machine_Math_Vector4_copy(other, self);
  return other;
}

void Machine_Math_Vector4_copy(Machine_Math_Vector4* self, const Machine_Math_Vector4* other) {
  self->x = other->x;
  self->y = other->y;
  self->z = other->z;
  self->w = other->w;
}

void Machine_Math_Vector4_add(Machine_Math_Vector4* c, Machine_Math_Vector4* a, Machine_Math_Vector4* b) {
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
  c->w = a->w + b->w;
}

Machine_Math_Vector4* Machine_Math_Vector4_sum(Machine_Math_Vector4* a, Machine_Math_Vector4* b) {
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, a->x + b->x,
                              a->y + b->y,
                              a->z + b->z,
                              a->w + b->w);
  return c;
}

void Machine_Math_Vector4_subtract(Machine_Math_Vector4* c, Machine_Math_Vector4* a, Machine_Math_Vector4* b) {
  c->x = a->x - b->x;
  c->y = a->y - b->y;
  c->z = a->z - b->z;
  c->w = a->w - b->w;
}

Machine_Math_Vector4* Machine_Math_Vector4_difference(Machine_Math_Vector4* a, Machine_Math_Vector4* b) {
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, a->x - b->x,
                              a->y - b->y,
                              a->z - b->z,
                              a->w - b->w);
  return c;
}

void Machine_Math_Vector4_multiply(Machine_Math_Vector4* c, Machine_Math_Vector4* a, Machine_Math_Vector4* b) {
  c->x = a->x * b->x;
  c->y = a->y * b->y;
  c->z = a->z * b->z;
  c->w = a->w * b->w;
}

Machine_Math_Vector4* Machine_Math_Vector4_product(Machine_Math_Vector4* a, Machine_Math_Vector4* b) {
  Machine_Math_Vector4* c = Machine_Math_Vector4_create();
  Machine_Math_Vector4_set(c, a->x * b->x,
                              a->y * b->y,
                              a->z * b->z,
                              a->w * b->w);
  return c;
}

float Machine_Math_Vector4_dot(const Machine_Math_Vector4* a, const Machine_Math_Vector4* b) {
  return a->x * b->x
       + a->y * b->y
       + a->z * b->z
       + a->w * b->w;
}

void Machine_Math_Vector4_maxima(Machine_Math_Vector4* c, const Machine_Math_Vector4* a, const Machine_Math_Vector4* b) {
#define MAX(x,y) ((x) > (y) ? (x) : (y)) 
  c->x = MAX(a->x, b->x);
  c->y = MAX(a->y, b->y);
  c->z = MAX(a->z, b->z);
  c->w = MAX(a->w, b->w);
#undef MAX
}

void Machine_Math_Vector4_minima(Machine_Math_Vector4* c, const Machine_Math_Vector4* a, const Machine_Math_Vector4* b) {
#define MIN(x,y) ((x) < (y) ? (x) : (y))
  c->x = MIN(a->x, b->x);
  c->y = MIN(a->y, b->y);
  c->z = MIN(a->z, b->z);
  c->w = MIN(a->w, b->w);
#undef MIN
}



void Machine_Math_Vector4_set(Machine_Math_Vector4* self, float x, float y, float z, float w) {
  self->x = x;
  self->y = y;
  self->z = z;
  self->w = w;
}

float Machine_Math_Vector4_getX(const Machine_Math_Vector4* self) {
  return self->x;
}

float Machine_Math_Vector4_getY(const Machine_Math_Vector4* self) {
  return self->y;
}

float Machine_Math_Vector4_getZ(const Machine_Math_Vector4* self) {
  return self->z;
}

float Machine_Math_Vector4_getW(const Machine_Math_Vector4* self) {
  return self->w;
}

