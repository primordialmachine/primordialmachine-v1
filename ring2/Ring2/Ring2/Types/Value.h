// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Value.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_VALUE_H_INCLUDED)
#define RING2_TYPES_VALUE_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/Value.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Types.h"

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  #define Ring2_Value_Tag_Array (1)
#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  #define Ring2_Value_Tag_Boolean (2)
#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure
  #define Ring2_Value_Tag_ForeignProcedure (3)
#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  #define Ring2_Value_Tag_Integer (4)
#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  #define Ring2_Value_Tag_Object (5)
#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  #define Ring2_Value_Tag_Real32 (6)
  #define Ring2_Value_Tag_Real64 (7)
#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  #define Ring2_Value_Tag_String (8)
#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  #define Ring2_Value_Tag_Void (9)
#endif

typedef struct Machine_Object Machine_Object;

typedef struct Ring2_Value {

  uint8_t tag;

  union {

    Ring2_Boolean booleanValue;

    Ring2_Integer integerValue;

    Machine_Object* objectValue;

    Ring2_ForeignProcedure* foreignProcedureValue;

    Ring2_Real32 real32Value;

    Ring2_String* stringValue;

    Ring2_Void voidValue;
  };

} Ring2_Value;

Ring1_Inline() void Ring2_Value_setBoolean(Ring2_Value* self, Ring2_Boolean value) {
  self->tag = Ring2_Value_Tag_Boolean;
  self->booleanValue = value;
}

Ring1_Inline() Ring2_Boolean Ring2_Value_getBoolean(Ring2_Value const* self) {
  return self->booleanValue;
}

Ring1_Inline() bool Ring2_Value_isBoolean(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_Boolean;
}

#define Ring2_Value_StaticInitializerBoolean(v)                                                  \
  { Ring2_Value_Tag_Boolean, v }

Ring1_Inline() void Ring2_Value_setInteger(Ring2_Value* self, Ring2_Integer value) {
  self->tag = Ring2_Value_Tag_Integer;
  self->integerValue = value;
}

Ring1_Inline() Ring2_Integer Ring2_Value_getInteger(Ring2_Value const* self) {
  return self->integerValue;
}

Ring1_Inline() bool Ring2_Value_isInteger(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_Integer;
}

#define Ring2_Value_StaticInitializerInteger(v)                                                  \
  { Ring2_Value_Tag_Integer, v }

Ring1_Inline() void Ring2_Value_setObject(Ring2_Value* self, Machine_Object* value) {
  self->tag = Ring2_Value_Tag_Object;
  self->objectValue = value;
}

Ring1_Inline() Machine_Object* Ring2_Value_getObject(Ring2_Value const* self) {
  return self->objectValue;
}

Ring1_Inline() bool Ring2_Value_isObject(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_Object;
}

#define Machine_Value_StaticInitializerObject(v)                                                   \
  { Ring2_Value_Tag_Object, v }

Ring1_Inline() void Ring2_Value_setForeignProcedure(Ring2_Value* self,
                                                    Ring2_ForeignProcedure* value) {
  self->tag = Ring2_Value_Tag_ForeignProcedure;
  self->foreignProcedureValue = value;
}

Ring1_Inline() Ring2_ForeignProcedure* Ring2_Value_getForeignProcedure(Ring2_Value const* self) {
  return self->foreignProcedureValue;
}

Ring1_Inline() bool Ring2_Value_isForeignProcedure(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_ForeignProcedure;
}

#define Ring2_Value_StaticInitializerForeignProcedure(v)                                         \
  { Ring2_Value_Tag_ForeignFunction, v }

Ring1_Inline() void Ring2_Value_setReal32(Ring2_Value* self, Ring2_Real32 value) {
  self->tag = Ring2_Value_Tag_Real32;
  self->real32Value = value;
}

Ring1_Inline() Ring2_Real32 Ring2_Value_getReal32(Ring2_Value const* self) {
  return self->real32Value;
}

Ring1_Inline() bool Ring2_Value_isReal32(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_Real32;
}

#define Ring2_Value_StaticInitializerReal32(v)                                                     \
  { Ring2_Value_Tag_Real32, v }

Ring1_Inline() void Ring2_Value_setString(Ring2_Value* self, Ring2_String const* value) {
  self->tag = Ring2_Value_Tag_String;
  self->stringValue = (Ring2_String*)value;
}

Ring1_Inline() Ring2_String* Ring2_Value_getString(Ring2_Value const* self) {
  return self->stringValue;
}

Ring1_Inline() bool Ring2_Value_isString(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_String;
}

#define Ring2_Value_StaticInitializerString(v)                                                   \
  { Ring2_Value_Tag_String, v }

Ring1_Inline() void Ring2_Value_setVoid(Ring2_Value* self, Ring2_Void value) {
  self->tag = Ring2_Value_Tag_Void;
  self->voidValue = value;
}

Ring1_Inline() Ring2_Void Ring2_Value_getVoid(Ring2_Value const* self) {
  return self->voidValue;
}

Ring1_Inline() bool Ring2_Value_isVoid(Ring2_Value const* self) {
  return self->tag == Ring2_Value_Tag_Void;
}

#define Ring2_Value_StaticInitializerVoid()                                                      \
  { Ring2_Value_Tag_Void, Ring2_Void_Void }

void Ring2_Value_visit(Ring2_Value* self);

Ring2_Boolean Ring2_Value_isEqualTo(Ring2_Value const* x, Ring2_Value const* y);

Ring2_Integer Ring2_Value_getHashValue(Ring2_Value const* x);

void Ring2_Value_swap(Ring2_Value* x, Ring2_Value* y);

#endif // RING2_TYPES_VALUE_H_INCLUDED
