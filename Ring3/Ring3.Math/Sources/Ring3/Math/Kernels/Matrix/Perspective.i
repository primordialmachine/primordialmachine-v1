
INLINE float
to_radians_f32
  (
    float x
  )
{
  static const float PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
  return x * (PI / 180.f);
}

INLINE float
cot
  (
    float x
  )
{ return 1.f / tanf(x); }

/**
 * @pre matrix must be a 4x4 matrix.
 * @param target the target matrix.
 * @param aspectRatio The aspect ratio.
 * @param fieldOfVision The field of vision.
 * @param near The signed distance from the origin to the near clip plane.
 * @param far The signed distance from the origin to the far clip plane.
 * @undefined
 * - @a near or @a far is non-positive
 * - @a near is greater than @a far
 * - @a aspectRatio is @a 0
 */
INLINE void
perspective_m4x4f32
  (
    SQUAREMATRIX4X4F32 target,
    float aspectRatio,
    float fieldOfVision,
    float near,
    float far
  )
{
  if (aspectRatio == 0.f) {
    Ring1_Status_set(Ring1_Status_DivisionByZero);
    Ring2_jump(); 
  }
  if (near < 0.f || far < 0.f) {
    Ring1_Status_set(Ring1_Status_DivisionByZero);
    Ring2_jump(); 
  }
  float f = cot(to_radians_f32(fieldOfVision));
  float depthNegated = near - far;
    
  // 1st row.
  target[0][0] = f / aspectRatio;
  target[0][1] = 0.;
  target[0][2] = 0.;
  target[0][3] = 0.;
  
  // 2nd row.
  target[1][0] = 0.;
  target[1][1] = f;
  target[1][2] = 0.;
  target[1][3] = 0.;
  
  // 3rd row.
  target[2][0] = 0.;
  target[2][1] = 0.;
  target[2][2] = (far + near) / depthNegated;
  target[2][3] = (2.f * far * near) / depthNegated;
  
  // 4th row.
  target[3][0] = 0.;
  target[3][1] = 0.;
  target[3][2] = -1.;
  target[3][3] = 0.;
}
