#if !defined(RING3_MATH_RAY2F32_H_INCLUDED)
#define RING3_MATH_RAY2F32_H_INCLUDED

#include "Ring2/Library/_Include.h"

typedef struct Ring3_Math_Vector2f32 Ring3_Math_Vector2f32;

#define RING3_MATH_RAY_DIMENSIONALITY 2

MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Ray2f32)

struct Ring3_Math_Ray2f32_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Ray2f32 {
  Machine_Object parent;
  Ring3_Math_Vector2f32 *origin;
  Ring3_Math_Vector2f32 *direction;
};

void
Ring3_Math_Ray2f32_construct
  (
    Ring3_Math_Ray2f32 *self,
    size_t numberOfArguments,
    Ring2_Value const *arguments
  );

/// @brief Create a ray.
/// @param origin The origin.
/// @param direction The direction.
/// @return The ray.
/// @remarks
/// @code
/// constructor(Ring3.Math.Vector a, Ring3.Math.Vector b);
/// @endcode
Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_create
  (
    Ring3_Math_Vector2f32 *origin,
    Ring3_Math_Vector2f32 *direction
  );

/// @brief Create a ray given two pointers.
/// @param a, b The point.
/// @return The ray.
/// @remarks
/// @code
/// static Ring3.Math.Ray createFromPoints(Ring3.Math.Vector a, Ring3.Math.Vector b);
/// @endcode
Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_createFromPoints
  (
    Ring3_Math_Vector2f32 *a,
    Ring3_Math_Vector2f32 *b
  );

/// @brief Compute the point at \(O + t \hat{d}\) for \(t = 0\).
/// @param self This ray.
/// @return The point.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Math_Ray2f32_getPoint
  (
    Ring3_Math_Ray2f32 *self,
    Ring2_Real32 t
  );

/// @section Geode interface
/// @{

/// @brief Clone this ray.
/// @param self This ray.
/// @return The clone of this ray.
Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_clone
  (
    Ring3_Math_Ray2f32 const* self
  );

/// @brief Translate this ray.
/// @param self This ray.
/// @param translation The translation transformation vector.
/// @return A copy of this ray transformed.
/// https://primordialmachine.com/reference/transformations/rays
Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_translate
  (
    Ring3_Math_Ray2f32 *self,
    Ring3_Math_Vector2f32 *transform
  );
  
/// @brief Translate this ray.
/// @param self This ray.
/// @param translation The translation transformation vector.
/// https://primordialmachine.com/reference/transformations/rays
void
Ring3_Math_Ray2f32_translateInSitu
  (
    Ring3_Math_Ray2f32* self,
    Ring3_Math_Vector2f32* transform
  );

/// @brief Uniform scale this ray.
/// @param self This ray.
/// @param scaling The scaling transformation scalar. Must not be @a 0.
/// https://primordialmachine.com/reference/transformations/rays
/// @warning Numeric imprecisions can cause a Geode object to assume invalid numeric values.
void
Ring3_Math_Ray2f32_uniformScaleInSitu
  (
    Ring3_Math_Ray2f32* self,
    Ring2_Real32 scaling
  );

/// @brief Compare this ray and another ray with tolerance.
/// @param self This ray.
/// @param other The other ray.
/// @param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @return @a true if the vectors are equal. @a false otherwise.
/// @remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() bool
Ring3_Math_Ray2f32_isEqualToWithTolerance
  (
    Ring3_Math_Ray2f32 const* self,
    Ring3_Math_Ray2f32 const* other,
     Ring2_Real32 absolute,
     Ring2_Real32 relative
  );
  
/// @}

#undef RING3_MATH_RAY_DIMENSIONALITY

#endif // RING3_MATH_RAY2F32_H_INCLUDED
