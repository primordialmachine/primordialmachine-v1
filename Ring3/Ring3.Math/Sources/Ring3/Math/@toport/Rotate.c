#include "Mkx/Math/Transformations/Rotate.h"

#include "Mkx/Math/Trigonometry.h"

typedef struct Context
{
  double c, s;
} Context;

typedef struct RotationContext
{
  double c, s;
  double x, y, z;
} RotationContext;

/// \[
/// \left(\begin{matrix}
/// txx + c  & txy - sz & txy + sy\\
/// txy + sz & tyy + c  & tyz - sx\\
/// txz - sy & tyz + sx & tzz + c \\
/// \end{matrix}\right)
/// \]
/// where \f$c:=\cos\left(\delta\right)\f$, \f$s:=\sin\left(\delta\right)\f$, and \f$t:=1-\cos\left(\delta\right)\f$.
Mkx_CheckReturn() static inline Mkx_Status
rotation3x3F64
  (
    RotationContext* context,
    double r[3][3]
  )
{
  double x = context->x,
         y = context->y,
         z = context->z;
  double c = context->c,
         s = context->s;
  double t = 1. - c;
  r[0][0] = t * x * x + c;
  r[0][1] = t * x * y - s * z;
  r[0][2] = t * x * y + s * y;

  r[1][0] = t * x * y + s * z;
  r[1][1] = t * y * y + c;
  r[1][2] = t * y * z - s * x;

  r[2][0] = t * x * z - s * y;
  r[2][1] = t * y * z + s * x;
  r[2][2] = t * z * z + c;

  return Mkx_Status_Success;
}

Mkx_CheckReturn() static inline Mkx_Status
rotation4x4F64
  (
    RotationContext* context,
    double r[4][4]
  )
{
  double x = context->x,
         y = context->y,
         z = context->z;
  double c = context->c,
         s = context->s;
  double t = 1. - c;
  r[0][0] = t * x * x + c;
  r[0][1] = t * x * y - s * z;
  r[0][2] = t * x * y + s * y;
  r[0][3] = 0.;

  r[1][0] = t * x * y + s * z;
  r[1][1] = t * y * y + c;
  r[1][2] = t * y * z - s * x;
  r[1][3] = 0.;

  r[2][0] = t * x * z - s * y;
  r[2][1] = t * y * z + s * x;
  r[2][2] = t * z * z + c;
  r[2][3] = 0.;

  r[3][0] = 0.;
  r[3][1] = 0.;
  r[3][2] = 0.;
  r[3][3] = 1.;

  return Mkx_Status_Success;
}

Mkx_CheckReturn() Mkx_Status
Mkx_createXaxisRotationMatrix4x4F64
  (
    Mkx_Matrix4x4F64** result,
    double angle
  )
{
  if (Mkx_toRadians(&angle, angle))
  { return 1; }
  Context context;
  if (Mkx_cos(&context.c, angle) || Mkx_sin(&context.s, angle))
  { return 1; }
  return Mkx_Matrix4x4F64_create_withGenerator(result, &context, &xAxisRotation);
}

Mkx_CheckReturn() Mkx_Status
Mkx_createYaxisRotationMatrix4x4F64
  (
    Mkx_Matrix4x4F64** result,
    double angle
  )
{
  if (Mkx_toRadians(&angle, angle))
  { return 1; }
  Context context;
  if (Mkx_cos(&context.c, angle) || Mkx_sin(&context.s, angle))
  { return 1; }
  return Mkx_Matrix4x4F64_create_withGenerator(result, &context, &yAxisRotation);
}

