
/**
 * @pre matrix must be a 4x4 matrix.
 * @param target the target matrix.
 * @param left, right, bottom, top the signed distance from the origin to the left, right, bottom, and top clip plane.
 * @param near, far the signed distance to the near and far clip plane.
 * @error Ring1_Status_InvalidArgument <code>r - l</code>, <code>t - b</code>, or <code>f - n</code> is @@a 0
 */
INLINE void
ortho_m4x4f32
  (
    SQUAREMATRIX4X4F32 target,
    float left,
    float right,
    float bottom,
    float top,
    float near,
    float far
  )
{
  float width = right - left;
  float height = top - bottom;
  float depth = far - near;
  
  if (width == 0.f) {
    Ring1_Status_set(Ring1_Status_DivisionByZero);
    Ring2_jump();
  }
  if (height == 0.f) {
    Ring1_Status_set(Ring1_Status_DivisionByZero);
    Ring2_jump();
  }
  if (depth == 0.f) {
    Ring1_Status_set(Ring1_Status_DivisionByZero);
    Ring2_jump();
  }
  
  // Adopted from https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml.
  target[0][0] = 2.f / width;
  target[1][0] = target[2][0] = target[3][0] = 0.f;

  target[1][1] = 2.f / height;
  target[0][1] = target[2][1] = target[3][1] = 0.f;

  target[2][2] = -2.f / depth;
  target[0][2] = target[1][2] = target[3][2] = 0.f;

  target[0][3] = -(right + left) / width;
  target[1][3] = -(top + bottom) / height;
  target[2][3] = -(far + near) / depth;
  target[3][3] = 1.f;
}
