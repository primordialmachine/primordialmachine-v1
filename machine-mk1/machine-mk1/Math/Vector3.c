#include "./../Math/Vector3.h"

struct Machine_Math_Vector3 {
  float x, y, z;
};

static void Machine_Math_Vector3_construct(Machine_Math_Vector3* self, size_t numberOfArguments, const Machine_Value* arguments) {
  self->x = 0.f;
  self->y = 0.f;
  self->z = 0.f;
}

Machine_ClassType* Machine_Math_Vector3_getClassType() {
  return
    Machine_createClassType
      (
        NULL,
        sizeof(Machine_Math_Vector3),
        (Machine_ClassObjectVisitCallback*)NULL,
        (Machine_ClassObjectConstructCallback*)&Machine_Math_Vector3_construct,
        (Machine_ClassObjectDestructCallback*)NULL
      );
}


Machine_Math_Vector3* Machine_Math_Vector3_create() {
  Machine_ClassType* ty = Machine_Math_Vector3_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_VoidValue_VOID } };
  Machine_Math_Vector3* self = (Machine_Math_Vector3*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

void Machine_Math_Vector3_set(Machine_Math_Vector3* self, float x, float y, float z) {
  self->x = x;
  self->y = y;
  self->z = z;
}

float Machine_Math_Vector3_getX(Machine_Math_Vector3* self) {
  return self->x;
}

float Machine_Math_Vector3_getY(Machine_Math_Vector3* self) {
  return self->y;
}

float Machine_Math_Vector3_getZ(Machine_Math_Vector3* self) {
  return self->z;
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

float Machine_Math_Vector3_dot(Machine_Math_Vector3* c) {
  return c->x * c->x
       + c->y * c->y
       + c->z * c->z;
}
