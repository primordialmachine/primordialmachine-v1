/// @file Runtime/Value.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_RUNTIME_VALUE_H_INCLUDED)
#define MACHINE_RUNTIME_VALUE_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif



#include "Runtime/PrimitiveTypes.h"
typedef struct Machine_String Machine_String;
typedef struct Machine_Object Machine_Object;



/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_Boolean (1)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_Function (2)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_Integer (3)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_Object (4)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_ForeignProcedure (5)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_Real (6)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_String (7)

/// @brief See Machine_Value::flags for more information.
#define Machine_ValueFlag_Void (8)



typedef struct Machine_Value {

  uint8_t tag;

  union {

    Machine_Boolean booleanValue;

    Machine_Integer integerValue;

    Machine_Object* objectValue;

    Machine_ForeignProcedure* foreignProcedureValue;

    Machine_Real realValue;

    Machine_String* stringValue;

    Machine_Void voidValue;

  };

} Machine_Value;



INLINE void Machine_Value_setBoolean(Machine_Value* self, Machine_Boolean value) {
  self->tag = Machine_ValueFlag_Boolean;
  self->booleanValue = value;
}

INLINE Machine_Boolean Machine_Value_getBoolean(Machine_Value const* self) {
  return self->booleanValue;
}

INLINE bool Machine_Value_isBoolean(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_Boolean;
}

#define Machine_Value_StaticInitializerBoolean(v) { Machine_ValueFlag_Boolean, v }



INLINE void Machine_Value_setInteger(Machine_Value* self, Machine_Integer value) {
  self->tag = Machine_ValueFlag_Integer;
  self->integerValue = value;
}

INLINE Machine_Integer Machine_Value_getInteger(Machine_Value const* self) {
  return self->integerValue;
}

INLINE bool Machine_Value_isInteger(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_Integer;
}

#define Machine_Value_StaticInitializerInteger(v) { Machine_ValueFlag_Integer, v }



INLINE void Machine_Value_setObject(Machine_Value* self, Machine_Object* value) {
  self->tag = Machine_ValueFlag_Object;
  self->objectValue = value;
}

INLINE Machine_Object* Machine_Value_getObject(Machine_Value const* self) {
  return self->objectValue;
}

INLINE bool Machine_Value_isObject(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_Object;
}

#define Machine_Value_StaticInitializerObject(v) { Machine_ValueFlag_Object, v }



INLINE void Machine_Value_setForeignProcedure(Machine_Value* self, Machine_ForeignProcedure* value) {
  self->tag = Machine_ValueFlag_ForeignProcedure;
  self->foreignProcedureValue = value;
}

INLINE Machine_ForeignProcedure* Machine_Value_getForeignProcedure(Machine_Value const* self) {
  return self->foreignProcedureValue;
}

INLINE bool Machine_Value_isForeignProcedure(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_ForeignProcedure;
}

#define Machine_Value_StaticInitializerForeignProcedure(v) { Machine_ValueFlag_ForeignProcedure, v }



INLINE void Machine_Value_setReal(Machine_Value* self, Machine_Real value) {
  self->tag = Machine_ValueFlag_Real;
  self->realValue = value;
}

INLINE Machine_Real Machine_Value_getReal(Machine_Value const* self) {
  return self->realValue;
}

INLINE bool Machine_Value_isReal(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_Real;
}

#define Machine_Value_StaticInitializerReal(v) { Machine_ValueFlag_Real, v }



INLINE void Machine_Value_setString(Machine_Value* self, Machine_String const* value) {
  self->tag = Machine_ValueFlag_String;
  self->stringValue = (Machine_String*)value;
}

INLINE Machine_String* Machine_Value_getString(Machine_Value const* self) {
  return self->stringValue;
}

INLINE bool Machine_Value_isString(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_String;
}

#define Machine_Value_StaticInitializerString(v) { Machine_ValueFlag_String, v }



INLINE void Machine_Value_setVoid(Machine_Value* self, Machine_Void value) {
  self->tag = Machine_ValueFlag_Void;
  self->voidValue = value;
}

INLINE Machine_Void Machine_Value_getVoid(Machine_Value const* self) {
  return self->voidValue;
}

INLINE bool Machine_Value_isVoid(Machine_Value const* self) {
  return self->tag == Machine_ValueFlag_Void;
}

#define Machine_Value_StaticInitializerVoid() { Machine_ValueFlag_Void, Machine_Void_Void }



void Machine_Value_visit(Machine_Value* self);

Machine_Boolean Machine_Value_isEqualTo(Machine_Value const* x, Machine_Value const* y);

Machine_Integer Machine_Value_getHashValue(Machine_Value const* x);

void Machine_Value_swap(Machine_Value* x, Machine_Value* y);



#endif // MACHINE_RUNTIME_VALUE_H_INCLUDED