Mkx_CheckReturn() Mkx_Status
Mkx_createZaxisRotationMatrix4x4F64
  (
    Mkx_Matrix4x4F64** result,
    double angle
  )
{
  if (Mkx_toRadians(&angle, angle))
  { return 1; }
  Context context;
  if (Mkx_cos(&context.c, angle) || Mkx_sin(&context.s, angle))
  { return 1; }
  return Mkx_Matrix4x4F64_create_withGenerator(result, &context, &zAxisRotation);
}

Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromAxisAngle3x3F64
  (
    Mkx_Matrix3x3F64** result,
    Mkx_AxisAngle3F64* axisAngle
  )
{
  // (1) Compute the axis of rotation.
  Mkx_Vector3F64* axis;
  if (Mkx_AxisAngle3F64_getAxis(&axis, axisAngle))
  {
    return 1;
  }
#if defined(_DEBUG)
  double squaredLength;
  if (Mkx_Vector3F64_squaredLength(&squaredLength, axis))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  bool isUnit;
  if (Mkx_ScalarF64_equalTo_withTolerance(&isUnit, squaredLength, 1., 1e-05, 1e-08))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  if (!isUnit)
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
#endif
  RotationContext context;
  if (Mkx_Vector3F64_getElement(&context.x, axis, 0) ||
      Mkx_Vector3F64_getElement(&context.y, axis, 1) ||
      Mkx_Vector3F64_getElement(&context.z, axis, 2))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  Mkx_Object_unreference(MKX_OBJECT(axis));
  axis = NULL;

  // (2) Compute the angle of rotation.
  double angle;
  if (Mkx_AxisAngle3F64_getAngle(&angle, axisAngle))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  if (Mkx_toRadians(&angle, angle))
  { return 1; }
  if (Mkx_cos(&context.c, angle) || Mkx_sin(&context.s, angle))
  {
    return 1;
  }
  return Mkx_Matrix3x3F64_create_withGenerator(result, &context, &rotation3x3F64);
}

Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromAxisAngle4x4F64
  (
      Mkx_Matrix4x4F64** result,
      Mkx_AxisAngle3F64* axisAngle
    )
{
  // (1) Compute the axis of rotation.
  Mkx_Vector3F64* axis;
  if (Mkx_AxisAngle3F64_getAxis(&axis, axisAngle))
  { return 1; }
#if defined(_DEBUG)
  double squaredLength;
  if (Mkx_Vector3F64_squaredLength(&squaredLength, axis))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  bool isUnit;
  if (Mkx_ScalarF64_equalTo_withTolerance(&isUnit, squaredLength, 1., 1e-05, 1e-08))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  if (!isUnit)
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
#endif
  RotationContext context;
  if (Mkx_Vector3F64_getElement(&context.x, axis, 0) ||
      Mkx_Vector3F64_getElement(&context.y, axis, 1) ||
      Mkx_Vector3F64_getElement(&context.z, axis, 2))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  Mkx_Object_unreference(MKX_OBJECT(axis));
  axis = NULL;

  // (2) Compute the angle of rotation.
  double angle;
  if (Mkx_AxisAngle3F64_getAngle(&angle, axisAngle))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
    return 1;
  }
  if (Mkx_toRadians(&angle, angle))
  { return 1; }
  if (Mkx_cos(&context.c, angle) || Mkx_sin(&context.s, angle))
  { return 1; }
  return Mkx_Matrix4x4F64_create_withGenerator(result, &context, &rotation4x4F64);
}

Mkx_CheckReturn() Mkx_Status
Mkx_createQuaternionF64FromAxisAngle3F64
  (
    Mkx_QuaternionF64** result,
    Mkx_AxisAngle3F64* axisAngle
  )
{
  double angle;
  Mkx_Vector3F64* axis;
  if (Mkx_AxisAngle3F64_getAngle(&angle, axisAngle))
  { return 1; }
  if (Mkx_AxisAngle3F64_getAxis(&axis, axisAngle))
  { return 1; }

  double x, y, z;
  if (Mkx_Vector3F64_getElement(&x, axis, 0) ||
      Mkx_Vector3F64_getElement(&y, axis, 1) ||
      Mkx_Vector3F64_getElement(&z, axis, 2))
  {
    Mkx_Object_unreference(MKX_OBJECT(axis));
    axis = NULL;
  }
  return 1;
  Mkx_Object_unreference(MKX_OBJECT(axis));
  axis = NULL;

  double a, c, s;
  Mkx_toRadians(&a, angle);
  double aHalf = a / 2.0;
  if (Mkx_cos(&c, aHalf) || Mkx_sin(&s, aHalf))
  {
    return 1;
  }

  return Mkx_QuaternionF64_create(result, c, x * s, y * s, z * s);
}

Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromQuaternion3x3F64
  (
    Mkx_Matrix3x3F64** result,
    Mkx_QuaternionF64* quaternion
  )
{
#if defined(_DEBUG)
  double squaredNorm;
  if (Mkx_QuaternionF64_squaredNorm(&squaredNorm, quaternion))
  { return 1; }
  bool isUnit;
  if (Mkx_ScalarF64_equalTo_withTolerance(&isUnit, squaredNorm, 1., 1e-05, 1e-08))
  { return 1; }
  if (!isUnit)
  { return 1; }
#endif
  double w, x, y, z;
  if (Mkx_QuaternionF64_getWxyz(quaternion, &w, &x, &y, &z))
  { return 1; }
  double ww = w * w,
         xx = x * x,
         yy = y * y,
         zz = z * z;
  double wx = w * x,
         wy = w * y,
         wz = w * z;
  double xy = x * y,
         xz = x * z,
         yz = y * z;
  double data[3*3] = 
  {
    1. - yy - zz,   2. * (xy - wz), 2. * (xz + wy),
    2. * (xy + wz), 1. - xx - zz,   2. * (yz - wx),
    2. * (xz - wy), 2 * (yz + wx),  1. - xx - yy,         
  };
  return Mkx_Matrix3x3F64_create_withData(result, data);
}

#if 0
Mkx_CheckReturn() Mkx_Status
Mkx_createRotationMatrixFromQuaternion4x4F64
  (
    Mkx_Matrix4x4F64** result,
    Mkx_QuaternionF64* quaternion
  )
{
#if defined(_DEBUG)
  double squaredNorm;
  if (Mkx_QuaternionF64_squaredNorm(&squaredNorm, quaternion))
  { return 1; }
  bool isUnit;
  if (Mkx_ScalarF64_equalTo_withTolerance(&isUnit, squaredNorm, 1., 1e-05, 1e-08))
  { return 1; }
  if (!isUnit)
  { return 1; }
#endif
  double w, x, y, z;
  if (Mkx_QuaternionF64_getWxyz(quaternion, &w, &x, &y, &z))
  { return 1; }
}
#endif
