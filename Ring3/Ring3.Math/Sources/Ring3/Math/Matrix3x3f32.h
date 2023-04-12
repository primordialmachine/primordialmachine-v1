/// @file Ring3/Math/Matrix3x3f32.h
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING3_MATH_MATRIX3X3F32_H_INCLUDED)
#define RING3_MATH_MATRIX3X3F32_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Matrix3x3f32.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring2/Library/_Include.h"

#define RING3_MATRIX_ROWS 3

#define RING3_MATRIX_COLUMNS 3

/// C-level definition of a 2D rectangle.
/// The HLL-level definition is
/// @code
/// class Ring3.Math.Matrix3x3f32 { ... }
/// @endcode
MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Matrix3x3f32)

struct Ring3_Math_Matrix3x3f32_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Matrix3x3f32 {
  Machine_Object parent;
  Ring2_Real32 e[3][3];
};

/// @brief Create a zero matrix.
/// @return The zero matrix.
Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_create
  (
  );

/// @brief Clone a matrix.
/// @param self The matrix to be cloned.
/// @return The cloned matrix.
Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_clone
  (
    Ring3_Math_Matrix3x3f32 const* self
  );

void
Ring3_Math_Matrix3x3f32_copy
  (
    Ring3_Math_Matrix3x3f32* self,
    Ring3_Math_Matrix3x3f32 const* other
  );

/// @brief Assign this matrix the values of the zero matrix.
/// @param self This matrix.
void
Ring3_Math_Matrix3x3f32_setZero
  (
    Ring3_Math_Matrix3x3f32* self
  );

/// @brief Assign this matrix the values of the identity matrix.
/// @param self This matrix.
void
Ring3_Math_Matrix3x3f32_setIdentity
  (
    Ring3_Math_Matrix3x3f32* self
  );

/// @brief Assign this matrix its transpose.
/// @param self This matrix.
void
Ring3_Math_Matrix3x3f32_transpose
  (
    Ring3_Math_Matrix3x3f32* self
  );

/// @brief Assign a matrix the sum of this matrix and another matrix.
/// @param self This matrix.
/// @param other The other matrix.
/// @param target The matrix to assign the sum to.
void
Ring3_Math_Matrix3x3f32_add
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring3_Math_Matrix3x3f32* target
  );

/// @brief Compute the sum of this matrix and another matrix.
/// @param self This matrix.
/// @param other The other matrix.
/// @return The sum matrix.
Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f324_sum
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other
  );

/// @brief Assign a matrix the difference of this matrix and another matrix.
/// @param self This matrix.
/// @param other The other matrix.
/// @param target The matrix to assign the difference to.
void
Ring3_Math_Matrix43x3f32_subtract
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring3_Math_Matrix3x3f32* target
  );

/// @brief Compute the difference of this matrix and another matrix.
/// @param self This matrix.
/// @param other The other matrix.
/// @return The difference matrix.
Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_difference
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other
  );

/// @brief Compare this matrix with another matrix with tolerance.
/// @param self This matrix.
/// @param other The other matrix.
/// @param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @return @a true if the matrices are equal. @a false otherwise.
/// @remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Matrix3x3f32_isEqualToWithTolerance
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  );

#if RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

/// @brief Assign this matrix the values for an orthographic projection transformation.
/// @param self This matrix.
/// @param l, r, b, t, n, f The distance from the origin of the left, right, bottom, top, near, and far clip planes.
/// @undefined <code>r - l</code>, <code>t - b</code>, or <code>f - n</code> is @a 0.
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
  );

#endif // RING3_MATRIX_ROWS == 4 && RING3_MATRIX_COLUMNS == 4

/// @brief Compute the product of this matrix and a scalar.
/// @param self This matrix.
/// @param other The scalar.
/// @param target The matrix to assign the product to.
void
Ring3_Math_Matrix3x3f32_multiplyScalar
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring2_Real32 other,
    Ring3_Math_Matrix3x3f32* target
  );

/// @brief Compute the product of this matrix and another matrix.
/// @param self This matrix.
/// @param other The other matrix.
/// @param target The matrix to assign the product to.
void
Ring3_Math_Matrix3x3f32_multiply
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other,
    Ring3_Math_Matrix3x3f32* target
  );

/// @brief Compute the product of this matrix and a scalar.
/// @param self This matrix.
/// @param other The scalar.
/// @return The product matrix.
Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_productScalar
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring2_Real32 other
  );

/// @brief Compute the product of this matrix and another matrix.
/// @param self This matrix.
/// @param other The other matrix.
/// @return The product matrix.
Ring1_CheckReturn() Ring3_Math_Matrix3x3f32*
Ring3_Math_Matrix3x3f32_product
  (
    Ring3_Math_Matrix3x3f32 const* self,
    Ring3_Math_Matrix3x3f32 const* other
  );

/// @brief Get the value of the element at the specified position in this matrix.
/// @param self This matrix.
/// @param rowIndex The row index.
/// @param columnIndex The column index.
/// @return The value.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Matrix3x3f32_getElement
  (
    Ring3_Math_Matrix3x3f32* self,
    int64_t rowIndex,
    int64_t columnIndex
  );

Ring1_NoDiscardReturn() void const*
Ring3_Math_Matrix3x3f32_getData
  (
    Ring3_Math_Matrix3x3f32 const* self
  );

#undef RING3_MATRIX_COLUMNS

#undef RING3_MATRIX_ROWS

#endif // RING3_MATH_MATRIX3X3F32_H_INCLUDED
