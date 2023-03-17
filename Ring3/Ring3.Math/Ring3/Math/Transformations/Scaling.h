#if !defined(RING3_MATH_TRANSFORMATIONS_SCALING_H_INCLUDED)
#define RING3_MATH_TRANSFORMATIONS_SCALING_H_INCLUDED

#if !defined(RING3_MATH_PRIVATE)
#error("Do not include `Ring3/Math/Transformations/Scaling.h` directly, include `Ring3/Math/_Include.h` instead.")
#endif

#include "Ring3/Math/Matrix3x3f32.h"
#include "Ring3/Math/Matrix4x4f32.h"

/// @brief Assign a \f$3 \times 3\f$ matrix a 3D scaling transformation.
/// @param matrix A pointer to the matrix.
/// @remark A 3D \f$3 \times 3\f$ scaling matrix is given by
/// \[
/// \left(\begin{matrix}
/// x & 0 & 0 \\
/// 0 & y & 0 \\
/// 0 & 0 & z
/// \end{matrix}\right)
/// \]
void
Ring3_Math_setScaling3Matrix3x3f32
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z
  );

/// @brief Assign a \f$4 \times 4\f$ matrix a 4D scaling transformation.
/// @param matrix A pointer to the matrix.
/// @remark A 4D \f$4 \times 4\f$ scaling matrix is given by
/// \[
/// \left(\begin{matrix}
/// x & 0 & 0 & 0\\
/// 0 & y & 0 & 0\\
/// 0 & 0 & z & 0\\
/// 0 & 0 & 0 & w
/// \end{matrix}\right)
/// \] 
void
Ring3_Math_setScaling4Matrix4x4f64
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z,
    Ring2_Real32 w
  );

#endif // RING3_MATH_TRANSFORMATIONS_SCALING_H_INCLUDED
