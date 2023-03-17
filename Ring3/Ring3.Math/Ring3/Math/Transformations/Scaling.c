#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Transformations/Scaling.h"
#undef RING3_MATH_PRIVATE

void
Ring3_Math_setScaling3Matrix3x3f32
  (
    Ring3_Math_Matrix3x3f32* matrix,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z
  )
{
  Ring3_Math_Matrix3x3f32_setZero(matrix);
  matrix->e[0][0] = x;
  matrix->e[1][1] = y;
  matrix->e[2][2] = z;
}

void
Ring3_Math_setScaling4Matrix4x4f64
  (
    Ring3_Math_Matrix4x4f32* matrix,
    Ring2_Real32 x,
    Ring2_Real32 y,
    Ring2_Real32 z,
    Ring2_Real32 w
  )
{
  Ring3_Math_Matrix4x4f32_setZero(matrix);
  matrix->e[0][0] = x;
  matrix->e[1][1] = y;
  matrix->e[2][2] = z;
}
