/// @file Machine.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_H_INCLUDED)
#define MACHINE_H_INCLUDED

#if !defined(MACHINE_RUNTIME_PRIVATE)
#error("Do not include this file directly, include `_Runtime.h` instead.")
#endif

#include "./Runtime/JumpTargetModule.h"
#include "./Runtime/StackModule.h"
#include "./Runtime/LogModule.h"

#include "./Runtime/PrimitiveTypes.h"
#include "./Runtime/Status.h"
#include "./Runtime/Value.h"

#include "Runtime/GC/GC.h"
#include "Runtime/TS/ClassType.h"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Machine_Value Machine_Value;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief Startup the machine.
 * @warning Undefined if the machine is already initialized.
 * @return #Machine_Status_Success on success, a non-zero Machine_Status value on failure.
 */
Machine_StatusValue Machine_startup();

/**
 * @brief Shutdown the machine.
 * Finalize and deallocate all payloads.
 * @warning Undefined if the machine is already uninitialized.
 */
void Machine_shutdown();

void Machine_update();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief Allocate a payload.
 * @param size The size, in Bytes, of the payload.
 * @param visit A pointer to the Machine_VisitCallback function for the object or a null pointer.
 * @param finalize A pointer to the Machine_FinalizeCallback function for the object or a null pointer.
 * @return A pointer to the object on success, a null pointer on failure.
 */
void* Machine_allocate(size_t size, Machine_VisitCallback *visit, Machine_FinalizeCallback *finalize);

/// @brief Visit an object.
/// @param object A pointer to the object.
/// @undefined Invoked outside of visit callback.
void Machine_visit(void* object);

/// @brief Increment the lock count of an object.
/// @param object A pointer to the object.
void Machine_lock(void* object);

/// @brief Decrement the lock count of an object.
/// @param object A pointer to the object.
void Machine_unlock(void* object);

/// @brief Set if an object is marked as a root object.
/// @undefined Invoked in visit callback or finalize callback.
void Machine_setRoot(void* object, bool isRoot);

/**
 * @brief Get if an object is marked as a root object.
 * @param object the object.
 */
bool Machine_getRoot(void* object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** @brief Tag flag indicating a class type object tag. */
#define Machine_Flag_Class (32)

typedef struct Machine_ClassObjectTag {
  Machine_ClassType* classType;
} Machine_ClassObjectTag;

typedef struct Machine_Object_Class Machine_Object_Class;

typedef struct Machine_Object Machine_Object;

struct Machine_Object_Class {
  size_t(*getHashValue)(Machine_Object const* self);
  Machine_Boolean(*isEqualTo)(Machine_Object const* self, Machine_Object const* other);
  Machine_String* (*toString)(Machine_Object const* self);
};

struct Machine_Object {
  char dummy;
};

Machine_ClassType* Machine_Object_getClassType();

/// @brief Get the hash value of this object.
/// @param self This object.
/// @return The hash value.
size_t Machine_Object_getHashValue(Machine_Object const* self);

/// @brief Get if an object is equal to another object.
/// @param self This object.
/// @param other The other object.
/// @return @a true if this object is equal to another object, @a false otherwise.
Machine_Boolean Machine_Object_isEqualTo(Machine_Object const* self, Machine_Object const* other);

/// @brief Convert an object to a <code>String</code> value.
/// @param self This object.
/// @return The <code>String</code> value.
Machine_String* Machine_Object_toString(Machine_Object const* self);

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
Machine_Object *Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, Machine_Value const* arguments);

/// @brief Set the class type of an object.
/// @param object The object.
/// @param classType The class type.
void Machine_setClassType(Machine_Object* object, Machine_ClassType* classType);

/// @brief Get the class type of an object.
/// @param object The object.
/// @return The class type.
Machine_ClassType* Machine_getClassType(Machine_Object* object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_DECLARE_CLASSTYPE(NAME) \
  typedef struct NAME NAME; \
  typedef struct NAME##_Class NAME##_Class; \
  Machine_ClassType *NAME##_getClassType();

#define MACHINE_DEFINE_CLASSTYPE(THIS_TYPE, PARENT_TYPE, VISIT, CONSTRUCT, DESTRUCT, CLASS_CONSTRUCT) \
\
  static Machine_ClassType *g_##THIS_TYPE##_ClassType = NULL; \
\
  static void THIS_TYPE##_onTypeDestroyed() { \
    g_##THIS_TYPE##_ClassType = NULL; \
  } \
\
  Machine_ClassType* THIS_TYPE##_getClassType() { \
    if (!g_##THIS_TYPE##_ClassType) { \
      Machine_CreateClassTypeArgs args = { \
        .createTypeArgs = { \
          .typeRemoved = (Machine_TypeRemovedCallback*)&THIS_TYPE##_onTypeDestroyed, \
        }, \
        .parent = PARENT_TYPE##_getClassType(), \
        .size = sizeof(THIS_TYPE), \
        .visit = (Machine_ClassObjectVisitCallback*)VISIT, \
        .construct = (Machine_ClassObjectConstructCallback*)CONSTRUCT, \
        .destruct = (Machine_ClassObjectDestructCallback*)DESTRUCT, \
        .classSize = sizeof(THIS_TYPE##_Class), \
        .constructClass = (Machine_ClassConstructCallback*)CLASS_CONSTRUCT, \
      }; \
      g_##THIS_TYPE##_ClassType = \
        Machine_createClassType \
          ( \
            &args \
          ); \
    } \
    return g_##THIS_TYPE##_ClassType; \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_ASSERT(e, s) \
  if (!(e)) \
  { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "assertion `%s` failed\n", #e); \
    Machine_setStatus(s); \
    Machine_jump(); \
  }

#define MACHINE_ASSERT_NOTNULL(e) \
  if (!(e)) \
  { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "assertion `%s != NULL' failed\n", #e); \
    Machine_setStatus(Machine_Status_ArgumentNull); \
    Machine_jump(); \
  }

#define MACHINE_ASSERT_UNREACHABLE() \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "unreachable program point reached\n"); \
    Machine_setStatus(Machine_Status_UnreachableProgramPointReached); \
    Machine_jump();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_VIRTUALCALL_IMPL(TYPE, METHODNAME, RETURN, ...) \
  MACHINE_ASSERT_NOTNULL(self); \
  Machine_ClassType* classType = Machine_getClassType((Machine_Object*)self); \
  MACHINE_ASSERT_NOTNULL(classType); \
  TYPE##_Class* data = classType->data; \
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

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_H_INCLUDED
