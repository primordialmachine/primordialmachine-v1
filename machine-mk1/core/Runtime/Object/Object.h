#if !defined(MACHINE_RUNTIME_OBJECT_OBJECT_H_INCLUDED)
#define MACHINE_RUNTIME_OBJECT_OBJECT_H_INCLUDED



#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include `Runtime/Object/Object.h` directly, include `_Runtime.h` instead.")
#endif
#include "Runtime/PrimitiveTypes.h"
#include "Ring2/_Include.h"
#include "Runtime/Gc/Gc.h"
#include "Runtime/Object/ClassType.h"


typedef struct Machine_Object_Class Machine_Object_Class;

typedef struct Machine_Object Machine_Object;

struct Machine_Object_Class {
  Ring2_Integer (*getHashValue)(Machine_Object const* self);
  Ring2_Boolean(*isEqualTo)(Machine_Object const* self, Machine_Object const* other);
  Ring2_String* (*toString)(Machine_Object const* self);
};

struct Machine_Object {
  Machine_ClassType* classType;
};

Machine_ClassType* Machine_Object_getType();

/// @brief Get the hash value of this object.
/// @param self This object.
/// @return The hash value.
Ring2_Integer Machine_Object_getHashValue(Machine_Object const* self);

/// @brief Get if an object is equal to another object.
/// @param self This object.
/// @param other The other object.
/// @return @a true if this object is equal to another object, @a false otherwise.
Ring2_Boolean Machine_Object_isEqualTo(Machine_Object const* self, Machine_Object const* other);

/// @brief Convert an object to a <code>String</code> value.
/// @param self This object.
/// @return The <code>String</code> value.
Ring2_String* Machine_Object_toString(Machine_Object const* self);

/// @brief Construct this object.
/// @param self This object.
/// @param numberOfArguments The number of arguments.
/// @param arguments The arguments.
void Machine_Object_construct(Machine_Object* self, size_t numberOfArguments, Machine_Value const* arguments);

/**
 * @brief Create an object.
 * @param type A pointer to the class type.
 * @param numberOfArguments The number of elements in the array pointed to by @a arguments.
 * @param arguments A pointer to an array of @a numberOfArguments elements.
 */
Machine_Object* Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, Machine_Value const* arguments);

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
  MACHINE_ASSERT_NOTNULL(self);                                                                    \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self);                      \
  MACHINE_ASSERT_NOTNULL(classType);                                                               \
  TYPE##_Dispatch* data = Machine_ClassType_getInterfaceDispatch(classType, TYPE##_getType());     \
  MACHINE_ASSERT_NOTNULL(data);                                                                    \
  RETURN data->METHODNAME(__VA_ARGS__);

#define MACHINE_VIRTUALCALL_IMPL(TYPE, METHODNAME, RETURN, ...) \
  MACHINE_ASSERT_NOTNULL(self); \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self); \
  MACHINE_ASSERT_NOTNULL(classType); \
  TYPE##_Class* data = Machine_ClassType_getDispatch(classType); \
  MACHINE_ASSERT_NOTNULL(data); \
  RETURN data->METHODNAME(__VA_ARGS__);

#define MACHINE_VIRTUALCALL_NORETURN_NOARGS(TYPENAME, METHODNAME) \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, , self);

#define MACHINE_VIRTUALCALL_NORETURN_ARGS(TYPENAME, METHODNAME, ...) \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, , self, __VA_ARGS__);

#define MACHINE_VIRTUALCALL_RETURN_NOARGS(TYPENAME, METHODNAME) \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, return, self);

#define MACHINE_VIRTUALCALL_RETURN_ARGS(TYPENAME, METHODNAME, ...) \
  MACHINE_VIRTUALCALL_IMPL(TYPENAME, METHODNAME, return, self, __VA_ARGS__);



#endif // MACHINE_RUNTIME_OBJECT_OBJECT_H_INCLUDED
