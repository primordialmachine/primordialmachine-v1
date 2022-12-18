/// @file Ring3/Math/Matrix4.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Matrix4.h"

#include "Ring1/All/_Include.h"
#include <math.h>

static void
Ring3_Math_Matrix4_construct
  (
    Ring3_Math_Matrix4* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      self->e[i][j] = 0.0f;
    }
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Matrix4_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Matrix4,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Matrix4_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Matrix4_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Matrix4* self = (Ring3_Math_Matrix4*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_clone
  (
    const Ring3_Math_Matrix4* self
  )
{
  Ring3_Math_Matrix4* clone = Ring3_Math_Matrix4_create();
  Ring3_Math_Matrix4_copy(clone, self);
  return clone;
}

void
Ring3_Math_Matrix4_copy
  (
    Ring3_Math_Matrix4* self,
    const Ring3_Math_Matrix4* other
  )
{
  if (self != other) {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        self->e[i][j] = other->e[i][j];
      }
    }
  }
}

void
Ring3_Math_Matrix4_setIdentity
  (
    Ring3_Math_Matrix4* self
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      self->e[i][j] = i == j ? 1.0f : 0.0f;
    }
  }
}

void
Ring3_Math_Matrix4_transpose
  (
    Ring3_Math_Matrix4* self
  )
{
  for (size_t i = 0; i < 4 - 1; ++i) {
    for (size_t j = i + 1; j < 4; ++j) {
      float temporary = self->e[i][j];
      self->e[i][j] = self->e[j][i];
      self->e[j][i] = temporary;
    }
  }
}

void
Ring3_Math_Matrix4_add
  (
    Ring3_Math_Matrix4* c,
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      c->e[i][j] = a->e[i][j] + b->e[i][j];
    }
  }
}

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_sum
  (
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  )
{
  Ring3_Math_Matrix4* c = Ring3_Math_Matrix4_clone(a);
  Ring3_Math_Matrix4_add(c, c, b);
  return c;
}

void
Ring3_Math_Matrix4_subtract
  (
    Ring3_Math_Matrix4* c,
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      c->e[i][j] = a->e[i][j] - b->e[i][j];
    }
  }
}

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_difference
  (
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  )
{
  Ring3_Math_Matrix4* c = Ring3_Math_Matrix4_clone(a);
  Ring3_Math_Matrix4_subtract(c, c, b);
  return c;
}

void
Ring3_Math_Matrix4_setOrtho
  (
    Ring3_Math_Matrix4* a,
    float l,
    float r,
    float b,
    float t,
    float n,
    float f
  )
{
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

void
Ring3_Math_Matrix4_multiply
  (
    Ring3_Math_Matrix4* c,
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  )
{
  if (c == a || c == b) {
    float t[4][4];
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        t[i][j] = 0.0f;
        for (size_t k = 0; k < 4; ++k) {
          t[i][j] += a->e[i][k] * b->e[k][j];
        }
      }
    }
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        c->e[i][j] = t[i][j];
      }
    }
  } else {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        c->e[i][j] = 0.0f;
        for (size_t k = 0; k < 4; ++k) {
          c->e[i][j] += a->e[i][k] * b->e[k][j];
        }
      }
    }
  }
}

Ring1_CheckReturn() Ring3_Math_Matrix4*
Ring3_Math_Matrix4_product
  (
    const Ring3_Math_Matrix4* a,
    const Ring3_Math_Matrix4* b
  )
{
  Ring3_Math_Matrix4* c = Ring3_Math_Matrix4_create();
  Ring3_Math_Matrix4_multiply(c, a, b);
  return c;
}

void
Ring3_Math_Matrix4_rotateZ
  (
    Ring3_Math_Matrix4* a,
    float d
  )
{
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
}
