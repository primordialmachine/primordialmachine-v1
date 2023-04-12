/// @@file Ring3/Math/Ray@(dimensionality)@(scalarTypeSuffix).c
/// @@copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @@author Michael Heilmann (michaelheilmann@@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Ray@(dimensionality)@(scalarTypeSuffix).h"
#undef RING3_MATH_PRIVATE

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector@(dimensionality)@(scalarTypeSuffix).h"
#undef RING3_MATH_PRIVATE

#define RING3_MATH_RAY_DIMENSIONALITY (@(dimensionality))

static void
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_construct
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->origin =
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_clone
      (
        (Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *)
        Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getType())
      );
  self->direction =
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_clone
      (
        (Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *)
        Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1, Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_getType())
      );
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix),
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_create
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* origin,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* direction
  )
{
  Machine_Type* ty = Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_getType();
  static size_t const NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setObject(&arguments[0], Ring1_cast(Machine_Object*,origin));
  Ring2_Value_setObject(&arguments[1], Ring1_cast(Machine_Object*,direction));
  Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)* self = Ring1_cast(Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)*,
                                                                        Machine_allocateClassObject(ty,
                                                                                                    NUMBER_OF_ARGUMENTS,
                                                                                                    arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_createFromPoints
  (
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* a,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* b
  )
{

  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *c = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_difference(a, b);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_normalize(c);
  return Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_create(a, c);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_getPoint
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)* self,
    Ring2_Real32 t
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  /// @@todo Repeated normalization might cause "direction" to mutate with each normalization due to numeric imprecisions.
  /// Cache if "direction" is normalized.
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_normalizeInSitu(self->direction);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* p = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiplyScalar(self->direction, t);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_add(self->origin, p, p);
  return p;
}

/// @@section Geode interface
/// @@{

Ring1_NoDiscardReturn() Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_clone
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix) const* self
  )
{
  return Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_create(self->origin, self->direction);
}

Ring1_NoDiscardReturn() Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)*
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_translate
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix) *self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *transform
  )
{
  Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)* clone = Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_clone(self);
  Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_translateInSitu(clone, transform);
  return clone;
}

void
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_translateInSitu
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix) *self,
    Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix) *transform
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_add(self->origin, transform, self->origin);
}

void
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_uniformScaleInSitu
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)* self,
    @(scalarType) scaling
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* newOrigin = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiplyScalar(self->origin, scaling);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)* newDirection = Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_sum(self->origin, self->direction);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_multiplyScalarInSitu(newDirection, scaling);
  Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_subtract(newDirection, newOrigin, newDirection);
  self->origin = newOrigin;
  self->direction = newDirection;
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance
  (
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix) const* self,
    Ring3_Math_Ray@(dimensionality)@(scalarTypeSuffix) const* other,
    @(scalarType) absolute,
    @(scalarType) relative
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (self == other) {
    return true;
  }
  return Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance(self->origin, other->origin, absolute, relative)
      && Ring3_Math_Vector@(dimensionality)@(scalarTypeSuffix)_isEqualToWithTolerance(self->direction, other->direction, absolute, relative);
}

/// @@}
