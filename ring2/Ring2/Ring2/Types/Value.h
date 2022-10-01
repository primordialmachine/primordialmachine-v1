// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Value.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_VALUE_H_INCLUDED)
#define RING2_TYPES_VALUE_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/Value.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
  #include "Ring2/Types/Array.h"
  #define Ring2_Value_Tag_Array (1)
#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean
  #include "Ring2/Types/Boolean.h"
  #define Ring2_Value_Tag_Boolean (2)
#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure
  #include "Ring2/Types/ForeignProcedure.h"
  #define Ring2_Value_Tag_ForeignProcedure (3)
#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger
  #include "Ring2/Types/Integer.h"
  #define Ring2_Value_Tag_Integer (4)
#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject
  #include "Ring2/Types/Object.h"
  #define Ring2_Value_Tag_Object (5)
#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal
  #include "Ring2/Types/Real.h"
  #define Ring2_Value_Tag_Real32 (6)
  #define Ring2_Value_Tag_Real64 (7)
#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString
  #include "Ring2/Types/String.h"
  #define Ring2_Value_Tag_String (8)
#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid
  #include "Ring2/Types/Void.h"
  #define Ring2_Value_Tag_Void (9)
#endif

typedef struct Ring2_Value {

  uint8_t tag;

  union {

#if defined(Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray
    
    Ring2_Array* arrayValue;

#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

    Ring2_Boolean booleanValue;

#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure
  
    Ring2_ForeignProcedure* foreignProcedureValue;

#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

    Ring2_Integer integerValue;

#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

    Machine_Object* objectValue;

#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

    Ring2_Real32 real32Value;

    Ring2_Real64 real64Value;

#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

    Ring2_String* stringValue;

#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

    Ring2_Void voidValue;

#endif

  };

} Ring2_Value;

Ring1_CheckReturn() inline uint8_t
Ring2_Value_getTag
  (
    Ring2_Value const* value
  )
{ return value->tag; }

#if defined (Ring2_Configuration_withArray) && 1 == Ring2_Configuration_withArray

/// @brief
/// Read an <code>Array</code> value from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// A pointer to the <code>Array</code> value object. 
Ring1_CheckReturn() Ring2_Array *
Ring2_Value_getArray
  (
    Ring2_Value const* value
  );

/// @brief
/// Get if a value object stores an <code>Array</code> value object.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value stores an <code>Array</code> value object.
/// @a false otherwise.
void
Ring2_Value_setArray
  (
    Ring2_Value* value,
    Ring2_Array *x
  );

/// @brief
/// Get if a value object stores a <code>Array</code> value object.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value object stores a <code>Array</code> value object.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isArray
  (
    Ring2_Value const* value
  );

#endif

#if defined(Ring2_Configuration_withBoolean) && 1 == Ring2_Configuration_withBoolean

#define Ring2_Value_StaticInitializerBoolean(v)                                                  \
  { Ring2_Value_Tag_Boolean, v }

/// @brief
/// Read a <code>Boolean</code> value from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// The <code>Boolean</code> value. 
Ring1_CheckReturn() Ring2_Boolean
Ring2_Value_getBoolean
  (
    Ring2_Value const* self
  );

/// @brief
/// Get if a value object stores a <code>Boolean</code> value.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value stores a <code>Boolean</code> value.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isBoolean
  (
    Ring2_Value const* self
  );

/// @brief
/// Store a <code>Boolean</code> value in a value object.
/// @param value
/// A pointer to the value object.
/// @param booleanValue
/// The <code>Boolean</code> value. 
void
Ring2_Value_setBoolean
  (
    Ring2_Value* self,
    Ring2_Boolean booleanValue
  );

#endif

#if defined(Ring2_Configuration_withForeignProcedure) && 1 == Ring2_Configuration_withForeignProcedure

#define Ring2_Value_StaticInitializerForeignProcedure(v)                                         \
  { Ring2_Value_Tag_ForeignFunction, v }

/// @brief
/// Read a <code>ForeignProcedure</code> value object from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// A pointer to the <code>ForeignProcedure</code> value object. 
Ring1_CheckReturn() Ring2_ForeignProcedure*
Ring2_Value_getForeignProcedure
  (
    Ring2_Value const* self
  );

/// @brief
/// Get if a value stores a <code>ForeignProcedure</code> value object.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value stores a <code>ForeignProcedure</code> value object.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isForeignProcedure
  (
    Ring2_Value const* self
  );

/// @brief
/// Store a <code>ForeignProcedure</code> value object in a value object.
/// @param value
/// A pointer to the value object.
/// @param foreignProcedureValue
/// A pointer to the <code>ForeignProcedure</code> value object. 
void
Ring2_Value_setForeignProcedure
  (
    Ring2_Value* self,
    Ring2_ForeignProcedure* value
  );

#endif

#if defined(Ring2_Configuration_withInteger) && 1 == Ring2_Configuration_withInteger

#define Ring2_Value_StaticInitializerInteger(v)                                                  \
  { Ring2_Value_Tag_Integer, v }

/// @brief
/// Read a <code>Integer</code> value from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// The <code>Integer</code> value. 
Ring1_CheckReturn() Ring2_Integer
Ring2_Value_getInteger
  (
    Ring2_Value const* self
  );

/// @brief
/// Get if a value object stores a <code>Integer</code> value.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value stores a <code>Integer</code> value.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isInteger
  (
    Ring2_Value const* self
  );

