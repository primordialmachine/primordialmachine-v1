// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Color/RgbaF64.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING3_MATH_PRIVATE (1)
#include "Ring3/Math/ColorRgbaF64.h"
#undef RING3_MATH_PRIVATE


#define With_getHashValue (0)


static void
Ring3_Math_ColorRgbaF64_construct
  (
    Ring3_Math_ColorRgbaF64* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );

static Ring1_CheckReturn() Ring2_Boolean
isEqualToImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaF64 const* self,
    Ring2_Value const* other
  );

#if defined(With_getHashValue) && 1 == With_getHashValue
static Ring1_CheckReturn() Ring2_Integer
getHashValueImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaF64 const* self
  );
#endif

static void
Ring3_Math_ColorRgbaF64_construct
  (
    Ring3_Math_ColorRgbaF64* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );

static void
Ring3_Math_ColorRgbaF64_Class_construct
  (
    Ring3_Math_ColorRgbaF64_Class *self
  );

// Raises an error if the argument's value is "no number".
// Clamps the argument's vallue to the interval @code{[0,1]} if it's not within that interval.
static Ring2_Real64
getComponentArgument
  (
    size_t numberOfArguments,
    Ring2_Value const *arguments,
    size_t index
  );


struct Ring3_Math_ColorRgbaF64 {
  Machine_Object parent;
  double red, green, blue, alpha;
};

struct Ring3_Math_ColorRgbaF64_Class {
  Machine_Object_Class parent;
};


MACHINE_DEFINE_CLASSTYPE(Ring3_Math_ColorRgbaF64 /*type*/,
                         Machine_Object /*parentType*/,
                         NULL,
                         &Ring3_Math_ColorRgbaF64_construct,
                         NULL,
                         &Ring3_Math_ColorRgbaF64_Class_construct,
                         NULL)


static Ring2_Real64
getComponentArgument
  (
    size_t numberOfArguments,
    Ring2_Value const *arguments,
    size_t index
  )
{
  Ring2_Real64 v = Ring2_CallArguments_getReal64Argument(numberOfArguments, arguments, index);
  if (isnan(v)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (v < 0.) {
    v = 0.f;
  } else {
    v = 1.f;
  }
  return v;
}

static void
Ring3_Math_ColorRgbaF64_construct
  (
    Ring3_Math_ColorRgbaF64* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->red = getComponentArgument(numberOfArguments, arguments, 0);
  self->green = getComponentArgument(numberOfArguments, arguments, 1);
  self->blue = getComponentArgument(numberOfArguments, arguments, 2);
  self->alpha = getComponentArgument(numberOfArguments, arguments, 3);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Math_ColorRgbaF64_getType());
}

static Ring1_CheckReturn() Ring2_Boolean
isEqualToImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaF64 const* self,
    Ring2_Value const* other
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    return Ring1_Result_Failure;
  }
  if (!Ring2_Value_isObject(other)) {
    return false;
  }
  Machine_Object *o1 = Ring2_Value_getObject(other);
  if (((Machine_Object *)self) == o1) {
    return true;
  }
  if (Machine_Type_isSubTypeOf((Machine_Type *)Machine_getClassType(o1), (Machine_Type *)Ring3_Math_ColorRgbaF64_getType())) {
    Ring3_Math_ColorRgbaF64 *o2 = (Ring3_Math_ColorRgbaF64 *)o1;
    return (self->red == o2->red)
        && (self->green == o2->green)
        && (self->blue == o2->blue)
        && (self->alpha == o2->alpha);
  } else {
    return false;
  }
}

#if defined(With_getHashValue) && 1 == With_getHashValue
static Ring1_CheckReturn() Ring2_Integer
getHashValueImpl
  (
    Ring3_Math_ColorRgbaF64 const* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  uint64_t r, g, b, a;
  if (Ring1_Fp_getBits_f64(&r, self->red) ||
      Ring1_Fp_getBits_f64(&g, self->green) ||
      Ring1_Fp_getBits_f64(&b, self->blue) ||
      Ring1_Fp_getBits_f64(&a, self->alpha)) {
    Ring2_jump();
  }
  return r
       ^ g
       ^ b
       ^ a;
}
#endif

static void
Ring3_Math_ColorRgbaF64_Class_construct
  (
    Ring3_Math_ColorRgbaF64_Class *self
  )
{
  ((Machine_Object_Class *)self)->isEqualTo = (Ring2_Boolean (*)(Ring2_Context *, Machine_Object const *, Ring2_Value const *)) & isEqualToImpl;
#if defined(With_getHashValue) && 1 == With_getHashValue
  ((Machine_Object_Class *)self)->getHashValue = (Ring2_Integer (*)(Ring2_Context *, Machine_Object const *)) & getHashValueImpl;
#endif
}

#if 1
Ring1_CheckReturn() Ring3_Math_ColorRgbaF64 *
Ring3_Math_ColorRgbaF64_create
  (
    double red,
    double green,
    double blue,
    double alpha
  )
{
  Machine_ClassType* ty = Ring3_Math_ColorRgbaF64_getType();

  static const size_t NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value ARGUMENTS[4] = {
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
  };
  Ring2_Value_setReal64(&ARGUMENTS[0], red);
  Ring2_Value_setReal64(&ARGUMENTS[1], green);
  Ring2_Value_setReal64(&ARGUMENTS[2], blue);
  Ring2_Value_setReal64(&ARGUMENTS[3], alpha);
  Ring3_Math_ColorRgbaF64* self = (Ring3_Math_ColorRgbaF64*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
#endif

#if 1
Ring1_CheckReturn() Ring3_Math_ColorRgbaF64 *
Ring3_Math_ColorRgbaF64_clone
  (
    Ring3_Math_ColorRgbaF64 *self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return Ring3_Math_ColorRgbaF64_create(self->red, self->green, self->blue, self->alpha);
}
#endif

Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getRed
  (
    Ring3_Math_ColorRgbaF64* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->red;
}

Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getGreen
  (
    Ring3_Math_ColorRgbaF64* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->green;
}

Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getBlue
  (
    Ring3_Math_ColorRgbaF64* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->blue;
}

Ring1_CheckReturn() Ring2_Real64
Ring3_Math_ColorRgbaF64_getAlpha
  (
    Ring3_Math_ColorRgbaF64* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->alpha;
}
