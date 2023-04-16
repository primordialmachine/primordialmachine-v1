/// @file Ring3/Math/Sphere3f32.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Sphere3f32.h"
#undef RING3_MATH_PRIVATE

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Sphere3f32,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Sphere3f32_construct,
                         NULL,
                         NULL,
                         NULL)

void
Ring3_Math_Sphere3f32_construct
  (
    Ring3_Math_Sphere3f32 *self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->center = Ring3_Math_Vector3f32_clone((Ring3_Math_Vector3f32*)Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Ring3_Math_Vector3f32_getType()));
  self->radius = Ring2_CallArguments_getReal32Argument(numberOfArguments, arguments, 1);
  if (self->radius < 0) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Sphere3f32_getType());
}

Ring1_NoDiscardReturn() Ring3_Math_Sphere3f32*
Ring3_Math_Sphere3f32_create
  (
    Ring3_Math_Vector3f32 *center,
    Ring2_Real32 radius
  )
{
  Machine_Type* ty = Ring3_Math_Sphere3f32_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,center));
  Ring2_Value_setReal32(&arguments[1], radius);
  Ring3_Math_Sphere3f32* self = Ring1_cast(Ring3_Math_Sphere3f32*,
                                                                           Machine_allocateClassObject(ty,
                                                                                                       NUMBER_OF_ARGUMENTS,
                                                                                                       arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring2_Real32
Ring3_Math_Sphere3f32_getRadius
  (
    Ring3_Math_Sphere3f32* self
  )
{ return self->radius; }

Ring1_NoDiscardReturn() Ring3_Math_Vector3f32*
Ring3_Math_Sphere3f32_getCenter
  (
    Ring3_Math_Sphere3f32 *self
  )
{ return Ring3_Math_Vector3f32_clone(self->center); }

/// @section Geode interface
/// @{

Ring1_NoDiscardReturn() Ring3_Math_Sphere3f32*
Ring3_Math_Sphere3f32_clone
  (
    Ring3_Math_Sphere3f32 const* self
  )
{
  return Ring3_Math_Sphere3f32_create(self->center, self->radius);
}

Ring1_NoDiscardReturn() Ring3_Math_Sphere3f32*
Ring3_Math_Sphere3f32_translate
  (
    Ring3_Math_Sphere3f32* self,
    Ring3_Math_Vector3f32* translation
  )
{
  Ring3_Math_Sphere3f32* clone = Ring3_Math_Sphere3f32_clone(self);
  Ring3_Math_Sphere3f32_translateInSitu(clone, translation);
  return clone;
}

void
Ring3_Math_Sphere3f32_translateInSitu
  (
    Ring3_Math_Sphere3f32* self,
    Ring3_Math_Vector3f32* translation
  )
{ Ring3_Math_Vector3f32_add(self->center, translation, self->center); }

void
Ring3_Math_Sphere3f32_uniformScaleInSitu
  (
    Ring3_Math_Sphere3f32 *self,
    Ring2_Real32 s
  )
{
  Ring3_Math_Vector3f32_multiplyScalarInSitu(self->center, s);
  self->radius *= fabs(s);
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Sphere3f32_isEqualToWithTolerance
  (
    Ring3_Math_Sphere3f32 const* self,
    Ring3_Math_Sphere3f32 const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
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
  if (Ring1_Fp_equalToWithTolerance_f32(&equal, self->radius, other->radius, absolute, relative)) {
    Ring2_jump();
  }
  return Ring3_Math_Vector3f32_isEqualToWithTolerance(self->center, other->center, absolute, relative)
      && equal;
}

/// @}
