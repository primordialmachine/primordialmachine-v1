#if !defined(RING3_MATH_SPHERE2F32_H_INCLUDED)
#define RING3_MATH_SPHERE2F32_H_INCLUDED

#include "Ring3/Math/Vector2f32.h"

#define RING3_MATH_SPHERE_DIMENSIONALITY 2

MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Sphere2f32)

struct Ring3_Math_Sphere2f32_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Sphere2f32 {
  Machine_Object parent;
  Ring3_Math_Vector2f32 *center;
  Ring2_Real32 radius;
};

/// @brief Construct this sphere with the specified center and radius.
/// @param self This sphere.
/// @param center The center of the sphere. A copy is stored.
/// @param radius The radius of the sphere.
/// @error Ring1_Status_InvalidArgument @a radius is negative
void
Ring3_Math_Sphere2f32_construct
  (
    Ring3_Math_Sphere2f32 *self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Math_Sphere2f32*
Ring3_Math_Sphere2f32_create
  (
    Ring3_Math_Vector2f32 *center,
    Ring2_Real32 radius
  );

/// @brief Get the radius of this sphere.
/// @param self This sphere.
/// @return The radius of this sphere.
Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Sphere2f32_getRadius
  (
    Ring3_Math_Sphere2f32 *self
  );

/// @brief Get the center of this sphere.
/// @param self This sphere.
/// @return The center of this sphere. A copy is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Math_Sphere2f32_getCenter
  (
    Ring3_Math_Sphere2f32* self
  );

#if 2 <= RING3_MATH_SPHERE_DIMENSIONALITY && RING3_MATH_SPHERE_DIMENSIONALITY <= 3

/// https://primordialmachine.com/reference/transformations/spheres
void
Ring3_Math_Sphere2f32_uniformScale
  (
    Ring3_Math_Sphere2f32 *self,
    Ring2_Real32 s
  );
  
#endif
 
/// @section Geode interface
/// @{

/// @brief Clone this sphere.
/// @param self This sphere.
/// @return The clone of this sphere.
Ring1_NoDiscardReturn() Ring3_Math_Sphere2f32*
Ring3_Math_Sphere2f32_clone
  (
    Ring3_Math_Sphere2f32 const* self
  );

/// @brief Translate this sphere.
/// @param self This sphere.
/// @param translation The translation transformation vector.
/// @return A copy of this sphere transformed.
/// https://primordialmachine.com/reference/transformations/spheres
Ring1_NoDiscardReturn() Ring3_Math_Sphere2f32*
Ring3_Math_Sphere2f32_translate
  (
    Ring3_Math_Sphere2f32* self,
    Ring3_Math_Vector2f32* translation
  );

/// @brief Translate this sphere.
/// @param self This sphere.
/// @param translation The translation transformation vector.
void
Ring3_Math_Sphere2f32_translateInSitu
  (
    Ring3_Math_Sphere2f32* self,
    Ring3_Math_Vector2f32* translation
  );
  
/// @brief Uniform scale this sphere.
/// @param self This sphere.
/// @param scaling The scaling transformation scalar. Must not be @a 0.
/// https://primordialmachine.com/reference/transformations/spheres
/// @warning Numeric imprecisions can cause a Geode object to assume invalid numeric values.
void
Ring3_Math_Sphere2f32_uniformScaleInSitu
  (
    Ring3_Math_Sphere2f32* self,
    Ring2_Real32 scaling
  );

/// @brief Compare this sphere and another sphere with tolerance.
/// @param self This sphere.
/// @param other The other sphere.
/// @param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @return @a true if the spheres are equal. @a false otherwise.
/// @remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Sphere2f32_isEqualToWithTolerance
  (
    Ring3_Math_Sphere2f32 const* self,
    Ring3_Math_Sphere2f32 const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  );
  
/// @}
  
#undef RING3_MATH_SPHERE_DIMENSIONALITY

#endif // RING3_MATH_SPHERE2F32_H_INCLUDED
