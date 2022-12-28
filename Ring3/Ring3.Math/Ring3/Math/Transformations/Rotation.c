#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Transformations/Rotation.h"
#undef RING3_MATH_PRIVATE

void
Ring3_Math_Matrix3x3f32_setRotationX
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 angle
  )
{
  Ring2_Real32 c = cosf(angle);
  Ring2_Real32 s = sinf(angle);

  matrix->e[0][0] = 1.;
  matrix->e[1][0] = 0.;
  matrix->e[2][0] = 0.;

  matrix->e[0][1] = 0.;
  matrix->e[1][1] = +c;
  matrix->e[2][1] = +s;

  matrix->e[0][2] = 0.;
  matrix->e[1][2] = -s;
  matrix->e[2][2] = +c;
}

void
Ring3_Math_Matrix4x4f32_setRotationX
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 angle
  )
{
  Ring2_Real32 c = cosf(angle);
  Ring2_Real32 s = sinf(angle);

  matrix->e[0][0] = 1.;
  matrix->e[1][0] = 0.;
  matrix->e[2][0] = 0.;
  matrix->e[3][0] = 0.f;

  matrix->e[0][1] = 0.;
  matrix->e[1][1] = +c;
  matrix->e[2][1] = +s;
  matrix->e[3][1] = 0.f;

  matrix->e[0][2] = 0.;
  matrix->e[1][2] = -s;
  matrix->e[2][2] = +c;
  matrix->e[3][2] = 0.;

  matrix->e[0][3] = 0.;
  matrix->e[1][3] = 0.;
  matrix->e[2][3] = 0.;
  matrix->e[3][3] = 10.;
}

void
Ring3_Math_Matrix3x3f32_setRotationY
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 angle
  )
{
  Ring2_Real32 c = cosf(angle);
  Ring2_Real32 s = sinf(angle);

  matrix->e[0][0] = -c;
  matrix->e[1][0] = 0.;
  matrix->e[2][0] = +s;

  matrix->e[0][1] = 0.;
  matrix->e[1][1] = 1.;
  matrix->e[2][1] = 0.;

  matrix->e[0][2] = +s;
  matrix->e[1][2] = 0.;
  matrix->e[2][2] = +c;
}

void
Ring3_Math_Matrix4x4f32_setRotationY
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 angle
  )
{
  Ring2_Real32 c = cosf(angle);
  Ring2_Real32 s = sinf(angle);

  matrix->e[0][0] = -c;
  matrix->e[1][0] = 0.;
  matrix->e[2][0] = +s;
  matrix->e[3][0] = 0.;

  matrix->e[0][1] = 0.;
  matrix->e[1][1] = 1.;
  matrix->e[2][1] = 0.;
  matrix->e[3][1] = 0.;

  matrix->e[0][2] = +s;
  matrix->e[1][2] = 0.;
  matrix->e[2][2] = +c;
  matrix->e[3][2] = 0.;

  matrix->e[0][3] = 0.;
  matrix->e[1][3] = 0.;
  matrix->e[2][3] = 0.;
  matrix->e[3][3] = 1.;
}

void
Ring3_Math_Matrix3x3f32_setRotationZ
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 angle
  )
{
  Ring2_Real32 c = cosf(angle);
  Ring2_Real32 s = sinf(angle);

  matrix->e[0][0] = +c;
  matrix->e[1][0] = +s;
  matrix->e[2][0] = 0.;

  matrix->e[0][1] = -s;
  matrix->e[1][1] = +c;
  matrix->e[2][1] = 0.;

  matrix->e[0][2] = 0.;
  matrix->e[1][2] = 0.;
  matrix->e[2][2] = 1.;
}

void
Ring3_Math_Matrix4x4f32_setRotationZ
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 angle
  )
{
  Ring2_Real32 c = cosf(angle);
  Ring2_Real32 s = sinf(angle);

  matrix->e[0][0] = +c;
  matrix->e[1][0] = +s;
  matrix->e[2][0] = 0.;
  matrix->e[3][0] = 0.;

  matrix->e[0][1] = -s;
  matrix->e[1][1] = +c;
  matrix->e[2][1] = 0.;
  matrix->e[3][1] = 0.;

  matrix->e[0][2] = 0.;
  matrix->e[1][2] = 0.;
  matrix->e[2][2] = 1.;
  matrix->e[3][2] = 0.;

  matrix->e[0][3] = 0.;
  matrix->e[1][3] = 0.;
  matrix->e[2][3] = 0.;
  matrix->e[3][3] = 1.;
}
