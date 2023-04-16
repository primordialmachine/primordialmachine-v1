#if !defined(RING3_MATH_TRANSFORMATIONS_ROTATION_H_INCLUDED)
#define RING3_MATH_TRANSFORMATIONS_ROTATION_H_INCLUDED


#include "Ring3/Math/Matrix3x3f32.h"
#include "Ring3/Math/Matrix4x4f32.h"


/// @brief Create a 3D \f$3 \times 3\f$ transformation matrix.
/// The matrix represents a counter-clockwise rotation around the x-axis.
/// @param angle The angle, in radians.
/// @remark A \$3 \times 3\f$ transformation matrix for a counter-clockwise rotation by \f$\delta\f$ degrees around the x-axis is given by
/// \[
/// \left(\begin{matrix}
/// 1 & 0 &  0 \\
/// 0 & c & -s \\
/// 0 & s &  c \\
/// \end{matrix}\right)
/// \]
/// where \f$c := \cos\left(\delta\right)\f$ and \f$s := \sin\left(\delta\right)\f$.
void
Ring3_Math_Matrix3x3f32_setRotationX
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 angle
  );

/// @brief Create a 3D \f$4 \times 4\f$ transformation matrix.
/// The matrix represents a counter-clockwise rotation around the x-axis.
/// @param angle The angle, in radians.
/// @remark A \$3 \times 3\f$ transformation matrix for a counter-clockwise rotation by \f$\delta\f$ degrees around the x-axis is given by
/// \[
/// \left(\begin{matrix}
/// 1 & 0 &  0 & 0\\
/// 0 & c & -s & 0\\
/// 0 & s &  c & 0\\
/// 0 & 0 &  0 & 1
/// \end{matrix}\right)
/// \]
/// where \f$c := \cos\left(\delta\right)\f$ and \f$s := \sin\left(\delta\right)\f$.
void
Ring3_Math_Matrix4x4f32_setRotationX
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 angle
  );

/// @brief Create a 3D \f$3 \times 3\f$ transformation matrix.
/// The matrix represents a counter-clockwise rotation around the y-axis.
/// @param angle The angle, in radians.
/// @remark A 3D \f$3 \times 3\f$ transformation matrix for a counter-clockwise rotation by \f$\delta\f$ degrees around the y-axis is given by
/// \[
/// \left(\begin{matrix}
///  c & 0 & s\\
///  0 & 1 & 0\\
/// -s & 0 & c\\
/// \end{matrix}\right)
/// \]
/// where \f$c:=\cos\left(\delta\right)\f$ and \f$s:=\sin\left(\delta\right)\f$.
void
Ring3_Math_Matrix3x3f32_setRotationY
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 angle
  );

/// @brief Create a 3D \f$4 \times 4\f$ transformation matrix.
/// The matrix represents a counter-clockwise rotation around the y-axis.
/// @param angle The angle, in radians.
/// @remark A 3D \f$4 \times 4\f$ transformation matrix for a counter-clockwise rotation by \f$\delta\f$ degrees around the y-axis is given by
/// \[
/// \left(\begin{matrix}
///  c & 0 & s & 0\\
///  0 & 1 & 0 & 0\\
/// -s & 0 & c & 0\\
///  0 & 0 & 0 & 1\\
/// \end{matrix}\right)
/// \]
/// where \f$c:=\cos\left(\delta\right)\f$ and \f$s:=\sin\left(\delta\right)\f$.
void
Ring3_Math_Matrix4x4f32_setRotationY
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 angle
  );

/// @brief Create a 3D \f$3 \times 3\f$ transformation matrix.
/// The matrix represents a counter-clockwise rotation around the z-axis.
/// @param angle The angle, in radians.
/// @remark A 3D \f$3 \times 3\f$ transformation matrix for a counter-clockwise rotation by \f$\delta\f$ degrees around the z-axis is given by
/// \[
/// \left(\begin{matrix}
/// c & -s & 0\\
/// s &  c & 0\\
/// 0 &  0 & 1\\
/// \end{matrix}\right)
/// \]
/// where \f$c:=\cos\left(\delta\right)\f$ and \f$s:=\sin\left(\delta\right)\f$.
void
Ring3_Math_Matrix3x3f32_setRotationZ
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 angle
  );

/// @brief Create a 3D \f$4 \times 4\f$ transformation matrix.
/// The matrix represents a counter-clockwise rotation around the z-axis.
/// @param angle The angle, in radians.
/// @remark A 3D \f$4 \times 4\f$ transformation matrix for a counter-clockwise rotation by \f$\delta\f$ degrees around the z-axis is given by
/// \[
/// \left(\begin{matrix}
/// c & -s & 0 & 0\\
/// s &  c & 0 & 0\\
/// 0 &  0 & 1 & 0\\
/// 0 &  0 & 0 & 1\\
/// \end{matrix}\right)
/// \]
/// where \f$c:=\cos\left(\delta\right)\f$ and \f$s:=\sin\left(\delta\right)\f$.
void
Ring3_Math_Matrix4x4f32_setRotationZ
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 angle
  );

#endif // RING3_MATH_TRANSFORMATIONS_ROTATION_H_INCLUDED
