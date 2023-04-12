/// @@file Ring3/Math/Matrix@(rows)x@(columns)@(scalarTypeSuffix).c
/// @@copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @@author Michael Heilmann (michaelheilmann@@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Matrix@(rows)x@(columns)@(scalarTypeSuffix).h"

#include "Ring3/Math/Kernels/MatrixKernel.h"

#define RING3_MATRIX_ROWS @(rows)

#define RING3_MATRIX_COLUMNS @(columns)

static void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_construct
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self,
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

#include "Ring3/Math/Kernels/Matrix/Zero@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix

  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix),
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_create
  (
  )
{
  Machine_Type* ty = Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 0;
  static Ring2_Value const ARGUMENTS[] = { Ring2_Value_StaticInitializerVoid() };
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self = Ring1_cast(Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*,
                                                                            Machine_allocateClassObject(ty,
                                                                                                        NUMBER_OF_ARGUMENTS,
                                                                                                        ARGUMENTS));
  return self;
}

Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_clone
  (
    const Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  )
{
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* clone = Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_create();
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_copy(clone, self);
  return clone;
}

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_copy
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self,
    const Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* other
  )
{
  if (self != other) {
    for (size_t i = 0, n = @(rows); i < n; ++i) {
      for (size_t j = 0, m = @(columns); j < m; ++j) {
        self->e[i][j] = other->e[i][j];
      }
    }
  }
}

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_setZero
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  )
{
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Zero@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
}

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_setIdentity
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  )
{
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) self->e[I][J] = E;

#include "Ring3/Math/Kernels/Matrix/Identity@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
}

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_transpose
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  )
{
  @(scalarType) temporary[@(rows)][@(columns)];

#define a (self->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) temporary[I][J] = E;
#define getMatrixElement(M, I, J) M[I][J];

#include "Ring3/Math/Kernels/Matrix/Transpose@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef a

  for (size_t i = 0, n = @(rows); i < n; ++i) {
    for (size_t j = 0, m = @(columns); j < m; ++j) {
      self->e[i][j] = temporary[i][j];
    }
  }
}

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_add
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
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

#include "Ring3/Math/Kernels/Matrix/Sum@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a
}

Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_sum
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* c = Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_clone(self);
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_add(c, other, c);
  return c;
}

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_subtract
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
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

#include "Ring3/Math/Kernels/Matrix/Difference@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a
}

Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_difference
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* c = Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_clone(self);
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_subtract(c, other, c);
  return c;
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_isEqualToWithTolerance
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
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
  for (size_t i = 0, n = @(rows); i < n; ++i) {
    for (size_t j = 0, n = @(columns); j < n; ++j) {
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
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_setOrtho
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self,
    @(scalarType) l,
    @(scalarType) r,
    @(scalarType) b,
    @(scalarType) t,
    @(scalarType) n,
    @(scalarType) f
  )
{
  ortho_m@(rows)x@(columns)@(scalarTypeSuffix)(self->e, l, r, b, t, n, f);
}

#endif // RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_multiplyScalar
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    @(scalarType) other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
  );

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_multiply
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
  )
{
@(scalarType) temporary[@(rows)][@(columns)];

#define a (self->e)
#define b (other->e)
#define beginMatrix()
#define endMatrix()
#define beginRow()
#define endRow()
#define setMatrixElement(I, J, E) temporary[I][J] = (E);
#define getMatrixElement(M, I, J) ((M)[I][J])

#include "Ring3/Math/Kernels/Matrix/Product@(rows)x@(columns)@(scalarTypeSuffix).g"

#undef getMatrixElement
#undef setMatrixElement
#undef endRow
#undef beginRow
#undef endMatrix
#undef beginMatrix
#undef b
#undef a

  for (size_t i = 0, n = @(rows); i < n; ++i) {
    for (size_t j = 0, m = @(columns); j < m; ++j) {
      target->e[i][j] = temporary[i][j];
    }
  }
}

Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_productScalar
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    @(scalarType) other
  );

Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_product
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  )
{
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* c = Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_clone(self);
  Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_multiply(c, other, c);
  return c;
}

Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_getElement
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self,
    int64_t rowIndex,
    int64_t columnIndex
  )
{
  if (rowIndex < 0 || rowIndex >= @(rows)) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  if (columnIndex < 0 || columnIndex >= @(columns)) {
    Ring1_Status_set(Ring1_Status_IndexOutOfBounds);
    Ring2_jump();
  }
  return self->e[rowIndex][columnIndex];
}

Ring1_NoDiscardReturn() void const*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_getData
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self
  )
{
  return &self->e[0][0];
}

#undef RING3_MATRIX_COLUMNS

#undef RING3_MATRIX_ROWS
