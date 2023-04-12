#include "Ring1/All/_Include.h"
#include <math.h>

#if defined(INLINE)
#error("symbol INLINE already defined")
#endif
#define INLINE static inline

typedef float SQUAREMATRIX3X3F32[3][3];

typedef float SQUAREMATRIX4X4F32[4][4];

#if 0
/**
 * @param source the source vector
 * @param target the target vector
 * @detail target[i][j] is assigned 0
 */
INLINE void
zero_m4x4f32
  (
    SQUAREMATRIX4X4F32 target
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      target[i][j] = 0.f;
    }
  }
}
#endif

#if 0
/**
 * @param source the source vector
 * @param target the target vector
 * @detail target[i][j] is assigned 0
 */
INLINE void
zero_m3x3f32
  (
    SQUAREMATRIX3X3F32 target
  )
{
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      target[i][j] = 0.f;
    }
  }
}
#endif

#if 0
/**
 * @param source the source vector
 * @param target the target vector
 * @detail
 * target[i][j] is assigned 0 if i != j
 * target[i][j] is assigned 1 if i == j
 */
INLINE void
identity_m4x4f32
  (
    SQUAREMATRIX4X4F32 target
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      target[i][j] = 0.f;
    }
  }
  for (size_t i = 0; i < 4; ++i) {
    target[i][i] = 1.f;
  }
}
#endif

#if 0
/**
 * @param source the source vector
 * @param target the target vector
 * @detail
 * target[i][j] is assigned 0 if i != j
 * target[i][j] is assigned 1 if i == j
 */
INLINE void
identity_m3x3f32
  (
    SQUAREMATRIX3X3F32 target
  )
{
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      target[i][j] = 0.f;
    }
  }
  for (size_t i = 0; i < 3; ++i) {
    target[i][i] = 1.f;
  }
}
#endif

#if 0
/**
 * @param source the source vector
 * @param target the target vector
 * @detail target[i][j] is assigned source[i][j]
 */
INLINE void
copy_m4x4f32_m4x4f32
  (
    SQUAREMATRIX4X4F32 const source,
    SQUAREMATRIX4X4F32 target
  )
{
  if (source != target) {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        target[i][j] = source[i][j];
      }
    }
  }
}
#endif

#if 0
/**
 * @param source the source vector
 * @param target the target vector
 * @detail target[i][j] is assigned source[i][j]
 */
INLINE void
copy_m3x3f32_m3x3f32
  (
    SQUAREMATRIX3X3F32 const source,
    SQUAREMATRIX3X3F32 target
  )
{
  if (source != target) {
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        target[i][j] = source[i][j];
      }
    }
  }
}
#endif

#if 0
/**
 * @param source1, source2 the source matrices
 * @param target the target matrix
 * @detail target[i][j] is assigned add(source1[i][j], source2[i][j])
 */
INLINE void
add_m4x4f32_m4x4f32
  (
    SQUAREMATRIX4X4F32 const source1,
    SQUAREMATRIX4X4F32 const source2,
    SQUAREMATRIX4X4F32 target
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      target[i][j] = source1[i][j] + source2[i][j];
    }
  }
}
#endif

#if 0
/**
 * @param source1, source2 the source matrices
 * @param target the target matrix
 * @detail target[i][j] is assigned add(source1[i][j], source2[i][j])
 */
INLINE void
add_m3x3f32_m3x3f32
  (
    SQUAREMATRIX3X3F32 const source1,
    SQUAREMATRIX3X3F32 const source2,
    SQUAREMATRIX3X3F32 target
  )
{
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      target[i][j] = source1[i][j] + source2[i][j];
    }
  }
}
#endif

#if 0
/**
 * @param source1, source2 the source matrices
 * @param target the target matrix
 * @detail target[i][j] is assigned sub(source1[i][j], source2[i][j])
 */
INLINE void
sub_m4x4f32_m4x4f32
  (
    SQUAREMATRIX4X4F32 const source1,
    SQUAREMATRIX4X4F32 const source2,
    SQUAREMATRIX4X4F32 target
  )
{
  for (size_t i = 0; i < 4; ++i) {
    for (size_t j = 0; j < 4; ++j) {
      target[i][j] = source1[i][j] - source2[i][j];
    }
  }
}
#endif

#if 0
/**
 * @param source1, source2 the source matrices
 * @param target the target matrix
 * @detail target[i][j] is assigned sub(source1[i][j], source2[i][j])
 */
INLINE void
sub_m3x3f32_m3x3f32
  (
    SQUAREMATRIX3X3F32 const source1,
    SQUAREMATRIX3X3F32 const source2,
    SQUAREMATRIX3X3F32 target
  )
{
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j) {
      target[i][j] = source1[i][j] - source2[i][j];
    }
  }
}
#endif

/**
 * @param target the target matrix
 * @detail target is assigned transpose(target)
 */
