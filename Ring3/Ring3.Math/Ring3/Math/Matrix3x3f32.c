/// @file Ring3/Math/Matrix3x3f32.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Matrix3x3f32.h"

#include "Ring1/All/_Include.h"
#include <math.h>

#define RING3_MATRIX_ROWS 3

#define RING3_MATRIX_COLUMNS 3

static void
Ring3_Math_Matrix3x3f32_construct
  (
    Ring3_Math_Matrix3x3f32* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);

#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Zero3x3f32.g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Matrix3x3f32_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Matrix3x3f32,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Matrix3x3f32_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_create
  (
  )
{
  Machine_ClassType* ty = Ring3_Math_Matrix3x3f32_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 0;
  static const Ring2_Value ARGUMENTS[] = { { Ring2_Value_Tag_Void, Ring2_Void_Void } };
  Ring3_Math_Matrix3x3f32* self = (Ring3_Math_Matrix3x3f32*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}

Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_clone
  (
    const Ring3_Math_Matrix3x3f32* self
  )
{
  Ring3_Math_Matrix3x3f32* clone = Ring3_Math_Matrix3x3f32_create();
  Ring3_Math_Matrix3x3f32_copy(clone, self);
  return clone;
}

void
Ring3_Math_Matrix3x3f32_copy
  (
    Ring3_Math_Matrix3x3f32* self,
    const Ring3_Math_Matrix3x3f32* other
  )
{
  if (self != other) {
    for (size_t i = 0, n = 3; i < n; ++i) {
      for (size_t j = 0, m = 3; j < m; ++j) {
        self->e[i][j] = other->e[i][j];
      }
    }
  }
}

void
Ring3_Math_Matrix3x3f32_setZero
  (
    Ring3_Math_Matrix3x3f32* self
  )
{
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Zero3x3f32.g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
}

void
Ring3_Math_Matrix3x3f32_setIdentity
  (
    Ring3_Math_Matrix3x3f32* self
  )
{
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Identity3x3f32.g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
}

void
Ring3_Math_Matrix3x3f32_transpose
  (
    Ring3_Math_Matrix3x3f32* self
  )
{
  Ring2_Real32 temporary[3][3];

#define a (self->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) temporary[I][J] = E;
#define getMatrixElement(M, I, J) M[I][J];

#include "Ring3/Math/Kernels/Matrix/Transpose3x3f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef a

  for (size_t i = 0, n = 3; i < n; ++i) {
    for (size_t j = 0, m = 3; j < m; ++j) {
      self->e[i][j] = temporary[i][j];
    }
  }
}

void
Ring3_Math_Matrix3x3f32_add
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring3_Math_Matrix3x3f32* target
  )
{
#define a (self->e)
#define b (other->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) (target->e)[I][J] = (E);
#define getMatrixElement(M, I, J) ((M)[I][J])

#include "Ring3/Math/Kernels/Matrix/Sum3x3f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a
}

Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_sum
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other
  )
{
  Ring3_Math_Matrix3x3f32* c = Ring3_Math_Matrix3x3f32_clone(self);
  Ring3_Math_Matrix3x3f32_add(c, other, c);
  return c;
}

void
Ring3_Math_Matrix3x3f32_subtract
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring3_Math_Matrix3x3f32* target
  )
{
#define a (self->e)
#define b (other->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) (target->e)[I][J] = (E);
#define getMatrixElement(M, I, J) ((M)[I][J])

#include "Ring3/Math/Kernels/Matrix/Difference3x3f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a
}

Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_difference
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other
  )
{
  Ring3_Math_Matrix3x3f32* c = Ring3_Math_Matrix3x3f32_clone(self);
  Ring3_Math_Matrix3x3f32_subtract(c, other, c);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Matrix3x3f32_isEqualToWithTolerance
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  )
{
  if (!self || !other || absolute <= 0. || relative <= 0.) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (self == other) {
    return true;
  }
  for (size_t i = 0, n = 3; i < n; ++i) {
    for (size_t j = 0, n = 3; j < n; ++j) {
      bool equal;
      if (Ring1_Fp_equalToWithTolerance_f32(&equal, self->e[i][j], other->e[i][j], absolute, relative)) {
        Ring2_jump();
      }
      if (!equal) {
        return false;
      }
    }
  }
  return true;
}

#if RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

void
Ring3_Math_Matrix3x3f32_setOrtho
  (
    Ring3_Math_Matrix3x3f32* self,
    Ring2_Real32 l,
    Ring2_Real32 r,
    Ring2_Real32 b,
    Ring2_Real32 t,
    Ring2_Real32 n,
    Ring2_Real32 f
  )
{
  ortho_m3x3f32(self->e, l, r, b, t, n, f);
}

#endif // RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

void
Ring3_Math_Matrix3x3f32_multiply
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring3_Math_Matrix3x3f32* target
  )
{
Ring2_Real32 temporary[3][3];

#define a (self->e)
#define b (other->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) temporary[I][J] = (E);
#define getMatrixElement(M, I, J) ((M)[I][J])

#include "Ring3/Math/Kernels/Matrix/Product3x3f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a

for (size_t i = 0, n = 3; i < n; ++i) {
  for (size_t j = 0, m = 3; j < m; ++j) {
    target->e[i][j] = temporary[i][j];
  }
}
}

Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_product
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other
  )
{
  Ring3_Math_Matrix3x3f32* c = Ring3_Math_Matrix3x3f32_clone(self);
  Ring3_Math_Matrix3x3f32_multiply(c, other, c);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Matrix3x3f32_getElement
  (
    Ring3_Math_Matrix3x3f32* self,
    int64_t rowIndex,
    int64_t columnIndex
  )
{
  if (rowIndex < 0 || rowIndex >= 3) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (columnIndex < 0 || columnIndex >= 3) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->e[rowIndex][columnIndex];
}

#undef RING3_MATRIX_COLUMNS

#undef RING3_MATRIX_ROWS
