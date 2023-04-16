#include "Ring1/All/_Include.h"
#include <math.h>
#include "Ring3/Math/abs.h"
#include "Ring3/Math/cos.h"
#include "Ring3/Math/sin.h"

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

#include "Ring3/Math/Kernels/Matrix/Ortho.i"
#include "Ring3/Math/Kernels/Matrix/Perspective.i"

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
