// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring3/Math/ColorRgbaU8.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#include "Ring3/Math/ColorRgbaU8.h"


#include "Ring2/Library/ArgumentsUtilities.h"


#define With_getHashValue (0)


static void
Ring3_Math_ColorRgbaU8_construct
  (
    Ring3_Math_ColorRgbaU8* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );
  
static Ring1_CheckReturn() Ring2_Boolean
isEqualToImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaU8 const* self,
    Ring2_Value const* other
  );

#if !defined(With_getHashValue) || 0 == With_getHashValue
static Ring1_CheckReturn() Ring2_Integer
getHashValueImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaU8 const* self
  );
#endif

static void
Ring3_Math_ColorRgbaU8_construct
  (
    Ring3_Math_ColorRgbaU8* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  );
  
static void
Ring3_Math_ColorRgbaU8_Class_construct
  (
    Ring3_Math_ColorRgbaU8_Class *self
  );

static uint8_t
getComponentArgument
  (
    size_t numberOfArguments,
    Ring2_Value const *arguments,
    size_t index
  );


struct Ring3_Math_ColorRgbaU8 {
  Machine_Object parent;
  uint8_t red, green, blue, alpha;
};

struct Ring3_Math_ColorRgbaU8_Class {
  Machine_Object_Class parent;
};


MACHINE_DEFINE_CLASSTYPE(Ring3_Math_ColorRgbaU8 /*type*/,
                         Machine_Object /*parentType*/,
                         NULL,
                         &Ring3_Math_ColorRgbaU8_construct,
                         NULL,
                         &Ring3_Math_ColorRgbaU8_Class_construct,
                         NULL)


static uint8_t
getComponentArgument
  (
    size_t numberOfArguments,
    Ring2_Value const *arguments,
    size_t index
  )
{
  Ring2_Integer v = Machine_Extensions_getIntegerArgument(numberOfArguments, arguments, index);
  if (v < 0 || v > UINT8_MAX) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return (uint8_t)v;
}

static void
Ring3_Math_ColorRgbaU8_construct
  (
    Ring3_Math_ColorRgbaU8* self,
    size_t numberOfArguments,
    const Ring2_Value* arguments
  )
{
  Machine_Object_construct(Ring1_cast(Machine_Object*, self), numberOfArguments, arguments);
  self->red = getComponentArgument(numberOfArguments, arguments, 0);
  self->green = getComponentArgument(numberOfArguments, arguments, 1);
  self->blue = getComponentArgument(numberOfArguments, arguments, 2);
  self->alpha = getComponentArgument(numberOfArguments, arguments, 3);
  Machine_setClassType(Ring1_cast(Machine_Object*, self), Ring3_Math_ColorRgbaU8_getType());
}

static Ring1_CheckReturn() Ring2_Boolean
isEqualToImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaU8 const* self,
    Ring2_Value const* other
  )
{
  if (Ring1_Unlikely(!self || !other)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  if (!Ring2_Value_isObject(other)) {
    return false;
  }
  Machine_Object *o1 = Ring2_Value_getObject(other);
  if (((Machine_Object *)self) == o1) {
    return true;
  }
  if (Machine_Type_isSubTypeOf((Machine_Type *)Machine_getClassType(o1), (Machine_Type *)Ring3_Math_ColorRgbaU8_getType())) {
    Ring3_Math_ColorRgbaU8* o2 = (Ring3_Math_ColorRgbaU8*)o1;
    return self->red == o2->red
        && self->green == o2->green
        && self->blue == o2->blue
        && self->alpha == o2->alpha;
  } else {
    return false;
  }
}

#if defined(With_getHashValue) && 1 == With_getHashValue
static Ring1_CheckReturn() Ring2_Integer
getHashValueImpl
  (
    Ring2_Context *context,
    Ring3_Math_ColorRgbaU8 const* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  uint64_t r = (uint64_t)self->red;
  uint64_t g = (uint64_t)self->green;
  uint64_t b = (uint64_t)self->blue;
  uint64_t a = (uint64_t)self->alpha;
  return r << 24
      || g << 16
      || b << 7
      || a << 0;
}
#endif

static void
Ring3_Math_ColorRgbaU8_Class_construct
  (
    Ring3_Math_ColorRgbaU8_Class *self
  )
{
  ((Machine_Object_Class *)self)->isEqualTo = (Ring2_Boolean (*)(Ring2_Context *, Machine_Object const *, Ring2_Value const *)) & isEqualToImpl;
#if defined(With_getHashValue) && 1 == With_getHashValue
  ((Machine_Object_Class *)self)->getHashValue = (Ring2_Integer (*)(Ring2_Context *, Machine_Object const*)) & getHashValueImpl;
#endif
}

#if 1
Ring1_CheckReturn() Ring3_Math_ColorRgbaU8 *
Ring3_Math_ColorRgbaU8_create
  (
    uint8_t red,
    uint8_t green,
    uint8_t blue,
    uint8_t alpha
  )
{
  Machine_ClassType* ty = Ring3_Math_ColorRgbaU8_getType();

  static const size_t NUMBER_OF_ARGUMENTS = 4;
  Ring2_Value ARGUMENTS[4] = {
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
    { Ring2_Value_Tag_Void, Ring2_Void_Void },
  };
  Ring2_Value_setInteger(&ARGUMENTS[0], red);
  Ring2_Value_setInteger(&ARGUMENTS[1], green);
  Ring2_Value_setInteger(&ARGUMENTS[2], blue);
  Ring2_Value_setInteger(&ARGUMENTS[3], alpha);
  Ring3_Math_ColorRgbaU8* self = (Ring3_Math_ColorRgbaU8*)Machine_allocateClassObject(ty, NUMBER_OF_ARGUMENTS, ARGUMENTS);
  return self;
}
#endif

#if 1
Ring1_CheckReturn() Ring3_Math_ColorRgbaU8 *
Ring3_Math_ColorRgbaU8_clone
  (
    Ring3_Math_ColorRgbaU8 *self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return Ring3_Math_ColorRgbaU8_create(self->red, self->green, self->blue, self->alpha);
}
#endif

Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getRed
  (
    Ring3_Math_ColorRgbaU8* self
  )
{ 
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->red;
}

Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getGreen
  (
    Ring3_Math_ColorRgbaU8* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->green;
}

Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getBlue
  (
    Ring3_Math_ColorRgbaU8* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->blue;
}

Ring1_CheckReturn() uint8_t
Ring3_Math_ColorRgbaU8_getAlpha
  (
    Ring3_Math_ColorRgbaU8* self
  )
{
  if (Ring1_Unlikely(!self)) {
    Ring1_Status_set(Ring1_Status_InvalidArgument);
    Ring2_jump();
  }
  return self->alpha;
}
