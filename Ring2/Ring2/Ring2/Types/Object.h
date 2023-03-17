// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Object.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_OBJECT_H_INCLUDED)
#define RING2_TYPES_OBJECT_H_INCLUDED


#if !defined(RING2_PRIVATE) || 1 != RING2_PRIVATE
#error("Do not include `Ring2/Types/Object.h` directly. Include `Ring2/_Include.h` instead.")
#endif
#include "Ring2/_header.h.i"


#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

#include "Ring2/Types/Boolean.h"
#include "Ring2/Types/Integer.h"
#include "Ring2/Gc.h"

Ring1_Module_Declare(Ring2, ObjectModule)

typedef struct Machine_Type Machine_Type;
typedef struct Machine_ClassType Machine_ClassType;

typedef struct Machine_Object_Class Machine_Object_Class;
typedef struct Machine_Object Machine_Object;

struct Machine_Object_Class {
  Ring2_Integer (*getHashValue)(Ring2_Context* context, Machine_Object const* self);
  Ring2_Boolean (*isEqualTo)(Ring2_Context* context, Machine_Object const* self, Ring2_Value const* other);
  Ring2_Boolean (*isNotEqualTo)(Ring2_Context* context, Machine_Object const* self, Ring2_Value const* other);
  Ring2_String* (*toString)(Ring2_Context* context, Machine_Object const* self);
};

struct Machine_Object {
  Machine_ClassType* classType;
};

Ring1_NoDiscardReturn() Machine_Type*
Machine_Object_getType
  (
  );

/// @brief Construct this object.
/// @param self This object.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void
Machine_Object_construct
  (
    Machine_Object* self,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Create an object.
/// @param type A pointer to the class type.
/// @param numberOfArguments The number of elements in the array pointed to by @a arguments.
/// @param arguments A pointer to an array of @a numberOfArguments elements.
/// @error #Ring1_Status_InvalidArgument type is null or does not point to a class type
Ring1_NoDiscardReturn() Machine_Object*
Machine_allocateClassObject
  (
    Machine_Type* type,
    size_t numberOfArguments,
    Ring2_Value const* arguments
  );

/// @brief Set the class type of an object.
/// @param object The object.
/// @param type The class type.
/// @error Ring1_Status_InvalidArgument object is null
/// @error Ring1_Status_InvalidArgument type is null
/// @error Ring1_Status_InvalidArgument type does not refer to a class type
void
Machine_setClassType
  (
    Machine_Object* object,
    Machine_Type* type
  );

/// @brief Get the class type of an object.
/// @param object The object.
/// @return The class type.
Ring1_NoDiscardReturn() Machine_ClassType*
Machine_getClassType
  (
    Machine_Object* object
  );

/// @brief Get if the object is of the specified type.
/// @param self A pointer to the object.
/// @param type A pointer to the type.
/// @return @a true if the object is of the specified type, @a false otherwise.
/// @error #Ring1_Status_InvalidArgument @a self is a null pointer
/// @error #Ring1_Status_InvalidArgument @a type is a null pointer
Ring1_NoDiscardReturn() Ring2_Boolean
Ring2_Object_isInstanceOf
  (
    Machine_Object* self,
    Machine_Type* type
  );

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_VIRTUALIFACECALL_IMPL(TYPE, METHODNAME, RETURN, ...)                               \
  Ring2_assertNotNull(self);                                                                       \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self);                      \
  Ring2_assertNotNull(classType);                                                                  \
  TYPE##_Dispatch* data = Machine_ClassType_getInterfaceDispatch(classType, TYPE##_getType());     \
  Ring2_assertNotNull(data);                                                                       \
  Ring2_assertNotNull(data->METHODNAME);                                                           \
  RETURN data->METHODNAME(__VA_ARGS__);

#define MACHINE_VIRTUALCALL_IMPL(TYPE, METHODNAME, RETURN, ...)                                    \
  Ring2_assertNotNull(self);                                                                       \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self);                      \
  Ring2_assertNotNull(classType);                                                                  \
  TYPE##_Class* data = Machine_ClassType_getDispatch(classType);                                   \
  Ring2_assertNotNull(data);                                                                       \
  Ring2_assertNotNull(data->METHODNAME);                                                           \
  RETURN data->METHODNAME(__VA_ARGS__);

#define MACHINE_VIRTUALCALL_NORETURN_NOARGS(TYPENAME, METHODNAME)                                  \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, , self);

#define MACHINE_VIRTUALCALL_NORETURN_ARGS(TYPENAME, METHODNAME, ...)                               \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, , self, __VA_ARGS__);

#define MACHINE_VIRTUALCALL_RETURN_NOARGS(TYPENAME, METHODNAME)                                    \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, return, self);

#define MACHINE_VIRTUALCALL_RETURN_ARGS(TYPENAME, METHODNAME, ...)                                 \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, return, self, __VA_ARGS__);

#endif // Ring2_Configuration_withObject

#endif // RING2_TYPES_OBJECT_H_INCLUDED
