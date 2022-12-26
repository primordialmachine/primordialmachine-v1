#include "Ring1/All/_Include.h"
#include <math.h>

#if defined(INLINE)
  #error("symbol INLINE already defined")
#endif
#define INLINE static inline

typedef float VECTOR[];

/**
 * @param source the source vector
 * @param target the target vector
 * @detail target[i] is assigned source
 */
INLINE void copy_vv_f32(VECTOR const source, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source[i];
  }  
}

/**
 * @param source1, source2 the source vectors
 * @param target the target vector
 * @detail target[i] is assigned add(source1[i], source2[i])
 */
INLINE void add_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source1[i] + source2[i];
  }
}

/**
 * @param source1, source2 the source vectors
 * @param target the target vector
 * @detail
 * target[i] is assigned sub(source1[i], source2[i])
 */
INLINE void sub_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source1[i] - source2[i];
  }
}

/**
 * @param source1, source2 the source vectors
 * @param target the target vector
 * @detail
 * target[i] is assigned mul(source1[i], source2[i])
 */
INLINE void mul_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source1[i] * source2[i];
  }
}

/**
 * @param source1 the source vector
 * @param source2 the source scalar
 * @param target the target vector
 * @detail
 * target[i] is assigned mul(source1[i], source2)
 */
INLINE void mul_vs_f32(VECTOR const source1, float const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source1[i] / source2;
  }
}


/**
 * @param source1, source2 the source vectors
 * @param target the target vector
 * @detail
 * target[i] is assigned div(source1[i], source2[i])
 */
INLINE void div_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source1[i] / source2[i];
  }
}

/**
 * @param source1 the source vector
 * @param source2 the source scalar
 * @param target the target vector
 * @detail
 * target[i] is assigned div(source1[i], source2)
 */
INLINE void div_vs_f32(VECTOR const source1, float const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    target[i] = source1[i] / source2;
  }
}

/**
 * @param source1, source2 the source vectors
 * @param target the target scalar
 * @detail
 * target is assigned dot(source1, source2])
 */
INLINE void dot_vv_f32(VECTOR const source1, VECTOR const source2, float *target, size_t n) {
  *target = 0;
  for (size_t i = 0; i < n; ++i) {
    *target += source1[i] * source2[i];
  }
}

/**
 * @param source1, source2 the source vectors
 * @param target the target vector
 * @detail
 * target[i] is assigned min(source1[i], source2[i])
 */
INLINE void min_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (source1[i] < source2[i]) {
      target[i] = source1[i];
    }
    else {
      target[i] = source2[i];
    }
  }
}

/**
 * @param source1, source2 the source vectors
 * @param target the target vector
 * @detail
 * target[i] is assigned max(source1[i], source2[i])
 */
INLINE void max_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (source1[i] > source2[i]) {
      target[i] = source1[i];
    }
    else {
      target[i] = source2[i];
    }
  }
}

/**
 * @param source1, source2 the source vectors
 * @param target1, target2 the target vectors
 * @detail
 * target1[i] is assigned min(source1[i], source2[i])
 * target2[i] is assigned max(source1[i], source2[i])
 */
INLINE void minMax_vv_f32(VECTOR const source1, VECTOR const source2, VECTOR target1, VECTOR target2, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    if (source1[i] < source2[i]) {
      target1[i] = source1[i];
      target2[i] = source2[i];
    } else {
      target1[i] = source2[i];
      target2[i] = source1[i];
    }
  }
}

/**
 * @param source the source vector
 * @param target the target scalar
 * @detail
 * target is assigned l(source)^2
 */
INLINE void squaredLength_vs_f32(VECTOR const source, float *target, size_t n) {
  float t = 0.f;
  for (size_t i = 0; i < n; ++i) {
    t += source[i] * source[i];
  }
  (*target) = t;
}

/**
 * @param source the source vector
 * @param target the target scalar
 * @detail
 * target is assigned l(source)
 */
INLINE void length_vs_f32(VECTOR const source, float* target, size_t n) {
  float t;
  squaredLength_vs_f32(source, &t, n);
  *target = sqrtf(t);
}

/** 
 * @param source1, source2 the source vectors
 * @param absolute, relative the absolute tolerance and the relative tolerance
 */
INLINE void areEqualToWithTolerance_vv_f32(VECTOR const source1, VECTOR const source2, float const absolute, float const relative, bool *areEqual, size_t n) {
  if (source1 == source2) {
    *areEqual = true;
    return;
  }
  for (size_t i = 0; i < n; ++i) {
    bool equal;
    if (Ring1_Fp_equalToWithTolerance_f32(&equal, source1[i], source2[i], absolute, relative)) {
      Ring2_jump();
    }
    if (!equal) {
      *areEqual = false;
      return;
    }
  }
  *areEqual = true;
  return;  
}

#undef INLINE
