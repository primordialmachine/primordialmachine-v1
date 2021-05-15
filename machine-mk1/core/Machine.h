/// @file Machine.h
/// @author Michael Heilmann <michaelheilmann@primordialmachine.com>
/// @copyright Copyright (c) 2021 Michael Heilmann. All rights reserved.
#if !defined(MACHINE_H_INCLUDED)
#define MACHINE_H_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <setjmp.h>

typedef size_t Machine_SizeValue;

typedef int Machine_StatusValue;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define Machine_VoidValue_VOID (0)
typedef int Machine_VoidValue;

#define Machine_BooleanValue_TRUE (true)
#define Machine_BooleanValue_FALSE (false)
typedef bool Machine_BooleanValue;

typedef uint32_t Machine_IntegerValue;

typedef float Machine_RealValue;

typedef struct Machine_String Machine_String;
typedef Machine_String* Machine_StringValue;

typedef struct Machine_Object Machine_Object;
typedef Machine_Object* Machine_ObjectValue;

typedef struct Machine_Value Machine_Value;

typedef Machine_Value(*Machine_ForeignProcedureValue)(size_t numberOfArguments, const Machine_Value* arguments);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * Symbolic constant for a status variable value.
 * Indicates success. Guaranteed to be 0.
 */
#define Machine_Status_Success (0)

/**
 * Symbolic constant for a status variable value.
 * Indicates an allocation failed.
 */
#define Machine_Status_AllocationFailed (1)

/**
 * Symbolic constant for a status variable value.
 * Indicates an invalid argument.
 */
#define Machine_Status_InvalidArgument (2)

/**
 * Symbolic constant for a status variable value.
 * Indicates an invalid operation.
 */
#define Machine_Status_InvalidOperation (3)

/**
 * Symbolic constant for a status variable value.
 * Indicates an index is out of bounds.
 */
#define Machine_Status_IndexOutOfBounds (4)

 /**
  * Symbolic constant for a status variable value.
  * Indicates a capacity is exhausted.
  */
#define Machine_Status_CapacityExhausted (5)

/**
 * Get the value of the status variable.
 * @return The value.
 * @default #Machine_Status_Success
 */
Machine_StatusValue Machine_getStatus();

/**
 * Set the value of the status variable.
 * @param status The value.
 */
void Machine_setStatus(Machine_StatusValue status);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef struct Machine_JumpTarget Machine_JumpTarget;

struct Machine_JumpTarget {
  Machine_JumpTarget* previous;
  jmp_buf environment;
};

/**
 * @brief Push a jump target on the jump target stack.
 * @param jumpTarget A pointer to the jump target.
 */
void Machine_pushJumpTarget(Machine_JumpTarget *jumpTarget);

/**
 * @brief Pop a jump target from the jump target stack.
 */
void Machine_popJumpTarget();

/**
 * @brief Jump to the top of the jump target stack.
 * @warning Undefined if the jump target stack is empty.
 */
__declspec(noreturn) void Machine_jump();

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief Type of a finalize callback function.
 * @param object The object to finalize.
 */
typedef void (Machine_FinalizeCallback)(void* object);

/**
 * @brief Type of a visit callback function.
 * @param object The object to visit.
 */
typedef void (Machine_VisitCallback)(void*);

typedef struct Machine_Tag Machine_Tag;
#define Machine_Flag_White (1)
#define Machine_Flag_Black (2)
#define Machine_Flag_Gray (Machine_Flag_White | Machine_Flag_Black)
#define Machine_Flag_Root (4)

struct Machine_Tag {
  Machine_Tag* next;
  Machine_Tag* gray;
  uint64_t lockCount;
  uint32_t flags;
  size_t size;
  Machine_VisitCallback* visit;
  Machine_FinalizeCallback* finalize;
};

/**
 * @brief Startup the machine.
 * @warning Undefined if the machine is already initialized.
 * @return #Machine_Status_Success on success, a non-zero Machine_Status value on failure.
 */
int Machine_startup();

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

/**
 * @undefined Invoked outside of visit callback.
 */
void Machine_visit(void* object);

/// @brief Increment the lock count of an object.
/// @param object A pointer to the object.
void Machine_lock(void* object);

/// @brief Decrement the lock count of an object.
/// @param object A pointer to the object.
void Machine_unlock(void* object);

/**
 * @brief Set if an object is marked as a root object.
 * @undefined Invoked in visit callback or finalize callback.
 */
void Machine_setRoot(void* object, bool isRoot);

