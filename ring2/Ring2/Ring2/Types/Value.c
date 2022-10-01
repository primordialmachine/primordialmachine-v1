// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Value.c
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#define RING2_INTERNAL (1)
#include "Ring2/Types/Value.h"
#include "Ring2/_Include.h"

#if defined (Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

Ring1_CheckReturn() Ring2_Array*
Ring2_Value_getArray
  (
    Ring2_Value const* value
  )
{ return value->arrayValue; }

Ring1_CheckReturn() bool
Ring2_Value_isArray
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Array; }

void
Ring2_Value_setArray
  (
    Ring2_Value* value,
    Ring2_Array* arrayValue
  )
{
  value->tag = Ring2_Value_Tag_Array;
  value->arrayValue = arrayValue;
}

#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

Ring1_CheckReturn() Ring2_Boolean
Ring2_Value_getBoolean
  (
    Ring2_Value const* value
  )
{ return value->booleanValue; }

Ring1_CheckReturn() bool
Ring2_Value_isBoolean
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Boolean; }

void
Ring2_Value_setBoolean
  (
    Ring2_Value* value,
    Ring2_Boolean booleanValue
  )
{
  value->tag = Ring2_Value_Tag_Boolean;
  value->booleanValue = booleanValue;
}

#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

Ring1_CheckReturn() Ring2_ForeignProcedure*
Ring2_Value_getForeignProcedure
  (
    Ring2_Value const* value
  )
{ return value->foreignProcedureValue; }

Ring1_CheckReturn() bool
Ring2_Value_isForeignProcedure
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_ForeignProcedure; }

void
Ring2_Value_setForeignProcedure
  (
    Ring2_Value* value,
    Ring2_ForeignProcedure* foreignProcedureValue
  )
{
  value->tag = Ring2_Value_Tag_ForeignProcedure;
  value->foreignProcedureValue = foreignProcedureValue;
}

#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

Ring1_CheckReturn() Ring2_Integer
Ring2_Value_getInteger
  (
    Ring2_Value const* value
  )
{ return value->integerValue; }

Ring1_CheckReturn() bool
Ring2_Value_isInteger
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Integer; }

void
Ring2_Value_setInteger
  (
    Ring2_Value* value,
    Ring2_Integer integerValue
  )
{
  value->tag = Ring2_Value_Tag_Integer;
  value->integerValue = integerValue;
}

#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

Ring1_CheckReturn() Machine_Object*
Ring2_Value_getObject
  (
    Ring2_Value const* value
  )
{ return value->objectValue; }

Ring1_CheckReturn() bool
Ring2_Value_isObject
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Object; }

void
Ring2_Value_setObject
  (
    Ring2_Value* value,
    Machine_Object* objectValue
  )
{
  value->tag = Ring2_Value_Tag_Object;
  value->objectValue = objectValue;
}

#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

Ring1_CheckReturn() Ring2_Real32
Ring2_Value_getReal32
  (
    Ring2_Value const* value
  )
{ return value->real32Value; }

Ring1_CheckReturn() bool
Ring2_Value_isReal32
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Real32; }

void
Ring2_Value_setReal32
  (
    Ring2_Value* value,
    Ring2_Real32 real32Value
  )
{
  value->tag = Ring2_Value_Tag_Real32;
  value->real32Value = real32Value;
}

Ring1_CheckReturn() Ring2_Real64
Ring2_Value_getReal64
  (
    Ring2_Value const* value
  )
{ return value->real64Value; }

Ring1_CheckReturn() bool
Ring2_Value_isReal64
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Real64; }

void
Ring2_Value_setReal64
  (
    Ring2_Value* value,
    Ring2_Real64 real64Value
  )
{
  value->tag = Ring2_Value_Tag_Real64;
  value->real64Value = real64Value;
}

#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

Ring1_CheckReturn() Ring2_String*
Ring2_Value_getString
  (
    Ring2_Value const* value
  )
{ return value->stringValue; }

Ring1_CheckReturn() bool
Ring2_Value_isString
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_String; }

void
Ring2_Value_setString
  (
    Ring2_Value* value,
    Ring2_String* stringValue
  )
{
  value->tag = Ring2_Value_Tag_String;
  value->stringValue = stringValue;
}

#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

Ring1_CheckReturn() Ring2_Void
Ring2_Value_getVoid
  (
    Ring2_Value const* value
  )
{ return value->voidValue; }

Ring1_CheckReturn() bool
Ring2_Value_isVoid
  (
    Ring2_Value const* value
  )
{ return value->tag == Ring2_Value_Tag_Void; }

void
Ring2_Value_setVoid
  (
    Ring2_Value* value,
    Ring2_Void voidValue
  )
{
  value->tag = Ring2_Value_Tag_Void;
  value->voidValue = voidValue;
}

#endif

void
Ring2_Value_set
  (
    Ring2_Value* x,
    Ring2_Value const* y
  )
{
  if (x != y) {
    *x = *y;
  }
}

void
Ring2_Value_swap
  (
    Ring2_Value* x,
    Ring2_Value* y
  )
{
  if (x != y) {
    Ring2_Value t = *x;
    *x = *y;
    *y = t;
  }
}


/*VISIT*/ void
Ring2_Value_visit
  (
    Ring2_Gc *gc,
    Ring2_Value* self
  )
{
  switch (self->tag) {
#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
    case Ring2_Value_Tag_Array:
      Ring2_Gc_visit(Ring2_Gc_get(), self->arrayValue);
      break;
#endif
#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
    case Ring2_Value_Tag_Object:
      Ring2_Gc_visit(Ring2_Gc_get(), self->objectValue);
      break;
#endif
#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
    case Ring2_Value_Tag_String:
      Ring2_Gc_visit(Ring2_Gc_get(), self->stringValue);
      break;
#endif
  };
}
