// Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.

/// @file Ring2/Types/Object.h
/// @copyright Copyright (c) 2019-2022 Michael Heilmann. All rights reserved.
/// @author Michael Heilmann (michaelheilmann@primordialmachine.com)

#if !defined(RING2_TYPES_OBJECT_H_INCLUDED)
#define RING2_TYPES_OBJECT_H_INCLUDED

#if !defined(RING2_INTERNAL) || 1 != RING2_INTERNAL
#error("Do not include `Ring2/Types/Object.h` directly. Include `Ring2/_Include.h` instead.")
#endif

#include "Ring2/Configuration.h"

#if defined(Ring2_Configuration_withObject) && 1 == Ring2_Configuration_withObject

#include "Ring1/Intrinsic/CheckReturn.h"
#include "Ring1/Result.h"
#include "Ring2/Gc.h"
#include "Ring2/Types/Integer.h"
#include "Ring2/Types/Boolean.h"
typedef struct Ring2_String Ring2_String;
typedef struct Machine_ClassType Machine_ClassType;
typedef struct Ring2_Context Ring2_Context;
typedef struct Ring2_Value Ring2_Value;

typedef struct Machine_Object_Class Machine_Object_Class;

typedef struct Machine_Object Machine_Object;

Ring1_CheckReturn() Ring1_Result
Ring2_ObjectModule_startup
  (
  );

void
Ring2_ObjectModule_shutdown
  (
  );

/// @brief Allocate a GC object.
/// @param arguments A pointer to a Machine_Gc_AllocationArguments structure providing the arguments for the allocation.
/// @return A pointer to the object on success, a null pointer on failure.
void *
Ring2_ObjectModule_allocate
  (
    Ring2_Gc *gc,
    size_t size,
    Ring2_Gc_Type const *type
  );

#endif // Ring2_Configuration_withObject

struct Machine_Object_Class {
  Ring2_Integer (*getHashValue)(Ring2_Context *, Machine_Object const *);
  Ring2_Boolean(*isEqualTo)(Ring2_Context *, Machine_Object const *, Ring2_Value const *);
  Ring2_String* (*toString)(Ring2_Context *, Machine_Object const *);
};

struct Machine_Object {
  Machine_ClassType* classType;
};

Machine_ClassType* Machine_Object_getType();

/// @brief Get the hash value of this object.
/// @param self This object.
/// @return The hash value.
Ring2_Integer Machine_Object_getHashValue(Ring2_Context* context, Machine_Object const* self);

/// @brief Get if an object is equal to another object.
/// @param self This object.
/// @param other The other object.
/// @return @a true if this object is equal to another object, @a false otherwise.
Ring2_Boolean Machine_Object_isEqualTo(Ring2_Context* context, Machine_Object const* self, Ring2_Value const* other);

/// @brief Convert an object to a <code>String</code> value.
/// @param self This object.
/// @return The <code>String</code> value.
Ring2_String* Machine_Object_toString(Ring2_Context* context, Machine_Object const* self);

/// @brief Construct this object.
/// @param self This object.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_Object_construct(Machine_Object* self, size_t numberOfArguments, Ring2_Value const* arguments);

/// @brief Create an object.
/// @param type A pointer to the class type.
/// @param numberOfArguments The number of elements in the array pointed to by @a arguments.
/// @param arguments A pointer to an array of @a numberOfArguments elements.
Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, Ring2_Value const* arguments);

/// @brief Set the class type of an object.
/// @param object The object.
/// @param classType The class type.
void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType);

/// @brief Get the class type of an object.
/// @param object The object.
/// @return The class type.
Machine_ClassType* Machine_getClassType(Machine_Object* object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_VIRTUALIFACECALL_IMPL(TYPE, METHODNAME, RETURN, ...)                               \
  Ring2_assertNotNull(self);                                                                       \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self);                      \
  Ring2_assertNotNull(classType);                                                                  \
  TYPE##_Dispatch* data = Machine_ClassType_getInterfaceDispatch(classType, TYPE##_getType());     \
  Ring2_assertNotNull(data);                                                                       \
  RETURN data->METHODNAME(__VA_ARGS__);

#define MACHINE_VIRTUALCALL_IMPL(TYPE, METHODNAME, RETURN, ...)                                    \
  Ring2_assertNotNull(self);                                                                       \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self);                      \
  Ring2_assertNotNull(classType);                                                                  \
  TYPE##_Class* data = Machine_ClassType_getDispatch(classType);                                   \
  Ring2_assertNotNull(data);                                                                       \
  RETURN data->METHODNAME(__VA_ARGS__);

#define MACHINE_VIRTUALCALL_NORETURN_NOARGS(TYPENAME, METHODNAME)                                  \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, , self);

#define MACHINE_VIRTUALCALL_NORETURN_ARGS(TYPENAME, METHODNAME, ...)                               \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, , self, __VA_ARGS__);

#define MACHINE_VIRTUALCALL_RETURN_NOARGS(TYPENAME, METHODNAME)                                    \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, return, self);

#define MACHINE_VIRTUALCALL_RETURN_ARGS(TYPENAME, METHODNAME, ...)                                 \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, return, self, __VA_ARGS__);

#endif // RING2_TYPES_VOID_H_INCLUDED
