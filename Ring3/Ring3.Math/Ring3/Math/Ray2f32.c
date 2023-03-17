/// @file Ring3/Math/Ray2f32.c
/// @copyright Copyright (c) 2021-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Ray2f32.h"
#undef RING3_MATH_PRIVATE

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/Vector2f32.h"
#undef RING3_MATH_PRIVATE

#define RING3_MATH_RAY_DIMENSIONALITY (2)

static void
Ring3_Math_Ray2f32_construct
  (
    Ring3_Math_Ray2f32* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object *, self), numberOfArguments, arguments);
  self->origin =
    Ring3_Math_Vector2f32_clone
      (
        (Ring3_Math_Vector2f32 *)
        Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 0, Ring3_Math_Vector2f32_getType())
      );
  self->direction =
    Ring3_Math_Vector2f32_clone
      (
        (Ring3_Math_Vector2f32 *)
        Ring2_CallArguments_getObjectArgument(numberOfArguments, arguments, 1, Ring3_Math_Vector2f32_getType())
      );
  Machine_setClassType(Ring1_cast(Machine_Object *, self), Ring3_Math_Ray2f32_getType());
}

MACHINE_DEFINE_CLASSTYPE(Ring3_Math_Ray2f32,
                         Machine_Object,
                         NULL,
                         &Ring3_Math_Ray2f32_construct,
                         NULL,
                         NULL,
                         NULL)

Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_create
  (
    Ring3_Math_Vector2f32* origin,
    Ring3_Math_Vector2f32* direction
  )
{
  Machine_Type* ty = Ring3_Math_Ray2f32_getType();
  static const size_t NUMBER_OF_ARGUMENTS = 2;
  Ring2_Value arguments[2];
  Ring2_Value_setObject(&arguments[0], (Machine_Object*)origin);
  Ring2_Value_setObject(&arguments[1], (Machine_Object*)direction);
  Ring3_Math_Ray2f32* self = Ring1_cast(Ring3_Math_Ray2f32*, Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, arguments));
  return self;
}

Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_createFromPoints
  (
    Ring3_Math_Vector2f32* a,
    Ring3_Math_Vector2f32* b
  )
{

  Ring3_Math_Vector2f32 *c = Ring3_Math_Vector2f32_difference(a, b);
  Ring3_Math_Vector2f32_normalize(c);
  return Ring3_Math_Ray2f32_create(a, c);
}

Ring1_NoDiscardReturn() Ring3_Math_Vector2f32*
Ring3_Math_Ray2f32_getPoint
  (
    Ring3_Math_Ray2f32* self,
    Ring2_Real32 t
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  /// @todo Repeated normalization might cause "direction" to mutate with each normalization due to numeric imprecisions.
  /// Cache if "direction" is normalized.
  Ring3_Math_Vector2f32_normalizeInSitu(self->direction);
  Ring3_Math_Vector2f32* p = Ring3_Math_Vector2f32_multiplyScalar(self->direction, t);
  Ring3_Math_Vector2f32_add(self->origin, p, p);
  return p;
}

/// @section Geode interface
/// @{

Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_clone
  (
    Ring3_Math_Ray2f32 const* self
  )
{
  return Ring3_Math_Ray2f32_create(self->origin, self->direction);
}

Ring1_NoDiscardReturn() Ring3_Math_Ray2f32*
Ring3_Math_Ray2f32_translate
  (
    Ring3_Math_Ray2f32 *self,
    Ring3_Math_Vector2f32 *transform
  )
{
  Ring3_Math_Ray2f32* clone = Ring3_Math_Ray2f32_clone(self);
  Ring3_Math_Ray2f32_translateInSitu(clone, transform);
  return clone;
}

void
Ring3_Math_Ray2f32_translateInSitu
  (
    Ring3_Math_Ray2f32 *self,
    Ring3_Math_Vector2f32 *transform
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring3_Math_Vector2f32_add(self->origin, transform, self->origin);
}

void
Ring3_Math_Ray2f32_uniformScaleInSitu
  (
    Ring3_Math_Ray2f32* self,
    Ring2_Real32 scaling
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  Ring3_Math_Vector2f32* newOrigin = Ring3_Math_Vector2f32_multiplyScalar(self->origin, scaling);
  Ring3_Math_Vector2f32* newDirection = Ring3_Math_Vector2f32_sum(self->origin, self->direction);
  Ring3_Math_Vector2f32_multiplyScalarInSitu(newDirection, scaling);
  Ring3_Math_Vector2f32_subtract(newDirection, newOrigin, newDirection);
  self->origin = newOrigin;
  self->direction = newDirection;
}

Ring1_NoDiscardReturn() Ring2_Boolean
Ring3_Math_Ray2f32_isEqualToWithTolerance
  (
    Ring3_Math_Ray2f32 const* self,
    Ring3_Math_Ray2f32 const* other,
    Ring2_Real32 absolute,
    Ring2_Real32 relative
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (self == other) {
    return true;
  }
  return Ring3_Math_Vector2f32_isEqualToWithTolerance(self->origin, other->origin, absolute, relative)
      && Ring3_Math_Vector2f32_isEqualToWithTolerance(self->direction, other->direction, absolute, relative);
}

/// @}