/**
 * @brief Get if an object is marked as a root object.
 * @param object the object.
 */
bool Machine_getRoot(void* object);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/** @brief See Machine_Value::flags for more information. */
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

    Machine_BooleanValue booleanValue;

    Machine_IntegerValue integerValue;

    Machine_ObjectValue objectValue;

    Machine_ForeignProcedureValue foreignProcedureValue;

    Machine_RealValue realValue;

    Machine_StringValue stringValue;

    Machine_VoidValue voidValue;

  };

} Machine_Value;

#define INLINE static inline

INLINE void Machine_Value_setBoolean(Machine_Value* self, Machine_BooleanValue value) {
  self->tag = Machine_ValueFlag_Boolean;
  self->booleanValue = value;
}

INLINE Machine_BooleanValue Machine_Value_getBoolean(Machine_Value* self) {
  return self->booleanValue;
}

INLINE bool Machine_Value_isBoolean(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Boolean;
}


INLINE void Machine_Value_setInteger(Machine_Value* self, Machine_IntegerValue value) {
  self->tag = Machine_ValueFlag_Integer;
  self->integerValue = value;
}

INLINE Machine_IntegerValue Machine_Value_getInteger(Machine_Value* self) {
  return self->integerValue;
}

INLINE bool Machine_Value_isInteger(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Integer;
}


INLINE void Machine_Value_setObject(Machine_Value* self, Machine_ObjectValue value) {
  self->tag = Machine_ValueFlag_Object;
  self->objectValue = value;
}

INLINE Machine_ObjectValue Machine_Value_getObject(Machine_Value* self) {
  return self->objectValue;
}

INLINE bool Machine_Value_isObject(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Object;
}


INLINE void Machine_Value_setForeignProcedure(Machine_Value* self, Machine_ForeignProcedureValue value) {
  self->tag = Machine_ValueFlag_ForeignProcedure;
  self->foreignProcedureValue = value;
}

INLINE Machine_ForeignProcedureValue Machine_Value_getForeignProcedure(Machine_Value* self) {
  return self->foreignProcedureValue;
}

INLINE bool Machine_Value_isForeignProcedure(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_ForeignProcedure;
}


INLINE void Machine_Value_setReal(Machine_Value* self, Machine_RealValue value) {
  self->tag = Machine_ValueFlag_Real;
  self->realValue = value;
}

INLINE Machine_RealValue Machine_Value_getReal(Machine_Value* self) {
  return self->realValue;
}

INLINE bool Machine_Value_isReal(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Real;
}


INLINE void Machine_Value_setString(Machine_Value* self, Machine_StringValue value) {
  self->tag = Machine_ValueFlag_String;
  self->stringValue = value;
}

INLINE Machine_StringValue Machine_Value_getString(Machine_Value* self) {
  return self->stringValue;
}

INLINE bool Machine_Value_isString(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_String;
}


INLINE void Machine_Value_setVoid(Machine_Value* self, Machine_VoidValue value) {
  self->tag = Machine_ValueFlag_Void;
  self->voidValue = value;
}

INLINE Machine_VoidValue Machine_Value_getVoid(Machine_Value* self) {
  return self->voidValue;
}

INLINE bool Machine_Value_isVoid(Machine_Value* self) {
  return self->tag == Machine_ValueFlag_Void;
}

INLINE void Machine_Value_visit(Machine_Value* self) {
  switch (self->tag) {
    case Machine_ValueFlag_Object:
      Machine_visit(self->objectValue);
    break;
    case Machine_ValueFlag_String:
      Machine_visit(self->stringValue);
    break;
  };
}

#undef INLINE

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/// @brief Load a <code>Boolean</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadBoolean(Machine_BooleanValue value);

/// @brief Load an <code>Integer</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadInteger(Machine_IntegerValue value);

/// @brief Load a <code>ForeignProcedure</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadForeignProcedure(Machine_ForeignProcedureValue value);

/// @brief Load a <code>Real</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadReal(Machine_RealValue value);

/// @brief Load a <code>String</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadString(Machine_StringValue value);

/// @brief Load a <code>Void</code> value on the stack.
/// @param value The value.
/// @error Machine_Status_StackOverflow The stack is full.
void Machine_loadVoid(Machine_VoidValue value);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** C level representation of a string. */
typedef struct Machine_String Machine_String;

/**
 * @brief Create a string.
 * @param p, n The Bytes.
 * @return The string on success, null on failure.
 * @deprecated Use Machine_String_create.
 */
