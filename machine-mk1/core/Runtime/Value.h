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

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Integer (2)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Object (3)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_ForeignProcedure (4)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Real (5)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_String (6)

/** @brief See Machine_Value::flags for more information. */
#define Machine_ValueFlag_Void (7)



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

INLINE Machine_Boolean Machine_Value_getBoolean(const Machine_Value* self) {
  return self->booleanValue;
}

INLINE bool Machine_Value_isBoolean(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Boolean;
}



INLINE void Machine_Value_setInteger(Machine_Value* self, Machine_Integer value) {
  self->tag = Machine_ValueFlag_Integer;
  self->integerValue = value;
}

INLINE Machine_Integer Machine_Value_getInteger(const Machine_Value* self) {
  return self->integerValue;
}

INLINE bool Machine_Value_isInteger(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Integer;
}



INLINE void Machine_Value_setObject(Machine_Value* self, Machine_Object* value) {
  self->tag = Machine_ValueFlag_Object;
  self->objectValue = value;
}

INLINE Machine_Object* Machine_Value_getObject(const Machine_Value* self) {
  return self->objectValue;
}

INLINE bool Machine_Value_isObject(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Object;
}



INLINE void Machine_Value_setForeignProcedure(Machine_Value* self, Machine_ForeignProcedure* value) {
  self->tag = Machine_ValueFlag_ForeignProcedure;
  self->foreignProcedureValue = value;
}

INLINE Machine_ForeignProcedure* Machine_Value_getForeignProcedure(const Machine_Value* self) {
  return self->foreignProcedureValue;
}

INLINE bool Machine_Value_isForeignProcedure(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_ForeignProcedure;
}



INLINE void Machine_Value_setReal(Machine_Value* self, Machine_Real value) {
  self->tag = Machine_ValueFlag_Real;
  self->realValue = value;
}

INLINE Machine_Real Machine_Value_getReal(const Machine_Value* self) {
  return self->realValue;
}

INLINE bool Machine_Value_isReal(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Real;
}



INLINE void Machine_Value_setString(Machine_Value* self, const Machine_String* value) {
  self->tag = Machine_ValueFlag_String;
  self->stringValue = (Machine_String*)value;
}

INLINE Machine_String* Machine_Value_getString(const Machine_Value* self) {
  return self->stringValue;
}

INLINE bool Machine_Value_isString(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_String;
}



INLINE void Machine_Value_setVoid(Machine_Value* self, Machine_Void value) {
  self->tag = Machine_ValueFlag_Void;
  self->voidValue = value;
}

INLINE Machine_Void Machine_Value_getVoid(const Machine_Value* self) {
  return self->voidValue;
}

INLINE bool Machine_Value_isVoid(const Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Void;
}



#endif // MACHINE_RUNTIME_VALUE_H_INCLUDED