/// @brief
/// Store a <code>Integer</code> value in a value object.
/// @param value
/// A pointer to the value object.
/// @param x
/// The <code>Integer</code> value. 
void
Ring2_Value_setInteger
  (
    Ring2_Value* self,
    Ring2_Integer value
  );

#endif

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

#define Machine_Value_StaticInitializerObject(v)                                                   \
  { Ring2_Value_Tag_Object, v }

/// @brief
/// Read a <code>Object</code> value object from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// A pointer to the <code>Object</code> value object. 
Ring1_CheckReturn() Machine_Object*
Ring2_Value_getObject
  (
    Ring2_Value const* self
  );

/// @brief
/// Get if a value object stores a <code>Object</code> value object.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value stores a <code>Object</code> value object.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isObject
  (
    Ring2_Value const* value
  );

/// @brief
/// Store a <code>Object</code> value object in a value object.
/// @param value
/// A pointer to the value object.
/// @param objectValue
/// A pointer to the <code>Object</code> value object. 
void
Ring2_Value_setObject
  (
    Ring2_Value* value,
    Machine_Object* objectValue
  );

#endif

#if defined(Ring2_Configuration_withReal) && 1 == Ring2_Configuration_withReal

#define Ring2_Value_StaticInitializerReal32(v)                                                     \
  { Ring2_Value_Tag_Real32, v }

/// @brief
/// Read a <code>Real32</code> value from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// The <code>Real32</code> value. 
Ring1_CheckReturn() Ring2_Real32
Ring2_Value_getReal32
  (
    Ring2_Value const* value
  );

/// @brief
/// Get if a value object stores a <code>Real32</code> value.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value object stores a <code>Real32</code> value.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isReal32
  (
    Ring2_Value const* value
  );

/// @brief
/// Store a <code>Real32</code> value in a value object.
/// @param value
/// A pointer to the value object.
/// @param real32Value
/// The <code>Real32</code> value. 
void
Ring2_Value_setReal32
  (
    Ring2_Value* value,
    Ring2_Real32 real32Value
  );

#define Ring2_Value_StaticInitializerReal64(v)                                                     \
  { Ring2_Value_Tag_Real32, v }

/// @brief
/// Read a <code>Real64</code> value from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// The <code>Real64</code> value. 
Ring1_CheckReturn() Ring2_Real64
Ring2_Value_getReal64
  (
    Ring2_Value const* value
  );

/// @brief
/// Get if a value object stores a <code>Real64</code> value.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value object stores a <code>Real64</code> value.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isReal64
  (
    Ring2_Value const* value
  );

/// @brief
/// Store a <code>Real64</code> value in a value object.
/// @param value
/// A pointer to the value object.
/// @param real64Value
/// The <code>Real64</code> value. 
void
Ring2_Value_setReal64
  (
    Ring2_Value* value,
    Ring2_Real64 real64Value
  );

#endif

#if defined(Ring2_Configuration_withString) && 1 == Ring2_Configuration_withString

#define Ring2_Value_StaticInitializerString(v)                                                   \
  { Ring2_Value_Tag_String, v }

/// @brief
/// Read a <code>String</code> value object from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// A pointer to the <code>String</code> value object. 
Ring1_CheckReturn() Ring2_String*
Ring2_Value_getString
  (
    Ring2_Value const* value
  );

/// @brief
/// Get if a value object stores a <code>String</code> value object.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value object stores a <code>String</code> value object.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isString
  (
    Ring2_Value const* value
  );

/// @brief
/// Store a <code>String</code> value object in a value object.
/// @param value
/// A pointer to the value object.
/// @param stringValue
/// A pointer to the <code>String</code> value object. 
void
Ring2_Value_setString
  (
    Ring2_Value* value,
    Ring2_String* stringValue
  );

#endif

#if defined(Ring2_Configuration_withVoid) && 1 == Ring2_Configuration_withVoid

#define Ring2_Value_StaticInitializerVoid()                                                      \
  { Ring2_Value_Tag_Void, Ring2_Void_Void }

/// @brief
/// Read a <code>Void</code> value from a value object.
/// @param value
/// A pointer to the value object.
/// @return
/// The <code>Void</code> value. 
Ring1_CheckReturn() Ring2_Void 
Ring2_Value_getVoid
  (
    Ring2_Value const* value
  );

/// @brief
/// Get if a value object stores a <code>Void</code> value.
/// @param value
/// A pointer to the value object.
/// @return
/// @a true if the value object stores a <code>Void</code> value.
/// @a false otherwise.
Ring1_CheckReturn() bool
Ring2_Value_isVoid
  (
    Ring2_Value const* value
  );

/// @brief
/// Store a <code>Void</code> value in a value object.
/// @param value
/// A pointer to the value object.
/// @param x
/// The <code>Void</code> value. 
void
Ring2_Value_setVoid
  (
    Ring2_Value* value,
    Ring2_Void voidValue
  );

#endif

/// @brief Assign a target value object the value of source value object.
/// @param x A pointer to the target value object.
/// @param y A pointer to the The source value object.
void
Ring2_Value_set
  (
    Ring2_Value* x,
    Ring2_Value const* y
  );

/// @brief Swap the values of a two value objects.
/// @param x A pointer to a value object.
/// @param y A pointer to another value object.
void
Ring2_Value_swap
  (
    Ring2_Value* x,
    Ring2_Value* y
  );

/*VISIT*/ void
Ring2_Value_visit
  (
    Ring2_Gc* gc,
    Ring2_Value* value
  );

#endif // RING2_TYPES_VALUE_H_INCLUDED
