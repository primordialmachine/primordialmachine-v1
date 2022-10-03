// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Operations/Value.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Operations/Value.h"

#include "Ring1/Status.h"
#include "Ring2/Operations.h"
#include "Ring2/JumpTarget.h"
#include "Ring2/Gc.h"

Ring1_CheckReturn() Ring2_Boolean
Ring2_Value_isEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  case Ring2_Value_Tag_Array: {
    if (!Ring2_Value_isArray(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Array_isEqualTo(context, Ring2_Value_getArray(x), Ring2_Value_getArray(y));
  } break;
#endif
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  case Ring2_Value_Tag_Boolean: {
    if (!Ring2_Value_isBoolean(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Boolean_isEqualTo(context, Ring2_Value_getBoolean(x), Ring2_Value_getBoolean(y));
  } break;
#endif
#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure
  case Ring2_Value_Tag_ForeignProcedure: {
    if (!Ring2_Value_isForeignProcedure(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_ForeignProcedure_isEqualTo(context, Ring2_Value_getForeignProcedure(x), Ring2_Value_getForeignProcedure(y));
  } break;
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  case Ring2_Value_Tag_Integer: {
    if (!Ring2_Value_isInteger(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Integer_isEqualTo(context, Ring2_Value_getInteger(x), Ring2_Value_getInteger(y));
  } break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object: {
    if (!Ring2_Value_isObject(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Machine_Object_isEqualTo(context, Ring2_Value_getObject(x), y);
  } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  case Ring2_Value_Tag_Real64: {
    if (!Ring2_Value_isReal64(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Real64_isEqualTo(context, Ring2_Value_getReal64(x), Ring2_Value_getReal64(y));
  } break;
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  case Ring2_Value_Tag_String: {
    if (!Ring2_Value_isString(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_String_isEqualTo(context, Ring2_Value_getString(x), Ring2_Value_getString(y));
  } break;
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  case Ring2_Value_Tag_Void: {
    if (!Ring2_Value_isVoid(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Void_isEqualTo(context, Ring2_Value_getVoid(x), Ring2_Value_getVoid(y));
  } break;
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidArgumentType);
    Ring2_jump();
  } break;
  };
}

Ring1_CheckReturn() Ring2_Boolean
Ring2_Value_isNotEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  case Ring2_Value_Tag_Array: {
    if (!Ring2_Value_isArray(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Array_isNotEqualTo(context, Ring2_Value_getArray(x), Ring2_Value_getArray(y));
  } break;
#endif
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  case Ring2_Value_Tag_Boolean: {
    if (!Ring2_Value_isBoolean(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Boolean_isNotEqualTo(context, Ring2_Value_getBoolean(x), Ring2_Value_getBoolean(y));
  } break;
#endif
#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure
  case Ring2_Value_Tag_ForeignProcedure: {
    if (!Ring2_Value_isForeignProcedure(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_ForeignProcedure_isNotEqualTo(context, Ring2_Value_getForeignProcedure(x), Ring2_Value_getForeignProcedure(y));
  } break;
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  case Ring2_Value_Tag_Integer: {
    if (!Ring2_Value_isInteger(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Integer_isNotEqualTo(context, Ring2_Value_getInteger(x), Ring2_Value_getInteger(y));
  } break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object: {
    if (!Ring2_Value_isObject(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Machine_Object_isNotEqualTo(context, Ring2_Value_getObject(x), y);
  } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  case Ring2_Value_Tag_Real64: {
    if (!Ring2_Value_isReal64(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Real64_isNotEqualTo(context, Ring2_Value_getReal64(x), Ring2_Value_getReal64(y));
  } break;
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  case Ring2_Value_Tag_String: {
    if (!Ring2_Value_isString(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_String_isNotEqualTo(context, Ring2_Value_getString(x), Ring2_Value_getString(y));
  } break;
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  case Ring2_Value_Tag_Void: {
    if (!Ring2_Value_isVoid(x)) {
      Ring1_Status_set(Ring1_Status_InvalidArgumentType);
      Ring2_jump();
    }
    return Ring2_Void_isNotEqualTo(context, Ring2_Value_getVoid(x), Ring2_Value_getVoid(y));
  } break;
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}

Ring1_Intrinsic_Deprecated()
#define Define_v1(Type, Operation) \
  case Ring2_Value_Tag_##Type: { \
    if (!Ring2_Value_is##Type(y)) { \
      Ring1_Status_set(Ring1_Status_InvalidArgumentType); \
      Ring2_jump(); \
    } \
    Ring2_Value_setBoolean \
      ( \
        z, \
        Ring2_##Type##_##Operation \
          ( \
            context, \
            Ring2_Value_get##Type(x), \
            Ring2_Value_get##Type(y) \
          ) \
      ); \
  } break;

#define Define_v2(Type, Operation) \
  case Ring2_Value_Tag_##Type: { \
    if (!Ring2_Value_is##Type(y)) { \
      Ring1_Status_set(Ring1_Status_InvalidArgumentType); \
      Ring2_jump(); \
    } \
    Ring2_##Type##_##Operation \
      ( \
        context, \
        x, \
        y, \
        z \
      ); \
  } break;

void
Ring2_Value_isLowerThan
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
    Define_v2(Boolean, isLowerThan);
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
    Define_v2(Integer, isLowerThan);
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
    Define_v1(Real64, isLowerThan);
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
    Define_v1(String, isLowerThan);
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
    Define_v1(Void, isLowerThan);
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}

void
Ring2_Value_isLowerThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
    Define_v2(Boolean, isLowerThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
    Define_v2(Integer, isLowerThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
    Define_v1(Real64, isLowerThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
    Define_v1(String, isLowerThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
    Define_v1(Void, isLowerThanOrEqualTo);
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}

void
Ring2_Value_isGreaterThan
  (
    Ring2_Context* context,
    Ring2_Value const* x,
    Ring2_Value const* y,
    Ring2_Value* z
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
    Define_v2(Boolean, isGreaterThan);
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
    Define_v2(Integer, isGreaterThan);
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
    Define_v1(Real64, isGreaterThan);
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
    Define_v1(String, isGreaterThan);
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
    Define_v1(Void, isGreaterThan);
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}

void
Ring2_Value_isGreaterThanOrEqualTo
  (
    Ring2_Context* context,
    Ring2_Value const *x,
    Ring2_Value const *y,
    Ring2_Value *z
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
    Define_v2(Boolean, isGreaterThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
    Define_v2(Integer, isGreaterThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
    Define_v1(Real64, isGreaterThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
    Define_v1(String, isGreaterThanOrEqualTo);
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
    Define_v1(Void, isGreaterThanOrEqualTo);
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}

#undef Define_v2
#undef Define_v1

Ring1_CheckReturn() Ring2_Integer
Ring2_Value_getHashValue
  (
    Ring2_Context* context,
    Ring2_Value const* x
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  case Ring2_Value_Tag_Boolean:
  { return Ring2_Boolean_getHashValue(context, Ring2_Value_getBoolean(x)); } break;
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  case Ring2_Value_Tag_Integer:
  { return Ring2_Integer_getHashValue(context, Ring2_Value_getInteger(x)); } break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object:
  { return Machine_Object_getHashValue(context, Ring2_Value_getObject(x)); } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  case Ring2_Value_Tag_Real64:
  { return Ring2_Real64_getHashValue(context, Ring2_Value_getReal64(x)); } break;
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  case Ring2_Value_Tag_String:
  { return Ring2_String_getHashValue(context, Ring2_Value_getString(x)); } break;
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  case Ring2_Value_Tag_Void:
  { return Ring2_Void_getHashValue(context, Ring2_Value_getVoid(x)); } break;
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}

void
Ring2_Value_toString
  (
    Ring2_Context *context,
    Ring2_Value const *x,
    Ring2_Value *y
  )
{
  switch (Ring2_Value_getTag(x))
  {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  case Ring2_Value_Tag_Array:
  { Ring2_Value_setString(y, Ring2_Array_toString(context, Ring2_Value_getArray(x))); } break;
#endif
#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  case Ring2_Value_Tag_Boolean:
  { Ring2_Value_setString(y, Ring2_Boolean_toString(context, Ring2_Value_getBoolean(x))); } break;
#endif
#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  case Ring2_Value_Tag_Integer:
  { Ring2_Value_setString(y, Ring2_Integer_toString(context, Ring2_Value_getInteger(x))); } break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  case Ring2_Value_Tag_Object:
  { Ring2_Value_setString(y, Machine_Object_toString(context, Ring2_Value_getObject(x))); } break;
#endif
#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  case Ring2_Value_Tag_Real64:
  { Ring2_Value_setString(y, Ring2_Real64_toString(context, Ring2_Value_getReal64(x))); } break;
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  case Ring2_Value_Tag_String:
  { Ring2_Value_setString(y, Ring2_String_toString(context, Ring2_Value_getString(x))); } break;
#endif
#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  case Ring2_Value_Tag_Void:
  { Ring2_Value_setString(y, Ring2_Void_toString(context, Ring2_Value_getVoid(x))); } break;
#endif
  default: {
    Ring1_Status_set(Ring1_Status_InvalidOperation);
    Ring2_jump();
  } break;
  };
}