Machine_String *Machine_String_create_noraise(const char* p, size_t n);

/**
 * @brief Create a string.
 * @param p, n The Bytes.
 * @return The string.
 */
Machine_String* Machine_String_create(const char* p, size_t n);

/**
 * @brief Get if this string is equal to another string.
 * @param self This string.
 * @param other The other string.
 * @return @a true if this string string is equal to the other string.
 */
bool Machine_String_equalTo(const Machine_String* self, const Machine_String* other);

/**
 * @brief Get the hash value of this string.
 * @param self This string.
 * @return The hash value of this string.
 */
size_t Machine_String_getHashValue(const Machine_String *self);

/**
 * @brief Get the Bytes of this string.
 * @param self A pointer to this string.
 * @return A pointer to the Bytes of this string.
 * @warning The pointer remains valid only as long as the string object is valid.
 * @warning The memory pointed to may not be modified.
 */
const char* Machine_String_getBytes(const Machine_String* self);
size_t Machine_String_getNumberOfBytes(const Machine_String* self);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** C level representation of a class type. */
typedef struct Machine_ClassType Machine_ClassType;

/** @brief Tag flag indicating a class type object tag. */
#define Machine_Flag_Class (32)

typedef struct Machine_ClassObjectTag {
  Machine_ClassType* classType;
  Machine_Tag tag;
} Machine_ClassObjectTag;

/// @brief Invoked when the class type is removed.
typedef void (Machine_ClassTypeRemovedCallback)();

/**
 * @brief Type of an object visit callback.
 * @param self A pointer to the object.
 */
typedef void (Machine_ClassObjectVisitCallback)(void* self);

/**
 * @brief Type of an object visiti callback.
 * @param self A pointer to the object.
 * @param numberOfArguments The number of elements in the array pointed to by @a arguments.
 * @param arguments A pointer to an array of @a numberOfArguments arguments.
 */
typedef void (Machine_ClassObjectConstructCallback)(void* self, size_t numberOfArguments, const Machine_Value* arguments);

/**
 * @brief Type of an object destruct callback.
 * @param self A pointer to the object.
 */
typedef void (Machine_ClassObjectDestructCallback)(void* self);

/**
 * @param visit Pointer to a Machine_ObjectVisitCallback function or a null pointer.
 * @param construct Pointer to a Machine_ObjectConstructCallback function or a null pointer.
 * @param destruct Pointer to a Machine_ObjectDestructCallback function or a null pointer.
 * @retrn A pointer to the classed type.
 */
Machine_ClassType* Machine_createClassType(Machine_ClassType* parent, size_t size, Machine_ClassTypeRemovedCallback* typeRemoved, Machine_ClassObjectVisitCallback* visit, Machine_ClassObjectConstructCallback* construct, Machine_ClassObjectDestructCallback* destruct);

/**
 * @brief Create an object.
 * @param type A pointer to the class type.
 * @param numberOfArguments The number of elements in the array pointed to by @a arguments.
 * @param arguments A pointer to an array of @a numberOfArguments elements.
 */
Machine_Object *Machine_allocateClassObject(Machine_ClassType* type, size_t numberOfArguments, const Machine_Value* arguments);

void Machine_setClassType(void* object, Machine_ClassType* classType);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_DECLARE_CLASSTYPE(NAME) \
  typedef struct NAME NAME; \
  Machine_ClassType *NAME##_getClassType();

#define MACHINE_DEFINE_CLASSTYPE(NAME) \
  static Machine_ClassType *g_##NAME##_ClassType = NULL; \
\
  static void NAME##_onTypeDestroyed() { \
    g_##NAME##_ClassType = NULL; \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MACHINE_ASSERT_NOTNULL(e) \
  if (!(e)) \
  { \
    Machine_log(Machine_LogFlags_ToErrors, __FILE__, __LINE__, "e == NULL\n"); \
  }

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * @brief If defined and @a 1, then logging functionality is compiled into the machine.
 */
#define MACHINE_WITH_LOG (1)

#if defined(MACHINE_WITH_LOG) && 1 == MACHINE_WITH_LOG

#define Machine_LogFlags_ToErrors (2)
#define Machine_LogFlags_ToWarnings (1)
#define Machine_LogFlags_ToInformations (0)

/**
 * @brief Write a log message.
 * @param flags Bitwise or of Machine_LogFlags_* constants.
 */
void Machine_log(int flags, const char* file, int line, const char* format, ...);

#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // MACHINE_H_INCLUDED
