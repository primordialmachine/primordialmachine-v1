#define MACHINE_MATH_PRIVATE (1)
#include "Math/Matrix4.h"

#define BEGINFOREACH() \
  for (size_t i = 0; i < 4; ++i) { \
    for (size_t j = 0; j < 4; ++j) {

#define ENDFOREACH() } }

static void Machine_Math_Matrix4_construct(Machine_Math_Matrix4* self, size_t numberOfArguments, const Machine_Value* arguments) {
  Machine_Object_construct((Machine_Object*)self, numberOfArguments, arguments);
  BEGINFOREACH()
      self->e[i][j] = 0.0f;
  ENDFOREACH()
  Machine_setClassType((Machine_Object*)self, Machine_Math_Matrix4_getClassType());
}

MACHINE_DEFINE_CLASSTYPE_EX(Machine_Math_Matrix4, Machine_Object, NULL, &Machine_Math_Matrix4_construct, NULL)

Machine_Math_Matrix4* Machine_Math_Matrix4_create() {
  Machine_ClassType* ty = Machine_Math_Matrix4_getClassType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Machine_Value ARGUMENTS[] = { { Machine_ValueFlag_Void, Machine_Void_Void } };
  Machine_Math_Matrix4* self = (Machine_Math_Matrix4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Machine_Math_Matrix4* Machine_Math_Matrix4_clone(const Machine_Math_Matrix4* self) {
  Machine_Math_Matrix4* clone = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_copy(clone, self);
  return clone;
}

void Machine_Math_Matrix4_copy(Machine_Math_Matrix4* self, const Machine_Math_Matrix4* other) {
  if (self != other) {
    BEGINFOREACH()
      self->e[i][j] = other->e[i][j];
    ENDFOREACH()
  }
}



void Machine_Math_Matrix4_setIdentity(Machine_Math_Matrix4* self) {
  BEGINFOREACH()
    self->e[i][j] = i == j ? 1.0f : 0.0f;
  ENDFOREACH()
}

void Machine_Math_Matrix4_transpose(Machine_Math_Matrix4* self) {
  for (size_t i = 0; i < 4 - 1; ++i) {
    for (size_t j = i + 1; j < 4; ++j) {
      float temporary = self->e[i][j];
      self->e[i][j] = self->e[j][i];
      self->e[j][i] = temporary;
    }
  }
}

void Machine_Math_Matrix4_add(Machine_Math_Matrix4* c, Machine_Math_Matrix4* a, Machine_Math_Matrix4* b) {
  BEGINFOREACH()
    c->e[i][j] = a->e[i][j] + b->e[i][j];
  ENDFOREACH()
}

Machine_Math_Matrix4* Machine_Math_Matrix4_sum(Machine_Math_Matrix4* a, Machine_Math_Matrix4* b) {
  Machine_Math_Matrix4* c = Machine_Math_Matrix4_clone(a);
  Machine_Math_Matrix4_add(c, c, b);
  return c;
}

void Machine_Math_Matrix4_subtract(Machine_Math_Matrix4* c, Machine_Math_Matrix4* a, Machine_Math_Matrix4* b) {
  BEGINFOREACH()
    c->e[i][j] = a->e[i][j] - b->e[i][j];
  ENDFOREACH()
}
Machine_Math_Matrix4* Machine_Math_Matrix4_difference(Machine_Math_Matrix4* a, Machine_Math_Matrix4* b) {
  Machine_Math_Matrix4* c = Machine_Math_Matrix4_clone(a);
  Machine_Math_Matrix4_subtract(c, c, b);
  return c;
}

void Machine_Math_Matrix4_setOrtho(Machine_Math_Matrix4* a, float l, float r, float b, float t, float n, float f) {
  // Adopted from https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml.
  a->e[0][0] = 2.f / (r - l);
  a->e[1][0] = a->e[2][0] = a->e[3][0] = 0.f;

  a->e[1][1] = 2.f / (t - b);
  a->e[0][1] = a->e[2][1] = a->e[3][1] = 0.f;

  a->e[2][2] = -2.f / (f - n);
  a->e[0][2] = a->e[1][2] = a->e[3][2] = 0.f;

  a->e[0][3] = -(r + l) / (r - l);
  a->e[1][3] = -(t + b) / (t - b);
  a->e[2][3] = -(f + n) / (f - n);
  a->e[3][3] = 1.f;
}

void Machine_Math_Matrix4_multiply(Machine_Math_Matrix4* c, Machine_Math_Matrix4* a, Machine_Math_Matrix4* b) {
  if (c == a || c == b) {
    float t[4][4];
    BEGINFOREACH()
      t[i][j] = 0.0f;
      for (size_t k = 0; k < 4; ++k) {
        t[i][j] += a->e[i][k] * b->e[k][j];
      }
    ENDFOREACH()
    BEGINFOREACH()
      c->e[i][j] = t[i][j];
    ENDFOREACH()
  } else {
    BEGINFOREACH()
      c->e[i][j] = 0.0f;
      for (size_t k = 0; k < 4; ++k) {
        c->e[i][j] += a->e[i][k] * b->e[k][j];
      }
    ENDFOREACH()
  }
}

Machine_Math_Matrix4* Machine_Math_Matrix4_product(Machine_Math_Matrix4* a, Machine_Math_Matrix4* b) {
  Machine_Math_Matrix4* c = Machine_Math_Matrix4_create();
  Machine_Math_Matrix4_multiply(c, a, b);
  return c;
}

#include <math.h>

void Machine_Math_Matrix4_rotateZ(Machine_Math_Matrix4* a, float d) {
  float c = cosf(d),
        s = sinf(d);
  a->e[0][0] = +c;
  a->e[1][0] = +s;
  a->e[2][0] = a->e[3][0] = 0.f;

  a->e[0][1] = -s;
  a->e[1][1] = +c;
  a->e[2][1] = a->e[3][1] = 0.f;

  a->e[0][2] = a->e[1][2] = a->e[3][2] = 0.f;
  a->e[0][3] = a->e[1][3] = a->e[2][3] = 0.f;

  a->e[2][2] = a->e[3][3] = 1.f;

#if 0
  mat4x4 R = {
    {   c,   s, 0.f, 0.f},
    {  -s,   c, 0.f, 0.f},
    { 0.f, 0.f, 1.f, 0.f},
    { 0.f, 0.f, 0.f, 1.f}
  };
#endif
}