INLINE void
transpose_m4x4f32
  (
    SQUAREMATRIX4X4F32 target
  )
{
  for (size_t i = 0; i < 4 - 1; ++i) {
    for (size_t j = i + 1; j < 4; ++j) {
      Ring2_Real32 temporary = target[i][j];
      target[i][j] = target[j][i];
      target[j][i] = temporary;
    }
  }
}

/**
 * @param target the target matrix
 * @detail target is assigned transpose(target)
 */
INLINE void
transpose_m3x3f32
  (
    SQUAREMATRIX3X3F32 target
  )
{
  for (size_t i = 0; i < 3 - 1; ++i) {
    for (size_t j = i + 1; j < 3; ++j) {
      Ring2_Real32 temporary = target[i][j];
      target[i][j] = target[j][i];
      target[j][i] = temporary;
    }
  }
}

/**
 * @pre matrix must be a 4x4 matrix.
 * @param target the target matrix.
 * @param left, right, bottom, top the signed distance from the origin to the left, right, bottom, and top clip plane.
 * @param near, far the signed distance to the near and far clip plane.
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
  // Adopted from https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glOrtho.xml.
  target[0][0] = 2.f / (right - left);
  target[1][0] = target[2][0] = target[3][0] = 0.f;

  target[1][1] = 2.f / (top - bottom);
  target[0][1] = target[2][1] = target[3][1] = 0.f;

  target[2][2] = -2.f / (far - near);
  target[0][2] = target[1][2] = target[3][2] = 0.f;

  target[0][3] = -(right + left) / (right - left);
  target[1][3] = -(top + bottom) / (top - bottom);
  target[2][3] = -(far + near) / (far - near);
  target[3][3] = 1.f;
}

INLINE void
multiply_m4x4f32_m4x4f32
  (
    SQUAREMATRIX4X4F32 const a,
    SQUAREMATRIX4X4F32 const b,
    SQUAREMATRIX4X4F32 c
  )
{
  if (c == a || c == b) {
    float t[4][4];
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        t[i][j] = 0.0f;
        for (size_t k = 0; k < 4; ++k) {
          t[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        c[i][j] = t[i][j];
      }
    }
  } else {
    for (size_t i = 0; i < 4; ++i) {
      for (size_t j = 0; j < 4; ++j) {
        c[i][j] = 0.0f;
        for (size_t k = 0; k < 4; ++k) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }
}

INLINE void
multiply_m3x3f32_m3x3f32
  (
    SQUAREMATRIX3X3F32 const a,
    SQUAREMATRIX3X3F32 const b,
    SQUAREMATRIX3X3F32 c
  )
{
  if (c == a || c == b) {
    float t[3][3];
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        t[i][j] = 0.0f;
        for (size_t k = 0; k < 3; ++k) {
          t[i][j] += a[i][k] * b[k][j];
        }
      }
    }
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        c[i][j] = t[i][j];
      }
    }
  } else {
    for (size_t i = 0; i < 3; ++i) {
      for (size_t j = 0; j < 3; ++j) {
        c[i][j] = 0.0f;
        for (size_t k = 0; k < 3; ++k) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }
}

/**
 * @details
 * @a a is assigned
 * @code
 * +c -s  0  0
 * +s +c  0  0
 *  0  0  1  0
 *  0  0  0  1
 * @endcode
 */
INLINE void
rotate_z_m4x4f32
  (
    SQUAREMATRIX4X4F32 a,
    Ring2_Real32 d
  )
{
  Ring2_Real32 c = cosf(d),
               s = sinf(d);
  
  a[0][0] = +c;
  a[1][0] = +s;
  a[2][0] = 0.f;
  a[3][0] = 0.f;

  a[0][1] = -s;
  a[1][1] = +c;
  a[2][1] = 0.f;
  a[3][1] = 0.f;

  a[0][2] = 0.f;
  a[1][2] = 0.f;
  a[2][2] = 1.f;
  a[3][2] = 0.f;
  
  a[0][3] = 0.f;
  a[1][3] = 0.f;
  a[2][3] = 0.f;
  a[3][3] = 1.0f;
}

/**
 * @details
 * @a a is assigned
 * @code
 * +c -s  0
 * +s +c  0
 *  0  0  1
 * @endcode
 */
INLINE void
rotate_z_m3x3f32
  (
    SQUAREMATRIX3X3F32 a,
    Ring2_Real32 d
  )
{
  Ring2_Real32 c = cosf(d),
               s = sinf(d);
  a[0][0] = +c;
  a[1][0] = +s;
  a[2][0] = 0.f;

  a[0][1] = -s;
  a[1][1] = +c;
  a[2][1] = 0.f;

  a[0][2] = 0.f;
  a[1][2] = 0.f;
  a[2][2] = 1.f;
}

#undef INLINE
