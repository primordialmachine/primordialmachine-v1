/// @@file Ring3/Math/Matrix@(rows)x@(columns)@(scalarTypeSuffix).h
/// @@copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @@author Michael Heilmann (michaelheilmann@@primordialmachine.com)

#if !defined(RING3_MATH_MATRIX@(rows)X@(columns)@(scalarTypeSuffixUppercase)_H_INCLUDED)
#define RING3_MATH_MATRIX@(rows)X@(columns)@(scalarTypeSuffixUppercase)_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Matrix@(rows)x@(columns)@(scalarTypeSuffix).h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

#define RING3_MATRIX_ROWS @(rows)

#define RING3_MATRIX_COLUMNS @(columns)

/// C-level definition of a 2D rectangle.
/// The HLL-level definition is
/// @@code
/// class Ring3.Math.Matrix@(rows)x@(columns)@(scalarTypeSuffix) { ... }
/// @@endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix))

struct Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) {
  Machine_Object parent;
  @(scalarType) e[@(rows)][@(columns)];
};

/// @@brief Create a zero matrix.
/// @@return The zero matrix.
Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_create
  (
  );

/// @@brief Clone a matrix.
/// @@param self The matrix to be cloned.
/// @@return The cloned matrix.
Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_clone
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self
  );

void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_copy
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  );

/// @@brief Assign this matrix the values of the zero matrix.
/// @@param self This matrix.
void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_setZero
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  );

/// @@brief Assign this matrix the values of the identity matrix.
/// @@param self This matrix.
void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_setIdentity
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  );

/// @@brief Assign this matrix its transpose.
/// @@param self This matrix.
void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_transpose
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self
  );

/// @@brief Assign a matrix the sum of this matrix and another matrix.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@param target The matrix to assign the sum to.
void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_add
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
  );

/// @@brief Compute the sum of this matrix and another matrix.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@return The sum matrix.
Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)4_sum
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  );

/// @@brief Assign a matrix the difference of this matrix and another matrix.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@param target The matrix to assign the difference to.
void
Ring3_Math_Matrix4@(rows)x@(columns)@(scalarTypeSuffix)_subtract
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
  );

/// @@brief Compute the difference of this matrix and another matrix.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@return The difference matrix.
Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_difference
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  );

/// @@brief Compare this matrix with another matrix with tolerance.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @@return @@a true if the matrices are equal. @@a false otherwise.
/// @@remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_isEqualToWithTolerance
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  );

#if RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

/// @@brief Assign this matrix the values for an orthographic projection transformation.
/// @@param self This matrix.
/// @@param l, r, b, t, n, f The distance from the origin of the left, right, bottom, top, near, and far clip planes.
/// @@undefined <code>r - l</code>, <code>t - b</code>, or <code>f - n</code> is @@a 0.
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
  );

#endif // RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

/// @@brief Compute the product of this matrix and a scalar.
/// @@param self This matrix.
/// @@param other The scalar.
/// @@param target The matrix to assign the product to.
void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_multiplyScalar
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    @(scalarType) other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
  );

/// @@brief Compute the product of this matrix and another matrix.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@param target The matrix to assign the product to.
void
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_multiply
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* target
  );

/// @@brief Compute the product of this matrix and a scalar.
/// @@param self This matrix.
/// @@param other The scalar.
/// @@return The product matrix.
Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_productScalar
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    @(scalarType) other
  );

/// @@brief Compute the product of this matrix and another matrix.
/// @@param self This matrix.
/// @@param other The other matrix.
/// @@return The product matrix.
Ring1_CheckReturn() Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_product
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self,
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* other
  );

/// @@brief Get the value of the element at the specified position in this matrix.
/// @@param self This matrix.
/// @@param rowIndex The row index.
/// @@param columnIndex The column index.
/// @@return The value.
Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_getElement
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)* self,
    int64_t rowIndex,
    int64_t columnIndex
  );

Ring1_NoDiscardReturn() void const*
Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix)_getData
  (
    Ring3_Math_Matrix@(rows)x@(columns)@(scalarTypeSuffix) const* self
  );

#undef RING3_MATRIX_COLUMNS

#undef RING3_MATRIX_ROWS

#endif // RING3_MATH_MATRIX@(rows)X@(columns)@(scalarTypeSuffixUppercase)_H_INCLUDED
