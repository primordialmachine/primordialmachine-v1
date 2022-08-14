/// @file Ring2/Old/Value.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(RING2_OLD_VALUE_H_INCLUDED)
#define RING2_OLD_VALUE_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Old/Value.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/Types/Value.h"
typedef struct Machine_Object Machine_Object;

typedef struct Machine_Value {

  uint8_t tag;

  union {

    Ring2_Boolean booleanValue;

    Ring2_Integer integerValue;

    Machine_Object* objectValue;

    Machine_ForeignProcedure* foreignProcedureValue;

    Ring2_Real32 real32Value;

    Ring2_String* stringValue;

    Ring2_Void voidValue;
  };

} Machine_Value;

Ring1_Inline() void Machine_Value_setBoolean(Machine_Value* self, Ring2_Boolean value) {
  self->tag = Ring2_Value_Tag_Boolean;
  self->booleanValue = value;
}

Ring1_Inline() Ring2_Boolean Machine_Value_getBoolean(Machine_Value const* self) {
  return self->booleanValue;
}

Ring1_Inline() bool Machine_Value_isBoolean(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_Boolean;
}

#define Machine_Value_StaticInitializerBoolean(v)                                                  \
  { Ring2_Value_Tag_Boolean, v }

Ring1_Inline() void Machine_Value_setInteger(Machine_Value* self, Ring2_Integer value) {
  self->tag = Ring2_Value_Tag_Integer;
  self->integerValue = value;
}

Ring1_Inline() Ring2_Integer Machine_Value_getInteger(Machine_Value const* self) {
  return self->integerValue;
}

Ring1_Inline() bool Machine_Value_isInteger(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_Integer;
}

#define Machine_Value_StaticInitializerInteger(v)                                                  \
  { Ring2_Value_Tag_Integer, v }

Ring1_Inline() void Machine_Value_setObject(Machine_Value* self, Machine_Object* value) {
  self->tag = Ring2_Value_Tag_Object;
  self->objectValue = value;
}

Ring1_Inline() Machine_Object* Machine_Value_getObject(Machine_Value const* self) {
  return self->objectValue;
}

Ring1_Inline() bool Machine_Value_isObject(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_Object;
}

#define Machine_Value_StaticInitializerObject(v)                                                   \
  { Ring2_Value_Tag_Object, v }

Ring1_Inline() void Machine_Value_setForeignProcedure(Machine_Value* self,
                                                      Machine_ForeignProcedure* value) {
  self->tag = Ring2_Value_Tag_ForeignFunction;
  self->foreignProcedureValue = value;
}

Ring1_Inline() Machine_ForeignProcedure* Machine_Value_getForeignProcedure(Machine_Value const* self) {
  return self->foreignProcedureValue;
}

Ring1_Inline() bool Machine_Value_isForeignProcedure(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_ForeignFunction;
}

#define Machine_Value_StaticInitializerForeignProcedure(v)                                         \
  { Ring2_Value_Tag_ForeignFunction, v }

Ring1_Inline() void Machine_Value_setReal32(Machine_Value* self, Ring2_Real32 value) {
  self->tag = Ring2_Value_Tag_Real32;
  self->real32Value = value;
}

Ring1_Inline() Ring2_Real32 Machine_Value_getReal32(Machine_Value const* self) {
  return self->real32Value;
}

Ring1_Inline() bool Machine_Value_isReal32(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_Real32;
}

#define Machine_Value_StaticInitializerReal32(v)                                                     \
  { Ring2_Value_Tag_Real32, v }

Ring1_Inline() void Machine_Value_setString(Machine_Value* self, Ring2_String const* value) {
  self->tag = Ring2_Value_Tag_String;
  self->stringValue = (Ring2_String*)value;
}

Ring1_Inline() Ring2_String* Machine_Value_getString(Machine_Value const* self) {
  return self->stringValue;
}

Ring1_Inline() bool Machine_Value_isString(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_String;
}

#define Machine_Value_StaticInitializerString(v)                                                   \
  { Ring2_Value_Tag_String, v }

Ring1_Inline() void Machine_Value_setVoid(Machine_Value* self, Ring2_Void value) {
  self->tag = Ring2_Value_Tag_Void;
  self->voidValue = value;
}

Ring1_Inline() Ring2_Void Machine_Value_getVoid(Machine_Value const* self) {
  return self->voidValue;
}

Ring1_Inline() bool Machine_Value_isVoid(Machine_Value const* self) {
  return self->tag == Ring2_Value_Tag_Void;
}

#define Machine_Value_StaticInitializerVoid()                                                      \
  { Ring2_Value_Tag_Void, Ring2_Void_Void }

void Machine_Value_visit(Machine_Value* self);

Ring2_Boolean Machine_Value_isEqualTo(Machine_Value const* x, Machine_Value const* y);

Ring2_Integer Machine_Value_getHashValue(Machine_Value const* x);

void Machine_Value_swap(Machine_Value* x, Machine_Value* y);

#endif // RING2_OLD_VALUE_H_INCLUDED
