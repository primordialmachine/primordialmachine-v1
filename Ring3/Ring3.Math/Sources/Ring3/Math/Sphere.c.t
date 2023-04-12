/// @@file Ring3/Math/Sphere@(dimensionality)@(scalarTypeSuffix).c
/// @@copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @@author Michael Heilmann (michaelheilmann@@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Sphere@(dimensionality)@(scalarTypeSuffix).h"
#undef RING3_MATH_PRIVATE

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix),
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_construct
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) *self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->center = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_clone((Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*)Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getType()));
  self->radius = Ring2_CallArguments_getReal32Argument(numberOfArguments, arguments, 1);
  if (self->radius < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_getType());
}

Ring1_NoDiscardReturn() Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_create
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *center,
    Ring2_Real32 radius
  )
{
  Machine_Type* ty = Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,center));
  Ring2_Value_setReal32(&arguments[1], radius);
  Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self = Ring1_cast(Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*,
                                                                           Machine_allocateClassObject(ty,
                                                                                                       NUMBER_OF_ARGUMENTS,
                                                                                                       arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_getRadius
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self
  )
{ return self->radius; }

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_getCenter
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) *self
  )
{ return Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_clone(self->center); }

/// @@section Geode interface
/// @@{

Ring1_NoDiscardReturn() Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_clone
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) const* self
  )
{
  return Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_create(self->center, self->radius);
}

Ring1_NoDiscardReturn() Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_translate
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* translation
  )
{
  Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* clone = Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_clone(self);
  Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_translateInSitu(clone, translation);
  return clone;
}

void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_translateInSitu
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)* self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* translation
  )
{ Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_add(self->center, translation, self->center); }

void
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_uniformScaleInSitu
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) *self,
    @(scalarType) s
  )
{
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiplyScalarInSitu(self->center, s);
  self->radius *= fabs(s);
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance
  (
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Sphere@(dimensionality)@(scalarTypeSuffix) const* other,
    @(scalarType) absolute,
    @(scalarType) relative
  )
{
  if (!self || !other) { 
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (self == other) {
    return true;
  }
  bool equal;
  if (Ring1_Fp_equalToWithTolerance_@(scalarTypeSuffix)(&equal, self->radius, other->radius, absolute, relative)) {
    Ring2_jump();
  }
  return Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance(self->center, other->center, absolute, relative)
      && equal;
}

/// @@}
