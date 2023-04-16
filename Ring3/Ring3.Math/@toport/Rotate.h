#if !defined(MKX_MATH_TRANSFORMATIONS_ROTATE_H_INCLUDED)
#define MKX_MATH_TRANSFORMATIONS_ROTATE_H_INCLUDED


#include "Mkx/Math/Matrix3x3F64.h"
#include "Mkx/Math/Matrix4x4F64.h"
#include "Mkx/Math/Vector3F64.h"
#include "Mkx/Math/QuaternionF64.h"
#include "Mkx/Math/AxisAngle3F64.h"
#include "Mkx/Math/ScalarF64.h"

/// @brief Create a 3D \f$3 \times 3\f$ transformation matrix representing an axis angle rotation.
/// The matrix represents a counter-clockwise rotation around the specified unit axis.
/// @return #Mkx_Status_Success on success, a failure status code on failure.
/// @remark See https://documentation.primordialmachine.com/reference/orientation-representation/axis-angle-to-matrix for more information.
Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromAxisAngle3x3F64
  (
    Mkx_Matrix3x3F64** result,
    Mkx_AxisAngle3F64* axisAngle
  );

/// @brief Create a 3D \f$4 \times 4\f$ transformation matrix representing an axis angle rotation.
/// @return #Mkx_Status_Success on success, a failure status code on failure.
/// @remark A 4D \f$4 \times 4\f$ transformation matrix for that axis angle is given by
/// \[
/// \left(\begin{matrix}
/// R     & 0\\
///       & 0\\
/// 0 & 0 & 1\\
/// \end{matrix}\right)
/// \]
/// where \(R\) is the \f$3 \times 3\f$ transformation matrix for that axis angle.
Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromAxisAngle4x4F64
  (
    Mkx_Matrix4x4F64** result,
    Mkx_AxisAngle3F64* axisAngle
  );

/// @brief @brief Create a 3D \f$3 \times 3\f$ transformation matrix representing a quaternion rotation.
/// @param result  A pointer to a <code>Mkx_Matrix3x3F64 *</code> variable.
/// @param quaternion A pointer to the quaternion.
/// @return #Mkx_Status_Success on success, a failure status code on failure.
/// @remarks See https://documentation.primordialmachine.com/reference/orientation-representation/quaternion-to-matrix for more information.
Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromQuaternion3x3F64
  (
    Mkx_Matrix3x3F64** result,
    Mkx_QuaternionF64* quaternion
  );

/// @brief @brief Create a 3D \f$4 \times 4\f$ transformation matrix representing a quaternion rotation.
/// @param result  A pointer to a <code>Mkx_Matrix4x4F64 *</code> variable.
/// @param quaternion A pointer to the quaternion.
/// @return #Mkx_Status_Success on success, a failure status code on failure.
/// @remark A 4D \f$4 \times 4\f$ transformation matrix for that quaternion is given by
/// \[
/// \left(\begin{matrix}
/// R     & 0\\
///       & 0\\
/// 0 & 0 & 1\\
/// \end{matrix}\right)
/// \]
/// where \(R\) is the \f$3 \times 3\f$ transformation matrix for that quaternion.
Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromQuaternion4x4F64
  (
    Mkx_Matrix4x4F64** result,
    Mkx_QuaternionF64* quaternion
  );

/// @brief Create a quaternion representing an equivalent rotation as the specified axis angle.
/// @param result A pointer to a <code>Mkx_QuaternionF64*</code> variable.
/// @param source A pointer to the <code>Mkx_AxisAngle3F64</code> object.
/// @return #Mkx_Status_Success on success, a failure status code on failure.
/// @see https://documentation.primordialmachine.com/reference/orientation-representation/axis-angle-to-quaternion for more information.
Mkx_CheckReturn() Mkx_Status
Mkx_createQuaternionF64FromAxisAngle3F64
  (
    Mkx_QuaternionF64** result,
    Mkx_AxisAngle3F64* source
  );

#endif // MKX_MATH_TRANSFORMATIONS_ROTATE_H_INCLUDED
