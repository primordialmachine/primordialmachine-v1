/// @file Ring3/Math/Matrix4x4f32.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Matrix4x4f32.h"

#include "Ring3/Math/Kernels/MatrixKernel.h"

#define RING3_MATRIX_ROWS 4

#define RING3_MATRIX_COLUMNS 4

static void
Ring3_Math_Matrix4x4f32_construct
  (
    Ring3_Math_Matrix4x4f32* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);

#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Zero4x4f32.g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Matrix4x4f32_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Matrix4x4f32,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Matrix4x4f32_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_CheckReturn() Ring3_Math_Matrix4x4f32*
Ring3_Math_Matrix4x4f32_create
  (
  )
{
  Machine_Type* ty = Ring3_Math_Matrix4x4f32_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Math_Matrix4x4f32* self = Ring1_cast(Ring3_Math_Matrix4x4f32*,
                                                                            Machine_allocateClassObject(ty,
                                                                                                        NUMBER_OF_ARGUMENTS,
                                                                                                        ARGUMENTS));
  return self;
}

Ring1_CheckReturn() Ring3_Math_Matrix4x4f32*
Ring3_Math_Matrix4x4f32_clone
  (
    Ring3_Math_Matrix4x4f32 const* self
  )
{
  Ring3_Math_Matrix4x4f32* clone = Ring3_Math_Matrix4x4f32_create();
  Ring3_Math_Matrix4x4f32_copy(clone, self);
  return clone;
}

void
Ring3_Math_Matrix4x4f32_copy
  (
    Ring3_Math_Matrix4x4f32* self,
    Ring3_Math_Matrix4x4f32 const* other
  )
{
  if (self != other) {
    for (size_t i = 0, n = 4; i < n; ++i) {
      for (size_t j = 0, m = 4; j < m; ++j) {
        self->e[i][j] = other->e[i][j];
      }
    }
  }
}

void
Ring3_Math_Matrix4x4f32_setZero
  (
    Ring3_Math_Matrix4x4f32* self
  )
{
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Zero4x4f32.g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
}

void
Ring3_Math_Matrix4x4f32_setIdentity
  (
    Ring3_Math_Matrix4x4f32* self
  )
{
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Identity4x4f32.g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
}

void
Ring3_Math_Matrix4x4f32_transpose
  (
    Ring3_Math_Matrix4x4f32* self
  )
{
  Ring2_Real32 temporary[4][4];

#define a (self->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) temporary[I][J] = E;
#define getMatrixElement(M, I, J) M[I][J];

#include "Ring3/Math/Kernels/Matrix/Transpose4x4f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef a

  for (size_t i = 0, n = 4; i < n; ++i) {
    for (size_t j = 0, m = 4; j < m; ++j) {
      self->e[i][j] = temporary[i][j];
    }
  }
}

void
Ring3_Math_Matrix4x4f32_add
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other,
    Ring3_Math_Matrix4x4f32* target
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

#include "Ring3/Math/Kernels/Matrix/Sum4x4f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a
}

Ring1_CheckReturn() Ring3_Math_Matrix4x4f32*
Ring3_Math_Matrix4x4f32_sum
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other
  )
{
  Ring3_Math_Matrix4x4f32* c = Ring3_Math_Matrix4x4f32_clone(self);
  Ring3_Math_Matrix4x4f32_add(c, other, c);
  return c;
}

void
Ring3_Math_Matrix4x4f32_subtract
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other,
    Ring3_Math_Matrix4x4f32* target
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

#include "Ring3/Math/Kernels/Matrix/Difference4x4f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a
}

Ring1_CheckReturn() Ring3_Math_Matrix4x4f32*
Ring3_Math_Matrix4x4f32_difference
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other
  )
{
  Ring3_Math_Matrix4x4f32* c = Ring3_Math_Matrix4x4f32_clone(self);
  Ring3_Math_Matrix4x4f32_subtract(c, other, c);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Matrix4x4f32_isEqualToWithTolerance
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other,
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
  for (size_t i = 0, n = 4; i < n; ++i) {
    for (size_t j = 0, n = 4; j < n; ++j) {
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
Ring3_Math_Matrix4x4f32_setOrtho
  (
    Ring3_Math_Matrix4x4f32* self,
    Ring2_Real32 l,
    Ring2_Real32 r,
    Ring2_Real32 b,
    Ring2_Real32 t,
    Ring2_Real32 n,
    Ring2_Real32 f
  )
{
  ortho_m4x4f32(self->e, l, r, b, t, n, f);
}

#endif // RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

void
Ring3_Math_Matrix4x4f32_multiplyScalar
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring2_Real32 other,
    Ring3_Math_Matrix4x4f32* target
  );

void
Ring3_Math_Matrix4x4f32_multiply
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other,
    Ring3_Math_Matrix4x4f32* target
  )
{
Ring2_Real32 temporary[4][4];

#define a (self->e)
#define b (other->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) temporary[I][J] = (E);
#define getMatrixElement(M, I, J) ((M)[I][J])

#include "Ring3/Math/Kernels/Matrix/Product4x4f32.g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a

  for (size_t i = 0, n = 4; i < n; ++i) {
    for (size_t j = 0, m = 4; j < m; ++j) {
      target->e[i][j] = temporary[i][j];
    }
  }
}

Ring1_CheckReturn() Ring3_Math_Matrix4x4f32*
Ring3_Math_Matrix4x4f32_productScalar
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring2_Real32 other
  );

Ring1_CheckReturn() Ring3_Math_Matrix4x4f32*
Ring3_Math_Matrix4x4f32_product
  (
    Ring3_Math_Matrix4x4f32 const* self,
    Ring3_Math_Matrix4x4f32 const* other
  )
{
  Ring3_Math_Matrix4x4f32* c = Ring3_Math_Matrix4x4f32_clone(self);
  Ring3_Math_Matrix4x4f32_multiply(c, other, c);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Matrix4x4f32_getElement
  (
    Ring3_Math_Matrix4x4f32* self,
    int64_t rowIndex,
    int64_t columnIndex
  )
{
  if (rowIndex < 0 || rowIndex >= 4) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (columnIndex < 0 || columnIndex >= 4) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->e[rowIndex][columnIndex];
}

Ring1_NoDiscardReturn() void const*
Ring3_Math_Matrix4x4f32_getData
  (
    Ring3_Math_Matrix4x4f32 const* self
  )
{
  return &self->e[0][0];
}

#undef RING3_MATRIX_COLUMNS

#undef RING3_MATRIX_ROWS
