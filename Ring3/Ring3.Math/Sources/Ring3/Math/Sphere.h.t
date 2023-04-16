#if !defined(RING3_MATH_SPHERE@(dimensionality)@(scalarTypeSuffixUppercase)_H_INCLUDED)
#define RING3_MATH_SPHERE@(dimensionality)@(scalarTypeSuffixUppercase)_H_INCLUDED

#include "Ring3/Math/Vector@(dimensionality)@(scalarTypeSuffix).h"

#define RING3_MATH_SPHERE_DIMENSIONALITY @(dimensionality)

MACHINE_DECLARE_CLASSTYPE(Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix))

struct Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_Class {
  Machine_Object_Class parent;
};

struct Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) {
  Machine_Object parent;
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *center;
  @(scalarType) radius;
};

/// @@brief Construct this sphere with the specified center and radius.
/// @@param self This sphere.
/// @@param center The center of the sphere. A copy is stored.
/// @@param radius The radius of the sphere.
/// @@error Ring1_Status_InvalidArgument @@a radius is negative
void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_construct
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) *self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

Ring1_NoDiscardReturn() Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_create
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *center,
    @(scalarType) radius
  );

/// @@brief Get the radius of this sphere.
/// @@param self This sphere.
/// @@return The radius of this sphere.
Ring1_NoDiscardReturn() @(scalarType)
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_getRadius
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) *self
  );

/// @@brief Get the center of this sphere.
/// @@param self This sphere.
/// @@return The center of this sphere. A copy is returned.
Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_getCenter
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self
  );

#if 2 <= RING3_MATH_SPHERE_DIMENSIONALITY && RING3_MATH_SPHERE_DIMENSIONALITY <= 3

/// https://primordialmachine.com/reference/transformations/spheres
void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_uniformScale
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) *self,
    Ring2_Real32 s
  );
  
#endif
 
/// @@section Geode interface
/// @@{

/// @@brief Clone this sphere.
/// @@param self This sphere.
/// @@return The clone of this sphere.
Ring1_NoDiscardReturn() Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_clone
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) const* self
  );

/// @@brief Translate this sphere.
/// @@param self This sphere.
/// @@param translation The translation transformation vector.
/// @@return A copy of this sphere transformed.
/// https://primordialmachine.com/reference/transformations/spheres
Ring1_NoDiscardReturn() Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_translate
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* translation
  );

/// @@brief Translate this sphere.
/// @@param self This sphere.
/// @@param translation The translation transformation vector.
void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_translateInSitu
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* translation
  );
  
/// @@brief Uniform scale this sphere.
/// @@param self This sphere.
/// @@param scaling The scaling transformation scalar. Must not be @@a 0.
/// https://primordialmachine.com/reference/transformations/spheres
/// @@warning Numeric imprecisions can cause a Geode object to assume invalid numeric values.
void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_uniformScaleInSitu
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self,
    @(scalarType) scaling
  );

/// @@brief Compare this sphere and another sphere with tolerance.
/// @@param self This sphere.
/// @@param other The other sphere.
/// @@param absolute, relative The absolute tolerance and the relative tolerance. Must be non-negative.
/// @@return @@a true if the spheres are equal. @@a false otherwise.
/// @@remark See Ring1_Fp_equalToWithTolerance_f32 for information the comparison function.
Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) const* other,
    @(scalarType) absolute,
    @(scalarType) relative
  );
  
/// @@}
  
#undef RING3_MATH_SPHERE_DIMENSIONALITY

#endif // RING3_MATH_SPHERE@(dimensionality)@(scalarTypeSuffixUppercase)_H_INCLUDED
